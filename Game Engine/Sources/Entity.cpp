#include "Entity.hpp"

namespace Pringine
{
    
    Entity::Entity(EntityType type):type(type)
    {
        id = -1;
    }

    Entity::Entity(std::string name, EntityType type):type(type)
    {
        id = -1;        
        this->name = name;
    }
    
    Entity::~Entity()
    {

    }

    void Entity::awake()
    {

    }

    void Entity::start()
    {
        
    }

    void Entity::update()
    {
        
    }

    void Entity::end()
    {
        
    }
}