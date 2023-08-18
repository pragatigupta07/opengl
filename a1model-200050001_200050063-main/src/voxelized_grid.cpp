#include "voxelized_grid.hpp"

VoxelGrid::VoxelGrid(){
    int n=0;
    for(int z = 0; z < GRID_SZ; z++){
        for(int y = 0; y < GRID_SZ; y++){
            for(int x = 0; x < GRID_SZ; x++){
                positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z + 1)/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*x/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*(y + 1)/(1.0 * GRID_SZ), -1.0  + 2*z/(1.0 * GRID_SZ), 1.0);
                positions[n++] = glm::vec4(-1.0 + 2*(x + 1)/(1.0 * GRID_SZ), -1.0 + 2*y/(1.0 * GRID_SZ), -1.0  + 2*(z)/(1.0 * GRID_SZ), 1.0);
            }
        }
    }
    //tri_idx = 0;
    cube_initialize();
}

void VoxelGrid::quad(int i, int j, int k, int a, int b, int c, int d, glm::vec4 color_val){
    int offset = (GRID_SZ*GRID_SZ*k + GRID_SZ*j + i)*NUM_VERTICES ; //ch
    int offset2 = (GRID_SZ*GRID_SZ*k + GRID_SZ*j + i)*8 ;
    v_positions[offset + tri_idx] = positions[offset2 + a]; v_colors[offset + tri_idx] = color_val; tri_idx++;
    v_positions[offset + tri_idx] = positions[offset2 + b]; v_colors[offset + tri_idx] = color_val; tri_idx++;
    v_positions[offset + tri_idx] = positions[offset2 + c]; v_colors[offset + tri_idx] = color_val; tri_idx++;
    v_positions[offset + tri_idx] = positions[offset2 + a]; v_colors[offset + tri_idx] = color_val; tri_idx++;
    v_positions[offset + tri_idx] = positions[offset2 + c]; v_colors[offset + tri_idx] = color_val; tri_idx++;
    v_positions[offset + tri_idx] = positions[offset2 + d]; v_colors[offset + tri_idx] = color_val; tri_idx++;
}

void VoxelGrid::cube_primitive(int i, int j, int k, glm::vec4 color_val){
    quad(i, j, k, 1, 0, 3, 2, color_val);
    quad(i, j, k, 2, 3, 7, 6, color_val);
    quad(i, j, k, 3, 0, 4, 7, color_val);
    quad(i, j, k, 6, 5, 1, 2, color_val);
    quad(i, j, k, 4, 5, 6, 7, color_val);
    quad(i, j, k, 5, 4, 0, 1, color_val);
}

void VoxelGrid::cube_initialize(){
    for(int k = 0; k < GRID_SZ; k++){
        for(int j = 0; j < GRID_SZ; j++){
            for(int i = 0; i < GRID_SZ; i++){
                tri_idx = 0;
                cube_primitive(i, j, k, glm::vec4(0.0, 0.0, 0.0, 0.0));
            }
        }
    }
}

void VoxelGrid::initBufferShaderGl(){
    std::string vertex_shader_file("voxel_vs.glsl");
    std::string fragment_shader_file("voxel_fs.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram(shaderProgram);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor");

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors), NULL, GL_STATIC_DRAW); //potential change
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );


    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(v_positions)) );

}

void VoxelGrid::re_init(){
    for(int i=0; i<NUM_VERTICES*GRID_SZ*GRID_SZ*GRID_SZ; i++){
        v_colors[i] = glm::vec4(0.0, 0.0, 0.0, 0.0);
    }
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );
}

void VoxelGrid::renderVoxel(){
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES * GRID_SZ * GRID_SZ * GRID_SZ);
}

void VoxelGrid::colorCell(int x, int y, int z, glm::vec4 draw_color){
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glm::vec4 ch_v_color[NUM_VERTICES];
    for(int i=0; i < NUM_VERTICES; i++){
        ch_v_color[i] = draw_color;
    }
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions) + NUM_VERTICES*(GRID_SZ*GRID_SZ*z+ GRID_SZ*y + x)*sizeof(glm::vec4), sizeof(glm::vec4)*NUM_VERTICES, ch_v_color);
}

VoxelGrid::~VoxelGrid(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
}

void VoxelGrid::saveModel(std::string filename){
    glm::vec4 color;
    std::ofstream fout(filename);
    for (int x = 0; x < GRID_SZ; x++)
        for (int y = 0; y < GRID_SZ; y++)
            for (int z = 0; z < GRID_SZ; z++){
                color=v_colors[(z * GRID_SZ * GRID_SZ + y * GRID_SZ + x) * NUM_VERTICES ];
                if(color.w!=0.0)
                fout << x << " " << y << " " << z << " " << color.x << " " << color.y << " " << color.z <<std::endl; 
            }
    fout.close();
}

void VoxelGrid::loadModel(std::string filename){
    std::ifstream fin(filename);
    int x,y,z;
    float r,g,b;

    while(!fin.eof()){
        fin>>x>>y>>z;
        fin>>r>>g>>b;
        for(int i = 0; i < NUM_VERTICES; i++){
            v_colors[(z*GRID_SZ*GRID_SZ + y*GRID_SZ + x)*NUM_VERTICES + i]=glm::vec4(r,g,b,1.0);
        }
    }
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors);

    fin.close();
}
