#ifndef CUBE_HPP
#define CUBE_HPP

#include "Entity.hpp"
#include "Renderer3D.hpp"

namespace Pringine
{
    class Cube : public Entity
    {
        public:
            Graphics3D* graphics;
            
            Cube(Graphics3D& graphics);
            ~Cube();

            void start() override;
            void update() override;
            void end() override;
    };
    
}



#endif