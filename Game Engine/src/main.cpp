//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.

#include "Module.hpp"
#include <stdlib.h>
#include <iostream>
//#include <emscripten.h>
#ifndef EMSCRIPTEN
#include "NetworkManager.hpp"
#endif
#include "Utils.hpp"
#include "Vector2.hpp"
#include "Engine.hpp"
#include "TimeModule.hpp"
#include "InputModule.hpp"
#include "EntityManagementSystemModule.hpp"
#include <SDL2/SDL.h>
//#include "RendererModule.hpp"
#include "Renderer3D.hpp"
#include "FrameRateRegulatorModule.hpp"
#include "FrameRateCounterModule.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "GUI.hpp"
#include "EditorModule.hpp"
#include "Cube.hpp"


using namespace Pringine;

void main_loop(void* game_engine);

bool is_running = true;
int main(int argc, const char * argv[]) 
{        

        // create a new game engine instance
        Pringine::Engine* game_engine = new Pringine::Engine();
        // add the components
        // render, frame regulator and frame counter should be the last three components updated ( and so added to engine )
        game_engine->add_module( new Pringine::Time("Time", 0));
        //game_engine->add_module(new Pringine::Input( "Input", 1));
        game_engine->add_module(new Pringine::InputManager("Input",1));
        Pringine::EntityManagementSystem* entity_management_system = 
                        ( Pringine::EntityManagementSystem*)game_engine->
                                add_module(new Pringine::EntityManagementSystem("EMS", 2));
        
        Pringine::FrameRateRegulator* frame_rate_regulator = 
                        (Pringine::FrameRateRegulator*)game_engine->
                                add_module( new Pringine::FrameRateRegulator("FrameRateRegulator", 100000));
        Pringine::FrameRateCounter* frame_rate_counter = 
                        (Pringine::FrameRateCounter*)game_engine->
                                add_module(new Pringine::FrameRateCounter("Frame Counter", 100001));
        
        // can't exceed 60fps if vsync is on
        frame_rate_regulator->set_frame_rate(120);
        //frame_rate_regulator->set_uncapped();
        //frame_rate_regulator->set_frame_rate(15);

        #ifndef EMSCRIPTEN
        Pringine::NetworkManager* network_manager = (Pringine::NetworkManager*) game_engine->
                                add_module(new Pringine::NetworkManager("Network manager", 5));
        #endif
        
        Pringine::Renderer3D* renderer3d = (Pringine::Renderer3D*) game_engine->
                                                add_module(new Pringine::Renderer3D(800,600,"Hello Opengl"));
        //Pringine::Renderer2D* renderer2d =
        //                (Pringine::Renderer2D*)game_engine->
        //                        add_module(new Pringine::Renderer2D(1280,720,"Pringine",false, 25, "Renderer", 99999));
        
        //frame_rate_counter->renderer2D = renderer2d;
        
        //Pringine::Editor* editor = (Pringine::Editor*) game_engine->
        //                                        add_module(new Pringine::Editor("Editor", 6, renderer2d));
        
        Pringine::GameController* gc = ((Pringine::InputManager*)game_engine->get_module("Input"))->get_gamecontroller(0);
        Pringine::Keyboard* kb =  &((Pringine::InputManager*)game_engine->get_module("Input"))->keyboard;
        Pringine::Mouse* mouse =  &((Pringine::InputManager*)game_engine->get_module("Input"))->mouse;
        //mouse->map_mb_to_mb(1,0);
        //mouse->map_mb_to_mb(3,1);

        //Pringine::initialize_gui(mouse, renderer2d);

        //Pringine::Camera* camera = new Pringine::Camera(16,9,renderer2d);
        //camera->transform.position = Pringine::Vector2<float>(2,0);
        //entity_management_system->assign_id_and_store_entity(*camera);

        //Pringine::Sprite** entities = new Pringine::Sprite*[500];
        //std::string graphics_file_location = Pringine::get_resource_path("highres.jpg");
        //for(int i=0; i<300; i++){
        Pringine::TextureSlicingParameters slicing_param_1(0,0,2560,1600,0,0);
        //Pringine::Sprite* sprite = new Pringine::Sprite(Pringine::get_resource_path("highres.jpg"), slicing_param_1, *renderer2d, 1, 100, 0);
        //sprite->transform.position = Pringine::Vector2<float>(0,0);
        //entity_management_system->assign_id_and_store_entity(*sprite);

        //        entity_management_system->assign_id_and_store_entity(*sprite_ui);
        //}
        
        if(gc == nullptr)
                Pringine::LOG( Pringine::LOGTYPE_ERROR,"Didn't return a valid gamecontroller");


        



LOG(LOGTYPE_GENERAL, std::string( (const char*)(glGetString(GL_VERSION))));//,",  ",std::string( (const char*)(glGetString(GL_EXTENSIONS)) ));

/*
        const int number_of_meshes = 1;
        Mesh meshes[number_of_meshes];

        Vertex vertices[4];
                    // pos,   color     texcoord
                    // x,y,z, r,g,b,a   
        vertices[0] = {-1.f,-1.f, 0.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.f};
        vertices[1] = { 1.f,-1.f, 0.f, 0.0f, 1.0f, 0.0f, 1.0f, 1.f, 0.f};
        vertices[2] = { 1.f, 1.f, 0.f, 0.0f, 0.0f, 1.0f, 1.0f, 1.f, 1.f};
        vertices[3] = {-1.f, 1.f, 0.f, 1.0f, 0.0f, 0.0f, 1.0f, 0.f, 1.f};
        
        GLuint element_array[] = {
            0, 1, 2,
            2, 3, 0
        };
        meshes[0].set_vertices(vertices, 4);
        meshes[0].set_indices(element_array, 6);
        
*/
        //std::cout<<"Stride"<<layout.stride<<std::endl;
        

        Graphics3D* graphics = renderer3d->generate_graphics3d(get_resource_path("TreasureChest").c_str(), get_resource_path(std::string("TreasureChest"+PATH_SEP+"treasure_chest.obj")).c_str(), 
                                get_resource_path(std::string("TreasureChest"+PATH_SEP+"Treasurechest_DIFF.png")).c_str());
        //Graphics3D* graphics = renderer3d->generate_graphics3d(get_resource_path("").c_str(), get_resource_path(std::string("cube.obj")).c_str(), 
        //                        get_resource_path(std::string("default.png")).c_str());
        if(graphics != nullptr)
        {
                Cube* cube = new Cube(graphics);
                cube->transform.set_position(Vector3<float>(0.0f,0.0f,-1.8f));
                cube->transform.set_scale(Vector3<float>{0.01f,0.01f,0.01f});
                entity_management_system->assign_id_and_store_entity(*cube);
        }
        //std::cout<<graphics->normal->data[0]<<std::endl;


        /*Pringine::Player* player = new Pringine::Player(gc);
        player->keyboard = kb;
        player->mouse = mouse;
        player->main_camera = camera;
        entity_management_system->assign_id_and_store_entity(*player);
        */
        //std::cout<<sprite->graphics.layer<<","<<sprite_cube->graphics.layer<<","<<sprite_cube_2->graphics.layer<<std::endl;
        game_engine->start();
        
        //Pringine::show_file_structure( Pringine::get_resource_path(""),"");

        #ifndef EMSCRIPTEN
                game_engine->update();
                game_engine->end();
                delete game_engine;
        #else
                emscripten_set_main_loop_arg(main_loop, game_engine, 0, 1);
        #endif
        
        return 0;
}


void main_loop(void* game_engine)
{
        ((Pringine::Engine*)game_engine)->update();
}