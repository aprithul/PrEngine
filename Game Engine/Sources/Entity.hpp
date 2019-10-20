#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "Transform.hpp"
#include "Utils.hpp"

namespace Pringine
{
    typedef enum
    {
        ENTITY_TYPE_SPRITE = 0,
        ENTITY_TYPE_CAMERA = 1,
        ENTITY_TYPE_PLAYER = 2,
        ENTITY_TYPE_COUNT
    }EntityType;


    class Entity
    {
        public:
            Entity(EntityType type);
            Entity(std::string name, EntityType type);
            virtual ~Entity();

            const EntityType type;
            int id;
            std::string name;
            bool is_sleeping;
            Rect bounding_box;
            
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void end();
    };
}


#endif