#include "Entity3D.hpp"

namespace Pringine
{
    
    void initialize(bool* has_comp)
    {
        for(int i=0; i<COMP_COUNT_MAX; i++)
            has_comp[i] = false;
    }
    ///////////////////////////////


    Entity3D::Entity3D(EntityType3D type):type(type)
    {
        id = -1;
        initialize(has_component);
        add_componenet(&transform);
    }

    Entity3D::Entity3D(std::string name, EntityType3D type):type(type)
    {
        id = -1;        
        this->name = name;
        initialize(has_component);
    }
    
    Entity3D::~Entity3D()
    {

    }

    void Entity3D::awake()
    {

    }

    void Entity3D::start()
    {
        
    }

    void Entity3D::update()
    {
        // update transform

    }

    void Entity3D::end()
    {
        
    }

    void Entity3D::add_componenet(Component* component)
    {
        components[component->type] = component;
        has_component[component->type]=true;
    }

    
}