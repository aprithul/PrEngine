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
                    //LOG(LOGTYPE_ERROR, "Update layer");

        Entity* camera = entity_management_system->get_entity(camera_handle);

        DirectionalLight* light = (DirectionalLight*)entity_management_system->get_entity_with_component(COMP_LIGHT);

        for(std::vector<Graphics*>::iterator it = graphics_list.begin(); it != graphics_list.end(); it++ )
        {
            Graphics* grp = (*it);
            //Matrix4x4<float> mvp = (projection) * (*(grp->model)) ;
            
            for(int i=0; i < grp->elements.size(); i++)
            {
                grp->elements[i].material.diffuse_texture->Bind(0);
                grp->elements[i].vao.Bind();
                grp->elements[i].ibo.Bind();
                

                //std::cout<<"before: "<<grp->elements[i].material.uniform_locations["u_MVP"]  <<std::endl;
                //if(grp->elements[i].material.uniform_locations["u_sampler2d"] != -1)
                //GL_CALL(
                //    glUniform1i(grp->elements[i].material.uniform_locations["u_sampler2d"], 0))
                if(grp->elements[i].material.uniform_locations["u_Dir_Light"] != -1)
                GL_CALL(
                    glUniform3f(grp->elements[i].material.uniform_locations["u_Dir_Light"], light->direction.x, light->direction.y, light->direction.z))
                
                // models and normals should be same size
                for(int j=0; j<grp->models.size() ; j++) 
                {

                    Camera* cam_component = (Camera*)(camera->components[COMP_CAMERA]);
                    Matrix4x4<float> mvp = (cam_component->projection_matrix) * cam_component->view_matrix * (*(grp->models[j])) ;

                    if(grp->elements[i].material.uniform_locations["u_MVP"] != -1)
                    GL_CALL(
                        glUniformMatrix4fv(grp->elements[i].material.uniform_locations["u_MVP"],1, GL_TRUE, mvp.data))

                    if(grp->elements[i].material.uniform_locations["u_Normal_M"] != -1)
                    GL_CALL(
                        glUniformMatrix4fv(grp->elements[i].material.uniform_locations["u_Normal_M"],1, GL_TRUE, grp->normals[j]->data ))
                    GL_CALL(
                        glUniform2f(grp->elements[i].material.uniform_locations["u_Panning"],grp->elements[i].material.panning.x, grp->elements[i].material.panning.y);
                    )
                    GL_CALL(
                        glUniform2f(grp->elements[i].material.uniform_locations["u_Tiling"],grp->elements[i].material.tiling.x, grp->elements[i].material.tiling.y);
                    )
                
                    GL_CALL(
                    //glDrawArrays(GL_TRIANGLES,0, grp->elements[i].num_of_triangles*3))
                    glDrawElements(GL_TRIANGLES, grp->elements[i].ibo.count, GL_UNSIGNED_INT, nullptr));
                
                }

                //grp->ibo[i].Bind();

                //GL_CALL(
                //    glUniform1f((*it)->material.uniform_locations["u_red"], 1.f))
               
                
                grp->elements[i].ibo.Unbind();
                grp->elements[i].vao.Unbind();
                //grp->ibo[i].Unbind();
            }
        }
    }

    void GeometryLayer::end()
    {

    }

}