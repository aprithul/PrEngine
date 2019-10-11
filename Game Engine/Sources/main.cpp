//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include <SDL2/SDL.h>
#include "Engine.hpp"
#include "RendererModule.hpp"
#include "InputModule.hpp"
#include "TimeModule.hpp"
#include "FrameRateRegulatorModule.hpp"
#include "FrameRateCounterModule.hpp"
#include "EntityManagementSystemModule.hpp"
#include "Sprite.hpp"
#include "Utils.hpp"

        
        bool is_running = true;

        int main(int argc, const char * argv[]) {
        
        SDL_Init(SDL_INIT_EVERYTHING);

        // create a new game engine instance
        Pringine::Engine* game_engine = new Pringine::Engine();
        // add the components
        // render, frame regulator and frame counter should be the last three components updated ( and so added to engine )
        game_engine->add_module( new Pringine::Time("Time", 0));
        game_engine->add_module(new Pringine::Input( "Input", 1));
        Pringine::EntityManagementSystem* entity_management_system = 
                        ( Pringine::EntityManagementSystem*)game_engine->
                                add_module(new Pringine::EntityManagementSystem("Entity Management System", 2));
        Pringine::Renderer2D* renderer2d = 
                        (Pringine::Renderer2D*)game_engine->
                                add_module(new Pringine::Renderer2D(1280,800,"Pringine",true, "Renderer", 99999));
        Pringine::FrameRateRegulator* frame_rate_regulator = 
                        (Pringine::FrameRateRegulator*)game_engine->
                                add_module( new Pringine::FrameRateRegulator("FrameRateRegulator", 100000));
        game_engine->add_module(new Pringine::FrameRateCounter("Frame Counter", 100001));
        
        // can't exceed 60fps if vsync is on
        frame_rate_regulator->set_frame_rate(60);
        //frame_rate_regulator->set_frame_rate_to_uncapped();

        Pringine::Sprite** entities = new Pringine::Sprite*[100];
        std::string graphics_file_location = Pringine::get_resource_path("highres.jpg");
        /*for(int i=0; i<15; i++){
                entities[i] = new Pringine::Sprite(graphics_file_location, *renderer2d);
                entity_management_system->assign_id_and_store_entity(*entities[i]);
        }*/
        /*
        entity_management_system->delete_entity(entities[0]->id);
        entity_management_system->delete_entity(entities[15]->id);
        entity_management_system->delete_entity(entities[45]->id);
        entity_management_system->delete_entity(entities[1]->id);
        //entity_management_system->delete_entity(entities[45]->id);
        */
        entities[0] = new Pringine::Sprite(Pringine::get_resource_path("highres.jpg"), *renderer2d);
        entity_management_system->assign_id_and_store_entity(*entities[0]);
        entities[1] = new Pringine::Sprite(Pringine::get_resource_path("cube.png"), *renderer2d);
        entity_management_system->assign_id_and_store_entity(*entities[1]);
        //entities[1] = new Pringine::Sprite(graphics_file_location, *renderer2d);
       // entity_management_system->assign_id_and_store_entity(*entities[1]);

        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);
        //entity_management_system->assign_id_and_store_entity(*entities[0]);



        game_engine->start();
        game_engine->update();
        game_engine->end();
        delete game_engine;
        
        return 0;
}
