#ifndef GEOMETRY_TYPE_H
#define GEOMETRY_TYPE_H
#include "Macro.h"
#include <cstdint>
#include <vector>
namespace Geometry
{
    struct MeshData
    {
        float *vertices;
        uint32_t verticesCount;
        uint32_t *indices;
        uint32_t indicesCount;
    };

    enum class BooleanComputeMode
    {
        INTERSECT,
        DIFFERENCE,
        UNION,
    };
};
#endif // GEOMETRY_TYPE_H