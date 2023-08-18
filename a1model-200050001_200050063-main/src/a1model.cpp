#include "model_helper.hpp"

glm::mat4 rotation_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 cursor_translate_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 projection_matrix;

glm::mat4 modelviewproject_matrix;
GLuint uModelViewProjectMatrix;

int main(int argc, char **argv)
{
    //! The pointer to the GLFW window
    GLFWwindow *window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(csX75::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
        return -1;

    // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1024, 1024, "CS475/CS675 Assign1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //! Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    // Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW Init Failed : %s" << std::endl;
    }

    // Keyboard Callback
    glfwSetKeyCallback(window, csX75::key_callback);
    // Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialize GL state
    csX75::initGL();

    Grid *grid = new Grid();
    grid->initBufferShaderGl();

    Cube *cursor = new Cube();
    cursor->initBufferShaderGl();

    VoxelGrid *voxel = new VoxelGrid();
    voxel->initBufferShaderGl();

    double cur_scale = 2*1.0/(1.0 * GRID_SZ);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
        rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
        rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
        model_matrix = rotation_matrix;

        cursor_translate_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(cur_scale * cur_pos_x, cur_scale * cur_pos_y, cur_scale * cur_pos_z));

        //Creating the lookat and the up vectors for the camera
        c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
        c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
        c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

        glm::vec4 c_pos = c_rotation_matrix*glm::vec4(c_xpos,c_ypos,c_zpos, 1.0);
        glm::vec4 c_up = c_rotation_matrix*glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);

        //Creating the view matrix
        view_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

        //creating the projection matrix
        projection_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -5.0, 5.0);

        if(fill_cell){
            voxel->colorCell(cur_pos_x, cur_pos_y, cur_pos_z, glm::vec4(draw_color[0], draw_color[1], draw_color[2], 1.0));
            fill_cell = false;
        }

        if(del_cell){
            voxel->colorCell(cur_pos_x, cur_pos_y, cur_pos_z, glm::vec4(0.0, 0.0, 0.0, 0.0));
            del_cell = false;
        }

        if(draw_color_ch){
            std::cout << "please enter the color you wanna model with (R, G, B):\n";
            std::cin >> draw_color[0] >> draw_color[1] >> draw_color[2];
            draw_color_ch = false;
        }

        if(re_init_voxel){
            voxel->re_init();
            re_init_voxel = false;
        }

        if (save_model){
            std::string filename;
            std::cout << "Enter file name , store model data: \n";
            while(true){
                std::cin >> filename;
                int len = filename.length();
                if (len > 4 && filename.substr(len - 4, 4) == ".raw")
                {
                    voxel->saveModel(filename);
                    save_model = false;
                    break;
                }
                else
                    std::cout << "Please give valid name: \n";
            }
        }

        if (load_model){
            std::string filename;
            std::cout << "Enter file name , load model data: \n";
            while(true){
                std::cin >> filename;
                int len = filename.length();
                if (len > 4 && filename.substr(len - 4, 4) == ".raw")
                {
                    voxel->loadModel(filename);
                    load_model = false;
                    break;
                }
                else
                    std::cout << "Please give valid name: \n"; 
            }
        }

        // Draw
        modelviewproject_matrix = projection_matrix*view_matrix*model_matrix;
        glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));
        cursor->renderCube();
        
        modelviewproject_matrix = projection_matrix*view_matrix*model_matrix*cursor_translate_matrix;
        glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));
        grid->renderGrid();
        
        modelviewproject_matrix = projection_matrix * view_matrix * model_matrix ;
        glUniformMatrix4fv(uModelViewProjectMatrix, 1, GL_FALSE, glm::value_ptr(modelviewproject_matrix));
        voxel->renderVoxel();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}