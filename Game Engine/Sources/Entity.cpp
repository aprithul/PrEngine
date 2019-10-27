#include "Entity.hpp"

namespace Pringine
{
    
    void initialize(bool* has_comp)
    {
        for(int i=0; i<COMP_COUNT_MAX; i++)
            has_comp[i] = false;
    }
    ///////////////////////////////


    Entity::Entity(EntityType type):type(type)
    {
        id = -1;
        initialize(has_component);
    }

    Entity::Entity(std::string name, EntityType type):type(type)
    {
        id = -1;        
        this->name = name;
        initialize(has_component);
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

    void Entity::add_componenet(Component* component)
    {
        components[component->type] = component;
        has_component[component->type]=true;
    }

    
}