#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Transform.hpp"
#include "Graphics.hpp"

namespace Pringine
{
    class Entity
    {
        public:
            Entity();
            ~Entity();
            Transform transform;
            Graphics graphics;
    };
}


#endif