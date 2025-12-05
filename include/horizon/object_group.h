#pragma once

#include "horizon/ray_object.h"
#include <vector>
#include <memory>

using std::shared_ptr;

class ObjectGroup : public RayObject {
public:
    ObjectGroup() {}
    ObjectGroup(shared_ptr<RayObject> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<RayObject> object);

    bool hit(const ray& r, Interval ray_t, HitRecord& rec) const override;

private:
    std::vector<shared_ptr<RayObject>> objects;
};
