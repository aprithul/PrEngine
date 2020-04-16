#ifndef CUBE_HPP
#define CUBE_HPP

#include "Entity3D.hpp"
#include "Renderer3D.hpp"

namespace Pringine
{
    class Cube : public Entity3D
    {
        public:
            Cube(Graphics3D* graphics);
            ~Cube();
            
            void start() override;
            void end() override;
            void update() override;
    };
    
}



#endif