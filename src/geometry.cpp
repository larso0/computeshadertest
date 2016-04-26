#include "geometry.h"
#include <stdexcept>

using glm::vec3;

geometry::~geometry()
{   if(inited)
    {   glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteBuffers(1, &index_buffer);
    }
}

void geometry::add_vertex(const vec3& position, const vec3& normal)
{   if(vertices.size() == 65536) throw std::out_of_range("Too many vertices (max 65536).");
    vertices.push_back({position, normal});
}

void geometry::add_index(GLushort i)
{   if(i > vertices.size()) throw std::out_of_range("Too big index.");
    indices.push_back(i);
}

void geometry::add_face(GLushort a, GLushort b, GLushort c)
{   add_index(a);
    add_index(b);
    add_index(c);
}

void geometry::set_mode(GLenum mode)
{   this->mode = mode;
}

void geometry::init(GLint position_location, GLint normal_location)
{   glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(geometry::vertex),
                 vertices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(GLushort),
                 indices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(position_location, 3, GL_FLOAT, false, sizeof(glm::vec3)*2, 0);
    glEnableVertexAttribArray(normal_location);
    glVertexAttribPointer(normal_location, 3, GL_FLOAT, false, sizeof(glm::vec3)*2, (const GLvoid*)sizeof(glm::vec3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
}

void geometry::draw()
{   glBindVertexArray(vao);
    glDrawElements(mode, indices.size(), GL_UNSIGNED_SHORT, 0);
}

GLuint geometry::vertex_count() const
{   return vertices.size();
}

const geometry::vertex& geometry::operator [] (GLuint index)
{   return vertices[index];
}
