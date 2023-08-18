#include "human.hpp"

Human::Human()
{
    cubes_init();

    // note that the buffers are initialized in the respective constructors

    torso3 = new csX75::HNode(NULL, NUM_VERTICES, v_positions3, v_colors1, 0, sizeof(v_positions1), sizeof(v_colors1));
    torso3->change_parameters(0.0, 3.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    hipL = new csX75::HNode(torso3, NUM_VERTICES, v_positions2, v_colors2, 0, sizeof(v_positions2), sizeof(v_colors2));
    hipL->change_parameters(2.0 / window_length_div, -4.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    hipR = new csX75::HNode(torso3, NUM_VERTICES, v_positions2, v_colors2, 0, sizeof(v_positions2), sizeof(v_colors2));
    hipR->change_parameters(-2.0 / window_length_div, -4.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    torso2 = new csX75::HNode(torso3, NUM_VERTICES, v_positions1, v_colors1, 6, sizeof(v_positions2), sizeof(v_colors2));
    torso2->change_parameters(0.0, 6.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    torso1 = new csX75::HNode(torso2, NUM_VERTICES, v_positions3, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    torso1->change_parameters(0.0, 6.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    neck = new csX75::HNode(torso1, NUM_VERTICES, v_positions2, v_colors3, 3, sizeof(v_positions2), sizeof(v_colors2));
    neck->change_parameters(0.0, 4.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    shouldL = new csX75::HNode(torso1, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    shouldL->change_parameters(4.5 / window_length_div, 2.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    shouldR = new csX75::HNode(torso1, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    shouldR->change_parameters(-4.5 / window_length_div, 2.5 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    head = new csX75::HNode(neck, NUM_VERTICES, v_positions1, v_colors3, 0, sizeof(v_positions2), sizeof(v_colors2));
    head->change_parameters(0.0, 4.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    uArmL = new csX75::HNode(shouldL, NUM_VERTICES, v_positions4, v_colors1, 2, sizeof(v_positions2), sizeof(v_colors2));
    uArmL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    uArmR = new csX75::HNode(shouldR, NUM_VERTICES, v_positions4, v_colors1, 7, sizeof(v_positions2), sizeof(v_colors2));
    uArmR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    elbowL = new csX75::HNode(uArmL, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    elbowL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    elbowR = new csX75::HNode(uArmR, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    elbowR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    lArmL = new csX75::HNode(elbowL, NUM_VERTICES, v_positions4, v_colors1, 1, sizeof(v_positions2), sizeof(v_colors2));
    lArmL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    lArmR = new csX75::HNode(elbowR, NUM_VERTICES, v_positions4, v_colors1, 1, sizeof(v_positions2), sizeof(v_colors2));
    lArmR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    wristL = new csX75::HNode(lArmL, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    wristL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    wristR = new csX75::HNode(lArmR, NUM_VERTICES, v_positions2, v_colors1, 0, sizeof(v_positions2), sizeof(v_colors2));
    wristR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    handL = new csX75::HNode(wristL, NUM_VERTICES, v_positions5, v_colors3, 0, sizeof(v_positions2), sizeof(v_colors2));
    handL->change_parameters(0.0, -3.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    handR = new csX75::HNode(wristR, NUM_VERTICES, v_positions5, v_colors3, 0, sizeof(v_positions2), sizeof(v_colors2));
    handR->change_parameters(0.0, -3.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    thighL = new csX75::HNode(hipL, NUM_VERTICES, v_positions4, v_colors2, 5, sizeof(v_positions2), sizeof(v_colors2));
    thighL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    thighR = new csX75::HNode(hipR, NUM_VERTICES, v_positions4, v_colors2, 5, sizeof(v_positions2), sizeof(v_colors2));
    thighR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    lKnee = new csX75::HNode(thighL, NUM_VERTICES, v_positions2, v_colors2, 0, sizeof(v_positions2), sizeof(v_colors2));
    lKnee->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    rKnee = new csX75::HNode(thighR, NUM_VERTICES, v_positions2, v_colors2, 0, sizeof(v_positions2), sizeof(v_colors2));
    rKnee->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    legL = new csX75::HNode(lKnee, NUM_VERTICES, v_positions4, v_colors2, 4, sizeof(v_positions2), sizeof(v_colors2));
    legL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    legR = new csX75::HNode(rKnee, NUM_VERTICES, v_positions4, v_colors2, 4, sizeof(v_positions2), sizeof(v_colors2));
    legR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    ankelL = new csX75::HNode(legL, NUM_VERTICES, v_positions2, v_colors2, 1, sizeof(v_positions2), sizeof(v_colors2));
    ankelL->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    ankelR = new csX75::HNode(legR, NUM_VERTICES, v_positions2, v_colors2, 1, sizeof(v_positions2), sizeof(v_colors2));
    ankelR->change_parameters(0.0, -5.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    footL = new csX75::HNode(ankelL, NUM_VERTICES, v_positions5, v_colors3, 1, sizeof(v_positions2), sizeof(v_colors2));
    footL->change_parameters(0.0, -3.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);
    footR = new csX75::HNode(ankelR, NUM_VERTICES, v_positions5, v_colors3, 1, sizeof(v_positions2), sizeof(v_colors2));
    footR->change_parameters(0.0, -3.0 / window_length_div, 0.0, 0.0, 0.0, 0.0);

    root_node = torso3;
    curr_node = neck;
}

// quad generates two triangles for each face and assigns colors to the vertices
void Human::quad(int a, int b, int c, int d, glm::vec4 *positions, glm::vec4 *v_positions)
{
  v_positions[tri_idx] = positions[a]; tri_idx++;
  v_positions[tri_idx] = positions[b]; tri_idx++;
  v_positions[tri_idx] = positions[c]; tri_idx++;
  v_positions[tri_idx] = positions[a]; tri_idx++;
  v_positions[tri_idx] = positions[c]; tri_idx++;
  v_positions[tri_idx] = positions[d]; tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void Human::colorcube(glm::vec4 *positions, glm::vec4 *v_positions)
{
    quad( 1, 0, 3, 2, positions, v_positions);
    quad( 2, 3, 7, 6, positions, v_positions);
    quad( 3, 0, 4, 7, positions, v_positions);
    quad( 6, 5, 1, 2, positions, v_positions);
    quad( 4, 5, 6, 7, positions, v_positions);
    quad( 5, 4, 0, 1, positions, v_positions);
}

void Human::cubes_init(void){
  colorcube(cube_type1, v_positions1);
  tri_idx = 0;
  colorcube(cube_type2, v_positions2);
  tri_idx = 0;
  colorcube(cube_type3, v_positions3);
  tri_idx = 0;
  colorcube(cube_type4, v_positions4);
  tri_idx = 0;
  colorcube(cube_type5, v_positions5);
  tri_idx = 0;
  colorcube(colors_shirt, v_colors1);
  tri_idx = 0;
  colorcube(colors_trouser, v_colors2);
  tri_idx = 0;
  colorcube(colors_body, v_colors3);
}

void Human::renderHuman(void){
    root_node ->render_tree();
}

void Human::ch_currnode(int joint){
    if(joint == 1) curr_node = lArmL;
    else if(joint == 2) curr_node = uArmL;
    else if(joint == 3) curr_node = neck;
    else if(joint == 4) curr_node = lKnee;
    else if(joint == 5) curr_node = thighL;
    else if(joint == 6) curr_node = torso2;
    else if(joint == 7) curr_node = elbowR;
    else if(joint == 8) curr_node = shouldR;
    else if(joint == 9) curr_node = rKnee;
    else if(joint == 10) curr_node = thighR;
}

void Human::translate(int v){
    if(v == 1) root_node->inc_tx();
    else if(v==2) root_node->dec_tx();
}

void Human::rotate(int v){
    if(v == 1) curr_node-> inc_rx();
    else if(v == 2) curr_node->dec_rx();
    else if(v == 3) curr_node-> inc_ry();
    else if(v == 4) curr_node-> dec_ry();
    else if(v == 5) curr_node-> inc_rz();
    else if(v == 6) curr_node-> dec_rz();
}