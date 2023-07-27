#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Nef_Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>
#include <CGAL/Surface_mesh.h>

#include <CGAL/Polyhedron_traits_with_normals_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_tree.h>

#include <fstream>
#include <iostream>

typedef CGAL::Simple_cartesian<float> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Nef_polyhedron_3 <Kernel> Nef_Polyhedron;
typedef Kernel::Point_3 Point;

typedef CGAL::Surface_mesh<Point> SurfaceMesh;
typedef SurfaceMesh::vertex_index vertec_index;
typedef Polyhedron::HalfedgeDS HalfedgeDS;


enum Boolean_op { INTERSECTION, UNION, DIFFERENCE };
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
            iss >> x>>y>>z;
            vertices.push_back(Point(x, y, z));
        }
        else if (type == "f") {
            uint32_t v1,v2,v3;
            iss >> v1>>v2>>v3;
            indices.push_back(v1-1);
            indices.push_back(v2-1);
            indices.push_back(v3-1);
            // 由于OBJ索引从1开始，需要将索引减1以适应C++数组索引从0开始的约定
            mesh.make_triangle(vertices.at(v1-1), vertices.at(v2-1), vertices.at(v3-1));
        }
    }

    input.close();
};

void read_obj(std::string path, SurfaceMesh& mesh,const float scale=1.0f)
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
            vertices.push_back(Point(x*scale, y * scale, z * scale));
            mesh.add_vertex(Point(x * scale, y * scale, z * scale));
        }
        else if (type == "f") {
            uint32_t v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            indices.push_back(v1 - 1);
            indices.push_back(v2 - 1);
            indices.push_back(v3 - 1);
            // 由于OBJ索引从1开始，需要将索引减1以适应C++数组索引从0开始的约定
            mesh.add_face(vertec_index(v1-1), vertec_index(v2-1), vertec_index(v3-1));
        }
    }
    if (mesh.is_empty())
        printf("read obj failed!\n");
    input.close();
};

#include <CGAL/Surface_mesh.h>
#include <fstream>

void write_obj(const std::string& filename,SurfaceMesh& mesh) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file " << filename << " for writing." << std::endl;
        return;
    }

    // Write vertices
    out << "# Vertices" << std::endl;
    for (auto v : mesh.vertices()) {
        out << "v " << mesh.point(v).x() << " " << mesh.point(v).y() << " " << mesh.point(v).z() << std::endl;
    }

    // Write faces
    out << "# Faces" << std::endl;
    for (auto f : mesh.faces()) {
        out << "f ";
        for (auto v : mesh.vertices_around_face(mesh.halfedge(f))) {
            out << v.idx() + 1 << " ";
        }
        out << std::endl;
    }
}

int main() {

    std::string path1 = "spot.obj";
    std::string path2 = "bullet.obj";
    SurfaceMesh mesh1, mesh2;

    read_obj(path1, mesh1);
    read_obj(path2, mesh2);
    clock_t start, end; 
    SurfaceMesh output_mesh;
    //start = clock();
    //CGAL::Polygon_mesh_processing::corefine_and_compute_union(mesh1, mesh2, output_mesh);
    //end = clock();
    //printf("union cost:%d ms!\n", end - start);
    //if (output_mesh.is_empty())
    //    printf("output null!\n");
    //write_obj("union.obj",output_mesh);

    output_mesh.clear();
    start = clock();
    CGAL::Polygon_mesh_processing::corefine_and_compute_intersection(mesh1, mesh2, output_mesh);
    end = clock();
    printf("intersect cost:%d ms!\n",end-start);
    if (output_mesh.is_empty())
        printf("output null!\n");
    write_obj("intersect.obj", output_mesh);


    //output_mesh.clear();
    //     start = clock();
    //CGAL::Polygon_mesh_processing::corefine_and_compute_difference(mesh2, mesh1, output_mesh);
    //     end = clock();
    //printf("difference cost:%d ms!\n", end - start);
    //if (output_mesh.is_empty())
    //    printf("output null!\n");
    //write_obj("difference.obj", output_mesh);
    return 0;
}