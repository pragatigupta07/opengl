#include "grid.hpp"

Grid::Grid(){
    int n = 0;
    for(int i = 0; i <= GRID_SZ; i++){
        for(int j = 0; j <= GRID_SZ; j++){
            v_positions[n++] = glm::vec4(1.0, 1.0 - 2*i/(1.0 * GRID_SZ), -1.0 + 2*j/(1.0 * GRID_SZ), 1.0);
            v_positions[n++] = glm::vec4(-1.0, 1.0 - 2*i/(1.0 * GRID_SZ), -1.0 + 2*j/(1.0 * GRID_SZ), 1.0);
        }
    }
    for(int i = 0; i <= GRID_SZ; i++){
        for(int j = 0; j <= GRID_SZ; j++){
            v_positions[n++] = glm::vec4(1.0 - 2*i/(1.0 * GRID_SZ), -1.0 + 2*j/(1.0 * GRID_SZ), 1.0, 1.0);
            v_positions[n++] = glm::vec4(1.0 - 2*i/(1.0 * GRID_SZ), -1.0 + 2*j/(1.0 * GRID_SZ), -1.0, 1.0);
        } 
    }
    for(int i = 0; i <= GRID_SZ; i++){
        for(int j = 0; j <= GRID_SZ; j++){
            v_positions[n++] = glm::vec4(1.0 - 2*i/(1.0 * GRID_SZ), 1.0, -1.0 + 2*j/(1.0 * GRID_SZ), 1.0);
            v_positions[n++] = glm::vec4(1.0 - 2*i/(1.0 * GRID_SZ), -1.0, -1.0 + 2*j/(1.0 * GRID_SZ), 1.0);
        }
    }
}

void Grid::initBufferShaderGl(){
    std::string vertex_shader_file("grid_vs.glsl");
    std::string fragment_shader_file("grid_fs.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram(shaderProgram);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions), v_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
}

void Grid::renderGrid(){
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6*(GRID_SZ + 1)*(GRID_SZ + 1));
}

Grid::~Grid(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}