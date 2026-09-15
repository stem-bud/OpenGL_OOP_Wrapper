#include "./glfw_glew_include.h"
#include <string>
#include "./uniform.h"
#include "./shader.h"



uniform::uniform(const char* name,const Shader& program)
{
    uniformid  = glGetUniformLocation(program.get_shader_program(),name);
    is_valid = true;
    if(uniformid == -1)
    {
        is_valid = false;
        //std::cerr << "unable to locate uniform" << std::endl;
    }
}

bool uniform::is_valid_uniform() const
{
    return is_valid;
}

void uniform::set_matrix_type(matrix::Matrix_Types type)
{
    matrix_type = type;
}

void uniform::data(bool x)
{
    data((int)x);
}

void uniform::data(bool x,bool y)
{
    data((int)x,(int)y);
}

void uniform::data(bool x,bool y,bool z)
{
    data((int)x,(int)y,(int)z);
}

void uniform::data(bool x,bool y,bool z,bool w)
{
    data((int)x,(int)y,(int)z,(int)w);
}

void uniform::data(int x)
{
    glUniform1i(uniformid,x);
}

void uniform::data(int x,int y)
{
    glUniform2i(uniformid,x,y);
}

void uniform::data(int x,int y,int z)
{
    glUniform3i(uniformid,x,y,z);
}

void uniform::data(int x,int y,int z,int w)
{
    glUniform4i(uniformid,x,y,z,w);
}

void uniform::data(float x)
{
    glUniform1f(uniformid,x);
}

void uniform::data(float x,float y)
{
    glUniform2f(uniformid,x,y);
}

void uniform::data(float x,float y,float z)
{
    glUniform3f(uniformid,x,y,z);
}

void uniform::data(float x,float y,float z,float w)
{
    glUniform4f(uniformid,x,y,z,w);
}

void uniform::data(double x)
{
    glUniform1d(uniformid,x);
}

void uniform::data(double x, double y)
{
    glUniform2d(uniformid,x,y);
}

void uniform::data(double x, double y,double z)
{
    glUniform3d(uniformid,x,y,z);
}

void uniform::data(double x,double y,double z,double w)
{
    glUniform4d(uniformid,x,y,z,w);
}

void uniform::data(const float* data)
{
    switch(matrix_type)
    {
        case matrix::Matrix_Types::MAT_4:
            glUniformMatrix4fv(uniformid,1,GL_TRUE,data);
        break;
        case matrix::Matrix_Types::MAT_3:
            glUniformMatrix3fv(uniformid,1,GL_TRUE,data);
        break;
        case matrix::Matrix_Types::MAT_2:
            glUniformMatrix2fv(uniformid,1,GL_TRUE,data);
        break;
    }  
}

void uniform::data(const double* data)
{
    switch(matrix_type)
    {
        case matrix::Matrix_Types::MAT_4:
            glUniformMatrix4dv(uniformid,1,GL_TRUE,data);
        break;
        case matrix::Matrix_Types::MAT_3:
            glUniformMatrix3dv(uniformid,1,GL_TRUE,data);
        break;
        case matrix::Matrix_Types::MAT_2:
            glUniformMatrix2dv(uniformid,1,GL_TRUE,data);
        break;
    }  
}
