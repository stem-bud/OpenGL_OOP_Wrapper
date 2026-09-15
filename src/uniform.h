#include "./shader.h"
#include "./matrix.h"


#ifndef UNIFORM_HEADER
#define UNIFORM_HEADER
class uniform
{
    private: 
        GLint  uniformid;
        matrix::Matrix_Types matrix_type;
        bool is_valid;
    public:
        uniform() = delete;
        uniform(const uniform&) = delete;
        uniform& operator=(const uniform&) = delete;
        uniform(uniform&& other) = delete;
        uniform& operator=(uniform&& other) = delete;
        /**
         * @param name name of the uniform
         * @param program shader program
         */
        uniform(const char* name,const Shader& program);
        uniform(std::string name,const Shader& program):uniform::uniform(name.c_str(),program){}
        uniform(const char* name,const Shader& program,matrix::Matrix_Types type):uniform::uniform(name,program)
        {
            set_matrix_type(type);
        }
        uniform(std::string name,const Shader& program,matrix::Matrix_Types type):uniform::uniform(name.c_str(),program,type){}
        bool is_valid_uniform() const;
        void set_matrix_type(matrix::Matrix_Types type);
        void data(bool x);
        void data(bool x,bool y);
        void data(bool x,bool y,bool z);
        void data(bool x,bool y,bool z,bool w);
        void data(int x);
        void data(int x,int y); 
        void data(int x,int y,int z);
        void data(int x,int y,int z,int w);
        void data(float x);
        void data(float x,float y); 
        void data(float x,float y,float z);
        void data(float x,float y,float z,float w);
        void data(double x);
        void data(double x,double y); 
        void data(double x,double y,double z);
        void data(double x,double y,double z,double w);   
        void data(const float* data);
        void data(const double* data);
};

#endif
