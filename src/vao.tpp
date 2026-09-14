#include "./vao.h"


template <typename T>
inline vao<T>::vao(T *vertices, int length, unsigned int *indices, GLsizei index_count)
{
    glGenVertexArrays(1,&id);
    bind();
    buffer = new vertex_buffer(vertices,length);
    indexes = new indices_buffer(indices,index_count);
    this->length = index_count;
    buffer->bind();
    indexes->bind();
    unbind();
}

template <typename T>
inline vao<T>::vao(T *vertices, int length, unsigned int *indices, GLsizei index_count,vao::render_mode mode):vao<T>::vao(vertices,length,indices,index_count)
{
    bind();
    set_mode(mode);
    unbind();
}

template <typename T>
inline void vao<T>::remodel(T *vertices, int length, unsigned int *indices, GLsizei index_count, vao::render_mode mode)
{
    delete buffer;
    delete indexes;
    glDeleteVertexArrays(1, &id);
    
    glGenVertexArrays(1,&id);
    bind();
    buffer = new vertex_buffer(vertices,length);
    indexes = new indices_buffer(indices,index_count);
    this->length = index_count;
    buffer->bind();
    indexes->bind();
    unbind();
    bind();
    set_mode(mode);
    unbind();
}

template <typename T>
inline void vao<T>::set_mode(vao<T>::render_mode mode)
{
    this->mode = render_modes.at(mode);
}

template <typename T>
inline void vao<T>::bind()
{
    glBindVertexArray(id);
}

template <typename T>
inline void vao<T>::unbind()
{
    glBindVertexArray(0);
}

template <typename T>
inline void vao<T>::define_attributes(int index, int number_of_comp, int stride, int offset)
{
    bind();
    buffer->bind();
    buffer->define_attributes(index,number_of_comp,stride,offset);
    unbind();
    buffer->unbind();
}

template <typename T>
inline void vao<T>::draw()
{
    draw(this->length);
}

template <typename T>
inline void vao<T>::draw(int length)
{
    bind();
    glDrawElements(mode,length>this->length?this->length:length,GL_UNSIGNED_INT,nullptr);
    unbind();
}

template <typename T>
inline vao<T>::~vao()
{
    delete buffer;
    delete indexes;
    glDeleteVertexArrays(1, &id);
}
