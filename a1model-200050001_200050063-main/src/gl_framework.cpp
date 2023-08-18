#include "gl_framework.hpp"

extern GLfloat xrot, yrot, zrot, c_xrot, c_yrot, c_zrot;
extern bool save_model, load_model;
extern bool model_mode, fill_cell, del_cell, draw_color_ch, re_init_voxel;
extern GLint cur_pos_x, cur_pos_y, cur_pos_z;

extern int grid_sz;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      yrot -= 1.0;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      yrot += 1.0;
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      xrot -= 1.0;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      xrot += 1.0;
    else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
      zrot -= 1.0;
    else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
      zrot += 1.0;  
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_L  && action == GLFW_PRESS)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_O  && action == GLFW_PRESS)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 1.0;   
    else if (key == GLFW_KEY_P && model_mode && action == GLFW_PRESS)
      fill_cell = true;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
      del_cell = true;
    else if (key == GLFW_KEY_C && model_mode && action == GLFW_PRESS)
      draw_color_ch = true;
    else if (key == GLFW_KEY_R && model_mode && action == GLFW_PRESS)
      re_init_voxel = true;
    else if (key == GLFW_KEY_S && model_mode && action == GLFW_PRESS)
      save_model = true;
    else if (key == GLFW_KEY_K && model_mode && action == GLFW_PRESS){
      re_init_voxel = true;
      load_model = true;
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS){
      model_mode = true;
      std::cout << "Modelling Mode \n";
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS){
      model_mode = false;
      std::cout << "Inspection Mode \n";
    }
    else if (key == GLFW_KEY_X && model_mode && action == GLFW_PRESS)
      if (mods == GLFW_MOD_SHIFT)
        cur_pos_x = (cur_pos_x + 1) % grid_sz;
      else
        cur_pos_x = (cur_pos_x - 1 + grid_sz) % grid_sz;
    else if (key == GLFW_KEY_Y && model_mode && action == GLFW_PRESS)
      if (mods == GLFW_MOD_SHIFT)
        cur_pos_y = (cur_pos_y + 1) % grid_sz;
      else
        cur_pos_y = (cur_pos_y - 1 + grid_sz) % grid_sz;
    else if (key == GLFW_KEY_Z && model_mode && action == GLFW_PRESS)
      if (mods == GLFW_MOD_SHIFT)
        cur_pos_z = (cur_pos_z + 1) % grid_sz;
      else
        cur_pos_z = (cur_pos_z - 1 + grid_sz) % grid_sz;
  }
};  
  


