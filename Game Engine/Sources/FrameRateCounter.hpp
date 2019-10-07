//
//  FrameRateCounter.hpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#ifndef FrameRateCounter_hpp
#define FrameRateCounter_hpp

#include <iostream>
#include "Component.hpp"
#include "TimeComponent.hpp"
namespace Pringine {
    class FrameRateCounter:public Component
    {
    public:
        FrameRateCounter();
        ~FrameRateCounter();
    private:
        void start() override;
        void update() override;
        void end() override;
        double one_second;
        int frame_count;
        
    };
}


#endif /* FrameRateCounter_hpp */
