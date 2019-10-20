//
//  Input.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/23/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "InputModule.hpp"

namespace Pringine {
    
    InputManager::InputManager(std::string name, int priority):Module(name, priority)
    {
        was_crossed = false;
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::start()
    {
        update_game_controllers();
    }

    void InputManager::update_game_controllers()
    {

        for(int i=0; i<SDL_NumJoysticks(); i++)
        {
            if (SDL_IsGameController(i)) {
                game_controllers[i].game_controller = SDL_GameControllerOpen(i);
                if(game_controllers[i].game_controller != nullptr)
                {
                    game_controllers[i].name = SDL_GameControllerName(game_controllers[i].game_controller);
                    game_controllers[i].joy_stick = SDL_GameControllerGetJoystick(game_controllers[i].game_controller);
                    game_controllers[i].instance_id = SDL_JoystickInstanceID(game_controllers[i].joy_stick) ;
                    std::cout<<"Game Controller: "<<game_controllers[i].name<<", "<<game_controllers[i].instance_id<<std::endl;
                }
                else
                    std::cout<<"couldn't get game controller"<<std::endl;
            }
        }
    }

    void InputManager::update()
    {

        for(int j=SDL_CONTROLLER_BUTTON_A; j<SDL_CONTROLLER_BUTTON_MAX; j++)
        {
            for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
            {
                game_controllers[i].button_released_flags[j] = false;
                game_controllers[i].button_pressed_flags[j] = false;
            }
            keyboardgc.button_released_flags[j] = false;
            keyboardgc.button_pressed_flags[j] = false;
        }

        for(int i=0; i<MAX_MOUSE_BUTTON_COUNT; i++)
        {
            mouse.button_pressed_flags[i] = false;
            mouse.button_released_flags[i] = false;
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {

            // handle all gamecontroller events
            case SDL_CONTROLLERAXISMOTION:
                for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
                {
                    if(event.caxis.which == game_controllers[i].instance_id)
                    {
                        float val = clamp(event.caxis.value/32767.f, -1.f,1.f);
                        if(abs(val) <= game_controllers[i].dead_zone)
                            val = 0.0f;
                        
                        game_controllers[i].axis_state[game_controllers[i].axis_binding[event.caxis.axis]] = val * (event.caxis.axis==SDL_CONTROLLER_AXIS_LEFTY || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY ? -1.f:1.f);//*-1.f;
                        if( abs(val) > game_controllers[i].dead_zone)
                            std::cout<<"Controller: "<<game_controllers[i].name<<" axis name: "<<game_controllers[i].axis_binding[event.caxis.axis]<<"  value: "<< game_controllers[i].axis_state[game_controllers[i].axis_binding[event.caxis.axis]]<<std::endl;

                    }
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
                {
                    if(event.cbutton.which == game_controllers[i].instance_id)
                    {
                        game_controllers[i].button_pressed_flags[game_controllers[i].button_binding[event.cbutton.button]] = event.cbutton.state;
                        game_controllers[i].button_state[game_controllers[i].button_binding[event.cbutton.button]] = event.cbutton.state;                        
                        std::cout<<"Controller: "<<game_controllers[i].name<<" Pressed: "<<(SDL_GameControllerButton)game_controllers[i].button_binding[event.cbutton.button]<<std::endl;
                    }
                }
                break;
            case SDL_CONTROLLERBUTTONUP:
                for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
                {
                    if(event.cbutton.which == game_controllers[i].instance_id)
                    {
                        game_controllers[i].button_released_flags[game_controllers[i].button_binding[event.cbutton.button]] = event.cbutton.state;
                        game_controllers[i].button_state[game_controllers[i].button_binding[event.cbutton.button]] = event.cbutton.state;                        
                        std::cout<<"Controller: "<<game_controllers[i].name<<" Released: "<<(SDL_GameControllerButton)game_controllers[i].button_binding[event.cbutton.button]<<std::endl;
                    }
                }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                std::cout<<"Controller detached "<< event.cdevice.which<<std::endl;
                update_game_controllers();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                std::cout<<"Controller added "<< event.cdevice.which<<std::endl;
                update_game_controllers();
                break;
            // end game controller events
            ///////////////////////////////
            // start keyboard to gamecontroller start
            case SDL_KEYDOWN:
                if(event.key.repeat == 0)
                {
                    if(keyboardgc.axis_binding.count(event.key.keysym.sym)>0)
                    {
                        std::pair<SDL_GameControllerAxis, float> _pair = keyboardgc.axis_binding[event.key.keysym.sym];
                        keyboardgc.axis_state[_pair.first] += _pair.second;
                        std::cout<<_pair.first<<" , "<<keyboardgc.axis_state[_pair.first]<<std::endl;
                    }
                    else if(keyboardgc.button_binding.count(event.key.keysym.sym)>0)
                    {
                        SDL_GameControllerButton button = keyboardgc.button_binding[event.key.keysym.sym];
                        keyboardgc.button_state[button] = true;
                        keyboardgc.button_pressed_flags[button] = true;
                        //std::cout<<button<<",  "<< true<<std::endl;
                    }
                }
                else
                {
                    //TEMPROARY
                    if(event.key.keysym.sym == SDLK_q)
                        was_crossed = true;
                }
                break;
            case SDL_KEYUP:
                if(keyboardgc.axis_binding.count(event.key.keysym.sym)>0)
                {
                    std::pair<SDL_GameControllerAxis, float> _pair = keyboardgc.axis_binding[event.key.keysym.sym];
                    keyboardgc.axis_state[_pair.first] -= _pair.second;
                    std::cout<<_pair.first<<" , "<<keyboardgc.axis_state[_pair.first]<<std::endl;
                }
                else if(keyboardgc.button_binding.count(event.key.keysym.sym)>0)
                {
                    SDL_GameControllerButton button = keyboardgc.button_binding[event.key.keysym.sym];
                    keyboardgc.button_state[button] = false;
                    keyboardgc.button_pressed_flags[button] = false;
                    //std::cout<<button<<",  "<< false<<std::endl;

                }
                break;
            
            // keyboard gamecontroller end
            case SDL_MOUSEMOTION:
                mouse.position.x = event.motion.x;
                mouse.position.y = event.motion.y;
                mouse.window_id  = event.motion.windowID;
                //std::cout<<"Mouse Position: "<< mouse.position.x<<","<<mouse.position.y<<std::endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse.button_pressed_flags[event.button.button] = event.button.state;
                mouse.click_count[event.button.button] = event.button.clicks;
                mouse.button_state[event.button.button] = event.button.state;
                //std::cout<<"mouse click: "<<mouse.click_count[event.button.button]<<std::endl;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse.button_released_flags[event.button.button] = event.button.state;
                mouse.button_state[event.button.button] = event.button.state;
                break;
            case SDL_QUIT:
                was_crossed = true;
                break;
            default:
                break;
            }
        }

    }

    void InputManager::end()
    {
        for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
        {
            if(game_controllers[i].game_controller != nullptr)
                SDL_GameControllerClose(game_controllers[i].game_controller);
        }
    }

    GameController* InputManager::get_gamecontroller()
    {
        update_game_controllers();
        for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
        {
            if(game_controllers[i].instance_id >= 0)
            {
                std::cout<<"Returned game controller: "<<game_controllers[i].name<<" , instnace id: "<<game_controllers[i].instance_id<<std::endl;
                return &game_controllers[i];
            }
        }

        std::cout<<"No gamecontroller attached, returing keyboard as gamecontroller"<<std::endl;
        return &keyboardgc;
    }


    GameController::GameController()
    {
        game_controller = nullptr;
        joy_stick = nullptr;
        instance_id = -1;

        for(int i=SDL_CONTROLLER_AXIS_LEFTX; i<SDL_CONTROLLER_AXIS_MAX; i++)
            axis_state[i] = 0.f;
        
        for(int i=SDL_CONTROLLER_BUTTON_A; i<SDL_CONTROLLER_BUTTON_MAX; i++)
        {
            button_state[i] = false;
            button_pressed_flags[i] = false;
            button_released_flags[i] = false;
        }
        dead_zone = 0.03f;


        // temporary
        // initial bindings
        for(int i=SDL_CONTROLLER_AXIS_LEFTX; i<SDL_CONTROLLER_AXIS_MAX; i++)
            axis_binding[i] = (SDL_GameControllerAxis)i;
       
        for(int i=SDL_CONTROLLER_BUTTON_A; i<SDL_CONTROLLER_BUTTON_MAX; i++)
            button_binding[i] = (SDL_GameControllerButton)i;
        
    }

    GameController::GameController(SDL_GameController* game_controller)
    {
        this->game_controller = game_controller;
        this->joy_stick = SDL_GameControllerGetJoystick(game_controller);
        this->name = SDL_GameControllerName(game_controller);
        dead_zone = 0.015f;

        // temporary
        // initial bindings
        for(int i=SDL_CONTROLLER_AXIS_LEFTX; i<SDL_CONTROLLER_AXIS_MAX; i++)
            axis_binding[i] = (SDL_GameControllerAxis)i;
       
        for(int i=SDL_CONTROLLER_BUTTON_A; i<SDL_CONTROLLER_BUTTON_MAX; i++)
            button_binding[i] = (SDL_GameControllerButton)i;

        
    }

    GameController::~GameController()
    {

    }

    float GameController::get_axis(SDL_GameControllerAxis axis)
    {
        return axis_state[axis];
    }

    bool GameController::get_button(SDL_GameControllerButton action)
    {
        return button_state[action];
    }

    bool GameController::get_button_pressed(SDL_GameControllerButton button)
    {
        return button_pressed_flags[button];
    }
    
    bool GameController::get_button_released(SDL_GameControllerButton button)
    {
        return button_released_flags[button];
    }

    ///////////////

    ////////// KeyboardGameController
    KeyboardGameController::KeyboardGameController()
    {
        for(int i=SDL_CONTROLLER_AXIS_LEFTX; i<SDL_CONTROLLER_AXIS_MAX; i++)
            axis_state[i] = 0.f;
        
        for(int i=SDL_CONTROLLER_BUTTON_A; i<SDL_CONTROLLER_BUTTON_MAX; i++)
        {
            button_state[i] = false;
            button_pressed_flags[i] = false;
            button_released_flags[i] = false;
        }

        // temporary binding for keyboard to gamecontroller
        axis_binding[SDLK_a] = std::pair<SDL_GameControllerAxis, float>{SDL_CONTROLLER_AXIS_LEFTX,-1.f};
        axis_binding[SDLK_d] = std::pair<SDL_GameControllerAxis, float>{SDL_CONTROLLER_AXIS_LEFTX, 1.f};
        axis_binding[SDLK_w] = std::pair<SDL_GameControllerAxis, float>{SDL_CONTROLLER_AXIS_LEFTY, 1.f};
        axis_binding[SDLK_s] = std::pair<SDL_GameControllerAxis, float>{SDL_CONTROLLER_AXIS_LEFTY, -1.f};

        button_binding[SDLK_j] = SDL_CONTROLLER_BUTTON_X;
        button_binding[SDLK_i] = SDL_CONTROLLER_BUTTON_Y;

    }

    KeyboardGameController::~KeyboardGameController()
    {

    }



///////////////////////////////////////////


    Mouse::Mouse()
    {
        position.x = 0;
        position.y = 0;
        window_id = -1;
        for(int i=0; i<MAX_MOUSE_BUTTON_COUNT; i++)
        {
            button_state[i] = false;
            button_pressed_flags[i] = false;
            button_released_flags[i] = false;
        }
    }


    Mouse::~Mouse()
    {

    }

    bool Mouse::get_mouse_button(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
            return button_state[index];
        else
        {
            std::cout<<"Invalid mouse index"<<std::endl;
            return false;
        }        
    }

    bool Mouse::get_mouse_button_down(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
            return button_pressed_flags[index];
        else
        {
            std::cout<<"Invalid mouse index"<<std::endl;
            return false;
        }        
    }

    bool Mouse::get_mouse_button_up(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
            return button_released_flags[index];
        else
        {
            std::cout<<"Invalid mouse index"<<std::endl;
            return false;
        }        
    }

    








}
