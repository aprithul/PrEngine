#ifndef ENTITY_3D_HPP
#define ENTITY_3D_HPP

#include "Entity.hpp"
#include "Renderer3D.hpp"
#include "Transform3D.hpp"

namespace Pringine
{
    class Entity3D : public Entity
    {
        public:
            Transform3D transform;
            Graphics3D* graphics;

            Entity3D(EntityType type, Graphics3D* graphics);
            ~Entity3D();


    };
}

#endif