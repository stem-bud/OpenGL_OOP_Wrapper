#include "./glfw_glew_include.h"
#include "./texture.h"

#ifndef SHADER_H_DEF
#define SHADER_H_DEF
class Shader
{
    private:
        GLuint program;
        static GLuint compile_shader(std::string shader,GLuint type);
        static inline Shader* active_program;
    public:
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&&)=delete;
        Shader& operator=(Shader&&)=delete;
        Shader(std::string path);
        Shader() = delete;
        GLuint get_shader_program()const;
        void bind();
        void sample(texture& tex,const char* name,int location);
        void sample(texture& tex,std::string name,int location);
        static void unbind();
        static Shader* current_program();
        ~Shader();
};
#endif
