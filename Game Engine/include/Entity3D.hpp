#ifndef Entity3D_HPP
#define Entity3D_HPP

#include <string>
#include "Transform3D.hpp"
#include "Utils.hpp"
#include "Component.hpp"

namespace Pringine
{
    typedef enum
    {
        Entity3D_TYPE_CAMERA_3D,
        Entity3D_TYPE_CUBE,
        Entity3D_TYPE_COUNT
    }EntityType3D;



    class Entity3D
    {
        public:
            Entity3D(EntityType3D type);
            Entity3D(std::string name, EntityType3D type);
            virtual ~Entity3D();

            const EntityType3D type;
            long id;
            std::string name;
            bool is_sleeping;
            Rect bounding_box;
            bool has_component[COMP_COUNT_MAX];
            Transform3D transform;
            Component* components[COMP_COUNT_MAX];

            void add_componenet(Component* comp);
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void end();
    };
}


#endif