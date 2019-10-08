//
//  FrameRateRegulatorComponent.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef FrameRateRegulatorComponent_hpp
#define FrameRateRegulatorComponent_hpp

#include <iostream>
#include "Component.hpp"
#include "TimeComponent.hpp"
#include "SDL2/SDL.h"


namespace Pringine {
    class FrameRateRegulator:public Component
    {
    public:
        FrameRateRegulator();
        ~FrameRateRegulator();
        void start() override;
        void update() override;
        void end() override;
        void set_frame_rate(int frame_rate);
    private:
        int frame_rate;
        double frame_delta;
        double idle_time;
        double target_time;
        double one_second;
        double sleep_time;
        int frame_count;
        
    };
}

#endif /* FrameRateRegulatorComponent_hpp */
