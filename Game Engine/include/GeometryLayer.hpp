#ifndef GEOMETRY_LAYER_HPP
#define GEOMETRY_LAYER_HPP

#include "GlAssert.hpp"
#include "RenderLayer.hpp"
#include "Graphics3D.hpp"
#include "EntityManagementSystemModule.hpp"
#include "DirectionalLight.hpp"
#include "Camera3D.hpp"
#include "Matrix4x4f.hpp"
#include <vector>

namespace Pringine
{
    class GeometryLayer : public RenderLayer
    {
        public:
            GeometryLayer(long camera_handle);
            ~GeometryLayer();

            void start() override;
            void update() override;
            void end() override;

            std::vector<Graphics3D*> graphics3d_list;
            long camera_handle;
    };
} // namespace Pringin

#endif