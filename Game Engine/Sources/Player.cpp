#include "Player.hpp"

namespace Pringine{

    Player::Player(GameController* game_controller):Entity(ENTITY_TYPE_PLAYER)
    {
        this->game_controller = game_controller;
    }

    Player::~Player()
    {

    }

    void Player::awake()
    {

    }

    void Player::start()
    {

    }

    void Player::update()
    {
    
        Vector2<float> translation( game_controller->get_axis(SDL_CONTROLLER_AXIS_LEFTX), game_controller->get_axis(SDL_CONTROLLER_AXIS_LEFTY));
        //std::cout<<translation.x<<" , "<<translation.y<<std::endl;
        translation = translation * (float)(Time::Frame_time*5.f);
        
        main_camera->transform.translate(translation);
    }

    void Player::end()
    {

    }


}