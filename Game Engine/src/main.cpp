//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.


#include "Module.hpp"
#include <stdlib.h>
#include <iostream>
//#include <emscripten.h>
#if defined(EMSCRIPTEN) && defined(_WIN64)
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
#include "RendererOpenGL.hpp"
#include "FrameRateRegulatorModule.hpp"
#include "FrameRateCounterModule.hpp"
#include "Sprite.hpp"
#include "Camera3D.hpp"
#include "DirectionalLight.hpp"
//#include "ImGuiModule.hpp"

using namespace PrEngine;

void main_loop(void* game_engine);

bool is_running = true;

int main(int argc, char * argv[]) 
{        

        // create a new game engine instance
        PrEngine::Engine* game_engine = new PrEngine::Engine();
        // add the components
        // render, frame regulator and frame counter should be the last three components updated ( and so added to engine )
        game_engine->add_module( new PrEngine::Time("Time", 0));
        //game_engine->add_module(new PrEngine::Input( "Input", 1));
        game_engine->add_module(new PrEngine::InputManager("Input",1));
        PrEngine::EntityManagementSystem* entity_management_system = 
                        ( PrEngine::EntityManagementSystem*)game_engine->
                                add_module(new PrEngine::EntityManagementSystem("EMS", 2));
        
        PrEngine::FrameRateRegulator* frame_rate_regulator = 
                        (PrEngine::FrameRateRegulator*)game_engine->
                                add_module( new PrEngine::FrameRateRegulator("FrameRateRegulator", 100000));
        PrEngine::FrameRateCounter* frame_rate_counter = 
                        (PrEngine::FrameRateCounter*)game_engine->
                                add_module(new PrEngine::FrameRateCounter("Frame Counter", 100001));
        
        // can't exceed 60fps if vsync is on
        //frame_rate_regulator->set_frame_rate(60);
        frame_rate_regulator->set_uncapped();
        //frame_rate_regulator->set_frame_rate(15);

        #if defined(EMSCRIPTEN) && defined(_WIN64)
        PrEngine::NetworkManager* network_manager = (PrEngine::NetworkManager*) game_engine->
                                add_module(new PrEngine::NetworkManager("Network manager", 5));
        #endif
        

        Entity* camera_ent = new Entity();
        Transform3D* camera_transform = new Transform3D();
        Camera* camera = new Camera(16, 9, 0.1f, 100.f, 45.f, *camera_transform);
        camera->projection_type = PERSPECTIVE;
        camera->transform.set_position(0.f, 1.f, -6.f);

        camera_ent->add_componenet(camera_transform);
        camera_ent->add_componenet(camera);
        entity_management_system->assign_id_and_store_entity(*camera_ent);
        PrEngine::RendererOpenGL* renderer = (PrEngine::RendererOpenGL*) game_engine->
                                                add_module(new PrEngine::RendererOpenGL(1280,720,"PrEngine"));
        renderer->set_vsync(true);
        PrEngine::GameController* gc = ((PrEngine::InputManager*)game_engine->get_module("Input"))->get_gamecontroller(0);
        PrEngine::Keyboard* kb =  &((PrEngine::InputManager*)game_engine->get_module("Input"))->keyboard;
        PrEngine::Mouse* mouse =  &((PrEngine::InputManager*)game_engine->get_module("Input"))->mouse;

        //PrEngine::TextureSlicingParameters slicing_param_1(0,0,2560,1600,0,0);
        
        if(gc == nullptr)
                PrEngine::LOG( PrEngine::LOGTYPE_ERROR,"Didn't return a valid gamecontroller");

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
        //Graphics* sprite = renderer3d->generate_graphics_quad(get_resource_path(std::string("braid"+PATH_SEP+"tim1.png")));

              //std::cout<<"num of tri: "<<graphics->elements[0].material.uniform_locations.count("u_sampler2d")<<std::endl;

/*for (auto const& pair: graphics->elements[0].material.uniform_locations) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }*/


       /* std::cout<<"print loaded"<<std::endl;   
            std::cout<< graphics->elements.back().material.uniform_locations["u_sampler2d"]<<std::endl;
            std::cout<< graphics->elements.back().material.uniform_locations["u_MVP"]<<std::endl;
            std::cout<< graphics->elements.back().material.uniform_locations["u_Normal_M"]<<std::endl;
            std::cout<< graphics->elements.back().material.uniform_locations["u_Dir_Light"]<<std::endl;
            std::cout<< graphics->elements.back().material.uniform_locations["u_Tiling"]<<std::endl;
            std::cout<< graphics->elements.back().material.uniform_locations["u_Panning"]<<std::endl;
*/


        Transform3D* tim_tran = new Transform3D();
        tim_tran->set_position(0,0.5f,0);
        //tim_tran->set_scale(2,2,2);
        Graphics* tim_1 = renderer->generate_graphics_quad(get_resource_path(std::string("braid"+PATH_SEP+"tim1.png")), true);
        tim_1->models.push_back( &(tim_tran->get_transformation()));
        tim_1->normals.push_back(&tim_tran->get_rotation_transformation());
        Entity* tim_ent = new Entity();
        tim_ent->add_componenet(tim_1);
        tim_ent->add_componenet(tim_tran);
        entity_management_system->assign_id_and_store_entity(*tim_ent);

        Transform3D* tim_tran_2 = new Transform3D();
        tim_tran_2->set_position(0.5f,0.5f,1.f);
        Graphics* tim_2 = renderer->generate_graphics_quad(get_resource_path(std::string("braid"+PATH_SEP+"tim1.png")), true);
        tim_2->models.push_back( &(tim_tran_2->get_transformation()));
        tim_2->normals.push_back(&tim_tran_2->get_rotation_transformation());
        Entity* tim_ent_1 = new Entity();
        tim_ent_1->add_componenet(tim_2);
        tim_ent_1->add_componenet(tim_tran_2);
        entity_management_system->assign_id_and_store_entity(*tim_ent_1);

        /*Graphics* graphics = renderer->generate_graphics(get_resource_path("TreasureChest"), get_resource_path(std::string("TreasureChest"+PATH_SEP+"treasure_chest.obj")), 
        get_resource_path(std::string("TreasureChest"+PATH_SEP+"Treasurechest_DIFF.png")));

        Entity* chest = new Entity();
        Transform3D* chest_tr = new Transform3D();
        chest_tr->set_position(Vector3<float>(0.f,0.5f,-1.8f));
        chest_tr->set_scale(Vector3<float>{0.01f,0.01f,0.01f});
        graphics->models.push_back( &(chest_tr->get_transformation()));
        graphics->normals.push_back(&chest_tr->get_rotation_transformation());

        chest->add_componenet(chest_tr);
        chest->add_componenet(graphics);

        entity_management_system->assign_id_and_store_entity(*chest);
        */
        
        Graphics* graphics_plane = renderer->generate_graphics(get_resource_path("").c_str(), get_resource_path(std::string("plane.obj")).c_str(), 
                get_resource_path(std::string("stonetile.png")).c_str());
        Entity* floor = new Entity();
        Transform3D* floor_transform = new Transform3D();
        floor_transform->set_scale(Vector3<float>(8.f,1.f,8.f));
        floor_transform->set_position(Vector3<float>(0.f, 0.f,0.f));
        graphics_plane->models.push_back( &(floor_transform->get_transformation()));
        graphics_plane->normals.push_back(&floor_transform->get_rotation_transformation());

        floor->add_componenet(floor_transform);
        floor->add_componenet(graphics_plane);
        entity_management_system->assign_id_and_store_entity(*floor);

        ((GuiLayer*)renderer->get_layer("GUI"))->panning =
                &(graphics_plane->elements.begin()->material.panning);
        ((GuiLayer*)renderer->get_layer("GUI"))->tiling =
                &(graphics_plane->elements.begin()->material.tiling);

        LOG(LOGTYPE_WARNING, "Pan: ",std::to_string(graphics_plane->elements.begin()->material.panning.x));

        Entity* light_ent = new Entity();
        DirectionalLight* light = new DirectionalLight();
        light_ent->add_componenet(light);
        entity_management_system->assign_id_and_store_entity(*light_ent);


        //std::cout<<graphics->normal->data[0]<<std::endl;
        /*PrEngine::Player* player = new PrEngine::Player(gc);
        player->keyboard = kb;
        player->mouse = mouse;
        player->main_camera = camera;
        entity_management_system->assign_id_and_store_entity(*player);
        */
        //std::cout<<sprite->graphics.layer<<","<<sprite_cube->graphics.layer<<","<<sprite_cube_2->graphics.layer<<std::endl;
        game_engine->start();
        
        //PrEngine::show_file_structure( PrEngine::get_resource_path(""),"");

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
        ((PrEngine::Engine*)game_engine)->update();
}