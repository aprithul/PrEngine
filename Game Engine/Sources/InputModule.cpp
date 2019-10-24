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
        SDL_Init(SDL_INIT_GAMECONTROLLER);
        SDL_Init(SDL_INIT_JOYSTICK);
        SDL_Init(SDL_INIT_EVENTS);
        SDL_Init(SDL_INIT_HAPTIC);
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
        LOG(LOGTYPE_GENERAL, "Num of Joysticks: ", std::to_string(SDL_NumJoysticks()));
        for(int i=0; i<SDL_NumJoysticks(); i++)
        {
            if (SDL_IsGameController(i)) {
                game_controllers[i].game_controller = SDL_GameControllerOpen(i);
                if(game_controllers[i].game_controller != nullptr)
                {
                    game_controllers[i].name = SDL_GameControllerName(game_controllers[i].game_controller);
                    game_controllers[i].joy_stick = SDL_GameControllerGetJoystick(game_controllers[i].game_controller);
                    game_controllers[i].instance_id = SDL_JoystickInstanceID(game_controllers[i].joy_stick) ;
                }
                else
                    LOG(LOGTYPE_GENERAL,"couldn't get game controller");
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
        }

        for(int i=0; i<MAX_MOUSE_BUTTON_COUNT; i++)
        {
            mouse.button_pressed_flags[i] = false;
            mouse.button_released_flags[i] = false;
            mouse.kb_up[ mouse.mb_to_kb_binding[i]] = false;
            mouse.kb_down[ mouse.mb_to_kb_binding[i]] = false;
        }
    
        for (std::map<SDL_Keycode,bool>::iterator it=keyboard.key_pressed_flags.begin(); it!=keyboard.key_pressed_flags.end(); ++it)
            keyboard.key_pressed_flags[it->first] = false;
        
        for (std::map<SDL_Keycode,bool>::iterator it=keyboard.key_released_flags.begin(); it!=keyboard.key_released_flags.end(); ++it)
            keyboard.key_released_flags[it->first] = false;

//        LOG(LOGTYPE_GENERAL, std::to_string(Time::get_time()));

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
                        
                        game_controllers[i].axis_state[event.caxis.axis] = val * (event.caxis.axis==SDL_CONTROLLER_AXIS_LEFTY || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY ? -1.f:1.f);//*-1.f;
                        //if( abs(val) > game_controllers[i].dead_zone)
                        //    std::cout<<"Controller: "<<game_controllers[i].name<<" axis name: "<<event.caxis.axis<<"  value: "<< game_controllers[i].axis_state[event.caxis.axis]<<std::endl;
                        //LOG(LOGTYPE_GENERAL, "Analog Motion ",std::to_string(val));
                    }
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
                {
                    if(event.cbutton.which == game_controllers[i].instance_id)
                    {
                        game_controllers[i].button_pressed_flags[event.cbutton.button] = true;
                        game_controllers[i].button_state[event.cbutton.button] = true;                        
                        LOG(LOGTYPE_GENERAL,"Controller: ",game_controllers[i].name," Pressed: ", std::to_string((SDL_GameControllerButton)event.cbutton.button));
                    }
                }
                break;
            case SDL_CONTROLLERBUTTONUP:
                for(int i=0; i<MAX_GAMECONTROLLER_COUNT; i++)
                {
                    if(event.cbutton.which == game_controllers[i].instance_id)
                    {
                        game_controllers[i].button_released_flags[event.cbutton.button] = true;
                        game_controllers[i].button_state[event.cbutton.button] = false;                        
                        LOG(LOGTYPE_GENERAL,"Controller: ",game_controllers[i].name," Released: ", std::to_string((SDL_GameControllerButton)event.cbutton.button));                        
                    }
                }
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                LOG(LOGTYPE_WARNING,"Controller detached  ", std::to_string(event.cdevice.which));
                update_game_controllers();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                LOG(LOGTYPE_GENERAL,"Controller added  ", std::to_string(event.cdevice.which));
                update_game_controllers();
                break;
            // end game controller events
            ///////////////////////////////
            // start keyboard / keboard to gamecontroller
            
            case SDL_KEYDOWN:
                if(event.key.repeat == 0)
                {
                    // KeyboardGameController
                    /*if(keyboardgc.axis_binding.count(event.key.keysym.sym)>0)
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
                    }*/

                    // keyboard
                    keyboard.key_state[ event.key.keysym.sym ] = true;
                    keyboard.key_pressed_flags[event.key.keysym.sym] = true;

                    // mouse button mapping to keyboard
                    if(mouse.kb.count(event.key.keysym.sym)>0)
                    {
                        mouse.kb[event.key.keysym.sym] = true;
                        mouse.kb_down[event.key.keysym.sym] = true;
                    }

                }
                else
                {
                    //TEMPROARY
                   // if(event.key.keysym.sym == SDLK_q)
                   //     was_crossed = true;
                }
                break;
            case SDL_KEYUP:
                // game controller
                /*if(keyboardgc.axis_binding.count(event.key.keysym.sym)>0)
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

                }*/

                keyboard.key_state[ event.key.keysym.sym ] = false;
                keyboard.key_released_flags[ event.key.keysym.sym] = true;

                // mouse button mapping to keyboard
                if(mouse.kb.count(event.key.keysym.sym)>0)
                {
                    mouse.kb[event.key.keysym.sym] = false;
                    mouse.kb_up[event.key.keysym.sym] = true;
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
                mouse.button_pressed_flags[event.button.button] = true;
                mouse.click_count[event.button.button] = event.button.clicks;
                mouse.button_state[event.button.button] = true;
                //std::cout<<"mouse click: "<<mouse.click_count[event.button.button]<<std::endl;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse.button_released_flags[event.button.button] = true;
                mouse.button_state[event.button.button] = false;
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

    GameController* InputManager::get_gamecontroller(int index)
    {
        update_game_controllers();
        if(index<MAX_GAMECONTROLLER_COUNT)
        {
            LOG(LOGTYPE_GENERAL,"Returned game controller: ",game_controllers[index].name," , instnace id: ", std::to_string(game_controllers[index].instance_id));
            LOG(LOGTYPE_WARNING, "Controller may not exist yet, verify instance id");
            return &game_controllers[index];
        }
        else
        {
            LOG(LOGTYPE_GENERAL,"Gamecontroller index is out of range");
            return nullptr;
        }
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
        

        button_binding[SDL_CONTROLLER_BUTTON_X] = SDL_CONTROLLER_BUTTON_Y;
        button_binding[SDL_CONTROLLER_BUTTON_Y] = SDL_CONTROLLER_BUTTON_X;
    }

    GameController::GameController(SDL_GameController* game_controller)
    {
        this->game_controller = game_controller;
        this->joy_stick = SDL_GameControllerGetJoystick(game_controller);
        this->name = SDL_GameControllerName(game_controller);
        
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

    GameController::~GameController()
    {

    }

    float GameController::get_axis(SDL_GameControllerAxis axis)
    {
        SDL_GameControllerAxis _axis = axis_binding[axis];
        return axis_state[_axis];
    }

    bool GameController::get_button(SDL_GameControllerButton button)
    {
        SDL_GameControllerButton _button = button_binding[button];
        return button_state[_button];
    }

    bool GameController::get_button_down(SDL_GameControllerButton button)
    {
        SDL_GameControllerButton _button = button_binding[button];
        return button_pressed_flags[_button];
    }
    
    bool GameController::get_button_up(SDL_GameControllerButton button)
    {
        SDL_GameControllerButton _button = button_binding[button];
        return button_released_flags[_button];
    }

    SDL_GameControllerButton GameController::find_down_button()
    {
        for(int i=0; i<SDL_CONTROLLER_BUTTON_MAX; i++)
        {
            if(button_pressed_flags[i] == true)
            {
                return (SDL_GameControllerButton)i;
            }
        }
        return SDL_CONTROLLER_BUTTON_INVALID;
    }

    std::pair<SDL_GameControllerAxis, float> GameController::find_max_axis()
    {
        float max = 0.0f;
        SDL_GameControllerAxis max_axis = SDL_CONTROLLER_AXIS_INVALID;
        for(int i=0; i<SDL_CONTROLLER_AXIS_MAX; i++)
        {
            if(abs(axis_state[i]) > abs(max))
            {
                max = axis_state[i];
                max_axis = (SDL_GameControllerAxis)i;
            }

        }
        return std::pair<SDL_GameControllerAxis, float>{max_axis, max};

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
/////////////////////////////////////////////////////////

    Keyboard::Keyboard()
    {
        // test binding
        key_binding[SDLK_ESCAPE] = SDLK_ESCAPE;
        key_binding[SDLK_c] = SDLK_c;
        key_binding[SDLK_t] = SDLK_r;
    }

    Keyboard::~Keyboard()
    {

    }
    
    bool Keyboard::get_key(SDL_Keycode k)
    {
        SDL_Keycode kk = key_binding[k];
        if(key_state.count(kk)>0)
            return key_state[kk];
        return false;
    }

    bool Keyboard::get_key_down(SDL_Keycode k)
    {
        SDL_Keycode kk = key_binding[k];
        if(key_pressed_flags.count(kk)>0)
            return key_pressed_flags[kk];
        return false;
    }

    bool Keyboard::get_key_up(SDL_Keycode k)
    {
        SDL_Keycode kk = key_binding[k];
        if(key_released_flags.count(kk)>0)
            return key_released_flags[kk];
        return false;

    }

    SDL_Keycode Keyboard::find_down_key()
    {
        for (std::map<SDL_Keycode,bool>::iterator it=key_pressed_flags.begin(); it!=key_pressed_flags.end(); ++it)
        {
            if(it->second == true)
            {
                return it->first;
            }
        }
        return -1;
    }



///////////////////////////////////////////


    Mouse::Mouse()
    {
        position.x = -100;
        position.y = -100;
        window_id = -1;

        for(int i=0; i<MAX_MOUSE_BUTTON_COUNT; i++)
        {
            button_state[i] = false;
            button_pressed_flags[i] = false;
            button_released_flags[i] = false;
        }

        //initial binding
        for(int i=0; i<MAX_MOUSE_BUTTON_COUNT; i++)
        {
            mb_to_mb_binding[i] = i;
            mb_to_kb_binding[i] = SDLK_UNKNOWN;
        }

    }


    Mouse::~Mouse()
    {

    }

    bool Mouse::get_mouse_button(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
        {
            int mb_index = mb_to_mb_binding[index];
            SDL_Keycode kb_index = mb_to_kb_binding[mb_index];
            if(kb_index == SDLK_UNKNOWN)
                return button_state[mb_index];
            else
                return kb[kb_index];
        }
        else
        {
            LOG(LOGTYPE_ERROR, "Invalid mouse index");
            return false;
        }        
    }

    bool Mouse::get_mouse_button_down(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
        {
            int mb_index = mb_to_mb_binding[index];
            SDL_Keycode kb_index = mb_to_kb_binding[mb_index];
            if(kb_index == SDLK_UNKNOWN)
                return button_pressed_flags[mb_index];
            else
                return kb_down[kb_index];
        }
        else
        {
            LOG(LOGTYPE_ERROR,"Invalid mouse index");
            return false;
        }        
    }

    bool Mouse::get_mouse_button_up(int index)
    {
        if(index < MAX_MOUSE_BUTTON_COUNT)  
        {
            int mb_index = mb_to_mb_binding[index];
            SDL_Keycode kb_index = mb_to_kb_binding[mb_index];
            if(kb_index == SDLK_UNKNOWN)
                return button_released_flags[mb_index];
            else
                return kb_up[kb_index];
        }
        else
        {
            LOG(LOGTYPE_ERROR,"Invalid mouse index");
            return false;
        }        
    }

    void Mouse::map_mb_to_mb(int from, int to)
    {
        mb_to_mb_binding[from] = to;
    }    


    void Mouse::map_mb_to_kb(int from, SDL_Keycode to)
    {
        mb_to_mb_binding[from] = from;
        mb_to_kb_binding[from] = to;
        kb[to] = false;
        kb_up[to] = false;
        kb_down[to] = false;
    }





}
