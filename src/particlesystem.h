#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>

class particle_system
{
public:
    particle_system(int particle_count = 512) :
        particle_count(particle_count),
        w(4.f), h(4.f), d(4.f),
        vao(0),
        particle_buffer(0),
        inited(false)
    {   srand(time(NULL));
    }

    virtual ~particle_system();

    void init(GLint position_location);
    void compute();
    void draw();

private:
    typedef struct
    {   glm::vec3 pos;
        glm::vec3 vel;
    } particle;

    int particle_count;
    float w, h, d;
    std::vector<particle> particles;
    GLuint vao;
    GLuint particle_buffer;
    bool inited;

    void generate_particles();

};

#endif
