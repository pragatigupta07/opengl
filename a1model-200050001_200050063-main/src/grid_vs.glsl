#version 330

in vec4 vPosition;
uniform mat4 uModelViewProjectMatrix;

void main (void) 
{
  gl_Position =  uModelViewProjectMatrix*vPosition;
}