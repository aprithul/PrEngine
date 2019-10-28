//
//  Vertex.cpp
//  Game Engine
//
//  Created by Aniruddha Prithul on 7/30/17.
//  Copyright © 2017 Aniruddha Prithul. All rights reserved.
//

#include "Vertex.hpp"

namespace Pringine {
            
    Vertex::Vertex()
    {
    }
    
    Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    
    Vertex::Vertex(Vector3<float> position)
    {
        data[0] = position.x;
        data[1] = position.y;
        data[2] = position.z;
    }
}
