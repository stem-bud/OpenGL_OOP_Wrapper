#include "./framebuffer.h"
#include "./glfw_glew_include.h"
#include <iostream>


framebuffer::framebuffer()
{
    glGenFramebuffers(1,&framebuffer_id);
}

void framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer_id);
}

void framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

unsigned int framebuffer::get_id() const
{
    return framebuffer_id;
}

void framebuffer::add_attachment(const texture& attachment, int location)
{
    bind();
    int max_attachment;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&max_attachment);

    switch(attachment.get_type())
    {
        case texture::attachment_type::COLOR:
            if(location >= max_attachment)
            {
                std::cerr << "unable to attach texture to framebuffer" << std::endl;
                
            }
            glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0+location,GL_TEXTURE_2D,attachment.get_id(),0);
        break;
        case texture::attachment_type::DEPTH:
            glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,attachment.get_id(),0);
        break;
        case texture::attachment_type::STENCIL:
            glFramebufferTexture2D(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_TEXTURE_2D,attachment.get_id(),0);
        break;
        default:
            std::cerr << "attachment type not supported" << std::endl;
            
    }
    attachment.get_size(&sizex,&sizey);
    //textures.push_back(attachment);
    unbind();
}

void framebuffer::add_attachment(const texture& attachment)
{
    if(attachment.get_type() == texture::attachment_type::COLOR)
    {
        std::cerr << "location not given for color attachment" << std::endl;
        
    }
    add_attachment(attachment,0);

}

/*void framebuffer::resize(int width, int height)
{
    if(width==sizex && height==sizey)
    {
        return;
    }
    for(int i = 0; i < textures.size(); i++)
    {
        //textures.at(i).resize(width,height);
    }
}*/

void framebuffer::get_size(int *width, int *height)
{
    *width = sizex;
    *height = sizey;
}

framebuffer* framebuffer::get_defaultframebuffer()
{
    init_default_framebuffer();
    return default_framebuffer;
}

void framebuffer::init_default_framebuffer()
{
    if(default_framebuffer == nullptr)
    {
        default_framebuffer = new framebuffer();
        glDeleteFramebuffers(1,&(default_framebuffer->framebuffer_id));
        default_framebuffer->framebuffer_id = 0;
    }
}

void framebuffer::set_default_framebuffer_size(int sizex,int sizey)
{
    init_default_framebuffer();
    default_framebuffer->sizex = sizex;
    default_framebuffer->sizey = sizey;
}



void framebuffer::copy_framebuffer(const framebuffer& source, const framebuffer& destination)
{
    if(source.sizex == -1)
    {
        std::cerr << "source framebuffer does not have an attachment" << std::endl;
        
    }
    if(destination.sizex == -1)
    {
        std::cerr << "destination framebuffer does not have an attachment" << std::endl;
        
    }
    //std::cout << destination.sizex << ", " << destination.sizey << std::endl;
    copy_framebuffer(source,destination,
    rectangle(source.sizex,source.sizey),
    rectangle(destination.sizex,destination.sizey));
}

void framebuffer::copy_framebuffer(const framebuffer& source, const framebuffer& destination, int sizex, int sizey)
{
    copy_framebuffer(source,destination,rectangle(sizex,sizey),rectangle(sizex,sizey));
}

void framebuffer::copy_framebuffer(const framebuffer& source, const framebuffer& destination, int offsetx, int offsety, int sizex, int sizey)
{
    copy_framebuffer(source,destination,offsetx,offsety,sizex,sizey,offsetx,offsety,sizex,sizey);
}

void framebuffer::copy_framebuffer(const framebuffer& source, const framebuffer& destination, int src_offsetx, int src_offsety, int src_sizex, int src_sizey, int dest_offsetx, int dest_offsety, int dest_sizex, int dest_sizey)
{
    GLint previous_read;
    GLint previous_draw;

    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING,&previous_read);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_draw);

    glBindFramebuffer(GL_READ_FRAMEBUFFER,source.get_id());
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,destination.get_id());
    glBlitFramebuffer(
        src_offsetx,src_offsety,
        src_offsetx+src_sizex,src_offsety+src_sizey,
        dest_offsetx,dest_offsety,
        dest_offsetx+dest_sizex,dest_offsety+dest_sizey,
        GL_COLOR_BUFFER_BIT,GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER,previous_read);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,previous_draw);
}

void framebuffer::copy_framebuffer(const framebuffer& source, const framebuffer& destination, rectangle src_rect, rectangle dest_rect)
{
    int src_offsetx;
    int src_offsety;

    int src_sizex;
    int src_sizey;
    
    int dest_offsetx;
    int dest_offsety;

    int dest_sizex;
    int dest_sizey;

    src_rect.get_offset(&src_offsetx,&src_offsety);
    src_rect.get_size(&src_sizex,&src_sizey);
    dest_rect.get_offset(&dest_offsetx,&dest_offsety);
    dest_rect.get_size(&dest_sizex,&dest_sizey);
    copy_framebuffer(source,destination,src_offsetx,src_offsety,src_sizex,src_sizey,dest_offsetx,dest_offsety,dest_sizex,dest_sizey);
}

void framebuffer::copy_framebuffer(const framebuffer& source)
{
    copy_framebuffer(source,*get_defaultframebuffer());
}

void framebuffer::copy_framebuffer(const framebuffer& source, int sizex, int sizey)
{
    copy_framebuffer(source,*get_defaultframebuffer(),sizex,sizey);
}

void framebuffer::copy_framebuffer(const framebuffer& source, int offsetx, int offsety, int sizex, int sizey)
{
    copy_framebuffer(source,*get_defaultframebuffer(),offsetx,offsety,sizex,sizey);
}

void framebuffer::copy_framebuffer(const framebuffer& source, int src_offsetx, int src_offsety, int src_sizex, int src_sizey, int dest_offsetx, int dest_offsety, int dest_sizex, int dest_sizey)
{
    copy_framebuffer(source,*get_defaultframebuffer(),src_offsetx,src_offsety,src_sizex,src_sizey,dest_offsetx,dest_offsety,dest_sizex,dest_sizey);
}

void framebuffer::copy_framebuffer(const framebuffer& source, rectangle src_rect, rectangle dest_rect)
{
    copy_framebuffer(source,*get_defaultframebuffer(),src_rect,dest_rect);
}

framebuffer::~framebuffer()
{

}

framebuffer::rectangle::rectangle(int offsetx,int offsety,int sizex,int sizey)
{
    this->offsetx = offsetx;
    this->offsety = offsety;
    this->sizex = sizex;
    this->sizey = sizey;
}

framebuffer::rectangle::rectangle(int offsetx,int offsety):rectangle(0,0,offsetx,offsety)
{
}

void framebuffer::rectangle::get_offset(int *offsetX, int *offsetY)
{
    *offsetX = offsetx;
    *offsetY = offsety;
}

void framebuffer::rectangle::get_size(int *sizeX, int *sizeY)
{
    *sizeX = sizex;
    *sizeY = sizey;
}
