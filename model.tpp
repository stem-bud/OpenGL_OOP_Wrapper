/*#include "model.h"

template<typename T>
model<T>::model(T*data, int length,unsigned int* indices,int indices_count)
{
    vertex_buffer vertices(data,length);
    indices_buffer indexes(indices,indices_count);
    my_vao = new vao(vertices,indexes);
    //buffer = new vertex_buffer((T*)this->data,length,false);
}
template<typename T>
model<T>::model(T*data, int length,unsigned int* indices,int indices_count, model<T>::render_mode mode):model<T>::model(data,length,indices,indices_count)
{
    set_mode(mode);
}

template<typename T>
void model<T>::set_mode(model<T>::render_mode mode)
{
    this->mode = render_modes.at(mode);
}

template<typename T>
void model<T>::draw()
{
    my_vao->bind();
    glDrawElements(this->mode,ind_num,GL_UNSIGNED_INT,nullptr);
}
template<typename T>
model<T>::~model()
{
    delete my_vao;
}*/
