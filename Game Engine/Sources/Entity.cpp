#include "Entity.hpp"

namespace Pringine
{
    
    Entity::Entity()
    {
        id = -1;
    }

    Entity::Entity(std::string name)
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