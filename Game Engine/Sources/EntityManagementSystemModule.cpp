#include "EntityManagementSystemModule.hpp"

namespace Pringine
{
    int EntityManagementSystem::current_max_entity_id = 0;
    int EntityManagementSystem::entity_count = 0;
    
    EntityManagementSystem::EntityManagementSystem(std::string name, int priority) : Module(name, priority)
    {
        //entities = new (*Entity)[MAX_ENTITY_COUNT];
        for(int i=0;i<MAX_ENTITY_ID;i++)
            entities[i] = nullptr;
    }

    EntityManagementSystem::~EntityManagementSystem()
    {
        for(int i=0; i<=current_max_entity_id; i++)
        {
            if(entities[i] != nullptr)
            {
                //LOG(LOGTYPE_GENERAL, std::string("Deleting entity, id: ").append(std::to_string(entities[i]->id)));
                delete entities[i];
            }
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
                LOG(LOGTYPE_ERROR, "No entity of with id exists");
            }
        }
        else
        {
            LOG(LOGTYPE_ERROR, "requested entity id is out of range ");
        }

        return nullptr;
    
    }


    bool EntityManagementSystem::delete_entity(int id)
    {
        if(id<=current_max_entity_id)
        {   
            Entity* _entity = entities[id];    
            if(_entity!= nullptr)
            {
                delete _entity;
                entities[id] = nullptr;
                entity_count--;
                released_ids.push(id);
                LOG(LOGTYPE_GENERAL, std::string("Entity id: ").append(std::to_string(id)).append(" deleted"));
                return true;
            }
            else
            {
                LOG(LOGTYPE_WARNING, std::string("No entity with id: ").append(std::to_string(id)).append(" exists"));
            }
        }
        else
        {
            LOG(LOGTYPE_WARNING, std::string("Requested entity id: ").append(std::to_string(id)).append(" is out of id range"));
        }
        return false;
    }

    Entity* EntityManagementSystem::assign_id_and_store_entity(Entity& entity)
    {
        if(entity.id != -1)
        {
            LOG(LOGTYPE_WARNING, "Entity already present in system, can't add duplicate");
            
            return &entity;       
        }

        // get next id either from freed id queue or create a new id if none available in queue
        int next_id = -1;
        if(!released_ids.empty())
        {
            next_id = released_ids.front();
            released_ids.pop();
        }
        else if(current_max_entity_id < MAX_ENTITY_ID)
        {
            next_id = (current_max_entity_id++);
        }
        else
        {
            LOG(LOGTYPE_ERROR, "Ran out of entity ids");
            return nullptr;

        }

        entity.id = next_id;
        entities[next_id] = &entity;
        entity_count++;
        return &entity;
    }


    void EntityManagementSystem::start()
    {
        LOG(LOGTYPE_GENERAL, "Entity Management System started");
        for(int _i=0; _i<current_max_entity_id; _i++)
            if(entities[_i] != nullptr)
                entities[_i]->awake();
        LOG(LOGTYPE_GENERAL, "Entity Management callled awake() on all entities");
        
        for(int _i=0; _i<current_max_entity_id; _i++)
            if(entities[_i] != nullptr)
                entities[_i]->start();
        LOG(LOGTYPE_GENERAL, "Entity Management System called start() on all entities");
    }

    void EntityManagementSystem::update()
    {
        //LOG(LOGTYPE_GENERAL, std::string("Entity count: ").append(std::to_string(entity_count)).append("  max id: ").append(std::to_string(current_max_entity_id).append("  queue_size: ").append(std::to_string(this->released_ids.size()))));
        for(int _i=0; _i<current_max_entity_id; _i++)
            if(entities[_i] != nullptr)
                entities[_i]->update();
        
        //LOG(LOGTYPE_GENERAL, "Entity Management System called update() on all entities");

    }

    void EntityManagementSystem::end()
    {
        for(int _i=0; _i<current_max_entity_id; _i++)
            if(entities[_i] != nullptr)
                entities[_i]->end();
        LOG(LOGTYPE_GENERAL, "Entity Management System called end() on all entities");

    }

}