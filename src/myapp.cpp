#include "myapp.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;

void my_app::before()
{   sdlw::shader vshader(GL_VERTEX_SHADER), fshader(GL_FRAGMENT_SHADER);
    vshader.load_src("shaders/vs.glsl");
    fshader.load_src("shaders/fs.glsl");
    program.attach(vshader);
    program.attach(fshader);
    program.link();

    sdlw::shader particle_cshader(GL_COMPUTE_SHADER),
                 particle_vshader(GL_VERTEX_SHADER),
                 particle_gshader(GL_GEOMETRY_SHADER),
                 particle_fshader(GL_FRAGMENT_SHADER);
    particle_cshader.load_src("shaders/particle_cs.glsl");
    particle_vshader.load_src("shaders/particle_vs.glsl");
    particle_gshader.load_src("shaders/particle_gs.glsl");
    particle_fshader.load_src("shaders/particle_fs.glsl");
    compute_program.attach(particle_cshader);
    compute_program.link();
    particle_draw_program.attach(particle_vshader);
    particle_draw_program.attach(particle_gshader);
    particle_draw_program.attach(particle_fshader);
    particle_draw_program.link();

    sphere_geometry = generate_sphere(5);
    sphere_geometry->init(program.attribute("vpos"), program.attribute("vnormal"));
    part_sys.init(particle_draw_program.attribute("vpos"));

    mvp_location = program.uniform("mvp");
    part_mvp_location = particle_draw_program.uniform("mvp");
    //part_current_time_location = compute_program.uniform("current_time");
    part_delta_time_location = compute_program.uniform("delta_time");

    view_matrix = glm::lookAt(vec3(0.f, 1.f, 2.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
    resize(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glPointSize(4.f);

    objects.push_back({
        vec3(-1.f, 0.f, 0.f),
        vec3(1.f, 1.f, 1.f),
        sphere_geometry.get()
    });
    objects.push_back({
        vec3(2.5f, 0.f, 0.f),
        vec3(2.f, 1.f, 1.f),
        sphere_geometry.get()
    });
}

void my_app::render(float delta)
{   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    compute_program.use();
    //glUniform1f(part_current_time_location, current_time());
    glUniform1f(part_delta_time_location, delta);
    part_sys.compute();

    particle_draw_program.use();
    glm::mat4 mvp_mat = projection_matrix * view_matrix;
    glUniformMatrix4fv(part_mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
    part_sys.draw();

    program.use();
    for(my_app::object& o : objects)
    {   glm::mat4 mvp_mat = glm::translate(glm::mat4(), o.position);
        mvp_mat = glm::scale(mvp_mat, o.scale);
        mvp_mat = projection_matrix * view_matrix * mvp_mat;
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
        o.geometry->draw();
    }
    swap_buffers();
}

void my_app::resize(int width, int height)
{   glViewport(0, 0, width, height);
    projection_matrix = glm::perspective(65.f, width/(float)height, 0.1f, 100.f);
    update_size();
}
