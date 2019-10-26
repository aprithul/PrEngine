#ifndef EDITOR_MODULE_HPP
#define EDITOR_MODULE_HPP

#include "Module.hpp"
#include "GUI.hpp"
#include "RendererModule.hpp"
#include <string>

namespace Pringine
{
    class Editor : public Module
    {
        public:
            Editor(std::string name, int priority, Renderer2D* renderer);
            ~Editor();

            void start() override;
            void update() override;
            void end() override;

        private:
            Renderer2D* renderer;
    };

}

#endif