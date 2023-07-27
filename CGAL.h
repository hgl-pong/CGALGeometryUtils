#pragma once
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

typedef CGAL::Simple_cartesian<float> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Nef_polyhedron_3 <Kernel> Nef_Polyhedron;
typedef Kernel::Point_3 Point;

typedef CGAL::Surface_mesh<Point> SurfaceMesh;
typedef SurfaceMesh::vertex_index vertec_index;
typedef Polyhedron::HalfedgeDS HalfedgeDS;