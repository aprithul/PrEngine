#include "GeometryLayer.hpp"

namespace PrEngine
{

    GeometryLayer::GeometryLayer(long camera_handle)
    {
        this->camera_handle = camera_handle;
        this->name = "Geometry";
    }

    void GeometryLayer::start()
    {
    }

    void GeometryLayer::update()
    {

        Entity* camera = entity_management_system->get_entity(camera_handle);

        DirectionalLight* light = (DirectionalLight*)entity_management_system->get_entity_with_component(COMP_LIGHT);

        for(std::vector<Graphics*>::iterator it = graphics_list.begin(); it != graphics_list.end(); it++ )
        {
            Graphics* grp = (*it);
            //Matrix4x4<float> mvp = (projection) * (*(grp->model)) ;
            
            for(int i=0; i < grp->elements.size(); i++)
            {
                grp->elements[i].material->Bind();
                grp->elements[i].vao.Bind();
                grp->elements[i].ibo.Bind();
                

                //std::cout<<"before: "<<grp->elements[i].material.uniform_locations["u_MVP"]  <<std::endl;
                
                std::unordered_map<std::string, GLint>& m = grp->elements[i].material->uniform_locations;
                if(m.find("u_sampler2d") != m.end())
                {
                    GL_CALL(
                        glUniform1i(m["u_sampler2d"], 0))
                }

                if(m.find("u_env_map") != m.end())
                {
                    GL_CALL(
                        glUniform1i(m["u_env_map"], 1))
                }

                if(m.find("u_sampler_cube") != m.end())
                {
                    GL_CALL(
                        glUniform1i(m["u_sampler_cube"], 0))
                }
                    
                if(m.find("u_Dir_Light") != m.end())
                {
                    GL_CALL(
                        glUniform3f(m["u_Dir_Light"], light->direction.x, light->direction.y, light->direction.z))
                }

                // models and normals should be same size
                for(int j=0; j<grp->models.size() ; j++) 
                {

                    Camera* cam_component = (Camera*)(camera->components[COMP_CAMERA]);
                    Matrix4x4<float> mvp = (cam_component->projection_matrix) * cam_component->view_matrix * (*(grp->models[j])) ;
                    
                    if(m.find("u_sampler_cube") != m.end())
                    {
                        Matrix4x4<float> _view = Matrix4x4<float>(cam_component->view_matrix);
                        _view.data[3] = 0;
                        _view.data[7] = 0;
                        _view.data[11] = 0;
                        _view.data[12] = 0;
                        _view.data[13] = 0;
                        _view.data[14] = 0;
                        _view.data[15] = 1;
                        mvp = (cam_component->projection_matrix) * _view * (*(grp->models[j])) ;

                        if(m.find("u_MVP") != m.end())
                        {
                            GL_CALL(
                                glUniformMatrix4fv(m["u_MVP"],1, GL_TRUE, mvp.data))
                        }
                    }

                    if(m.find("u_Model") != m.end())
                    {
                        GL_CALL(
                            glUniformMatrix4fv(m["u_Model"],1, GL_TRUE, (*(grp->models[j])).data))
                    }
                    if(m.find("u_View") != m.end())
                    {
                        GL_CALL(
                            glUniformMatrix4fv(m["u_View"],1, GL_TRUE, (cam_component->view_matrix).data) )
                    }
                    if(m.find("u_Projection") != m.end())
                    {
                        GL_CALL(
                            glUniformMatrix4fv(m["u_Projection"],1, GL_TRUE, (cam_component->projection_matrix).data))
                    }

                    if(m.find("u_Camera_Position") != m.end())
                    {
                        Vector3<float> cam_pos = cam_component->transform.get_position();
                        GL_CALL(
                            glUniform3f(m["u_Camera_Position"], cam_pos.x, cam_pos.y, cam_pos.z) )
                    }

                    if(m.find("u_Normal_M") != m.end())
                    {
                        GL_CALL(
                            glUniformMatrix4fv(m["u_Normal_M"],1, GL_TRUE, grp->normals[j]->data ))
                    }
                    
                    if(m.find("u_Panning") != m.end())
                    {
                        GL_CALL(
                            glUniform2f(m["u_Panning"],grp->elements[i].material->panning.x, grp->elements[i].material->panning.y);
                        )
                    }

                    if(m.find("u_Tiling") != m.end())
                    {
                        GL_CALL(
                            glUniform2f(m["u_Tiling"],grp->elements[i].material->tiling.x, grp->elements[i].material->tiling.y);
                        )
                    }

                    GL_CALL(
                        //glDrawArrays(GL_TRIANGLES,0, grp->elements[i].num_of_triangles*3))
                        glDrawElements(GL_TRIANGLES, grp->elements[i].ibo.count, GL_UNSIGNED_INT, nullptr));
                
                }

                //grp->ibo[i].Bind();

                //GL_CALL(
                //    glUniform1f((*it)->material.uniform_locations["u_red"], 1.f))
               
                
                grp->elements[i].ibo.Unbind();
                grp->elements[i].vao.Unbind();
                grp->elements[i].material->Unbind();
                //grp->ibo[i].Unbind();
            }
        }
    }

    void GeometryLayer::end()
    {

    }

    GeometryLayer::~GeometryLayer()
    {
        LOG(LOGTYPE_GENERAL, "Deleting geometry layer");

    }

}