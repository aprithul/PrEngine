#ifndef SHADOW_PASS_LAYER_HPP
#define SHADOW_PASS_LAYER_HPP

#include "GlAssert.hpp"
#include "RenderLayer.hpp"
#include "DirectionalLight.hpp"
#include "GeometryLayer.hpp"
#include "Graphics.hpp"

namespace PrEngine
{
    class ShadowPassLayer : public RenderLayer
    {
        public:
            ShadowPassLayer();
            ~ShadowPassLayer() override;

            void start() override;
            void update() override;
            void end() override;

            long camera_handle;


    };
} // namespace Pringin

#endif