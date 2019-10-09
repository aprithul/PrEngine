//
//  FrameRateCounter.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/28/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "FrameRateCounter.hpp"

namespace Pringine {
    
    FrameRateCounter::FrameRateCounter(std::string name, int priority):Module(name,priority)
    {
        one_second = 0;
    }
    
    FrameRateCounter::~FrameRateCounter()
    {
        
    }
    
    void FrameRateCounter::start()
    {
        
    }
    
    void FrameRateCounter::update()
    {
        frame_count++;
        one_second += Time::Frame_time;
        
        if(one_second>=1.0)
        {
            std::cout<<"frame rate: "<< frame_count<<std::endl;
            frame_count = 0;
            one_second -= 1.0;
        }
    }
    
    void FrameRateCounter::end()
    {
        
    }
}
