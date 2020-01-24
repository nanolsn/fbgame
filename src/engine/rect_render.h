#pragma once

#include <vector>
#include <GL/glew.h>
#include "rect.h"

namespace engine {
    struct rect_render {
        explicit rect_render(GLuint pos_index, GLuint st_map_index);

        ~rect_render();

        void draw(rect r) const;

    private:
        GLuint vbo_handler = 0;
        GLuint vao_handler = 0;
    };
}
