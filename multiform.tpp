#include "multiform.h"
#include <cstring>

multiform::multiform(const char *name, Shader **shaders,int number_of_shaders)
{
    
    number_of_uniforms = number_of_shaders;
    uniforms = new uniform*[number_of_shaders];
    //shader_ref = shaders;
    for(int i = 0; i < number_of_shaders; i++)
    {
        uniforms[i] = new uniform(name,*shaders[i]);
    }   
    shader_ref = new Shader*[number_of_shaders];
    std::memcpy(shader_ref,shaders,number_of_shaders*sizeof(shader_ref[0]));
}

inline multiform::multiform(const char *name, Shader **shaders, int number_of_shaders, matrix::Matrix_Types matrix_type):multiform::multiform(name,shaders,number_of_shaders)
{
    
    for(int i = 0; i < number_of_uniforms; i++)
    {
        uniforms[i]->set_matrix_type(matrix_type);
    }
}

template <typename T>
inline void multiform::data(T x)
{
    Shader* active_shader = Shader::current_program();
    for(int i = 0; i < number_of_uniforms; i++)
    {
        shader_ref[i]->bind();
        uniforms[i]->data(x);
    }
    active_shader->bind();
}

template <typename T>
inline void multiform::data(T x, T y)
{
    Shader* active_shader = Shader::current_program();
    for(int i = 0; i < number_of_uniforms; i++)
    {
        shader_ref[i]->bind();
        uniforms[i]->data(x,y);
    }
    active_shader->bind();
}

template <typename T>
inline void multiform::data(T x, T y, T z)
{
    Shader* active_shader = Shader::current_program();
    for(int i = 0; i < number_of_uniforms; i++)
    {
        shader_ref[i]->bind();
        uniforms[i]->data(x,y,z);
    }
    active_shader->bind();
}

template <typename T>
inline void multiform::data(T x, T y, T z, T w)
{
    Shader* active_shader = Shader::current_program();
    for(int i = 0; i < number_of_uniforms; i++)
    {
        shader_ref[i]->bind();
        uniforms[i]->data(x,y,z,w);
    }
    active_shader->bind();
}

template <typename T>
inline void multiform::data(T *data)
{
    Shader* active_shader = Shader::current_program();
    for(int i = 0; i < number_of_uniforms; i++)
    {
        shader_ref[i]->bind();
        uniforms[i]->data(data);
    }
    active_shader->bind();
}

inline multiform::~multiform()
{
    delete[] shader_ref;
    for(int i = 0; i < number_of_uniforms; i++)
    {
        delete uniforms[i];
    }
    delete[] uniforms;
}
