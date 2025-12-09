#include "horizon/object_group.h"

void ObjectGroup::add(shared_ptr<RayObject> object) {
    objects.push_back(object);

    if (objects.size() == 1) {
        bbox = object->bounding_box();
    } else {
        bbox = aabb(bbox, object->bounding_box());
    }
}

bool ObjectGroup::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const auto& object : objects) {
        if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
