#include "./glfw_glew_include.h"
#include "./vertex_buffer.h"
#include "./indices_buffer.h"

#ifndef VAO_HEADER
#define VAO_HEADER

template<typename T>
class vao
{
    public:
        enum class render_mode
        {
            POINTS,
            LINES,
            LINE_STRIP,
            LINE_LOOP,
            TRIANGLES,
            TRIANGLE_STRIP,
            TRIANGLE_FAN,
            PATCHES
        };
    private:
        GLuint id;
        GLuint vertex_id;
        vertex_buffer* buffer;
        indices_buffer* indexes;
        GLsizei length;
        GLenum mode;
        inline static const std::unordered_map<vao::render_mode,GLenum> render_modes =
        {
            {vao::render_mode::POINTS,GL_POINTS},
            {vao::render_mode::LINES,GL_LINES},
            {vao::render_mode::LINE_STRIP,GL_LINE_STRIP},
            {vao::render_mode::LINE_LOOP,GL_LINE_LOOP},
            {vao::render_mode::TRIANGLES,GL_TRIANGLES},
            {vao::render_mode::TRIANGLE_STRIP,GL_TRIANGLE_STRIP},
            {vao::render_mode::TRIANGLE_FAN,GL_TRIANGLE_FAN},
            {vao::render_mode::PATCHES,GL_PATCHES}
        };
    public:
        /**
         * @brief contructor of vao
         * @param vertices pointer to vertex array
         * @param length number of elements in vertex array
         * @param indices pointer to index array
         * @param number of elements in index array
         */
        vao(T* vertices,int length,unsigned int* indices,GLsizei index_count);
        vao(T* vertices,int length,unsigned int* indices,GLsizei index_count,vao::render_mode mode);
        /**
         * @brief allows vao to be remodelled
         * @param vertices pointer to vertex array
         * @param length number of elements in vertex array
         * @param indices pointer to index array
         * @param number of elements in index array
         * @param mode render mode of model;
         */
        void remodel(T*vertices,int length,unsigned int* indices,GLsizei index_count, vao::render_mode mode);
        void set_mode(vao::render_mode mode);
        void bind();
        void unbind();
        /**
         * @brief defines attributes and automatically enables it
         * @param index index of attribute
         * @param number_of_comp number of component for that attribute 1 2 3 4
         * @param stride number of elements in one vertex
         * @param offset starting index of attribute. any primintive type.
         */
        void define_attributes(int index,int number_of_comp,int stride,int offset);
        void draw();
        void draw(int vertex_number);
        ~vao();
};

#include "./vao.tpp"

#endif
