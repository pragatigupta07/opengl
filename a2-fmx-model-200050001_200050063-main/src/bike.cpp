#include "bike.hpp"

Bike::Bike(){
  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  cubes_init();

  //note that the buffers are initialized in the respective constructors

  front_wsupp = new csX75::HNode(NULL,NUM_VERTICES,v_positionsf,v_colors_supp,0,sizeof(v_positions1),sizeof(v_colors_w));
  front_wsupp->change_parameters(4.0-fws*sin(M_PI/22)/resize, -1.0 + fws*cos(M_PI/22)/resize, 0.0, 0.0, 0.0, 8.0); //hardcoded rz

  centre_node2 = new csX75::HNode(front_wsupp,NUM_VERTICES,v_positions1,v_colors_w,0,sizeof(v_positions1),sizeof(v_colors_w));
  for(int i = 0; i<theta_part; i++){
    spike_node2[i] = new csX75::HNode(centre_node2, NUM_VERTICES,v_positions2,v_colors_w,0,sizeof(v_positions2),sizeof(v_colors_w));
    part_node2[i] = new csX75::HNode(spike_node2[i], NUM_VERTICES,v_positions3,v_colors_w,0,sizeof(v_positions3),sizeof(v_colors_w));
    part_node2[i]->change_parameters(1.0*(radius1 + radius2)/resize,0.0,0.0,0.0,0.0,0.0);
    part_node2[i+theta_part] = new csX75::HNode(spike_node2[i], NUM_VERTICES,v_positions3,v_colors_w,0,sizeof(v_positions3),sizeof(v_colors_w));
    part_node2[i+theta_part]->change_parameters(-1.0*(radius1 + radius2)/resize,0.0,0.0,0.0,0.0,M_PI);
    spike_node2[i]->change_parameters(0.0,0.0,0.0,0.0,0.0,i*d_theta);
  }
  centre_node2->change_parameters(fws*sin(M_PI/22)/resize-0.35, -fws*cos(M_PI/22)/resize, 0.0, 0.0, 0.0, 0.0);

  handle = new csX75::HNode(front_wsupp,NUM_VERTICES,v_positionsh,v_colors_seat,0,sizeof(v_positions1),sizeof(v_colors_w));
  handle->change_parameters(-fws*sin(M_PI/22)/resize+0.35, fws*cos(M_PI/22)/resize, 0.0, 0.0, 0.0, 0.0);

  engine1 = new csX75::HNode(front_wsupp,NUM_VERTICES,v_positionse1,v_colors_en,0,sizeof(v_positions1),sizeof(v_colors_w));
  engine1->change_parameters(-fws*sin(M_PI/22)/resize+0.35-rear*cos(M_PI/22)/resize, 5*cos(M_PI/22)/resize-rear*sin(M_PI/22)/resize, 0.0, 0.0, 0.0, 0.0);
  
  seat = new csX75::HNode(engine1,NUM_VERTICES,v_positionst,v_colors_seat,0,sizeof(v_positions1),sizeof(v_colors_w));
  seat->change_parameters(-(rear+length)/resize + 0.35, 2*up/resize, 0.0, 0.0, 0.0, -20.0);
  
  back_wsupp = new csX75::HNode(engine1,NUM_VERTICES,v_positionsb,v_colors_supp,0,sizeof(v_positions1),sizeof(v_colors_w));
  back_wsupp->change_parameters(-(rear+length)/resize + 0.4, -down/resize, 0.0, 0.0, 0.0, +10.0);
  // change_parameters(bws*cos(M_PI/12)/resize, bws*sin(M_PI/12)/resize, 0.0, 0.0, 0.0, 15.0); //hardcoded rz

  centre_node1 = new csX75::HNode(back_wsupp,NUM_VERTICES,v_positions1,v_colors_w,0,sizeof(v_positions1),sizeof(v_colors_w));
  for(int i = 0; i<theta_part; i++){
    spike_node1[i] = new csX75::HNode(centre_node1, NUM_VERTICES,v_positions2,v_colors_w,0,sizeof(v_positions2),sizeof(v_colors_w));
    part_node1[i] = new csX75::HNode(spike_node1[i], NUM_VERTICES,v_positions3,v_colors_w,0,sizeof(v_positions3),sizeof(v_colors_w));
    part_node1[i]->change_parameters(1.0*(radius1 + radius2)/resize,0.0,0.0,0.0,0.0,0.0);
    part_node1[i+theta_part] = new csX75::HNode(spike_node1[i], NUM_VERTICES,v_positions3,v_colors_w,0,sizeof(v_positions3),sizeof(v_colors_w));
    part_node1[i+theta_part]->change_parameters(-1.0*(radius1 + radius2)/resize,0.0,0.0,0.0,0.0,M_PI);
    spike_node1[i]->change_parameters(0.0,0.0,0.0,0.0,0.0,i*d_theta);
  }
  centre_node1->change_parameters(-bws*cos(M_PI/18)/resize, -bws*sin(M_PI)/resize, 0.0, 0.0, 0.0, 0.0);

  root_node = front_wsupp;
  curr_node = front_wsupp;
}

void Bike::colorcube(glm::vec4 *positions, glm::vec4 *v_positions){
    quad( 1, 0, 3, 2, positions, v_positions);
    quad( 2, 3, 7, 6, positions, v_positions);
    quad( 3, 0, 4, 7, positions, v_positions);
    quad( 6, 5, 1, 2, positions, v_positions);
    quad( 4, 5, 6, 7, positions, v_positions);
    quad( 5, 4, 0, 1, positions, v_positions);
}

void Bike::quad(int a, int b, int c, int d, glm::vec4 *positions, glm::vec4 *v_positions){
    v_positions[tri_idx] = positions[a]; tri_idx++;
    v_positions[tri_idx] = positions[b]; tri_idx++;
    v_positions[tri_idx] = positions[c]; tri_idx++;
    v_positions[tri_idx] = positions[a]; tri_idx++;
    v_positions[tri_idx] = positions[c]; tri_idx++;
    v_positions[tri_idx] = positions[d]; tri_idx++;
}

void Bike::cubes_init(void){
  colorcube(centre_w, v_positions1);
  tri_idx = 0;
  colorcube(spike_w, v_positions2);
  tri_idx = 0;
  colorcube(part_w, v_positions3);
  tri_idx = 0;
  colorcube(front_ws, v_positionsf);
  tri_idx = 0;
  colorcube(back_ws, v_positionsb);
  tri_idx = 0;
  colorcube(en1, v_positionse1);
  tri_idx = 0;
  colorcube(seat_p, v_positionst);
  tri_idx = 0;
  colorcube(handle_p, v_positionsh);
  tri_idx = 0;
  colorcube(colors_en, v_colors_en);
  tri_idx = 0;
  colorcube(colors_seat, v_colors_seat);
  tri_idx = 0;
  colorcube(colors_supp, v_colors_supp);
  tri_idx = 0;
  colorcube(colors_w, v_colors_w);
}

void Bike::renderBike(void){
    root_node -> render_tree();
}

void Bike::translate(int x){
    if(x == 1){
      centre_node1->dec_rz();
      centre_node1->dec_rz();
      centre_node2->dec_rz();
      centre_node2->dec_rz();
      front_wsupp->inc_tx();
      centre_node1->dec_rz();
      centre_node1->dec_rz();
      centre_node2->dec_rz();
      centre_node2->dec_rz();
    }
    else if(x==2){
      centre_node1->inc_rz();
      centre_node1->inc_rz();
      centre_node2->inc_rz();
      centre_node2->inc_rz();
      front_wsupp->dec_tx();
      centre_node1->inc_rz();
      centre_node1->inc_rz();
      centre_node2->inc_rz();
      centre_node2->inc_rz();
    }
}

void Bike::f_rotate(int l){
    if(l == 1) {
        handle->inc_ry();
        centre_node2->inc_ry();
    }
    else if(l==2){
        handle->dec_ry();
        centre_node2->dec_ry();
    }
}

// void Bike::ch_currnode(bool trans){
//     if(trans) curr_node = front_wsupp;
//     else curr_node = centre_node2;
// }