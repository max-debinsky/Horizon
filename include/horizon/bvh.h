#pragma once

#include "horizon/ray_object.h"
#include "horizon/aabb.h"
#include <vector>
#include <memory>
#include <algorithm>

using std::shared_ptr;

class BVHNode : public RayObject {
public:
    BVHNode(std::vector<shared_ptr<RayObject>>& objects, size_t start, size_t end);
    BVHNode(const std::vector<shared_ptr<RayObject>>& objects); // convenience

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;
    aabb bounding_box() const override;

private:
    shared_ptr<RayObject> left;
    shared_ptr<RayObject> right;
    aabb bbox;

    static bool box_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b, int axis);
    static bool box_x_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b);
    static bool box_y_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b);
    static bool box_z_compare(const shared_ptr<RayObject>& a, const shared_ptr<RayObject>& b);
};
