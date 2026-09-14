#include "./texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"


GLenum texture::get_gl_format()
{
    GLenum format;
    switch (inner_format)
    {
        case internal_format::RGBA32F:
        case internal_format::RGBA16F:
        case internal_format::RGBA8:
        case internal_format::RGBA:
            format = GL_RGBA;
        break;
        case internal_format::RGBA32UI:
            format = GL_RGBA_INTEGER;
        break;
        case internal_format::RGB32F:
        case internal_format::RGB16F:
        case internal_format::RGB8:
        case internal_format::RGB:
            format = GL_RGB;
        break;
        case internal_format::R32F:
            format = GL_RED;
        break;
        case internal_format::R32I:
        case internal_format::R32UI:
            format = GL_RED_INTEGER;
        break;
        case internal_format::UNASSIGNED:
            format = 0;
        break;
        default:
            format = GL_DEPTH_COMPONENT;
    };
    return format;
}

int texture::number_of_channels()
{
    switch(inner_format)
    {
        case texture::internal_format::RGBA32F:
        case texture::internal_format::RGBA32UI:
        case texture::internal_format::RGBA16F:
        case texture::internal_format::RGBA8:
        case texture::internal_format::RGBA:
        return 4;
        case texture::internal_format::RGB32F:
        case texture::internal_format::RGB16F:
        case texture::internal_format::RGB8:
        case texture::internal_format::RGB:
        return 3;
        case texture::internal_format::R32F:
        case texture::internal_format::R32I:
        case texture::internal_format::R32UI:
        case texture::internal_format::DEPTH_COMPONENT32F:
        return 1;
        default:
        return -1;
    }
}

texture::attachment_type texture::get_attachment_type(internal_format format)
{
    switch(format)
    {
        case internal_format::RGBA32F:
        case internal_format::RGBA32UI:
        case internal_format::RGBA16F:
        case internal_format::RGBA8:
        case internal_format::RGBA:
        case internal_format::RGB32F:
        case internal_format::RGB16F:
        case internal_format::RGB8:
        case internal_format::RGB:
        case internal_format::R32F:
        case internal_format::R32I:
        case internal_format::R32UI:
        return attachment_type::COLOR;

        case internal_format::DEPTH_COMPONENT32F:
        return attachment_type::DEPTH;
        default:
        return attachment_type::STENCIL;
    }
}


texture::texture(bool one_dimensional)
{
    glGenTextures(1,&tex_id);
    dimension = texture::texture_dimension::TEXTURE_2D;
    if(one_dimensional)
    {
        dimension = texture::texture_dimension::TEXTURE_1D;
    }
    bind();
}

void texture::init(internal_format format, int sizex, int sizey)
{
    inner_format = format;
    type = get_attachment_type(format);
    set_size(sizex,sizey);
    set_internal_format(format);
    channels = number_of_channels();
}

texture::texture(internal_format format, int sizex, int sizey) : texture::texture(sizey == 0)
{
    
    init(format,sizex,sizey);
    internal_number_type = texture::get_number_type(format);
    GLenum number_type = number_types.at(internal_number_type);
    if(dimension == texture_dimension::TEXTURE_2D)
    {
        glTexImage2D(GL_TEXTURE_2D,0,inner_formats.at(inner_format),size_x,size_y,0,get_gl_format(),number_type,NULL);
    }else
    {
        glTexImage1D(GL_TEXTURE_1D,0,inner_formats.at(inner_format),size_x,0,get_gl_format(),number_type,NULL);
    }
    unbind();
}

texture::texture(internal_format format, int sizex, int sizey, bool samplable):texture::texture(format,sizex,sizey)
{
    bind();
    if(samplable)
    {
        this->samplable = samplable;
        glGenerateMipmap(gl_dimension.at(dimension));
    }
    unbind();
}

texture::texture(const char *path):texture::texture(false)
{
    samplable = true;
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char* data = stbi_load(path,&width,&height,&channels,0);
    
    init(channels == 4?internal_format::RGBA:internal_format::RGB,width,height);
    glTexImage2D(GL_TEXTURE_2D,0,inner_formats.at(inner_format),width,height,0,get_gl_format(),GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    unbind();
}


void texture::bind()
{
    bind(0);
}
void texture::bind(GLint location)
{
    int max;
    
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&max);
    if(location >= max)
    {
        std::cerr << "invalid location"<< std::endl;
        return;
    }
    
    bound_location = location;
    glActiveTexture(GL_TEXTURE0+location);
    
    glBindTexture(gl_dimension.at(dimension),tex_id);
}

void texture::unbind()
{
    if(bound_location == -1)
    {
        return;
    }
    glActiveTexture(GL_TEXTURE0+bound_location);
    bound_location = -1;
    glBindTexture(gl_dimension.at(dimension),0);
}

bool texture::is_samplable() const
{
    return samplable;
}

void texture::set_clear_color(int r, int g, int b, int a)
{
    int color[4] = {r,g,b,a};
    set_clear_color(number_type::INT,color);
}

void texture::set_clear_color(float r, float g, float b, float a)
{
    float color[4] = {r,g,b,a};
    set_clear_color(number_type::FLOAT,(void*)color);
}

void texture::set_clear_color(number_type type, void *color)
{
    if(clear_colors.at(type)!=nullptr)
    {
        delete[] clear_colors.at(type);
    }

    clear_colors[type] = new byte[16];
    for(int i = 0; i < 16; i++)
    {
        clear_colors[type][i] = ((byte*)color)[i];
    }
}

void texture::set_internal_clear_color(void * color)
{
    if(internal_clear_color !=nullptr)
    {
        delete[] internal_clear_color;
    }
    internal_clear_color = new byte[16];
    for(int i = 0; i < 16; i++)
    {
        internal_clear_color[i] = ((byte*)color)[i];
    }
}

void texture::remove_internal_clear_color()
{
    if(internal_clear_color!= nullptr)
    {
        delete[] internal_clear_color;
        internal_clear_color = nullptr;
    }
}

GLuint texture::get_id() const
{
    return tex_id;
}

texture::attachment_type texture::get_type() const
{
    return type;
}

void texture::get_size(int *width, int *height) const
{
    *width = size_x;
    *height = size_y;
}

void texture::clear(void *clear_color)
{
    glClearTexImage(get_id(),0,get_gl_format(),number_types.at(internal_number_type),clear_color);
}

void texture::clear()
{
    if(clear_colors.at(internal_number_type) == nullptr)
    {
        std::cerr << "default clear color not set" << std::endl;
        
    }
    clear(internal_clear_color==nullptr?clear_colors.at(internal_number_type):internal_clear_color);
}

texture::internal_format texture::get_internal_format() const
{
    return inner_format;
}

GLenum texture::get_gl_inner_format(texture::internal_format inner_format)
{
    return inner_formats.at(inner_format);
}

texture::number_type texture::get_number_type(texture::internal_format inner_format)
{
        switch(inner_format)
        {
            case internal_format::RGBA32F:
            case internal_format::RGBA16F:
            case internal_format::RGB32F:
            case internal_format::RGB16F:
            case internal_format::R32F:
            case internal_format::DEPTH_COMPONENT32F:
                return number_type::FLOAT;
            case internal_format::RGBA8:
            case internal_format::RGB8:
            case internal_format::RGBA:
            case internal_format::RGB:
                return number_type::UNSIGNED_BYTE;
            case internal_format::R32I:
                return number_type::INT;
            case internal_format::RGBA32UI:
            case internal_format::R32UI:
                return number_type::UNSIGNED_INT;
            case internal_format::UNASSIGNED:
            default:
                std::cerr << "unknown internal format" << std::endl;
                return number_type::UNASSIGNED;
        }
}

void texture::upload(void *data, int x_offset, int y_offset, int width, int height)
{
    if(height == 0)
    {
        glTextureSubImage1D(tex_id,0,x_offset,width,get_gl_format(),number_types.at(internal_number_type),data);
    }else
    {
        glTextureSubImage2D(tex_id,0,x_offset,y_offset,width,height,get_gl_format(),number_types.at(internal_number_type),data);
        
    }
}

void texture::upload(void *data, int offset, int length)
{
    this->upload(data,offset,0,length,0);
}

void texture::get_pixel_data(void *data_store)
{
    bind();
    GLenum enum_dimension = gl_dimension.at(dimension);
    glGetTexImage(enum_dimension,0,get_gl_format(),number_types.at(internal_number_type),data_store);
    unbind();
}

texture::~texture()
{
    if(tex_id)
    {
        glDeleteTextures(1, &tex_id);
    }
    if(internal_clear_color!= nullptr)
    {
        delete[] internal_clear_color;
    }
}

void texture::set_internal_format(internal_format format)
{
    this->inner_format = format;
}

void texture::set_size(int sizex, int sizey)
{
    size_x = sizex;
    size_y = sizey;
}
