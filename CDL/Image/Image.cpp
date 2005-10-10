#include <CDL/Image/Image.h>
#include <GL/glu.h>

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif

namespace CDL
{
    DEFCLASS("Image");

    static const size_t g_channels[]=
    {
        0,1,2,3,4,3,4,2
    };
    static size_t g_ref=0;

    static struct Filter
    {
        size_t size, divisor, offset;
        int  kernel[25];
    }
    Filters[] =
    {
        3, 9, 0,   {1, 1, 1,                                 // BLUR
            1, 1, 1,
            1, 1, 1},
        3, 1, 0,   {0, -1,  0,                               // SHARPEN
            -1, 5, -1,
            0, -1, 0},
        3, 1, 128, {1, 1, 0,                                 // EMBOSS
            1, 0, -1,
            0, -1,-1},
        3, 1, 128, {-1, -1, -1,                              // EDGE
            -1,  8, -1,
            -1, -1, -1},
        3, 16, 0,  {1, 2, 1,                                 // BLUR
            2, 4, 2,
            1, 2, 1},
        5, 32, 0,  {0, 1, 2, 1, 0,                           // SMOOTH
            1, 1, 2, 1, 1,
            2, 2, 4, 2, 2,
            1, 1, 2, 1, 1,
            0, 1, 2, 1, 0}

    };

    bool identical(const Image &img1, const Image &img2)
    {
        return img1.getWidth()==img2.getWidth() && img1.getHeight()==img2.getHeight() && img1.getType()==img2.getType();
    }


    void Image::create(const size_t &width, const size_t &height, const Image_type &type, byte *data)
    {
        if (width<1 || height<1 || type<1)
        {
            m_width=0;
            m_height=0;
            m_type=NONE;
            m_channels=0;
            m_clean=false;
        }
        else
        {
            m_width=width;
            m_height=height;
            m_type=type;
            m_channels=g_channels[type];
            if (data)
            {
                m_clean=false;
                m_data=data;
            }
            else
            {
                m_clean=true;
                m_data=new byte[m_width*m_height*m_channels];
            }
        }
    }

    void Image::destroy()
    {
        m_width=0;
        m_height=0;
        m_type=NONE;
        m_channels=0;
        if (m_clean)
        {
            delete []m_data;
            m_data='\0';
        }
        m_clean=false;

    }

    Image::Image(const size_t &width, const size_t &height, const Image_type &type, byte *data)
    {
        create(width,height,type,data);
    }

    Image::~Image()
    {
        destroy();
    }

    Image::Image(const Image &img)
    {
        m_width=img.m_width;
        m_height=img.m_height;
        m_type=img.m_type;
        m_channels=img.m_channels;
        m_clean=img.m_clean;
        if (m_clean)
        {
            m_data=new byte[m_width*m_height*m_channels];
            memcpy(m_data, img.m_data, m_width*m_height*m_channels);
        }
        else
            m_data=img.m_data;
    }

    Image& Image::operator=(const Image &img)
    {
        if (this != &img)
        {
            bool erase=m_clean&&(m_width!=img.m_width||m_height!=img.m_height||m_channels!=img.m_channels||!img.m_type);
            m_width=img.m_width;
            m_height=img.m_height;
            m_channels=img.m_channels;

            if (erase)
            {
                delete []m_data;
                m_clean=false;
            }

            if (m_data != img.m_data && img.m_type)
            {
                if (erase || !m_type && img.m_clean)
                {
                    m_data=new byte[m_width*m_height*m_channels];
                    m_clean=true;
                }

                if (m_clean)
                    memcpy(m_data, img.m_data, m_width*m_height*m_channels);
                else
                {
                    m_data=img.m_data;
                    m_clean=false;
                }
            }

            m_type=img.m_type;
        }

        return *this;
    }

    Image Image::blend(const size_t &num, const Image tex[])
    {
        Image &alpha=*this;
        Image res(alpha.getWidth(), alpha.getHeight(), tex[0].getType());


        float step=256.0f/(num-1);
        for (size_t x=0; x<res.getWidth(); x++)
            for (size_t y=0; y<res.getHeight(); y++)
            {
                float height=(float)alpha(x,y);
                int   i=(int)(height/step), j=i+1;
                float f=height/step-i;
                for (size_t k=0; k<res.getChannels(); k++)
                {
                    byte c1=tex[i](x%tex[i].getWidth(),y%tex[i].getHeight(),k%tex[i].getChannels());
                    byte c2=tex[j](x%tex[j].getWidth(),y%tex[j].getHeight(),k%tex[j].getChannels());
                    res(x,y,k)=(byte)(c1*(1-f)+c2*f);
                }
            }

        return res;
    }

    void Image::alpha(const Image &img)
    {
        if (img.getWidth() != m_width || img.getHeight() != m_height)
        {
            Error_send("Unable to create alpha channel from an image of different size\n");
            return;
        }

        size_t channels, skip;
        if (img.getType()&1)
            channels=img.m_channels;
        else
            channels=img.m_channels-1;
        skip=img.m_channels-channels;

        size_t chans=m_channels;

        if (m_type&1)  // no dest alpha
        {
            m_type=(Image_type)(m_type+1);

            byte *newData=new byte[m_width*m_height*(m_channels+1)];

            byte *p=newData, *q=img.m_data, *r=m_data;
            size_t pixels=m_width*m_height;

            while (pixels--)
            {
                float intensity=0;
                for (size_t k=0; k<m_channels; k++)
                    *(p++)=*(r++);
                for (size_t k=0; k<channels; k++)
                    intensity+=*(q++);
                intensity/=channels;
                *(p++)=(byte)intensity;
                q+=skip;
            }

            m_channels++;
            if (m_clean)
                delete []m_data;
            m_data=newData;
            m_clean=true;
        }
        else
        {
            byte *p=m_data, *q=img.m_data;
            size_t pixels=m_width*m_height;
            size_t mskip=m_channels-1;

            while (pixels--)
            {
                float intensity=0;
                p+=mskip;
                for (size_t k=0; k<channels; k++)
                    intensity+=*(q++);
                intensity/=channels;
                *(p++)=(byte)intensity;
                q+=skip;
            }
        }
    }

    void Image::modulate(const Image &img)
    {
        byte *p=m_data;
        byte *q=img.m_data;
        size_t pixels=m_width*m_height;
        size_t alpha=img.m_channels-1;
        while (pixels--)
        {
            for (size_t k=0; k<m_channels; k++)
                *(p)=(byte)(*(p++)*((float)*(q+alpha)/255.0f));
            *q+=img.m_channels;
        }
    }

    void Image::resizeCanvas(const size_t &width,const size_t &height,const Image_alignment &x,const Image_alignment &y)
    {
        size_t mwidth=MIN(width,m_width), mheight=MIN(height,m_height);
        byte *data=new byte[width*height*m_channels];
        size_t stride1=m_width*m_channels, stride2=width*m_channels, stride=mwidth*m_channels;

        for (size_t i=0; i<mheight; i++)
            memcpy(m_data+i*stride1, data+i*stride2, stride);

        if (m_clean) delete []m_data;
        m_clean=true;
        m_width=width;
        m_height=height;
        m_data=data;
    }

    void Image::convert(const Image &img)
    {
        enum type_t {
            INVALID=0,
            ONE_TO_ONE,
            LUM_TO_LUMALPHA,
            LUM_TO_RGB,
            LUM_TO_RGBA,
            LUMALPHA_TO_LUM,
            LUMALPHA_TO_RGB,
            LUMALPHA_TO_RGBA,
            RGB_TO_LUM,
            RGB_TO_LUMALPHA,
            RGB_TO_BGR,
            RGB_TO_RGBA,
            RGB_TO_BGRA,
            RGBA_TO_LUM,
            RGBA_TO_LUMALPHA,
            RGBA_TO_RGB,
            RGBA_TO_BGR,
            RGBA_TO_BGRA,
            YUV422_TO_LUM,
            YUV422_TO_LUMALPHA,
            YUV422_TO_RGB,
            YUV422_TO_BGR,
            YUV422_TO_RGBA,
            YUV422_TO_BGRA,
            LUM_TO_YUV422,
            LUMALPHA_TO_YUV422,
            RGB_TO_YUV422,
            BGR_TO_YUV422,
            RGBA_TO_YUV422,
            BGRA_TO_YUV422
        } type=INVALID;
        int u, v, y1, y2, r, g, b, u1, u2, v1, v2;

        if (this == &img || m_data == img.m_data || !img.m_type || !m_type)
            return;

        if (m_width != img.m_width || m_height != img.m_height)
        {
            Image tmp;
            byte *data=img.m_data;
            if (m_type != img.m_type)
            {
                tmp=Image(img.m_width,img.m_height,m_type);
                tmp.convert(img);
                data=tmp.getData();
            }

            int fmt;
            switch (m_type)
            {
                case Image::LUMINANCE:
                    fmt=GL_LUMINANCE;
                    break;
                case Image::LUMINANCE_ALPHA:
                    fmt=GL_LUMINANCE_ALPHA;
                    break;
                case Image::RGB:
                    fmt=GL_RGB;
                    break;
                case Image::BGR:
                    fmt=GL_BGR;
                    break;
                case Image::RGBA:
                    fmt=GL_RGBA;
                    break;
                case Image::BGRA:
                    fmt=GL_BGRA;
                    break;
                default:
                    Error_send("Invalid format to convert %d\n", m_type);
                    return;
            }

            gluScaleImage(fmt,img.m_width,img.m_height,GL_UNSIGNED_BYTE,data,m_width,m_height,GL_UNSIGNED_BYTE,m_data);
            return;
        }

        switch(img.m_type)
        {
            case LUMINANCE:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=ONE_TO_ONE;
                        break;
                    case LUMINANCE_ALPHA:
                        type=LUM_TO_LUMALPHA;
                        break;
                    case RGB:
                    case BGR:
                        type=LUM_TO_RGB;
                        break;
                    case RGBA:
                    case BGRA:
                        type=LUM_TO_RGBA;
                        break;
                    case YUV422:
                        type=LUM_TO_YUV422;
                        break;
                }
                break;
            case LUMINANCE_ALPHA:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=LUMALPHA_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=ONE_TO_ONE;
                        break;
                    case RGB:
                    case BGR:
                        type=LUMALPHA_TO_RGB;
                        break;
                    case RGBA:
                    case BGRA:
                        type=LUMALPHA_TO_RGBA;
                        break;
                    case YUV422:
                        type=LUMALPHA_TO_YUV422;
                        break;
                }
                break;
            case RGB:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=RGB_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=RGB_TO_LUMALPHA;
                        break;
                    case RGB:
                        type=ONE_TO_ONE;
                        break;
                    case BGR:
                        type=RGB_TO_BGR;
                        break;
                    case RGBA:
                        type=RGB_TO_RGBA;
                        break;
                    case BGRA:
                        type=RGB_TO_BGRA;
                        break;
                    case YUV422:
                        type=RGB_TO_YUV422;
                        break;
                }
                break;
            case BGR:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=RGB_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=RGB_TO_LUMALPHA;
                        break;
                    case RGB:
                        type=RGB_TO_BGR;
                        break;
                    case BGR:
                        type=ONE_TO_ONE;
                        break;
                    case RGBA:
                        type=RGB_TO_BGRA;
                        break;
                    case BGRA:
                        type=RGB_TO_RGBA;
                        break;
                    case YUV422:
                        type=BGR_TO_YUV422;
                        break;
                }
                break;
            case RGBA:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=RGBA_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=RGBA_TO_LUMALPHA;
                        break;
                    case RGB:
                        type=RGBA_TO_RGB;
                        break;
                    case BGR:
                        type=RGBA_TO_BGR;
                        break;
                    case RGBA:
                        type=ONE_TO_ONE;
                        break;
                    case BGRA:
                        type=RGBA_TO_BGRA;
                        break;
                    case YUV422:
                        type=RGBA_TO_YUV422;
                        break;
                }
                break;
            case BGRA:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=RGBA_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=RGBA_TO_LUMALPHA;
                        break;
                    case RGB:
                        type=RGBA_TO_BGR;
                        break;
                    case BGR:
                        type=RGBA_TO_RGB;
                        break;
                    case RGBA:
                        type=RGBA_TO_BGRA;
                        break;
                    case BGRA:
                        type=ONE_TO_ONE;
                        break;
                    case YUV422:
                        type=BGRA_TO_YUV422;
                        break;
                }
                break;
            case YUV422:
                switch(m_type)
                {
                    case LUMINANCE:
                        type=YUV422_TO_LUM;
                        break;
                    case LUMINANCE_ALPHA:
                        type=YUV422_TO_LUMALPHA;
                        break;
                    case RGB:
                        type=YUV422_TO_RGB;
                        break;
                    case BGR:
                        type=YUV422_TO_BGR;
                        break;
                    case RGBA:
                        type=YUV422_TO_RGBA;
                        break;
                    case BGRA:
                        type=YUV422_TO_BGRA;
                        break;
                    case YUV422:
                        type=ONE_TO_ONE;
                        break;
                }
        }

        byte *p=m_data;
        byte *q=img.m_data;
        size_t pixels=m_width*m_height;

        switch(type)
        {
            case ONE_TO_ONE:
                memcpy(p,q,pixels*m_channels);
                break;
            case LUM_TO_LUMALPHA:
                while (pixels--)
                {
                    *(p++)=*(q++);
                    *(p++)=0;
                }
                break;
            case LUM_TO_RGB:
                while (pixels--)
                {
                    *(p++)=*q;
                    *(p++)=*q;
                    *(p++)=*(q++);
                }
                break;
            case LUM_TO_RGBA:
                while (pixels--)
                {
                    *(p++)=*q;
                    *(p++)=*q;
                    *(p++)=*(q++);
                    *(p++)=0;
                }
                break;
            case LUMALPHA_TO_LUM:
                while (pixels--)
                {
                    *(p++)=*(q++);
                    q++;
                }
                break;
            case LUMALPHA_TO_RGB:
                while (pixels--)
                {
                    *(p++)=*q;
                    *(p++)=*q;
                    *(p++)=*q++;
                    q++;
                }
                break;
            case LUMALPHA_TO_RGBA:
                while (pixels--)
                {
                    *(p++)=*q;
                    *(p++)=*q;
                    *(p++)=*(q++);
                    *(p++)=*(q++);
                }
                break;
            case RGB_TO_LUM:
                while (pixels--)
                {
                    *(p++)=(*(q++)+*(q++)+*(q++))/3;
                }
                break;
            case RGB_TO_LUMALPHA:
                while (pixels--)
                {
                    *(p++)=(*(q++)+*(q++)+*(q++))/3;
                    *(p++)=0;
                }
                break;
            case RGB_TO_BGR:
                while (pixels--)
                {
                    *(p++)=*(q+2);
                    *(p++)=*(q+1);
                    *(p++)=*(q+0);
                    q+=3;
                }
                break;
            case RGB_TO_RGBA:
                while (pixels--)
                {
                    *(p++)=*(q++);
                    *(p++)=*(q++);
                    *(p++)=*(q++);
                    *(p++)=0;
                }
                break;
            case RGB_TO_BGRA:
                while (pixels--)
                {
                    *(p++)=*(q+2);
                    *(p++)=*(q+1);
                    *(p++)=*(q+0);
                    *(p++)=0;
                    q+=3;
                }
                break;
            case RGBA_TO_LUM:
                while (pixels--)
                {
                    *(p++)=(*(q++)+*(q++)+*(q++))/3;
                    q++;
                }
                break;
            case RGBA_TO_LUMALPHA:
                while (pixels--)
                {
                    *(p++)=(*(q++)+*(q++)+*(q++))/3;
                    *(p++)=*(q++);
                }
                break;
            case RGBA_TO_RGB:
                while (pixels--)
                {
                    *(p++)=*(q++);
                    *(p++)=*(q++);
                    *(p++)=*(q++);
                    q++;
                }
                break;
            case RGBA_TO_BGR:
                while (pixels--)
                {
                    *(p++)=*(q+2);
                    *(p++)=*(q+1);
                    *(p++)=*(q+0);
                    q+=4;
                }
                break;
            case RGBA_TO_BGRA:
                while (pixels--)
                {
                    *(p++)=*(q+2);
                    *(p++)=*(q+1);
                    *(p++)=*(q+0);
                    *(p++)=*(q+3);
                    q+=4;
                }
                break;
            case LUM_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    *(p++)=128;
                    *(p++)=*(q++);
                    *(p++)=128;
                    *(p++)=*(q++);
                }
                break;
            case LUMALPHA_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    *(p++)=128;
                    *(p++)=*(q++);
                    *(q++);
                    *(p++)=128;
                    *(p++)=*(q++);
                    *(q++);
                }
                break;
            case RGB_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    r=*(q++);
                    g=*(q++);
                    b=*(q++);

                    y1=(int)(0.299*r+0.587*g+0.114*b);
                    u1=(int)((b-y1)*0.565);
                    v1=(int)((r-y1)*0.713);

                    r=*(q++);
                    g=*(q++);
                    b=*(q++);

                    y2=(int)(0.299*r+0.587*g+0.114*b);
                    u2=(int)((b-y2)*0.565);
                    v2=(int)((r-y2)*0.713);

                    u=((u1+u2)>>1)+128;
                    v=((v1+v2)>>1)+128;

                    *(p++)=CLAMP(0,u,255);
                    *(p++)=CLAMP(0,y1,255);
                    *(p++)=CLAMP(0,v,255);
                    *(p++)=CLAMP(0,y2,255);
                }
                break;
            case RGBA_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    r=*(q++);
                    g=*(q++);
                    b=*(q++);
                    q++;

                    y1=(int)(0.299*r+0.587*g+0.114*b);
                    u1=(int)((b-y1)*0.565);
                    v1=(int)((r-y1)*0.713);

                    r=*(q++);
                    g=*(q++);
                    b=*(q++);
                    q++;

                    y2=(int)(0.299*r+0.587*g+0.114*b);
                    u2=(int)((b-y2)*0.565);
                    v2=(int)((r-y2)*0.713);

                    u=((u1+u2)>>1)+128;
                    v=((v1+v2)>>1)+128;

                    *(p++)=CLAMP(0,u,255);
                    *(p++)=CLAMP(0,y1,255);
                    *(p++)=CLAMP(0,v,255);
                    *(p++)=CLAMP(0,y2,255);
                }
                break;
            case BGR_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    b=*(q++);
                    g=*(q++);
                    r=*(q++);

                    y1=(int)(0.299*r+0.587*g+0.114*b);
                    u1=(int)((b-y1)*0.565);
                    v1=(int)((r-y1)*0.713);

                    b=*(q++);
                    g=*(q++);
                    r=*(q++);

                    y2=(int)(0.299*r+0.587*g+0.114*b);
                    u2=(int)((b-y2)*0.565);
                    v2=(int)((r-y2)*0.713);

                    u=((u1+u2)>>1)+128;
                    v=((v1+v2)>>1)+128;

                    *(p++)=CLAMP(0,u,255);
                    *(p++)=CLAMP(0,y1,255);
                    *(p++)=CLAMP(0,v,255);
                    *(p++)=CLAMP(0,y2,255);
                }
                break;
            case BGRA_TO_YUV422:
                while (pixels--)
                {
                    pixels--;
                    b=*(q++);
                    g=*(q++);
                    r=*(q++);
                    q++;

                    y1=(int)(0.299*r+0.587*g+0.114*b);
                    u1=(int)((b-y1)*0.565);
                    v1=(int)((r-y1)*0.713);

                    b=*(q++);
                    g=*(q++);
                    r=*(q++);
                    q++;

                    y2=(int)(0.299*r+0.587*g+0.114*b);
                    u2=(int)((b-y2)*0.565);
                    v2=(int)((r-y2)*0.713);

                    u=((u1+u2)>>1)+128;
                    v=((v1+v2)>>1)+128;

                    *(p++)=CLAMP(0,u,255);
                    *(p++)=CLAMP(0,y1,255);
                    *(p++)=CLAMP(0,v,255);
                    *(p++)=CLAMP(0,y2,255);
                }
                break;
            case YUV422_TO_LUM:
                while (pixels--)
                {
                    q++;
                    *(p++)=*(q++);
                }
                break;
            case YUV422_TO_LUMALPHA:
                while (pixels--)
                {
                    q++;
                    *(p++)=*(q++);
                    *(p++)=0;
                }
                break;
            case YUV422_TO_RGB:
                while (pixels--)
                {
                    pixels--;
                    u=*(q++)-128;
                    y1=*(q++);
                    v=*(q++)-128;
                    y2=*(q++);

                    r=(int)(y1+1.403*v);
                    g=(int)(y1-0.344*u-0.714*v);
                    b=(int)(y1+1.770*u);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,b,255);

                    r=(int)(y2+1.403*v);
                    g=(int)(y2-0.344*u-0.714*v);
                    b=(int)(y2+1.770*u);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,b,255);
                }
                break;
            case YUV422_TO_RGBA:
                while (pixels--)
                {
                    pixels--;
                    u=*(q++)-128;
                    y1=*(q++);
                    v=*(q++)-128;
                    y2=*(q++);

                    r=(int)(y1+1.403*v);
                    g=(int)(y1-0.344*u-0.714*v);
                    b=(int)(y1+1.770*u);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=0;

                    r=(int)(y2+1.403*v);
                    g=(int)(y2-0.344*u-0.714*v);
                    b=(int)(y2+1.770*u);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=0;
                }
                break;
            case YUV422_TO_BGR:
                while (pixels--)
                {
                    pixels--;
                    u=*(q++)-128;
                    y1=*(q++);
                    v=*(q++)-128;
                    y2=*(q++);

                    r=(int)(y1+1.403*v);
                    g=(int)(y1-0.344*u-0.714*v);
                    b=(int)(y1+1.770*u);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,r,255);

                    r=(int)(y2+1.403*v);
                    g=(int)(y2-0.344*u-0.714*v);
                    b=(int)(y2+1.770*u);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,r,255);
                }
                break;
            case YUV422_TO_BGRA:
                while (pixels--)
                {
                    pixels--;
                    u=*(q++)-128;
                    y1=*(q++);
                    v=*(q++)-128;
                    y2=*(q++);

                    r=(int)(y1+1.403*v);
                    g=(int)(y1-0.344*u-0.714*v);
                    b=(int)(y1+1.770*u);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=0;

                    r=(int)(y2+1.403*v);
                    g=(int)(y2-0.344*u-0.714*v);
                    b=(int)(y2+1.770*u);
                    *(p++)=CLAMP(0,b,255);
                    *(p++)=CLAMP(0,g,255);
                    *(p++)=CLAMP(0,r,255);
                    *(p++)=0;
                }
                break;
            case INVALID:
                break;
            default:
                Error_send("Not implemented\n");
        }
    }

    void Image::filter(const Image &src, const Image_filter &effect)
    {
        if (!identical(*this,src))
        {
            if (m_clean)
                destroy();
            create(src.m_width,src.m_height,src.m_type, '\0');
        }

        size_t sum;
        Filter &flt=Filters[effect];
        size_t edge=flt.size/2;

        for (size_t x=edge; x<m_width-edge; x++)
            for (size_t y=edge; y<m_height-edge; y++)
                for  (size_t k=0; k<m_channels; k++)
                {
                    sum=0;
                    for (size_t i=0; i<flt.size; i++)
                        for (size_t j=0; j<flt.size; j++)
                            sum+=src.m_data[(x-edge+i+(y-edge+j)*m_width)*m_channels+k]*flt.kernel[i+j*flt.size];
                    sum/=flt.divisor;
                    sum+=flt.offset;
                    m_data[(x+y*m_width)*m_channels+k]=(byte)sum;
                }
    }

    void Image::interlace()
    {
        size_t rowstride=m_width*m_channels;

        for (size_t y=0; y<m_height; y+=2)
            memcpy(m_data+(y+1)*rowstride, m_data+y*rowstride, rowstride);
    }

    void Image::flip()
    {
        size_t rowstride=m_width*m_channels;
        byte row[rowstride];

        for (size_t y=0; y<m_height/2; y++)
        {
            memcpy(row,m_data+(m_height-y-1)*rowstride,rowstride);
            memcpy(m_data+(m_height-y-1)*rowstride,m_data+y*rowstride,rowstride);
            memcpy(m_data+y*rowstride, row, rowstride);
        }
    }

    void Image::mirror()
    {
        for (size_t x=0; x<m_width/2; x++)
            for (size_t y=0; y<m_height; y++)
                for (size_t c=0; c<m_channels; c++)
                {
                    byte b0=m_data[(m_width-x-1+m_width*y)*m_channels+c];
                    m_data[(m_width-x-1+m_width*y)*m_channels+c]=m_data[(x+m_width*y)*m_channels+c];
                    m_data[(x+m_width*y)*m_channels+c]=b0;
                }
    }

    void Image::invert()
    {
        mirror();
        flip();
    }
}
