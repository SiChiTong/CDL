#ifndef __CDL_IMAGE_H__
#define __CDL_IMAGE_H__

#include <CDL/defs.h>

namespace CDL
{
    typedef unsigned char byte;

    class DLL_API Image
    {
        public:
            typedef enum {BLUR=0, SHARPEN, EMBOSS, EDGE, GAUSS_BLUR, SMOOTH, MAX_IMG_FILTERS} Image_filter;
            typedef enum {NONE=0, LUMINANCE, LUMINANCE_ALPHA, RGB, RGBA, BGR, BGRA, YUV422} Image_type;
			typedef enum {LEFT=0, RIGHT=1, CENTER=2} Image_halignment;
			typedef enum {TOP=0, BOTTOM=1, MIDDLE=2} Image_valignment;

        protected:
            byte*        m_data;
            size_t       m_width;
            size_t       m_height;
            Image_type   m_type;
            size_t       m_channels;
            bool         m_clean;

            void create(const size_t &, const size_t &, const Image_type &, byte *d='\0');
            void copy(const Image &);
            void destroy();

        public:
            Image(const size_t &x=0, const size_t &y=0, const Image_type &t=RGB, byte *d='\0');
            virtual ~Image();
            Image(const Image &);
            Image& operator=(const Image &);

            byte& operator()(const size_t &i, const size_t &j, const size_t &c=0)\
                {return m_data[(j*m_width+i)*m_channels+c];}
            byte  operator()(const size_t &i, const size_t &j, const size_t &c=0) const\
                {return m_data[(j*m_width+i)*m_channels+c];}

            byte *            getData()     const {return m_data;}
            const size_t     &getWidth()    const {return m_width;}
            const size_t     &getHeight()   const {return m_height;}
            const Image_type &getType()     const {return m_type;}
            const size_t     &getChannels() const {return m_channels;}

            Image blend(const size_t &, const Image tex[]);
            void alpha(const Image &);
            void modulate(const Image &);
            void convert(const Image &);
			void resizeCanvas(const size_t&,const size_t&,const Image_halignment &x=LEFT,const Image_valignment &y=TOP);
            void filter(const Image &, const Image_filter &);
            void interlace();
            void flip();
            void mirror();
            void invert();
    };
}

#include <CDL/Image/ImageLib.h>

#endif//__CDL_IMAGE_H__
