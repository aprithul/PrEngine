#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Entity.hpp"
#include "Vector3.hpp"

namespace Pringine
{
    class DirectionalLight : public Entity
    {
        public:
            DirectionalLight();
            ~DirectionalLight() override;
            Vector3<float> direction;

            void start() override;
            void update() override;
            void end() override;
    };
}


#endif