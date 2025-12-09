#include "horizon/bvh.h"

#include <algorithm>
#include <stdexcept>

BVHNode::BVHNode(std::vector<shared_ptr<RayObject>>& objects, size_t start, size_t end) {
    bbox = aabb::empty;
    for (size_t i = start; i < end; ++i)
        bbox = aabb(bbox, objects[i]->bounding_box());

    int axis = bbox.longest_axis();

    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        left = objects[start];
        right = objects[start + 1];
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        size_t mid = start + object_span / 2;
        left = std::make_shared<BVHNode>(objects, start, mid);
        right = std::make_shared<BVHNode>(objects, mid, end);
    }
}

BVHNode::BVHNode(const std::vector<shared_ptr<RayObject>>& objects) {
    if (objects.empty())
        throw std::runtime_error("Cannot build BVH from empty object list.");

    std::vector<shared_ptr<RayObject>> objs = objects;
    *this = BVHNode(objs, 0, objs.size());
}

bool BVHNode::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    if (!bbox.hit(r, ray_t)) return false;

    bool hit_left = left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

    return hit_left || hit_right;
}

aabb BVHNode::bounding_box() const {
    return bbox;
}

bool BVHNode::box_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b, int axis) {
    auto a_interval = a->bounding_box().axis_interval(axis);
    auto b_interval = b->bounding_box().axis_interval(axis);
    return a_interval.min < b_interval.min;
}

bool BVHNode::box_x_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b) {
    return box_compare(a, b, 0);
}

bool BVHNode::box_y_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b) {
    return box_compare(a, b, 1);
}

bool BVHNode::box_z_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b) {
    return box_compare(a, b, 2);
}
