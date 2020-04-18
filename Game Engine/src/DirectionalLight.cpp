#include "DirectionalLight.hpp"

namespace PrEngine
{
    DirectionalLight::DirectionalLight():Component(COMP_LIGHT)
    {
        direction = Vector3<float>(.2,.2,-0.1).normalize();
        
    }

    DirectionalLight::~DirectionalLight()
    {

    }

    void DirectionalLight::awake()
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