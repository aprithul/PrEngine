#include "Game.hpp"
#include "InputModule.hpp"
#include "EntityManagementSystemModule.hpp"
#include "TimeModule.hpp"

namespace PrEngine
{
    Game::Game(std::string name, int priority):Module(name, priority)
    {

    }

    Game::~Game()
    {

    }

    void Game::start()
    {

    }

    void Game::update()
    {
        Entity* entity = entity_management_system->get_entity_with_component(COMP_LIGHT);
        if(entity != nullptr)        
        {
            Transform3D* t = (Transform3D*)entity->components[COMP_TRANSFORM_3D];
            auto pos = t->get_position();
            auto rot = t->get_rotation();

            if(input_manager->keyboard.get_key(SDLK_UP))
            {
                //pos.y+=2;//(1*Time::Frame_time);
                rot.x+=0.5;
            }
            if(input_manager->keyboard.get_key(SDLK_DOWN))
            {
                //pos.y-=2;//(1*Time::Frame_time);
                rot.x-=0.5;
            }
            if(input_manager->keyboard.get_key(SDLK_LEFT))
            {
                pos.x-=0.1;//(1*Time::Frame_time);
            }
            if(input_manager->keyboard.get_key(SDLK_RIGHT))
            {
                pos.x+=0.1;//(1*Time::Frame_time);
            }
            t->set_position(pos);
            t->set_rotation(rot);
        }
        else
        {
            LOG(LOGTYPE_ERROR, "Couldn't find entity ", "floor");
        }
    }

    void Game::end()
    {

    }

}