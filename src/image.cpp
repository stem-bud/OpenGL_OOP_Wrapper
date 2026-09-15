#include "./image.h"


image::image(const texture& texture)
{
    inner_format = texture.get_internal_format();
    id = texture.get_id();
}

void image::bind()
{
    bind(image::bind_state::READ_ONLY);
}

void image::bind(image::bind_state bind_state)
{
    bind(bind_state,0);
}

void image::bind(image::bind_state bind_state, int bind_unit)
{
    this->bind_unit = bind_unit;
    GLenum binding_as;
    switch(bind_state)
    {
        case image::bind_state::READ_ONLY:
            binding_as = GL_READ_ONLY;
        break;
        case image::bind_state::WRITE_ONLY:
            binding_as = GL_WRITE_ONLY;
        break;
        case image::bind_state::READ_AND_WRITE:
            binding_as = GL_READ_WRITE;
        break;
        default:
            //std::cerr << "invalid binding state for image" << std::endl; 
        break;
    }
    glBindImageTexture(bind_unit,id,0,GL_FALSE,0,binding_as,texture::get_gl_inner_format(inner_format));
}

void image::unbind()
{
    glBindImageTexture(bind_unit,0,0,GL_FALSE,0,GL_READ_ONLY,GL_RGBA8);
}
