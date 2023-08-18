#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "shader_util.hpp"

#define GRID_SZ 100
#define NUM_VERTICES 36

// glm::vec4 cursor_color = glm::vec4(0.0, 1.0, 0.0, 1.0);

// enum DIRECTION {LEFT, RIGHT, UP, DOWN, FRONT, BACK};

class Cube{
    GLuint shaderProgram;
    GLuint vbo, vao;
    glm::vec4 positions[8];
    glm::vec4 v_positions[NUM_VERTICES];
    glm::vec4 v_colors[NUM_VERTICES];
    int tri_idx;

    public :

        Cube();
        void quad(int a, int b, int c, int d);
        void colorcube();
        void initBufferShaderGl();
        void renderCube();
        ~Cube();
};
#endif