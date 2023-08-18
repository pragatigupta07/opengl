#ifndef _VOXELIZED_GRID_HPP_
#define _VOXELIZED_GRID_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "shader_util.hpp"

#define NUM_VERTICES 36
#define GRID_SZ 100

class VoxelGrid{
    GLuint shaderProgram;
    GLuint vbo, vao;
    glm::vec4 positions[8 * GRID_SZ * GRID_SZ * GRID_SZ];
    glm::vec4 v_positions[NUM_VERTICES * GRID_SZ * GRID_SZ * GRID_SZ];
    glm::vec4 v_colors[NUM_VERTICES * GRID_SZ * GRID_SZ * GRID_SZ];
    int tri_idx;

    public : 
        VoxelGrid();
        void quad(int i, int j, int k, int a, int b, int c, int d, glm::vec4 color_val);
        void cube_primitive(int i, int j, int k, glm::vec4 color_val);
        void cube_initialize();
        void initBufferShaderGl();
        void re_init();
        void renderVoxel();
        void colorCell(int x, int y, int z, glm::vec4 draw_color);
        void saveModel(std::string);
        void loadModel(std::string);
        ~VoxelGrid();
};

#endif