//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "Engine.hpp"
#include "RendererModule.hpp"
#include "InputModule.hpp"
#include "TimeModule.hpp"
#include "FrameRateRegulatorModule.hpp"
#include "FrameRateCounterModule.hpp"
#include "EntityManagementSystemModule.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Utils.hpp"
#include "Vector2.hpp"

        
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
        
        Pringine::FrameRateRegulator* frame_rate_regulator = 
                        (Pringine::FrameRateRegulator*)game_engine->
                                add_module( new Pringine::FrameRateRegulator("FrameRateRegulator", 100000));
        game_engine->add_module(new Pringine::FrameRateCounter("Frame Counter", 100001));
        
        // can't exceed 60fps if vsync is on
        frame_rate_regulator->set_frame_rate(100);
        //frame_rate_regulator->set_frame_rate_to_uncapped();


        Pringine::Camera* camera = new Pringine::Camera(1,1,0.01f);
        camera->transform.position = Pringine::Vector2<float>(0,0);
        entity_management_system->assign_id_and_store_entity(*camera);
        Pringine::Renderer2D* renderer2d = 
                        (Pringine::Renderer2D*)game_engine->
                                add_module(new Pringine::Renderer2D(1024,768,"Pringine",false,camera, 25, "Renderer", 99999));

        //Pringine::Sprite** entities = new Pringine::Sprite*[500];
        std::string graphics_file_location = Pringine::get_resource_path("highres.jpg");
        //for(int i=0; i<300; i++){
        Pringine::TextureSlicingParameters slicing_param_1(0,0,2560,1600,0,0);
        Pringine::Sprite* sprite = new Pringine::Sprite(Pringine::get_resource_path("highres.jpg"), slicing_param_1, *renderer2d, 1);
        sprite->transform.position = Pringine::Vector2<float>(0,0);
        entity_management_system->assign_id_and_store_entity(*sprite);

        game_engine->start();
        game_engine->update();
        game_engine->end();
        delete game_engine;
        
        return 0;
}
