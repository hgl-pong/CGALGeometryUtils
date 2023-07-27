#include "CGAL.h"
#include "IO.h"
#include <fstream>
#include <iostream>


enum Boolean_op { INTERSECTION, UNION, DIFFERENCE };

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