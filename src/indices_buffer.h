#ifndef INDICES_BUFFER_HEADER
#define INDICES_BUFFER_HEADER
#include "./glfw_glew_include.h"
class indices_buffer
{
    private:
        GLuint id;
    public:
        indices_buffer(unsigned int* indices,int length);
        indices_buffer(const indices_buffer&) = delete;
        indices_buffer& operator=(const indices_buffer&) = delete;
        indices_buffer(indices_buffer&& other) = delete;
        indices_buffer& operator=(indices_buffer&& other) = delete;
        void bind();
        void unbind();
        ~indices_buffer();
};
#endif
