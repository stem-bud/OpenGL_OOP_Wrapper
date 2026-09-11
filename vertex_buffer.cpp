#include "vertex_buffer.h"

vertex_buffer::vertex_buffer(void *data, int length,number_type type)
{
    glGenBuffers(1,&id);
    bind();
    bytes_per_comp = number_type_sizes.at(type);
    this->length = length*number_type_sizes.at(type);
    this->type = type;
    glBufferData(GL_ARRAY_BUFFER,this->length,data,GL_STATIC_DRAW);
    this->length = length;
    unbind();
}

void vertex_buffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER,id);
}

void vertex_buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void vertex_buffer::define_attributes(int index, int number_of_component,int stride,int offset)
{
    if(type == vertex_buffer::number_type::INT)
    {
        glVertexAttribIPointer(index,number_of_component,number_types.at(type),stride*number_type_sizes.at(type),(const void*)(intptr_t)(offset*number_type_sizes.at(type)));
        
    }else
    {
        glVertexAttribPointer(index,number_of_component,number_types.at(type),GL_FALSE,stride*number_type_sizes.at(type),(const void*)(intptr_t)(offset*number_type_sizes.at(type)));
    }
    glEnableVertexAttribArray(index);
}

vertex_buffer::~vertex_buffer()
{
   glDeleteBuffers(1,&id);
}
