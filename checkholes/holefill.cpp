//
// Created by mk on 02.04.19.
//
#include "holefill.h"
#include<spdlog/spdlog.h>
#include<exception>
namespace {
    auto console = spdlog::get("console");
}
// A hole is identified by being a boundary
std::vector<Holefill::Hole> Holefill::get_holes() {
    std::vector<Holefill::Hole> result;
    console->info("faces: {0}; vertices: {1}", m_mesh.n_faces(), m_mesh.n_vertices());
    OpenMesh::EPropHandleT< bool > boundary;
    mesh::mesh_type a_mesh = m_mesh;
    a_mesh.add_property(boundary, "boundary");
    // mark all edges as not part of a boundary
    std::for_each(a_mesh.edges_begin(), a_mesh.edges_end(),
            [&a_mesh, boundary](const mesh::mesh_type::EdgeHandle& edge){
        a_mesh.property(boundary, edge) = false;
    });

    for(auto a_edge : a_mesh.edges()) {
        if(a_mesh.property(boundary, a_edge))
            continue;
        if(!a_mesh.is_boundary(a_edge))
            continue;
        mesh::mesh_type::HalfedgeHandle heh = a_mesh.halfedge_handle(a_edge,0);
        if(!a_mesh.is_boundary(heh))
            heh = a_mesh.opposite_halfedge_handle(heh);
        mesh::mesh_type::HalfedgeHandle current_heh = heh;
        Hole current_hole;
        do {
            mesh::mesh_type::EdgeHandle eh = a_mesh.edge_handle(current_heh);
            current_hole.push_back(eh);
            a_mesh.property(boundary,m_mesh.edge_handle(current_heh)) = true;
            int cnt = 0;
            mesh::mesh_type::VertexHandle vh = m_mesh.to_vertex_handle(current_heh);
            for (mesh::mesh_type::VertexOHalfedgeIter vhe_it(m_mesh, vh); vhe_it.is_valid(); ++vhe_it) {
                if(m_mesh.is_boundary(*vhe_it))
                    cnt++;
            }

            if(cnt > 1) {
                mesh::mesh_type::HalfedgeHandle opposit = m_mesh.opposite_halfedge_handle(current_heh);
                mesh::mesh_type::VertexOHalfedgeIter vohe_it(m_mesh, opposit);
                current_heh = *(vohe_it);
            } else
                current_heh = m_mesh.next_halfedge_handle(current_heh);

        } while(current_heh != heh);
        result.push_back(current_hole);
    }
    a_mesh.remove_property(boundary);
    std::sort(result.begin(), result.end(), [](const Hole& hole_one, const Hole& hole_two) { return hole_one.size() > hole_two.size();});
    return result;
}

void Holefill::fill(const std::vector<Holefill::Hole> &holes) {
    std::for_each(holes.begin(),holes.end(),[&](const Holefill::Hole& hole) {fill(hole);});
}

void Holefill::fill(const Holefill::Hole &hole) const {
    throw std::runtime_error("not implemented yet");
}

std::string Holefill::print_hole(const Holefill::Hole &a_hole) {
    std::string hole_string{};
    for(auto e : a_hole) {
        auto vh = m_mesh.from_vertex_handle(m_mesh.halfedge_handle(e,0));
        auto point = m_mesh.point(vh);
        hole_string += fmt::format("{0} {1} {2}\n",point[0], point[1], point[2]);
    }
    return hole_string;
}
