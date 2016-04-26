#ifndef _MYAPP_H_
#define _MYAPP_H_

#include <sdlw/gl_application.h>
#include "geometries.h"
#include "particlesystem.h"
#include <sdlw/program.h>

class my_app : public sdlw::gl_application
{
public:
    my_app(int argc, char** argv) :
        sdlw::gl_application(argc, argv),
        part_sys(512),
        mvp_location(-1),
        part_mvp_location(-1),
        part_current_time_location(-1),
        part_delta_time_location(-1)
    {   set_title("My Application");
        enable_window_flags(SDL_WINDOW_RESIZABLE);
        enable_window_flags(SDL_WINDOW_MAXIMIZED);
    }
    ~my_app() {}

    void before() override;
    void render(float delta) override;
    void resize(int width, int height) override;

private:
    std::shared_ptr<geometry> sphere_geometry;
    particle_system part_sys;
    sdlw::program program;
    sdlw::program compute_program;
    sdlw::program particle_draw_program;
    GLint mvp_location;
    GLint part_mvp_location;
    GLint part_current_time_location;
    GLint part_delta_time_location;

    typedef struct
    {   glm::vec3 position;
        glm::vec3 scale;
        geometry* geometry;
    } object;

    std::vector<object> objects;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;
};

#endif
