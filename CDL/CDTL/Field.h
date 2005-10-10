//========================================================================
/** @type     C/C++ Header File
 *  @file     Field.h
 *  @author   acornejo
 *  @date
 *   Created:       21:36:35 28/05/2005
 *   Last Update:   02:12:30 23/06/2005
 */
//========================================================================

#ifndef __CDL_FIELD_H__
#define __CDL_FIELD_H__

#include <CDL/defs.h>
#include <cstdarg>

namespace CDL
{
    namespace CDTL
    {
        template <class Type>
            class Field
            {
                private:
                    static const char *__class__;

                protected:
                    Type *m_field;
                    size_t m_dimensions;
                    size_t m_totalSize;
                    size_t *m_length;

                public:
                    Field(const size_t &dim=0);
                    Field(const Field &);
                    virtual ~Field();
                    Field &operator=(const Field &);
                    Type       &operator()(const size_t & ...);
                    const Type &operator()(const size_t & ...) const;
                    const size_t &getDimensions() const;
                    void setDimensions(const size_t &);
                    const size_t &getLength(const size_t &) const;
                    void setLength(const size_t &, const size_t &);
                    size_t getHash(const size_t & ...) const;
                    const Type &getHashValue(const size_t &) const;
                    void setHashValue(const size_t &, const Type &);
            };
    }
}




























namespace CDL
{
    namespace CDTL
    {

#define __FieldHASH(dim,x,offset) {offset=x;va_list ap;va_start(ap, x);for(size_t i=1; i<dim; i++) offset=offset*m_length[i]+(size_t)va_arg(ap, size_t);va_end(ap);}
        template <class Type>
            const char *Field<Type>::__class__="Field<Type>";

        template <class Type>
            Field<Type>::Field(const size_t &dimensions)
            {
                m_field='\0';
                m_totalSize=0;
                m_dimensions=dimensions;
                if (m_dimensions)
                {
                    m_length=new size_t[m_dimensions];
                    memset(m_length, 0, m_dimensions*sizeof(size_t));
                }
                else
                    m_length='\0';
            }

        template <class Type>
            Field<Type>::Field(const Field &f)
            {
                m_dimensions=f.m_dimensions;
                m_totalSize=f.m_totalSize;
                if (m_dimensions)
                {
                    m_length=new size_t[m_dimensions];
                    memcpy(m_length, f.m_length, sizeof(size_t)*m_dimensions);
                }
                else
                    m_length='\0';
                if (f.m_field)
                {
                    m_field=new Type[m_totalSize];
                    memcpy(m_field, f.m_field, sizeof(Type)*m_totalSize);
                }
                else
                    m_field='\0';
            }

        template <class Type>
            Field<Type>::~Field()
            {
                if (m_field)  delete []m_field;
                if (m_length) delete []m_length;
            }

        template <class Type>
            const size_t &Field<Type>::getDimensions() const
            {
                return m_dimensions;
            }

        template <class Type>
            void Field<Type>::setDimensions(const size_t &dim)
            {
                if (dim != m_dimensions)
                {
                    if (m_length) delete []m_length;
                    if (m_field)  delete []m_field;
                    m_field='\0';
                    m_totalSize=0;
                    m_dimensions=dim;
                    m_length=new size_t[m_dimensions];
                    memset(m_length, 0, sizeof(size_t)*m_dimensions);
                }
            }

        template <class Type>
            const size_t &Field<Type>::getLength(const size_t &dim) const
            {
                if (dim < m_dimensions)
                    return m_length[dim];
                else
                {
                    Error_send("Index %d exceeds dimensions %d\n", dim, m_dimensions);
                    return m_length[0];
                }
            }

        template <class Type>
            void Field<Type>::setLength(const size_t &dim, const size_t &length)
            {
                if (dim < m_dimensions)
                {
                    if (m_length[dim] != length)
                    {
                        m_length[dim]=length;
                        if (m_field) delete []m_field;
                        for (int i=0; i<m_dimensions; i++)
                            if (!m_length[i]) return;

                        m_totalSize=1;
                        for (int i=0; i<m_dimensions; i++)
                            m_totalSize*=m_length[i];
                        m_field=new Type[m_totalSize];
                    }
                }
                else
                {
                    Error_send("Index %d exceeds dimensions %d\n", dim, m_dimensions);
                }
            }

        template <class Type>
            Type &Field<Type>::operator()(const size_t &index0 ...)
            {
                if (m_field)
                {
                    size_t hash;
                    __FieldHASH(m_dimensions, index0, hash);

                    if (hash >= m_totalSize)
                    {
                        Error_send("Hash %d exceeds maximum of %d\n", hash, m_totalSize);
                        return m_field[0];
                    }
                    else
                        return m_field[hash];
                }
                else
                {
                    Error_send("Size not yet defined in all dimensions\n");
                    return m_field[0];
                }
            }

        template <class Type>
            const Type &Field<Type>::operator()(const size_t &index0 ...) const
            {
                if (m_field)
                {
                    size_t hash;
                    __FieldHASH(m_dimensions, index0, hash);

                    if (hash >= m_totalSize)
                    {
                        Error_send("Hash %d exceeds maximum of %d\n", hash, m_totalSize);
                        return m_field[0];
                    }
                    else
                        return m_field[hash];
                }
                else
                {
                    Error_send("Size not yet defined in all dimensions\n");
                    return m_field[0];
                }
            }

        template<class Type>
            size_t Field<Type>::getHash(const size_t &index0 ...) const
            {
                size_t hash=0;

                if (m_field)
                {
                    __FieldHASH(m_dimensions, index0, hash);

                    if (hash >= m_totalSize)
                    {
                        Error_send("Hash %d exceeds maximum of %d\n", hash, m_totalSize);
                    }
                }
                else
                {
                    Error_send("Size not yet defined in all dimensions\n");
                }

                return hash;
            }

        template<class Type>
            const Type &Field<Type>::getHashValue(const size_t &hash) const
            {
                if (m_field)
                {
                    if (hash >= m_totalSize)
                    {
                        Error_send("Hash %d exceeds maximum of %d\n", hash, m_totalSize);
                        return m_field[0];
                    }
                    else
                        return m_field[hash];
                }
                else
                {
                    Error_send("Size not yet defined in all dimensions\n");
                    return m_field[0];
                }
            }

        template<class Type>
            void Field<Type>::setHashValue(const size_t &hash, const Type &v)
            {
                if (m_field)
                {
                    if (hash >= m_totalSize)
                    {
                        Error_send("Hash %d exceeds maximum of %d\n", hash, m_totalSize);
                    }
                    else
                        m_field[hash]=v;
                }
                else
                {
                    Error_send("Size not yet defined in all dimensions\n");
                }
            }
    }
}
#endif//__CDL_FIELD_H__
