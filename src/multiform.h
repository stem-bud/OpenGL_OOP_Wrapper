#include "uniform.h"
#include "shader.h"

#ifndef MULTIFORM_HEADER
#define MULTIFORM_HEADER

/**
 * @brief class to ease managing the same uniform across multiple shaders
 */
class multiform
{
    private:
        uniform** uniforms;
        Shader** shader_ref;
        int number_of_uniforms;
    public:
        multiform(const multiform&) = delete;
        multiform& operator=(const multiform&) = delete;
        multiform(multiform&& other) = delete;
        multiform& operator=(multiform&& other) = delete;
        /**
         * @param name name of uniform
         * @param shaders array of addressed of shaders
         * @param number_of_shaders number of shaders
         */
        multiform(const char* name,Shader** shaders,int number_of_shaders);
        multiform(std::string name,Shader** shaders,int number_of_shaders):multiform::multiform(name.c_str(),shaders,number_of_shaders){}
        multiform(const char* name,Shader** shaders,int number_of_shaders,matrix::Matrix_Types matrix_type);
        multiform(std::string name,Shader** shaders,int number_of_shaders,matrix::Matrix_Types matrix_type):multiform::multiform(name.c_str(),shaders,number_of_shaders,matrix_type){}
        template<typename T>
        void data(T x);
        template<typename T>
        void data(T x,T y);
        template<typename T>
        void data(T x,T y,T z);
        template<typename T>
        void data(T x,T y,T z,T w);
        template <typename T>
        void data(T* data);
        ~multiform();
};


#include "multiform.tpp"

#endif
