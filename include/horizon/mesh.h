#pragma once

#include "horizon/triangle.h"
#include "horizon/object_group.h"
#include "horizon/material.h"
#include "horizon/vector3.h"

#include <string>
#include <vector>
#include <memory>

class Mesh : public ObjectGroup {
public:
    Mesh() = default;

    bool load_obj(const std::string& filename, std::shared_ptr<Material> mat);

private:
    std::vector<point3> vertices;
    std::vector<vector3> normals;
};
