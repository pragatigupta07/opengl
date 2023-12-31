#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, int t, std::size_t v_size, std::size_t c_size){

		type = t;
		
		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));


		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		if(type == 1){	//el
			if(rx < 180) rx++;
			else return;
		}
		else if(type == 4){	//knee
			if(rx > 180) rx++;
			else return;
		}
		else if(type == 3){	//neck
			if(rx < 90) rx++;
			else return;
		}
		else if(type == 6){	//torso
			if(rx < 30) rx++;
			else return;
		}
		else if(type == 5){	//torso
			if(rx < 180) rx++;
			else return;
		}
		else
			rx++;
		update_matrices();
	}

	void HNode::inc_ry(){
		if(type == 1 || type==5|| type==4) return;
		if(type == 2 || type ==6 || type == 7){
			if(ry < 30) ry++;
			else return;
		}
		else if(type == 3){
			if(ry < 90) ry++;
			else return;
		}
		else
			ry++;
		update_matrices();
	}

	void HNode::inc_rz(){
		if(type == 1||type==4) return;
		else if(type == 3||type==6){
			if(rz < 90) rz++;
			else return;
		}
		else if(type == 5){
			if(rz < 30) rz++;
			else return;
		}
		else if(type == 7){
			if(rz < 0) rz++;
			else return;
		}
		else
		rz++;
		update_matrices();
	}

	void HNode::dec_rx(){
		if(type == 1){ //el
			if(rx > 0) rx--;
			else return;
		}
		else if(type == 1){ //knee
			if(rx < 0) rx--;
			else return;
		}
		else if(type == 3){ //neck
			if(rx > -90) rx--;
			else return;
		}
		else if(type == 6){ //torso
			if(rx < -180) rx--;
			else return;
		}
		else if(type == 5){ //torso
			if(rx < -30) rx--;
			else return;
		}
		else rx--;
		update_matrices();
	}

	void HNode::dec_ry(){
		if(type == 1||type==5||type==4) return;
		if(type == 2||type==6){
			if(ry > -30) ry--;
			else return;
		}
		else if(type == 3){
			if(ry > -90) ry--;
			else return;
		}
		else
		ry--;
		update_matrices();
	}

	void HNode::dec_rz(){
		if(type == 1||type==4) return;
		else if(type == 3 || type == 6){
			if(rz > -90) rz--;
			else return;
		}
		else if(type == 5){
			if(rz > -30) rz--;
			else return;
		}
		else if(type == 7){
			if(rz > -210) rz--;
			else return;
		}
		else
		rz--;
		update_matrices();
	}

	void HNode::inc_tx(){
		tx = tx + 0.1;
		// rz-=5;
		update_matrices();
	}

	void HNode::dec_tx(){
		tx = tx - 0.1;
		// rz+=5;
		update_matrices();
	}

	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}