#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "Transform.hpp"
#include "Utils.hpp"
#include "Component.hpp"

namespace Pringine
{
    typedef enum
    {
        ENTITY_TYPE_SPRITE = 0,
        ENTITY_TYPE_CAMERA,
        ENTITY_TYPE_LIGHT,
        ENTITY_TYPE_PLAYER,
        ENTITY_TYPE_CUBE,
        ENTITY_TYPE_COUNT
    }EntityType;



    class Entity
    {
        public:
            Entity(EntityType type);
            Entity(std::string name, EntityType type);
            virtual ~Entity();

            const EntityType type;
            long id;
            std::string name;
            bool is_sleeping;
            Rect bounding_box;
            bool has_component[COMP_COUNT_MAX];
            Component* components[COMP_COUNT_MAX];

            void add_componenet(Component* comp);
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void end();
    };
}


#endif