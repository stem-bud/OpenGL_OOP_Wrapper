#include <cstddef>
#include "./glfw_glew_include.h"
#include <unordered_map>

#ifndef VERTEX_BUFFER_HEADER
#define VERTEX_BUFFER_HEADER
using byte = std::byte;

class vertex_buffer
{
    private:
        GLuint id;
        int length;
        bool copied;
        int bytes_per_comp;
        
        enum class number_type
        {
            DOUBLE,
            FLOAT,
            UNSIGNED_INT,
            INT,
            UNSIGNED_BYTE,
            BYTE,
            UNASSIGNED
        };
        number_type type;
        inline static const std::unordered_map<number_type,GLenum> number_types = 
        {
            {number_type::DOUBLE,GL_DOUBLE},
            {number_type::FLOAT,GL_FLOAT},
            {number_type::UNSIGNED_INT,GL_UNSIGNED_INT},
            {number_type::INT,GL_INT},
            {number_type::UNSIGNED_BYTE,GL_UNSIGNED_BYTE},
            {number_type::BYTE,GL_BYTE}
        };
        inline static const std::unordered_map<number_type,int> number_type_sizes = 
        {
            {number_type::DOUBLE,sizeof(double)},
            {number_type::FLOAT,sizeof(float)},
            {number_type::UNSIGNED_INT,sizeof(unsigned int)},
            {number_type::INT,sizeof(int)},
            {number_type::UNSIGNED_BYTE,sizeof(unsigned char)},
            {number_type::BYTE,sizeof(signed char)},
        };
    public:
        vertex_buffer() = delete;
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to data
         * @param length number of bytes that make up the data
         * @param type number type
         */
        vertex_buffer(void* data,int length,number_type type);
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to float array
         * @param length number of elements in the array
         */
        vertex_buffer(float* data,int length):vertex_buffer::vertex_buffer(data,length,number_type::FLOAT){}
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to unsigned int array
         * @param length number of elements in the array
         */
        vertex_buffer(unsigned int* data,int length):vertex_buffer::vertex_buffer(data,length,number_type::UNSIGNED_INT){}
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to int array
         * @param length number of elements in the array
         */
        vertex_buffer(int* data, int length):vertex_buffer::vertex_buffer(data,length,number_type::INT){}
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to unsigned char array
         * @param length number of elements in the array
         */
        vertex_buffer(unsigned char* data, int length):vertex_buffer::vertex_buffer(data,length,number_type::UNSIGNED_BYTE){}
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to signed char array
         * @param length number of elements in the array
         */
        vertex_buffer(signed char* data, int length):vertex_buffer::vertex_buffer(data,length,number_type::BYTE){}
        /**
         * @brief constructor for vertex buffer
         * @param data pointer to char array
         * @param length number of elements in the array
         */
        vertex_buffer(char* data, int length):vertex_buffer::vertex_buffer((signed char*)data,length){}
        /**
         * @brief binds this vertex buffer
         */
        void bind();
        /**
         * @brief guarantees this buffer is not bound after completion
         */
        void unbind();
        /**
         * @brief defines attributes and automatically enables it
         * @param index index of attribute
         * @param number_of_comp number of component for that attribute 1 2 3 4
         * @param offset starting index of attribute. any primintive type.
         */
        void define_attributes(int index,int number_of_comp,int stride,int offset);
        ~vertex_buffer();
};

#endif
