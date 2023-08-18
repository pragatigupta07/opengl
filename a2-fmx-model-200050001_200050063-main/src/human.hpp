#ifndef _HUMAN_HPP_
#define _HUMAN_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "hierarchy_node.hpp"

#define NUM_VERTICES 36

class Human
{
    const float window_length_div = 8;  //resize human

    csX75::HNode *root_node;
    csX75::HNode *curr_node;

    csX75::HNode *torso1;
    csX75::HNode *torso2;
    csX75::HNode *torso3;
    csX75::HNode *head, *neck;
    csX75::HNode *shouldL, *shouldR;
    csX75::HNode *uArmL, *uArmR, *thighL, *thighR;
    csX75::HNode *elbowL, *elbowR, *lKnee, *rKnee;
    csX75::HNode *wristL, *wristR, *ankelL, *ankelR;
    csX75::HNode *handL, *handR, *footL, *footR;
    csX75::HNode *hipL, *hipR;
    csX75::HNode *lArmL, *lArmR, *legL, *legR;

    // cubified model for head and torso2 in the hierarchy;
    glm::vec4 cube_type1[8] = {
        glm::vec4(-3.0 / window_length_div, -3.0 / window_length_div, 3.0 / window_length_div, 1.0),
        glm::vec4(-3.0 / window_length_div, 3.0 / window_length_div, 3.0 / window_length_div, 1.0),
        glm::vec4(3.0 / window_length_div, 3.0 / window_length_div, 3.0 / window_length_div, 1.0),
        glm::vec4(3.0 / window_length_div, -3.0 / window_length_div, 3.0 / window_length_div, 1.0),
        glm::vec4(-3.0 / window_length_div, -3.0 / window_length_div, -3.0 / window_length_div, 1.0),
        glm::vec4(-3.0 / window_length_div, 3.0 / window_length_div, -3.0 / window_length_div, 1.0),
        glm::vec4(3.0 / window_length_div, 3.0 / window_length_div, -3.0 / window_length_div, 1.0),
        glm::vec4(3.0 / window_length_div, -3.0 / window_length_div, -3.0 / window_length_div, 1.0)};

    // cube to model joints
    glm::vec4 cube_type2[8] = {
        glm::vec4(-1.0 / window_length_div, -1.0 / window_length_div, 1.0 / window_length_div, 1.0),
        glm::vec4(-1.0 / window_length_div, 1.0 / window_length_div, 1.0 / window_length_div, 1.0),
        glm::vec4(1.0 / window_length_div, 1.0 / window_length_div, 1.0 / window_length_div, 1.0),
        glm::vec4(1.0 / window_length_div, -1.0 / window_length_div, 1.0 / window_length_div, 1.0),
        glm::vec4(-1.0 / window_length_div, -1.0 / window_length_div, -1.0 / window_length_div, 1.0),
        glm::vec4(-1.0 / window_length_div, 1.0 / window_length_div, -1.0 / window_length_div, 1.0),
        glm::vec4(1.0 / window_length_div, 1.0 / window_length_div, -1.0 / window_length_div, 1.0),
        glm::vec4(1.0 / window_length_div, -1.0 / window_length_div, -1.0 / window_length_div, 1.0)};

    // cubified model for torso1 and torso3 in hierarchy
    glm::vec4 cube_type3[8] = {
        glm::vec4(-3.5 / window_length_div, -3.5 / window_length_div, 3.5 / window_length_div, 1.0),
        glm::vec4(-3.5 / window_length_div, 3.5 / window_length_div, 3.5 / window_length_div, 1.0),
        glm::vec4(3.5 / window_length_div, 3.5 / window_length_div, 3.5 / window_length_div, 1.0),
        glm::vec4(3.5 / window_length_div, -3.5 / window_length_div, 3.5 / window_length_div, 1.0),
        glm::vec4(-3.5 / window_length_div, -3.5 / window_length_div, -3.5 / window_length_div, 1.0),
        glm::vec4(-3.5 / window_length_div, 3.5 / window_length_div, -3.5 / window_length_div, 1.0),
        glm::vec4(3.5 / window_length_div, 3.5 / window_length_div, -3.5 / window_length_div, 1.0),
        glm::vec4(3.5 / window_length_div, -3.5 / window_length_div, -3.5 / window_length_div, 1.0)};

    // cubified model for arms and legs in the hierarchy
    glm::vec4 cube_type4[8] = {
        glm::vec4(-1.5 / window_length_div, -4.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, 4.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, 4.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, -4.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, -4.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, 4.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, 4.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, -4.0 / window_length_div, -1.5 / window_length_div, 1.0)};

    // cubified model for hand and leg in the hierarchy
    glm::vec4 cube_type5[8] = {
        glm::vec4(-1.5 / window_length_div, -2.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, 2.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, 2.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, -2.0 / window_length_div, 1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, -2.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(-1.5 / window_length_div, 2.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, 2.0 / window_length_div, -1.5 / window_length_div, 1.0),
        glm::vec4(1.5 / window_length_div, -2.0 / window_length_div, -1.5 / window_length_div, 1.0)};

    // red upper_cloth
    glm::vec4 colors_shirt[8] = {
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0)};

    // blue lower_cloth
    glm::vec4 colors_trouser[8] = {
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0)};

    // body color
    glm::vec4 colors_body[8] = {
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0),
        glm::vec4(224.0 / 255, 172.0 / 255, 105.0 / 255, 1.0)};

    int tri_idx = 0;
    glm::vec4 v_positions1[NUM_VERTICES];
    glm::vec4 v_positions2[NUM_VERTICES];
    glm::vec4 v_positions3[NUM_VERTICES];
    glm::vec4 v_positions4[NUM_VERTICES];
    glm::vec4 v_positions5[NUM_VERTICES];
    glm::vec4 v_colors1[NUM_VERTICES];
    glm::vec4 v_colors2[NUM_VERTICES];
    glm::vec4 v_colors3[NUM_VERTICES];

public:
    Human();
    void quad(int a, int b, int c, int d, glm::vec4 *positions, glm::vec4 *v_positions);
    void colorcube(glm::vec4 *positions, glm::vec4 *v_positions);
    void cubes_init(void);
    void renderHuman(void);
    void ch_currnode(int);
    void translate(int);
    void rotate(int);
    ~Human();
};

#endif