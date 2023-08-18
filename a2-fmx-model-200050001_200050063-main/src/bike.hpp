#ifndef _BIKE_HPP_
#define _BIKE_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "hierarchy_node.hpp"

#define NUM_VERTICES 36

class Bike
{
    const int radius1 = 6, radius2 = 6.5;
    const int resize = 8;   //used to resize cycle size
    static const int theta_part = 20;
    const double d_theta = 60 * M_PI / theta_part;
    const double theta = 2 * M_PI / theta_part;
    const int a = 1.5, b = 2;

    csX75::HNode* root_node;
    csX75::HNode* curr_node;

    csX75::HNode* front_wsupp;
    csX75::HNode* handle;
    csX75::HNode* engine1, *engine2;
    csX75::HNode* seat;
    csX75::HNode* back_wsupp;
    csX75::HNode* centre_node1;
    csX75::HNode* spike_node1[theta_part];
    csX75::HNode* part_node1[theta_part*2];
    csX75::HNode* centre_node2;
    csX75::HNode* spike_node2[theta_part];
    csX75::HNode* part_node2[theta_part*2];

    glm::vec4 centre_w[8] = {
        glm::vec4(-1.0 / resize, -1.0 / resize, 2.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, 1.0 / resize, 2.0 / resize, 1.0),
        glm::vec4(1.0 / resize, 1.0 / resize, 2.0 / resize, 1.0),
        glm::vec4(1.0 / resize, -1.0 / resize, 2.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, -1.0 / resize, -2.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, 1.0 / resize, -2.0 / resize, 1.0),
        glm::vec4(1.0 / resize, 1.0 / resize, -2.0 / resize, 1.0),
        glm::vec4(1.0 / resize, -1.0 / resize, -2.0 / resize, 1.0)};

    glm::vec4 spike_w[8] = {
        glm::vec4(-2.0 * radius1 / resize, -0.1 / resize, 0.5 / resize, 1.0),
        glm::vec4(-2.0 * radius1 / resize, 0.1 / resize, 0.5 / resize, 1.0),
        glm::vec4(2.0 * radius1 / resize, 0.1 / resize, 0.5 / resize, 1.0),
        glm::vec4(2.0 * radius1 / resize, -0.1 / resize, 0.5 / resize, 1.0),
        glm::vec4(-2.0 * radius1 / resize, -0.1 / resize, -0.5 / resize, 1.0),
        glm::vec4(-2.0 * radius1 / resize, 0.1 / resize, -0.5 / resize, 1.0),
        glm::vec4(2.0 * radius1 / resize, 0.1 / resize, -0.5 / resize, 1.0),
        glm::vec4(2.0 * radius1 / resize, -0.1 / resize, -0.5 / resize, 1.0)};

    glm::vec4 part_w[8] = {
        glm::vec4(-2.0 / resize, -a *cos(theta / 2) / resize, 2.0 / resize, 1.0),
        glm::vec4(-2.0 / resize, a *cos(theta / 2) / resize, 2.0 / resize, 1.0),
        glm::vec4(2.0 / resize, b *cos(theta / 2) / resize, 2.0 / resize, 1.0),
        glm::vec4(2.0 / resize, -b *cos(theta / 2) / resize, 2.0 / resize, 1.0),
        glm::vec4(-2.0 / resize, -a *cos(theta / 2) / resize, -2.0 / resize, 1.0),
        glm::vec4(-2.0 / resize, a *cos(theta / 2) / resize, -2.0 / resize, 1.0),
        glm::vec4(2.0 / resize, b *cos(theta / 2) / resize, -2.0 / resize, 1.0),
        glm::vec4(2.0 / resize, -b *cos(theta / 2) / resize, -2.0 / resize, 1.0)};

    // front wheel support of 12 length
    double fws = 12.0;
    glm::vec4 front_ws[8] = {
        glm::vec4(-1.0 / resize, -fws / resize, 3.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, fws / resize, 3.0 / resize, 1.0),
        glm::vec4(1.0 / resize, fws / resize, 3.0 / resize, 1.0),
        glm::vec4(1.0 / resize, -fws / resize, 3.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, -fws / resize, -3.0 / resize, 1.0),
        glm::vec4(-1.0 / resize, fws / resize, -3.0 / resize, 1.0),
        glm::vec4(1.0 / resize, fws / resize, -3.0 / resize, 1.0),
        glm::vec4(1.0 / resize, -fws / resize, -3.0 / resize, 1.0)};

    // back wheel support of 9 length
    double bws = 10.0;
    glm::vec4 back_ws[8] = {
        glm::vec4(-bws / resize, -1.0 / resize, 2.5 / resize, 1.0),
        glm::vec4(-bws / resize, 1.0 / resize, 2.5 / resize, 1.0),
        glm::vec4(bws / resize, 1.0 / resize, 2.5 / resize, 1.0),
        glm::vec4(bws / resize, -1.0 / resize, 2.5 / resize, 1.0),
        glm::vec4(-bws / resize, -1.0 / resize, -2.5 / resize, 1.0),
        glm::vec4(-bws / resize, 1.0 / resize, -2.5 / resize, 1.0),
        glm::vec4(bws / resize, 1.0 / resize, -2.5 / resize, 1.0),
        glm::vec4(bws / resize, -1.0 / resize, -2.5 / resize, 1.0)};

    // handle
    double hl = 10.0;
    glm::vec4 handle_p[8] = {
        glm::vec4(-1.0 / resize, -1.0 / resize, hl / resize, 1.0),
        glm::vec4(-1.0 / resize, 1.0 / resize, hl / resize, 1.0),
        glm::vec4(1.0 / resize, 1.0 / resize, hl / resize, 1.0),
        glm::vec4(1.0 / resize, -1.0 / resize, hl / resize, 1.0),
        glm::vec4(-1.0 / resize, -1.0 / resize, -hl / resize, 1.0),
        glm::vec4(-1.0 / resize, 1.0 / resize, -hl / resize, 1.0),
        glm::vec4(1.0 / resize, 1.0 / resize, -hl / resize, 1.0),
        glm::vec4(1.0 / resize, -1.0 / resize, -hl / resize, 1.0)};

    // seat
    double width = 3.0, height = 1.0, length = 12.0;
    glm::vec4 seat_p[8] = {
        glm::vec4(-length / resize, -height / resize, width / resize, 1.0),
        glm::vec4(-length / resize, height / resize, width / resize, 1.0),
        glm::vec4(length / resize, height / resize, width / resize, 1.0),
        glm::vec4(length / resize, -height / resize, width / resize, 1.0),
        glm::vec4(-length / resize, -height / resize, -width / resize, 1.0),
        glm::vec4(-length / resize, height / resize, -width / resize, 1.0),
        glm::vec4(length / resize, height / resize, -width / resize, 1.0),
        glm::vec4(length / resize, -height / resize, -width / resize, 1.0)};

    // engine1
    double rear = 10, up = 3.0, down = 8.5;
    glm::vec4 en1[8] = {
        glm::vec4(-rear / resize, -down / resize, width / resize, 1.0),
        glm::vec4(-rear / resize, up / resize, width / resize, 1.0),
        glm::vec4(rear / resize, up / resize, width / resize, 1.0),
        glm::vec4(rear / resize, 0.0, width / resize, 1.0),
        glm::vec4(-rear / resize, -down / resize, -width / resize, 1.0),
        glm::vec4(-rear / resize, up / resize, -width / resize, 1.0),
        glm::vec4(rear / resize, up / resize, -width / resize, 1.0),
        glm::vec4(rear / resize, 0.0, -width / resize, 1.0)};

    // engine2
    //  double adj_seat = 8.0, adj_en = 6.0;
    //  glm::vec4 en2[8] = {
    //    glm::vec4(-rear/resize, -down/resize, width/resize, 1.0),
    //    glm::vec4(-rear/resize, up/resize, width/resize, 1.0),
    //    glm::vec4(rear/resize, up/resize, width/resize, 1.0),
    //    glm::vec4(rear/resize, 0.0, width/resize, 1.0),
    //    glm::vec4(-rear/resize, -down/resize, -width/resize, 1.0),
    //    glm::vec4(-rear/resize, up/resize, -width/resize, 1.0),
    //    glm::vec4(rear/resize, up/resize, -width/resize, 1.0),
    //    glm::vec4(rear/resize, 0.0, -width/resize, 1.0)
    //  };

    // white wheel
    glm::vec4 colors_w[8] = {
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0),
        glm::vec4(1.0, 1.0, 1.0, 1.0)};

    // red supports
    glm::vec4 colors_supp[8] = {
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(1.0, 0.0, 0.0, 1.0)};

    // blue engine
    glm::vec4 colors_en[8] = {
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0)};

    // green seat
    glm::vec4 colors_seat[8] = {
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 0.0, 1.0)};

    int tri_idx = 0;
    glm::vec4 v_positions1[NUM_VERTICES];
    glm::vec4 v_positions2[NUM_VERTICES];
    glm::vec4 v_positions3[NUM_VERTICES];
    glm::vec4 v_positionsf[NUM_VERTICES];
    glm::vec4 v_positionsb[NUM_VERTICES];
    glm::vec4 v_positionse1[NUM_VERTICES];
    // glm::vec4 v_positionse2[NUM_VERTICES];
    glm::vec4 v_positionsh[NUM_VERTICES];
    glm::vec4 v_positionst[NUM_VERTICES];
    glm::vec4 v_colors_w[NUM_VERTICES];
    glm::vec4 v_colors_supp[NUM_VERTICES];
    glm::vec4 v_colors_en[NUM_VERTICES];
    glm::vec4 v_colors_seat[NUM_VERTICES];

    public:
    Bike();
    void quad(int a, int b, int c, int d, glm::vec4 *positions, glm::vec4 *v_positions);
    void colorcube(glm::vec4 *positions, glm::vec4 *v_positions);
    void cubes_init(void);
    void renderBike(void);
    void translate(int x);
    void f_rotate(int l);
    // void ch_currnode(bool);
    ~Bike();
};

#endif