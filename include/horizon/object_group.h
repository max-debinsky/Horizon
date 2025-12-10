#pragma once

#include "horizon/ray_object.h"
#include "horizon/aabb.h"

#include <vector>
#include <memory>
#include <algorithm>

using std::shared_ptr;

class ObjectGroup : public RayObject {
public:
    ObjectGroup() {}
    ObjectGroup(shared_ptr<RayObject> object) { add(object); }

    void clear() { 
        objects.clear(); 
        bbox = aabb();
    }

    void add(shared_ptr<RayObject> object);

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override { return bbox; }

    std::vector<shared_ptr<RayObject>>& get_objects() { return objects; }
    const std::vector<shared_ptr<RayObject>>& get_objects() const { return objects; }

    friend class Mesh;

private:
    std::vector<shared_ptr<RayObject>> objects;
    aabb bbox;
};
