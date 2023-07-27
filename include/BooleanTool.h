#ifndef BOOLEAN_TOOL_H
#define BOOLEAN_TOOL_H
#include "GeometryTypes.h"

namespace Geometry
{
    MeshData ComputeIntersect(const MeshData& meshA,const MeshData&meshB,const BooleanComputeMode& mode);

    class BatchBooleanTool
    {
    public:
        BatchBooleanTool(const MeshData &meshData);
        void SetBaseMesh(const MeshData &meshData);
        std::vector<MeshData> BatchCompute(const std::vector<MeshData> &meshes,
                                           const std::vector<BooleanComputeMode> &modes) const;

    private:
        MeshData mMeshData;
    };
};
#endif // BOOLEAN_TOOL_H