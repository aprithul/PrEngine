#include "DirectionalLight.hpp"

namespace Pringine
{
    DirectionalLight::DirectionalLight():Entity(ENTITY_TYPE_LIGHT)
    {
        direction = Vector3<float>(.2,.2,-0.1).normalize();
    }

    DirectionalLight::~DirectionalLight()
    {

    }

    void DirectionalLight::start()
    {

    }

    void DirectionalLight::update()
    {

    }


    void DirectionalLight::end()
    {

    }

}