//  main.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/22/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Engine.hpp"
#include "RendererComponent_SDL.hpp"
#include "Input.hpp"
#include "TimeComponent.hpp"
#include "FrameRateRegulatorComponent.hpp"
#include "FrameRateCounter.hpp"


bool is_running = true;

int main(int argc, const char * argv[]) {
    
    SDL_Init(SDL_INIT_EVERYTHING);

    // create a new game engine instance
    Pringine::Engine* game_engine = new Pringine::Engine();
    // add the components
    // render, frame regulator and frame counter should be the last three components updated ( and so added to engine )
    game_engine->add_component( new Pringine::Time("Time", 0));
    game_engine->add_component(new Pringine::Input( "Input", 1));
    Pringine::RendererComponent_SDL* renderer_SDL = (Pringine::RendererComponent_SDL*)game_engine->add_component(new Pringine::RendererComponent_SDL(800,600,"Pringine",false, "Renderer", 99999));
    Pringine::FrameRateRegulator* frame_rate_regulator = (Pringine::FrameRateRegulator*)game_engine->add_component( new Pringine::FrameRateRegulator("FrameRateRegulator", 100000));
    game_engine->add_component(new Pringine::FrameRateCounter("Frame Counter", 100001));
    
    // can't exceed 60fps if vsync is on
    frame_rate_regulator->set_frame_rate(100);
    //renderer->set_vsync(false);
    
    game_engine->start();
    game_engine->update();
    game_engine->end();
    delete game_engine;
    
    return 0;
}
