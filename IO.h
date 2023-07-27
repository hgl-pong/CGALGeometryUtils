#pragma once
#include "CGAL.h"
void read_obj(std::string path, Polyhedron& mesh)
{
    // Read the OBJ file as a polygon soup
    std::vector<Point> vertices;
    std::vector<uint32_t> indices;
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Point point;
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(Point(x, y, z));
        }
        else if (type == "f") {
            uint32_t v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            indices.push_back(v1 - 1);
            indices.push_back(v2 - 1);
            indices.push_back(v3 - 1);
            // 由于OBJ索引从1开始，需要将索引减1以适应C++数组索引从0开始的约定
            mesh.make_triangle(vertices.at(v1 - 1), vertices.at(v2 - 1), vertices.at(v3 - 1));
        }
    }

    input.close();
};

void read_obj(std::string path, SurfaceMesh& mesh, const float scale = 1.0f)
{
    // Read the OBJ file as a polygon soup
    std::vector<Point> vertices;
    std::vector<uint32_t> indices;
    std::ifstream input(path);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Point point;
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(Point(x * scale, y * scale, z * scale));
            mesh.add_vertex(Point(x * scale, y * scale, z * scale));
        }
        else if (type == "f") {
            uint32_t v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            indices.push_back(v1 - 1);
            indices.push_back(v2 - 1);
            indices.push_back(v3 - 1);
            // 由于OBJ索引从1开始，需要将索引减1以适应C++数组索引从0开始的约定
            mesh.add_face(vertec_index(v1 - 1), vertec_index(v2 - 1), vertec_index(v3 - 1));
        }
    }
    if (mesh.is_empty())
        printf("read obj failed!\n");
    input.close();
};