#include "particlesystem.h"

particle_system::~particle_system()
{   if(inited)
    {   glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &particle_buffer);
    }
}

void particle_system::init(GLint position_location)
{   generate_particles();
    glGenBuffers(1, &particle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle_buffer);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec3),
                 particles.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, particle_buffer);
    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(position_location, 3, GL_FLOAT, false, sizeof(particle), 0);
    inited = true;
}

void particle_system::compute()
{   glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, particle_buffer);
    glDispatchCompute(particle_count / 32, 1, 1);
}

void particle_system::draw()
{   glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, particle_count);
}

static inline float rand_float(float min, float max)
{   return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

void particle_system::generate_particles()
{   for(int i = 0; i < particle_count; i++)
    {
        glm::vec3 pos(rand_float(-(w/2), w/2),
                      rand_float(-(h/2), h/2),
                      rand_float(-(d/2), d/2));
        glm::vec3 vel(rand_float(-10.f, 10.f),
                      rand_float(-10.f, 10.f),
                      rand_float(-10.f, 10.f));
        particles.push_back({pos, vel});
    }
}
