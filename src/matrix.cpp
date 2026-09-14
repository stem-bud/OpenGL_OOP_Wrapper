#include "glfw_glew_include.h"
#include "constants.h"
#include "string"
#include "vector"
#include "matrix.h"
#include <iostream>
#include <cmath>
#include "shader.h"

int matrix::get_size(Matrix_Types mat_type)
{
    switch (mat_type)
    {
    case matrix::Matrix_Types::MAT_2:
        return 2;
    case matrix::Matrix_Types::MAT_3:
        return 3;
    case matrix::Matrix_Types::MAT_4:
        return 4;
    default:
        return -1;
    }
}

void matrix::rotation_matrix(float angle,matrix::Axes axis, float *store)
{
    float radian = (angle/180.0f)*constants::PI;
    switch(axis)
    {
        case matrix::Axes::x_axis:
            store[0] = 1;          store[1] = 0;           store[2] = 0;
            store[3] = 0;store[4] = cos(radian);store[5] = -sin(radian);
            store[6] = 0;store[7] = sin(radian); store[8] = cos(radian);
        break;
        case matrix::Axes::y_axis:
            store[0] = cos(radian); store[1] = 0;store[2] = sin(radian);
            store[3] = 0;           store[4] = 1;          store[5] = 0;
            store[6] = -sin(radian);store[7] = 0;store[8] = cos(radian);
        break;
        case matrix::Axes::z_axis:
            store[0] = cos(radian);store[1] = -sin(radian);store[2] = 0;
            store[3] = sin(radian); store[4] = cos(radian);store[5] = 0;
            store[6] = 0;                     store[7] = 0;store[8] = 1;
        break;
        default:
            store[0] = 1;store[1] = 0;store[2] = 0;
            store[3] = 0;store[4] = 1;store[5] = 0;
            store[6] = 0;store[7] = 0;store[8] = 1;
    }
}

void matrix::identity_matrix(matrix::Matrix_Types mat_type, float *store)
{
    int n = get_size(mat_type);
    int length = n*n;
    for(int i = 0; i < length; i++)
    {
        if(i/n == i%n)
        {
            store[i] = 1;
        }else
        {
            store[i] = 0;
        }
    }
}

void matrix::square_matrix_multiplication(const float *matrix1,const float *matrix2,matrix::Matrix_Types mat_type, float *store)
{
    int size = matrix::get_size(mat_type);
    /** 
     * @note size 16 because maximum size of matrix is 4 by 4;
     */
    float temp_store[16];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            float sum = 0;
            for(int k = 0; k < size; k++)
            {
                sum+=matrix1[i*size+k]*matrix2[k*size+j];
            }
            temp_store[i*size+j] = sum;
        }
    }
    for(int i = 0; i < size*size; i++)
    {
        store[i] = temp_store[i];
    }
}

std::string matrix::output_square_matrix(const float *data, matrix::Matrix_Types mat_type)
{
    int size = get_size(mat_type);
    std::vector<char> string;

    for(int i = 0; i < size*size; i++)
    {
        std::string num = std::to_string(data[i]);
        for(char c:num)
        {
            string.push_back(c);
        }
        if((i+1)%size == 0)
        {   
            string.push_back('\n');
            continue;
        }
        string.push_back(' ');
    }
    return std::string(string.begin(),string.end());
    
}

void matrix::rotation_matrix(float angle_x, float angle_y, float angle_z, float *store)
{
    float x_rotation[9];
    float y_rotation[9];
    float z_rotation[9];
    rotation_matrix(angle_x,matrix::matrix::Axes::x_axis,x_rotation);
    rotation_matrix(angle_y,matrix::matrix::Axes::y_axis,y_rotation);
    rotation_matrix(angle_z,matrix::matrix::Axes::z_axis,z_rotation);
    
    float result[9];
    square_matrix_multiplication(x_rotation,y_rotation,matrix::Matrix_Types::MAT_3,result);
    square_matrix_multiplication(result,z_rotation,matrix::Matrix_Types::MAT_3,store);
}

void matrix::rotation_set(const float *angular_sets,int sequences,float *store)
{
    float axes[9];
    identity_matrix(matrix::Matrix_Types::MAT_3,axes);
    for(int i = 0; i < sequences; i++)
    {
        add_rotation(axes,angular_sets[i*number_of_axes],matrix::Axes::x_axis,axes);
        add_rotation(axes,angular_sets[i*number_of_axes+1],matrix::Axes::y_axis,axes);
        add_rotation(axes,angular_sets[i*number_of_axes+2],matrix::Axes::z_axis,i == sequences-1?store:axes);
    }
}

void matrix::rotation_set(const float *initial_axes, const float *angular_sets, int sequences, float *store)
{
    float temp[9];
    rotation_set(angular_sets,sequences,temp);
    square_matrix_multiplication(initial_axes,temp,matrix::Matrix_Types::MAT_3,store);
}

void matrix::add_rotation(const float *initial_axes, float angle, matrix::Axes axis,float* store)
{
    float additional_rotation[9];
    rotation_matrix(angle,axis,additional_rotation);
    square_matrix_multiplication(initial_axes,additional_rotation,matrix::Matrix_Types::MAT_3,store);
}
