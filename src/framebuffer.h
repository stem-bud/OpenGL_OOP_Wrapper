#include "texture.h"
#include <vector>

#ifndef FRAMEBUFFER_HEADER
#define FRAMEBUFFER_HEADER
/**
 * @brief opengl framebuffer wrapper
 */
class framebuffer
{
    public:
        /**
         * @brief rectangle class for copying framebuffers
         */
        class rectangle
        {
            private:
                int offsetx;
                int offsety;
                int sizex;
                int sizey;
            public:
                rectangle(int offsetx,int offsety,int sizex,int sizey);
                rectangle(int sizex,int sizey);
                /**
                 * @brief returns offset of rectangle
                 * @param offsetX location to where x offset gets written to
                 * @param offsetY location to where y offset gets written to
                 */
                void get_offset(int*offsetX,int*offsetY);
                /**
                 * @brief returns size of rectangle
                 * @param sizeX location to where x dimenstion gets written to
                 * @param sizeY location to where y dimenstion gets written to
                 */
                void get_size(int*sizeX,int*sizeY);
        };
    private:
        unsigned int framebuffer_id;
        int sizex=-1;
        int sizey=-1;
        static inline framebuffer* default_framebuffer = nullptr;
        std::vector<texture> textures;
    public:
        framebuffer();
        /**
         * @brief binds the framebuffer
         */
        void bind();
        /**
         * @brief binds default framebuffer
         */
        void unbind();
        /**
         * @brief returns id of the framebuffer
         * @returns id of the framebuffer
         */
        unsigned int get_id() const;
        /**
         * @brief attaches a texture as an attachment to the framebuffer
         * @param attachment texture to be attached
         * @param location which location starting from 0 to at least 7 for color attachments
         */
        void add_attachment(const texture& attachment,int location);
        /**
         * @brief attaches a texture as an attachment to the framebuffer at location 0
         * @param attachment texture to be attached
         */
        void add_attachment(const texture& attachment);
        /**
         * @brief returns size of framebuffer
         * @param width pointer to where width gets written to
         * @param height pointer to where height gets written to
         */
        void get_size(int*width,int*height);
        /**
         * @brief resizes framebuffer
         * @param width new width dimension
         * @param height new height dimension
         */
        //void resize(int width, int height);

        /**
         * @brief returns a pointer to the default framebuffer
         * @return a pointer to the default framebuffer
         */
        static framebuffer* get_defaultframebuffer();
        static void init_default_framebuffer();
        /**
         * @brief sets the size of the default framebuffer
         * @param sizex x dimension
         * @param sizey y dimenstion
         */
        static void set_default_framebuffer_size(int sizex,int sizey);
        
        /**
         * @brief copies source framebuffer into the destination framebuffer. compresses or stretches as necessary.
         * @param source source framebuffer
         * @param destination destination framebuffer
         */
        static void copy_framebuffer(const framebuffer& source,const framebuffer& destination);
        /**
         * @brief copies recangular section from source framebuffer into the destination framebuffer starting from bottom left 0,0
         * @param source source framebuffer
         * @param destination destination
         * @param sizex x dimenstion of rectangle
         * @param sizey y dimension rectangle
         */
        static void copy_framebuffer(const framebuffer& source,const framebuffer& destination,int sizex,int sizey);
        /**
         * @brief copies recangular section from source framebuffer into the destination framebuffer 
         * @param source source framebuffer
         * @param destination destination framebuffer
         * @param offsetx x offset of rectangular section starting from bottom left
         * @param offsety y offset of rectangular section starting from bottom left
         * @param sizex x dimenstion of rectangle
         * @param sizey y dimension rectangle
         */
        static void copy_framebuffer(const framebuffer& source,const framebuffer& destination,int offsetx,int offsety,int sizex,int sizey);
        /**
         * @brief copies recangular section from source framebuffer into a rectangular section in the destination framebuffer
         * @param source source framebuffer
         * @param destination destination framebuffer
         * @param src_offsetx x offset of source rectangular section starting from bottom left
         * @param src_offsety y offset of source rectangular section starting from bottom left
         * @param src_sizex x dimension of source rectangle
         * @param src_sizey y dimension of source rectangle
         * @param dest_offsetx x offset of destination rectangular section starting from bottom left
         * @param dest_offsety y offset of destination rectangular section starting from bottom left
         * @param dest_sizex x dimension of destination rectangle
         * @param dest_sizey x dimension of destination rectangle
         */
        static void copy_framebuffer(const framebuffer& source,const framebuffer& destination,int src_offsetx,int src_offsety,int src_sizex,int src_sizey,int dest_offsetx,int dest_offsety,int dest_sizex,int dest_sizey);
        /**
         * @brief copies recangular section from source framebuffer into a rectangular section in the destination framebuffer
         * @param source source framebuffer
         * @param destination destination framebuffer
         * @param src_rect source rectangle
         * @param dest_rect destination rectangle
         */
        static void copy_framebuffer(const framebuffer& source,const framebuffer& destination,rectangle src_rect,rectangle dest_rect);
        /**
         * @brief copies source framebuffer into default framebuffer. compresses or stretches as necessary.
         * @param source source framebuffer
         */
        static void copy_framebuffer(const framebuffer& source);
        /**
         * @brief copies recangular section from source framebuffer into default framebuffer starting from bottom left 0,0
         * @param source source framebuffer
         * @param sizex x dimenstion of rectangle
         * @param sizey y dimension rectangle
         */
        static void copy_framebuffer(const framebuffer& source,int sizex,int sizey);
        /**
         * @brief copies recangular section from source framebuffer into default framebuffer 
         * @param source source framebuffer
         * @param offsetx x offset of rectangular section starting from bottom left
         * @param offsety y offset of rectangular section starting from bottom left
         * @param sizex x dimenstion of rectangle
         * @param sizey y dimension rectangle
         */
        static void copy_framebuffer(const framebuffer& source,int offsetx,int offsety,int sizex,int sizey);
        /**
         * @brief copies recangular section from source framebuffer into a rectangular section in the default framebuffer
         * @param source source framebuffer
         * @param src_offsetx x offset of source rectangular section starting from bottom left
         * @param src_offsety y offset of source rectangular section starting from bottom left
         * @param src_sizex x dimension of source rectangle
         * @param src_sizey y dimension of source rectangle
         * @param dest_offsetx x offset of destination rectangular section starting from bottom left
         * @param dest_offsety y offset of destination rectangular section starting from bottom left
         * @param dest_sizex x dimension of destination rectangle
         * @param dest_sizey x dimension of destination rectangle
         */
        static void copy_framebuffer(const framebuffer& source,int src_offsetx,int src_offsety,int src_sizex,int src_sizey,int dest_offsetx,int dest_offsety,int dest_sizex,int dest_sizey);
        /**
         * @brief copies recangular section from source framebuffer into a rectangular section in the default framebuffer
         * @param source source framebuffer
         * @param src_rect source rectangle
         * @param dest_rect destination rectangle
         */
        static void copy_framebuffer(const framebuffer& source,rectangle src_rect,rectangle dest_rect);
        ~framebuffer();
};

#endif