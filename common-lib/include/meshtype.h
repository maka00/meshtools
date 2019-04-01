#pragma once

#include<OpenMesh/Core/Mesh/Traits.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include<OpenMesh/Core/IO/MeshIO.hh>

namespace mesh {
    struct MeshTraits : public OpenMesh::DefaultTraits {
        VertexTraits
        {
        public:
            unsigned short tag;
        };

        VertexAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Status | OpenMesh::Attributes::Color |
                         OpenMesh::Attributes::TexCoord2D);
        FaceAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Status);
        EdgeAttributes(OpenMesh::Attributes::Status);

    };

    typedef OpenMesh::TriMesh_ArrayKernelT<MeshTraits> mesh_type;

    // stores a mesh to a file.
    // the format depends on the file extension
    // \param a_mesh[in] The mesh to store
    // \param path[in] The filename of the mesh
    // \param write_option[in] store the mesh in binary format (default), also possible to store with color, normals etc.
    // \return true if everything went ok
    inline bool store_mesh(const mesh_type& a_mesh, const std::string& path, const OpenMesh::IO::Options& write_option = OpenMesh::IO::Options::Default + OpenMesh::IO::Options::Binary ) {
        return OpenMesh::IO::write_mesh(a_mesh, path, write_option);
    }

    // loads a mesh from a file.
    // \param path[in] The filename of the mesh
    // \return The mesh from the file
    inline mesh_type load_mesh(const std::string& path) {
        mesh::mesh_type a_mesh;
        OpenMesh::IO::Options ropt = OpenMesh::IO::Options::Default;
        if (!OpenMesh::IO::read_mesh(a_mesh, path,ropt)) {
            return mesh::mesh_type();
        }
        return a_mesh;
    }
}
