#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;

extern int obj;   //initially human
extern int hum_joints; //total 5, 0 for translation
extern int translate;
extern int dir;

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
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      obj = 0;
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      obj = 1; 
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      obj = 2;
    else if (obj==0 && key == GLFW_KEY_E && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        hum_joints = 7;
      else
        hum_joints = 1;
    else if (obj==0 && key == GLFW_KEY_S && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        hum_joints = 8;
      else
        hum_joints = 2;
    else if (obj==0 && key == GLFW_KEY_K && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        hum_joints = 9;
      else
        hum_joints = 4;
    else if (obj==0 && key == GLFW_KEY_H && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        hum_joints = 10;
      else
        hum_joints = 5;
    else if (obj ==0 && key == GLFW_KEY_N && action == GLFW_PRESS)
      hum_joints = 3;
    else if (obj == 0 && key == GLFW_KEY_T && action == GLFW_PRESS)
      hum_joints = 6;
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        translate = 1;
      else
        translate = 2;
    else if (obj ==1 && key == GLFW_KEY_F && action == GLFW_PRESS)
      if(mods == GLFW_MOD_SHIFT)
        dir = 1;
      else
        dir = 2;
    else if (key == GLFW_KEY_B && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_X  && action == GLFW_PRESS)
      c_zrot += 1.0;  
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      dir = 4;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      dir = 3;
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      dir = 1;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      dir = 2;
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      dir = 6;
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      dir = 5; 
  }
};  
  


