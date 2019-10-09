#ifndef ENTITY_MANAGEMENT_SYSTEM_HPP
#define ENTITY_MANAGEMENT_SYSTEM_HPP

#include "Module.hpp"
#include "Entity.hpp"
#include <vector>
#include <queue>
#define MAX_ENTITY_ID 999999
namespace Pringine
{
    class EntityManagementSystem : public Module
    {
        public:
            EntityManagementSystem(std::string name, int priority);
            ~EntityManagementSystem();

            Entity* get_entity(int id);
            bool delete_entity(int id);
            Entity* assign_id_and_store_entity(Entity& entity);

            void start() override;
            void update() override;
            void end() override;

        private:
            Entity* entities[MAX_ENTITY_ID];
            std::queue<int> released_ids;
            static int entity_count;
    };
}


#endif