#include "../include/VertexFormat.hpp"


namespace Andromeda::Rendering
{
    size_t ComponentTypeSizeBytes(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Float32: return 4;
        case ComponentType::Int32:   return 4;
        case ComponentType::UInt32:  return 4;
        case ComponentType::UInt16:  return 2;
        case ComponentType::UInt8:   return 1;
        default:                     return 0;
        }
    }

    bool IsIntegerComponentType(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Int32:
        case ComponentType::UInt32:
        case ComponentType::UInt16:
        case ComponentType::UInt8:
            return true;

        case ComponentType::Float32:
        default:
            return false;
        }
    }
}