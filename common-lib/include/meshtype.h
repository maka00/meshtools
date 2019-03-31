#pragma once

#include<OpenMesh/Core/Mesh/Traits.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

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

}
