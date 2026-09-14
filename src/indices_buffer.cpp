#include "./glfw_glew_include.h"
#include "./indices_buffer.h"

indices_buffer::indices_buffer(unsigned int *indices, int length)
{
    glGenBuffers(1,&id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,length*sizeof(unsigned int),indices,GL_STATIC_DRAW);
}

void indices_buffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
}

void indices_buffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); 
}

indices_buffer::~indices_buffer()
{
    glDeleteBuffers(1,&id);
}
