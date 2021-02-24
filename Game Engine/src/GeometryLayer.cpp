#include "GeometryLayer.hpp"
#include "RendererOpenGL.hpp"

namespace PrEngine
{

    GeometryLayer::GeometryLayer(long camera_handle, const int& _sw, const int& _sh):screen_width(_sw),screen_height(_sh)
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

        DirectionalLight* light = (DirectionalLight*)(((Entity*)entity_management_system->get_entity_with_component(COMP_LIGHT))->components[COMP_LIGHT]);
        glViewport(0,0,screen_width, screen_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //GL_CALL(glViewport(0,0,screen_width, screen_height))
        //GL_CALL(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT))
        //glBindFramebuffer(0);
        for(std::vector<DirectionalLight*>::iterator l_it = RendererOpenGL::lights_list.begin(); l_it != RendererOpenGL::lights_list.end(); l_it++)
        {
            
            // binding shadow map to slot 3 for now
            GL_CALL(
                glActiveTexture(GL_TEXTURE0+2)
            )
            GL_CALL(
                glBindTexture(GL_TEXTURE_2D, (*l_it)->shadow_map_texture)
            )

            for(std::vector<Graphics*>::iterator it = RendererOpenGL::graphics_list.begin(); it != RendererOpenGL::graphics_list.end(); it++ )
            {
                
                Graphics* grp = (*it);
                //Matrix4x4<float> mvp = (projection) * (*(grp->model)) ;
                
                for(int i=0; i < grp->elements.size(); i++)
                {
                    grp->elements[i].material->Bind();

                    //std::cout<<"before: "<<grp->elements[i].material.uniform_locations["u_MVP"]  <<std::endl;
                    
                    std::unordered_map<std::string, std::pair<std::string,GLuint>>& m = grp->elements[i].material->shader_program.uniform_locations;
                    

                    for( std::unordered_map<std::string, std::pair<std::string,GLuint>>::iterator it = m.begin(); it!=m.end(); it++)
                    {

                        if(it->first == "u_shadowmap")
                        {
                            GL_CALL(
                                glUniform1i(it->second.second, 2)
                            )
                        }

                        if(it->first == "u_Light_MVP")
                        {
                            Matrix4x4<float> light_mvp = (*l_it)->projection * (*(*l_it)->view) * (*grp->model);
                            GL_CALL(
                                glUniformMatrix4fv(it->second.second, 1, GL_TRUE, light_mvp.data)
                            )
                        }

                        if( it->first == "u_sampler2d")
                        {
                            GL_CALL(
                                glUniform1i(it->second.second, 0))
                        }


                        if(it->first == "u_env_map")
                        {
                            GL_CALL(
                                glUniform1i(it->second.second, 1))
                        }

                        if(it->first == "u_Dir_Light")
                        {

                            Vector3<float> dir = ((Transform3D*)(entity_management_system->get_entity_with_component(COMP_LIGHT)->components[COMP_TRANSFORM_3D]))->get_forward(); // must change
                            GL_CALL(
                                glUniform3f(it->second.second, dir.x, dir.y, dir.z))
                        }

                        if(it->first == "u_Pos_Light")
                        {

                            Vector3<float> pos = ((Transform3D*)(entity_management_system->get_entity_with_component(COMP_LIGHT)->components[COMP_TRANSFORM_3D]))->get_position(); // must change
                            GL_CALL(
                                glUniform3f(it->second.second, pos.x, pos.y, pos.z))
                        }

                        if(it->first == "u_Ambient_Strength")
                        {
                            //LOG(LOGTYPE_ERROR, "Dir: ", std::to_string(light->direction.x));
                            GL_CALL(
                                glUniform1f(it->second.second, (*l_it)->ambient)
                            )
                        }

                        if(it->first == "u_Specular_Strength")
                        {
                            GL_CALL(
                                glUniform1f(it->second.second, (*l_it)->specular)
                            )
                        }
                        // models and normals should be same size
                        //for(int j=0; j<grp->models.size() ; j++) 
                        //{

                        Camera* cam_component = (Camera*)(camera->components[COMP_CAMERA]);
                        //Matrix4x4<float> mvp = (cam_component->projection_matrix) * cam_component->view_matrix * (*(grp->models[j])) ;
                        

                        if(it->first == "u_skybox")
                        {
                            GL_CALL(glUniform1i(it->second.second, 0))
                            //mvp = (cam_component->projection_matrix) * _view * (*(grp->models[j])) ;

                        }

                        if(it->first == "u_Model")
                        {
                            GL_CALL(
                                glUniformMatrix4fv(it->second.second,1, GL_TRUE, (*(grp->model)).data))
                        }

                        if(it->first == "u_View")
                        {
                            GL_CALL(
                                glUniformMatrix4fv(it->second.second, 1, GL_TRUE, cam_component->view_matrix.data) )
                        }

                        if(it->first == "u_View_t")
                        {
                            Matrix4x4<float> _view = Matrix4x4<float>(cam_component->view_matrix);
                            _view.data[3] = 0;
                            _view.data[7] = 0;
                            _view.data[11] = 0;
                            _view.data[12] = 0;
                            _view.data[13] = 0;
                            _view.data[14] = 0;
                            _view.data[15] = 1;

                            GL_CALL(
                                glUniformMatrix4fv(it->second.second, 1, GL_TRUE, _view.data) )
                        }

                        if(it->first == "u_Projection")
                        {
                            GL_CALL(
                                glUniformMatrix4fv(it->second.second,1, GL_TRUE, (cam_component->projection_matrix).data))
                        }

                        if(it->first == "u_Camera_Position")
                        {
                            Vector3<float> cam_pos = cam_component->transform.get_position();
                            GL_CALL(
                                glUniform3f(it->second.second, cam_pos.x, cam_pos.y, cam_pos.z) )
                        }

                        if(it->first == "u_Normal_M")
                        {
                            GL_CALL(
                                glUniformMatrix4fv(it->second.second,1, GL_TRUE, grp->normal->data ))
                        }
                        
                        if(it->first =="u_Panning")
                        {
                            GL_CALL(
                                glUniform2f(it->second.second,grp->elements[0].material->panning.x, grp->elements[0].material->panning.y);
                            )
                        }

                        if(it->first =="u_Tiling")
                        {
                            GL_CALL(
                                glUniform2f(it->second.second,grp->elements[0].material->tiling.x, grp->elements[0].material->tiling.y);
                            )
                        }


                        //}

                        //grp->ibo[i].Bind();

                        //GL_CALL(
                        //    glUniform1f((*it)->material.uniform_locations["u_red"], 1.f))
                    }

                    grp->elements[i].vao.Bind();
                    grp->elements[i].ibo.Bind();
                    GL_CALL(
                        //glDrawArrays(GL_TRIANGLES,0, grp->elements[i].num_of_triangles*3))
                        glDrawElements(GL_TRIANGLES, grp->elements[i].ibo.count, GL_UNSIGNED_INT, nullptr));
                    grp->elements[i].vao.Unbind();
                    grp->elements[i].ibo.Unbind();

                    grp->elements[i].material->Unbind();
    
                    //grp->ibo[i].Unbind();
                }
            }
            
            GL_CALL(
                glActiveTexture(GL_TEXTURE0+2)
            )
            GL_CALL(
                glBindTexture(GL_TEXTURE_2D, 0)
            )
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