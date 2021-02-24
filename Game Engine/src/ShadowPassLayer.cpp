#include "ShadowPassLayer.hpp"
#include "RendererOpenGL.hpp"

namespace PrEngine
{

    ShadowPassLayer::ShadowPassLayer()
    {
        this->name = "Shadowpass";        
    }
    
    void ShadowPassLayer::start()
    {
        
    }

    void ShadowPassLayer::update()
    {
        
        
        Entity* camera = entity_management_system->get_entity(1);

        for(std::vector<DirectionalLight*>::iterator l_it = RendererOpenGL::lights_list.begin(); l_it != RendererOpenGL::lights_list.end(); l_it++)
        {
            (*l_it)->BindShadowmapBuffer();

            GL_CALL(glViewport(0,0,SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT))
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            GL_CALL(glClear(GL_DEPTH_BUFFER_BIT))
            glEnable(GL_DEPTH_TEST);

            for(std::vector<Graphics*>::const_iterator g_it = RendererOpenGL::graphics_list.begin(); g_it != RendererOpenGL::graphics_list.end(); g_it++ )
            {
                Graphics* g = (*g_it);


                // get uniform locations
                std::unordered_map<std::string, std::pair<std::string,GLuint>>& m = (*l_it)->light_shader.uniform_locations;


                Camera* cam_component = (Camera*)(camera->components[COMP_CAMERA]);
                // set light uniform values
                GL_CALL(glUniformMatrix4fv(m["u_Model"].second, 1, GL_TRUE, g->model->data))
                //GL_CALL(glUniformMatrix4fv(m["u_View"].second, 1, GL_TRUE, _view.data))
                auto _v = Matrix4x4<float>::identity();
                _v.set(0,3,0);
                _v.set(1,3,1);
                _v.set(2,3,-2);

                GL_CALL(glUniformMatrix4fv(m["u_View"].second, 1, GL_TRUE, (*l_it)->view->data) )//  cam_component->view_matrix.data))
                //auto _proj = Matrix4x4<float>::perspective(0.5f, 10.f, 16, 9, 45.f);
                auto _proj = Matrix4x4<float>::ortho(-8, 8, -4.5f, 4.5f, -10, 10);
                GL_CALL(glUniformMatrix4fv(m["u_Projection"].second, 1, GL_TRUE, (*l_it)->projection.data))
                //Matrix4x4<float> _proj = Matrix4x4<float>::perspective(16, 9, 0.1f, 10.f, 45.f);
                //GL_CALL(glUniformMatrix4fv(m["u_Projection"].second, 1, GL_TRUE, _proj.data))

                g->elements[0].vao.Bind();
                g->elements[0].ibo.Bind();
                //render to depth buffer
                GL_CALL(glDrawElements(GL_TRIANGLES, g->elements[0].ibo.count, GL_UNSIGNED_INT, nullptr))
                
                g->elements[0].vao.Unbind();
                g->elements[0].ibo.Unbind();
            }
            (*l_it)->UnbindShadowmapBuffer();
        }

    }

    void ShadowPassLayer::end()
    {

    }

    ShadowPassLayer::~ShadowPassLayer()
    {
        LOG(LOGTYPE_GENERAL, "Deleting ShadowPass layer");

    }

}