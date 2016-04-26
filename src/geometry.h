#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>

class geometry
{
public:
    geometry() :
        mode(GL_TRIANGLES),
        vao(0),
        vertex_buffer(0),
        index_buffer(0),
        inited(false)
    {}

    virtual ~geometry();

    void add_vertex(const glm::vec3& position, const glm::vec3& normal);
    void add_index(GLushort i);
    void add_face(GLushort a, GLushort b, GLushort c);
    void set_mode(GLenum mode);
    void init(GLint position_location, GLint normal_location);
    void draw();

    typedef struct { glm::vec3 position, normal; } vertex;

    GLuint vertex_count() const;

    const vertex& operator [] (GLuint index);

private:
    std::vector<vertex> vertices;
    std::vector<GLushort> indices;
    GLenum mode;
    GLuint vao;
    GLuint vertex_buffer;
    GLuint index_buffer;
    bool inited;
};

#endif
