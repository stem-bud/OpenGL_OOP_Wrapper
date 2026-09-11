#include "texture.h"
class image
{
    public:
        enum class bind_state
        {
            READ_ONLY,
            WRITE_ONLY,
            READ_AND_WRITE
        };
    private:
        GLuint id;
        texture::internal_format inner_format;
        unsigned int bind_unit = 0;
    public:
        image() = delete;
        image(const texture& texture);
        //image(texture::internal_format format,int sizex, int sizey);
        void bind();
        void bind(bind_state bind_state);
        void bind(bind_state bind_state,int bind_unit);
        void unbind();
};
