#include <unordered_map>
#include "./glfw_glew_include.h"
#include <string>
#include <iostream>
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
using byte = std::byte;

class texture
{
    private:
        enum class texture_dimension
        {
            TEXTURE_1D,
            TEXTURE_2D,
        };

        static inline std::unordered_map<texture::texture_dimension,GLenum> gl_dimension
        {
            {texture::texture_dimension::TEXTURE_1D,GL_TEXTURE_1D},
            {texture::texture_dimension::TEXTURE_2D,GL_TEXTURE_2D},
        };
    public:
        enum class attachment_type
        {
            COLOR,
            DEPTH,
            STENCIL,
            UNASSIGNED
        };

        enum class number_type
        {
            FLOAT,
            UNSIGNED_INT,
            INT,
            UNSIGNED_BYTE,
            BYTE,
            UNASSIGNED
        };

        enum class internal_format
        {
            RGBA32F,
            RGBA32UI,
            RGBA16F,
            RGBA8,
            RGBA,
            RGB32F,
            RGB16F,
            RGB8,
            RGB,
            R32F,
            R32I,
            R32UI,
            DEPTH_COMPONENT32F,
            UNASSIGNED
        };
    private:
        inline static std::unordered_map<number_type,byte*> clear_colors = 
        {
            {number_type::FLOAT,nullptr},
            {number_type::UNSIGNED_INT,nullptr},
            {number_type::INT,nullptr},
            {number_type::UNSIGNED_BYTE,nullptr},
            {number_type::BYTE,nullptr}
        };

        byte* internal_clear_color = nullptr;

        inline static const std::unordered_map<number_type,GLenum> number_types = 
        {
            {number_type::FLOAT,GL_FLOAT},
            {number_type::UNSIGNED_INT,GL_UNSIGNED_INT},
            {number_type::INT,GL_INT},
            {number_type::UNSIGNED_BYTE,GL_UNSIGNED_BYTE},
            {number_type::BYTE,GL_BYTE}
        };
        
        inline static const std::unordered_map<internal_format,GLenum> inner_formats = 
        {
            {internal_format::RGBA32F,GL_RGBA32F},
            {internal_format::RGBA32UI,GL_RGBA32UI},
            {internal_format::RGBA16F,GL_RGBA16F},
            {internal_format::RGBA8,GL_RGBA8},
            {internal_format::RGBA,GL_RGBA8},
            {internal_format::RGB32F,GL_RGB32F},
            {internal_format::RGB16F,GL_RGB16F},
            {internal_format::RGB8,GL_RGB8},
            {internal_format::RGB,GL_RGB8},
            {internal_format::R32F,GL_R32F},
            {internal_format::R32I,GL_R32I},
            {internal_format::R32UI,GL_R32UI},
            {internal_format::DEPTH_COMPONENT32F,GL_DEPTH_COMPONENT32F}
        };
        attachment_type type;
        internal_format inner_format;
        number_type internal_number_type;
        texture::texture_dimension dimension;
        int size_x;
        int size_y;
        GLuint tex_id;
        int bound_location = -1;
        int channels;
        bool samplable = false;
        std::string my_name;
        GLenum get_gl_format();
        
        int number_of_channels();
        static texture::attachment_type get_attachment_type(internal_format format);
        texture() = delete;
        texture(bool one_dimensional);
        void init(internal_format format,int size, int sizey);
    public:
        texture(internal_format format, int sizex, int sizey);
        texture(internal_format format, int sizex, int sizey,bool samplable);
        texture(internal_format format, int sizex,bool samplable):texture::texture(format,sizex,0,samplable){}
        texture(internal_format format, int sizex):texture::texture(format,sizex,false){}
        texture(const char* path);
        texture(std::string path):texture::texture(path.c_str()){}
        void bind();
        void bind(GLint location);
        void unbind();
        bool is_samplable() const;
        static void set_clear_color(int r, int g, int b, int a);
        static void set_clear_color(float r, float g, float b, float a);
        static void set_clear_color(number_type type,void* color);
        void set_internal_clear_color(void* color);
        void remove_internal_clear_color();
        GLuint get_id()const;
        attachment_type get_type()const;
        void get_size(int*width,int*height) const;
        void clear(void*clear_color);
        void clear();
        texture::internal_format get_internal_format() const;
        static GLenum get_gl_inner_format(texture::internal_format inner_format);
        static texture::number_type get_number_type(texture::internal_format inner_format);
        void upload(void* data,int x_offset,int y_offset,int width,int height);
        void upload(void* data,int offset, int length);
        void get_pixel_data(void* data_store);
        template<typename T>
        void print_pixels();
        ~texture();
    private:
        void set_internal_format(internal_format format);
        void set_size(int sizex,int sizey);
    public:
        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;
        texture(texture&& other) = delete;
        texture& operator=(texture&& other) = delete;
};


template <typename T>
inline void texture::print_pixels()
{
    int length = size_x*(size_y>0?size_y:1);
    int height = (size_y>0?size_y:1);

    T* data = new T[length*channels];

    get_pixel_data(data);
    std::string string;
    string.reserve(length*channels*3);
    for(int i = 0; i < length; i++)
    {
        string+= ("[" + std::to_string(i/height) + ", " + std::to_string(i%height) + "] = ");
        for(int j = 0; j < channels; j++)
        {
            
            string+=std::to_string(data[i*channels+j]);
            string+= (j != channels-1?" ":"");
        }
        string+=i!=length-1?"\n":"";
    }
    delete[] data;
    std::cout << string << std::endl;

}


template<typename T>
std::ostream& operator<<(std::ostream& os, const texture& texture)
{
    // Format the output exactly how you want it
    //os << "Player(Name: " << player.name << ", Score: " << player.score << ")";
    
    // Always return the stream to allow chaining (e.g., std::cout << a << b;)
    return os; 
}

#endif


