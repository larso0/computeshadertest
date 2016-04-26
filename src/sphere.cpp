#include "geometries.h"

static GLushort sub_vertex(geometry* g, GLushort a, GLushort b)
{   GLushort index = g->vertex_count();
    glm::vec3 pos = glm::normalize(glm::mix((*g)[a].position, (*g)[b].position, 0.5f));
    g->add_vertex(pos, pos);
    return index;
}

static void subdivide(geometry* g, GLushort a, GLushort b, GLushort c, int level)
{   if(level > 0)
    {   GLushort ab = sub_vertex(g, a, b);
        GLushort ac = sub_vertex(g, a, c);
        GLushort bc = sub_vertex(g, b, c);
        level--;
        subdivide(g, a, ab, ac, level);
        subdivide(g, ab, b, bc, level);
        subdivide(g, bc, c, ac, level);
        subdivide(g, ab, bc, ac, level);
    } else
    {   g->add_face(a, b, c);
    }
}

std::shared_ptr<geometry> generate_sphere(int level)
{   std::shared_ptr<geometry> g(new geometry());
    glm::vec3 va(-1.f, 0.f, 1.f), vb(1.f, 0.f, 1.f), vc(1.f, 0.f, -1.f), vd(
        -1.f, 0.f, -1.f), ve(0.f, 1.f, 0.f), vf(0.f, -1.f, 0.f);
    va = glm::normalize(va);
    vb = glm::normalize(vb);
    vc = glm::normalize(vc);
    vd = glm::normalize(vd);

    GLushort a = 0;
    g->add_vertex(va, va);
    GLushort b = 1;
    g->add_vertex(vb, vb);
    GLushort c = 2;
    g->add_vertex(vc, vc);
    GLushort d = 3;
    g->add_vertex(vd, vd);
    GLushort e = 4;
    g->add_vertex(ve, ve);
    GLushort f = 5;
    g->add_vertex(vf, vf);

    subdivide(g.get(), a, b, e, level);
    subdivide(g.get(), b, c, e, level);
    subdivide(g.get(), c, d, e, level);
    subdivide(g.get(), d, a, e, level);
    subdivide(g.get(), b, a, f, level);
    subdivide(g.get(), c, b, f, level);
    subdivide(g.get(), d, c, f, level);
    subdivide(g.get(), a, d, f, level);

    return g;
}
