
#include "./shader.h"
#include <fstream>
#include <vector>

Shader::Shader(std::string path)
{

    std::string::size_type pos = path.find_last_not_of(
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "._0123456789"
    );

    //std::cout << path.substr(pos + 1) << std::endl;
    //std::smatch matches;
    //std::regex_search(path,matches,std::regex("[a-zA-Z\\._0-9]+$"));

    //std::cout << matches[0].str() << std::endl;
    std::ifstream file(path);
    std::string line;
    std::string vertexShader;
    std::string fragmentShader;
    std::string geometryShader;
    std::string tesselControl;
    std::string tesselEval;
    bool isNull = false;
    std::string * tobeStrung;
    while(getline(file,line))
    {
        if(line.find("#shader Vertex") != std::string::npos)
        {
            tobeStrung = &vertexShader;
            isNull = false;
            continue;
        }

        if(line.find("#shader Fragment") != std::string::npos)
        {
            tobeStrung = &fragmentShader;
            isNull = false;
            continue;
        }

        if(line.find("#shader Geometry") != std::string::npos)
        {
            tobeStrung = &geometryShader;
            isNull = false;
            continue;
        }

        if(line.find("#shader Tessel Control") != std::string::npos)
        {
            tobeStrung = &tesselControl;
            isNull = false;
            continue;
        }

        if(line.find("#shader Tessel Evaluate")!= std::string::npos)
        {
            tobeStrung = &tesselEval;
            isNull = false;  
            continue; 
        }

        if(line.find("#shader") != std::string::npos)
        {
            tobeStrung = nullptr;
            isNull = true;
            continue;
        }

        if(!isNull)
        {
            *tobeStrung+=line+"\n";
        }
    }   

    GLuint vertShader = compile_shader(vertexShader,GL_VERTEX_SHADER);
    GLuint fragShader = compile_shader(fragmentShader,GL_FRAGMENT_SHADER);
    GLuint geomShader = compile_shader(geometryShader,GL_GEOMETRY_SHADER);
    GLuint tessconShader = compile_shader(tesselControl,GL_TESS_CONTROL_SHADER);
    GLuint tessEvShader = compile_shader(tesselEval,GL_TESS_EVALUATION_SHADER);
    
    program = glCreateProgram();
    glAttachShader(program,vertShader);

    if(tessconShader!=0)
    {
        glAttachShader(program,tessconShader);
    }

    if(tessEvShader!=0)
    {
        glAttachShader(program,tessEvShader);
    }

    if(geomShader!=0)
    {
        glAttachShader(program,geomShader);
    }

    glAttachShader(program,fragShader);
    glLinkProgram(program);

    /*GLint isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        GLint logLength;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, &errorLog[0]);
        //std::cout << "PROGRAM LINKING ERROR:\n" << errorLog.data() << std::endl;
    }*/

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteShader(geomShader);
    glDeleteShader(tessconShader);
    glDeleteShader(tessEvShader);
    bind();
}

GLuint Shader::compile_shader(std::string shader,GLuint type)
{
    if(shader.length() == 0)
    {
        //no shader found
        //std::cerr << "no shader found " <<  std::endl;
        return 0;
    }
    const char * shaderSource = shader.c_str();
    unsigned int id = glCreateShader(type);
    glShaderSource(id,1,&shaderSource,nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE)
    {   
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        //std::cout << (type == GL_VERTEX_SHADER? "vertex shader":type==GL_FRAGMENT_SHADER?"fragmanet shader":type==GL_GEOMETRY_SHADER?"geometry shader":type == GL_TESS_CONTROL_SHADER?"tessellation control shader":"tessellation evaluation shader") << " error" << std::endl;
        //std::cerr << message << std::endl;
        
    }
    if(id == 0)
    {
        //std::cerr << "shader error" << std::endl;
    }
    return id;
}


GLuint Shader::get_shader_program() const
{
    return program;
}

void Shader::bind()
{
    Shader::active_program = this;
    glUseProgram(program);
}

void Shader::sample(texture& tex,const char *name,int location)
{
    if(!tex.is_samplable())
    {
        //std::cerr << "texture not samplable" << std::endl; 
        return;
    }
    bind();
    tex.bind(location);
    GLint texLocation = glGetUniformLocation(program,static_cast<const GLchar*>(name));
    glUniform1i(texLocation,static_cast<GLint>(location));
}

void Shader::sample(texture& tex, std::string name,int location)
{
    sample(tex,name.c_str(),location);
}

void Shader::unbind()
{
    glUseProgram(0);
}

Shader* Shader::current_program()
{
    return active_program;
}

Shader::~Shader()
{
    if(active_program == this)
    {
        active_program = nullptr;
    }
    glDeleteProgram(program);
}