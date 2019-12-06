#ifndef COMPONENET_HPP
#define COMPONENET_HPP


namespace Pringine
{

    enum ComponentType
    {
        COMP_UNKNOWN,
        COMP_TRANSFORM,
        COMP_TRANSFORM_3D,
        COMP_GRAPHICS,
        COMP_GRAPHICS_3D,
        COMP_COUNT_MAX
    };


    class Component
    {
    private:
        /* data */
    public:
        Component(ComponentType type);
        virtual ~Component();
        
        const ComponentType type;
    };

}













#endif