#ifndef _GRID_HPP_
#define _GRID_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "shader_util.hpp"

#define GRID_SZ 100
#define NUM_VERTICES 36

class Grid{
    GLuint shaderProgram;
    GLuint vbo, vao;
    glm::vec4 v_positions[6*(GRID_SZ+1)*(GRID_SZ+1)];

    public:
        Grid();
        void initBufferShaderGl();
        void renderGrid();
        ~Grid();
};

#endif