#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "Transform.hpp"
namespace Pringine
{
    class Entity
    {
        public:
            Entity();
            Entity(std::string name);
            virtual ~Entity();

            int id;
            std::string name;
            bool is_sleeping;
            
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void end();
    };
}


#endif