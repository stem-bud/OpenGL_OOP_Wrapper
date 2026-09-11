/*#pragma once
#include <unordered_map>
#include "glfw_glew_include.h"
#include "vao.h"
using byte = std::byte;
#ifndef MODEL_HEADER
#define MODEL_HEADER

template<typename T>class model
{
    private:
        vao* my_vao = nullptr;
        int ind_num;
    public:
        model(const model&) = delete;
        model& operator=(const model&) = delete;
        model(model&& other) = delete;
        model& operator=(model&& other) = delete;
        model() = delete;
        model(T* data,int length,unsigned int* indices,int indices_count);
        model(T* data,int length,unsigned int* indices,int indices_count,model<T>::render_mode mode);
        void set_mode(model::render_mode mode);
        void draw();
        ~model();
};

#include "model.tpp"

#endif*/
