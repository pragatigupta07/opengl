#include "cube.hpp"

Cube::Cube(){
    int n=0;
    int x = 0, y=0, z=0; 
    positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
    positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z)/(1.0 * GRID_SZ), 1.0);
    for(int i=0; i<NUM_VERTICES; i++){
        v_colors[i] = glm::vec4(0.0, 1.0, 0.0, 1.0);
    }
    colorcube();
}

void Cube::quad(int a, int b, int c, int d){
    v_positions[tri_idx] = positions[a]; tri_idx++;
    v_positions[tri_idx] = positions[b]; tri_idx++;
    v_positions[tri_idx] = positions[c]; tri_idx++;
    v_positions[tri_idx] = positions[a]; tri_idx++;
    v_positions[tri_idx] = positions[c]; tri_idx++;
    v_positions[tri_idx] = positions[d]; tri_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void Cube::colorcube(){
    tri_idx = 0;
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

void Cube::initBufferShaderGl(){
    std::string vertex_shader_file("cube_vs.glsl");
    std::string fragment_shader_file("cube_fs.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram(shaderProgram);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );

    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions)) );
}

void Cube::renderCube(){
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    // glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
}

Cube::~Cube(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}

//fixed color green