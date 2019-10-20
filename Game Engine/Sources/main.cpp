//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_revision.h>
#include "Engine.hpp"
#include "RendererModule.hpp"
#include "InputModule.hpp"
#include "TimeModule.hpp"
#include "FrameRateRegulatorModule.hpp"
#include "FrameRateCounterModule.hpp"
#include "EntityManagementSystemModule.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Vector2.hpp"

        
        bool is_running = true;

        int main(int argc, const char * argv[]) {
        
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Init(SDL_INIT_TIMER);

        // create a new game engine instance
        Pringine::Engine* game_engine = new Pringine::Engine();
        // add the components
        // render, frame regulator and frame counter should be the last three components updated ( and so added to engine )
        game_engine->add_module( new Pringine::Time("Time", 0));
        //game_engine->add_module(new Pringine::Input( "Input", 1));
        game_engine->add_module(new Pringine::InputManager("Input",1));
        Pringine::EntityManagementSystem* entity_management_system = 
                        ( Pringine::EntityManagementSystem*)game_engine->
                                add_module(new Pringine::EntityManagementSystem("Entity Management System", 2));
        
        Pringine::FrameRateRegulator* frame_rate_regulator = 
                        (Pringine::FrameRateRegulator*)game_engine->
                                add_module( new Pringine::FrameRateRegulator("FrameRateRegulator", 100000));
        //game_engine->add_module(new Pringine::FrameRateCounter("Frame Counter", 100001));
        
        // can't exceed 60fps if vsync is on
        //frame_rate_regulator->set_frame_rate(100);
        frame_rate_regulator->set_frame_rate_to_uncapped();

        Pringine::Renderer2D* renderer2d = 
                        (Pringine::Renderer2D*)game_engine->
                                add_module(new Pringine::Renderer2D(640,480,"Pringine",true, 25, "Renderer", 99999));

        Pringine::Camera* camera = new Pringine::Camera(16,9,0.01f,renderer2d);
        camera->transform.position = Pringine::Vector2<float>(0,0);
        entity_management_system->assign_id_and_store_entity(*camera);

        //Pringine::Sprite** entities = new Pringine::Sprite*[500];
        std::string graphics_file_location = Pringine::get_resource_path("highres.jpg");
        //for(int i=0; i<300; i++){
        Pringine::TextureSlicingParameters slicing_param_1(0,0,2560,1600,0,0);
        //Pringine::Sprite* sprite = new Pringine::Sprite(Pringine::get_resource_path("highres.jpg"), slicing_param_1, *renderer2d, 1, 100, 0);
        //sprite->transform.position = Pringine::Vector2<float>(0,0);
        //entity_management_system->assign_id_and_store_entity(*sprite);

        Pringine::TextureSlicingParameters slicing_param_2(0,0,1024,1024,0,0);

        //for(int i=0; i<10; i++)
        {
                Pringine::Sprite* sprite_cube = new Pringine::Sprite(Pringine::get_resource_path("cube.png"), slicing_param_2, *renderer2d, 4, 50, 10);
                sprite_cube->transform.position = Pringine::Vector2<float>(0,0);
                //sprite_cube->set_animation(true, 4);
                entity_management_system->assign_id_and_store_entity(*sprite_cube);
        }
        Pringine::GameController* gc = ((Pringine::InputManager*)game_engine->get_module("Input"))->get_gamecontroller();
        Pringine::Keyboard* kb =  &((Pringine::InputManager*)game_engine->get_module("Input"))->keyboard;
        Pringine::Mouse* mouse =  &((Pringine::InputManager*)game_engine->get_module("Input"))->mouse;

        if(gc == nullptr)
                std::cout<<"Didn't return a valid gamecontroller"<<std::endl;
        else
        {
                Pringine::Player* player = new Pringine::Player(gc);
                player->keyboard = kb;
                player->mouse = mouse;
                player->main_camera = camera;
                entity_management_system->assign_id_and_store_entity(*player);
        }

        //std::cout<<sprite->graphics.layer<<","<<sprite_cube->graphics.layer<<","<<sprite_cube_2->graphics.layer<<std::endl;
        game_engine->start();
        game_engine->update();
        game_engine->end();
        delete game_engine;
        
        return 0;
}
