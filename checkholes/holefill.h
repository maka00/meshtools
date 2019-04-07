//
// Created by mk on 02.04.19.
//
// A simple hole analysing tool. Also able to close holes (in a trivial way, not taking curvature in account)
#pragma once

#include<meshtype.h>
class Holefill {
public:
    // The definition of a hole as a set of half-edges on the boundary
    using Hole = std::vector<mesh::mesh_type::EdgeHandle>;

    // sets the mesh into the class
    explicit Holefill(const mesh::mesh_type& a_mesh) : m_mesh(a_mesh) {};

    // analyses the mesh and returns all holes. sorted by size (bigger holes are first - the bottom is the first element)
    std::vector<Hole> get_holes();

    // fill a list of holes
    void fill(const std::vector<Hole>& holes);

    // fill one single hole
    // a very simple holefiller by inserting one vertice in the middle of the hole and stitch it together
    void fill(const Hole& hole) const;

    // returns the processed mesh
    mesh::mesh_type get_mesh() { return std::move(m_mesh); };

    // prints a hole to the std::cout
    std::string print_hole(const Hole& a_hole);
private:
    mesh::mesh_type m_mesh;
};



