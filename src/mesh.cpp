#include "horizon/mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Mesh::load_obj(const std::string& filename, std::shared_ptr<Material> mat) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open OBJ file " << filename << std::endl;
        return false;
    }

    vertices.clear();
    normals.clear();
    this->objects.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            double x, y, z;
            ss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        } else if (prefix == "vn") {
            double x, y, z;
            ss >> x >> y >> z;
            normals.emplace_back(unit_vector(vector3(x, y, z)));
        } else if (prefix == "f") {
            std::vector<int> v_idx, n_idx;
            std::string token;
            while (ss >> token) {
                std::replace(token.begin(), token.end(), '/', ' ');
                std::istringstream ts(token);
                int vi = -1, ti = -1, ni = -1;
                ts >> vi;
                if (ts.peek() == ' ') ts.ignore();
                if (ts.peek() != EOF) ts >> ti;
                if (ts.peek() == ' ') ts.ignore();
                if (ts.peek() != EOF) ts >> ni;
                v_idx.push_back(vi - 1); // OBJ index starts at 1
                n_idx.push_back(ni - 1);
            }

            // Triangulate polygon (supports quads)
            for (size_t i = 1; i + 1 < v_idx.size(); ++i) {
                vector3* n0 = n_idx[0] >= 0 ? &normals[n_idx[0]] : nullptr;
                vector3* n1 = n_idx[i] >= 0 ? &normals[n_idx[i]] : nullptr;
                vector3* n2 = n_idx[i+1] >= 0 ? &normals[n_idx[i+1]] : nullptr;

                this->add(std::make_shared<Triangle>(
                    vertices[v_idx[0]],
                    vertices[v_idx[i]],
                    vertices[v_idx[i+1]],
                    mat,
                    n0, n1, n2
                ));
            }
        }
    }

    std::cout << "Loaded OBJ: " << filename << " with " << this->objects.size() << " triangles.\n";
    return true;
}
