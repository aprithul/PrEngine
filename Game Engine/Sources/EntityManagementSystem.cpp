#include "EntityManagementSystem.hpp"

namespace Pringine
{
    int EntityManagementSystem::entity_count = 0;

    EntityManagementSystem::EntityManagementSystem(std::string name, int priority) : Module(name, priority)
    {
        //entities = new (*Entity)[MAX_ENTITY_COUNT];
        for(int i=0;i<MAX_ENTITY_ID;i++)
            entities[i] = nullptr;
    }

    EntityManagementSystem::~EntityManagementSystem()
    {
        for(int i=0; i<MAX_ENTITY_ID; i++)
        {
            if(entities[i])
                delete entities[i];
        }
    }


    Entity* EntityManagementSystem::get_entity(int id)
    {
        if(id<MAX_ENTITY_ID)
        {   
            Entity* _entity = entities[id];    
            if(_entity)
            {
                return _entity;
            }
            else
            {
                log_to(LOGTYPE_ERROR, "No entity of with id exists");
            }
        }
        else
        {
            log_to(LOGTYPE_ERROR, "requested entity id is out of range ");
        }

        return nullptr;
    
    }


    bool EntityManagementSystem::delete_entity(int id)
    {
        if(id<MAX_ENTITY_ID)
        {   
            Entity* _entity = entities[id];    
            if(_entity)
            {
                delete _entity;
                entities[id] = nullptr;
                log_to(LOGTYPE_ERROR, (std::string("Entity id: ")+std::to_string(id)+ std::string(" deleted")).c_str());
                return true;
            }
            else
            {
                log_to(LOGTYPE_ERROR, "No entity of with id exists");
            }
        }
        else
        {
            log_to(LOGTYPE_ERROR, "requested entity id is out of range ");
        }
        return false;
    }

    Entity* EntityManagementSystem::assign_id_and_store_entity(Entity& entity)
    {
        // get next id either from freed id queue or create a new id if none available in queue
        int next_id = -1;
        if(!released_ids.empty())
        {
            next_id = released_ids.front();
            released_ids.pop();
        }
        else if(entity_count+1 <= MAX_ENTITY_ID)
        {
            next_id = (entity_count++);
        }
        else
        {
            log_to(LOGTYPE_ERROR, "Ran out of entity ids");
            return nullptr;

        }

        entity.id = next_id;
        entities[next_id] = &entity;
        return &entity;
    }


    void EntityManagementSystem::start()
    {
        log_to(LOGTYPE_GENERAL, "Entity Management System started");
    }

    void EntityManagementSystem::update()
    {

    }

    void EntityManagementSystem::end()
    {
        log_to(LOGTYPE_GENERAL, "Entity Management System ended");
    }

}