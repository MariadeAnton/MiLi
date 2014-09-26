/*
binary_streams: A minimal library supporting encoding of different data
                types in a single binary stream.
    Copyright (C) 2009, 2010  Guillermo Biset,
                  2012 Matias Tripode, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BINARY_STREAMS_H
#define BINARY_STREAMS_H


#include <string>
#include <assert.h>
#include <stdint.h>
#include <stdexcept>
#include <typeinfo>

#include "compile_assert.h"
#include "generic_exception.h"
#include "template_info.h"
#include "container_utils.h"



NAMESPACE_BEGIN

declare_static_assert(pointers_not_allowed);
declare_static_assert(must_use_container);

class BstreamExceptionHierarchy {};

typedef GenericException< BstreamExceptionHierarchy> BstreamException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_not_finished,
                               BstreamExceptionHierarchy,
                               "More elements were expected to be written.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_finished,
                               BstreamExceptionHierarchy,
                               "The container was finished already.");


DEFINE_SPECIFIC_EXCEPTION_TEXT(stream_too_small,
                               BstreamExceptionHierarchy,
                               "Stream is too small for read size, maybe not a container.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(skip_excess,
                               BstreamExceptionHierarchy,
                               "Trying to skip too much.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(type_too_large,
                               BstreamExceptionHierarchy,
                               "The string can't be read from the stream.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(type_mismatch,
                               BstreamExceptionHierarchy,
                               "Types of input and output streams mismatch.");


/*******************************************************************************
 * DEBUGGING POLICY.
 ******************************************************************************/

/**
 * DebugPolicyBostream enables debugging info for bostream
 * @param T : Type of the object/value to be written into bostream
 */
template <typename T>
struct DebugPolicyBostream
{
    static void on_debug(std::string& _s)
    {
        const std::string s(typeid(T).name());
        const uint32_t sz(s.size());
        _s.append(reinterpret_cast<const char*>(&sz), sizeof(uint32_t));
        _s += s;
    }
};

/**
 * DebugPolicyBistream enables debugging info for bistream
 * @param T : Type of the object/value to be read from bistream
 */
template <typename T>
struct DebugPolicyBistream
{
    static void on_debug(uint32_t& _pos, std::string& _s)
    {
        std::string s(typeid(T).name());
        uint32_t sz;
        _pos += _s.copy(reinterpret_cast<char*>(&sz), sizeof(uint32_t), _pos);
        std::string name  = _s.substr(_pos, sz);
        _pos += sz;
        if (s != name)
        {
            std::cerr << s << " | " << name << std::endl;
            throw type_mismatch();
        }
    }
};


/**
 * NoDebugPolicyBostream makes not debugging info for bostream
 * @param T : Type of the object/value to be written to bostream
 */
template <typename T>
struct NoDebugPolicyBostream
{
    static void on_debug(std::string&) {}
};

/**
 * NoDebugPolicyBistream makes not debugging info for bistream
 * @param T : Type of the object/value to be read from bistream
 */
template <typename T>
struct NoDebugPolicyBistream
{
    static void on_debug(uint32_t&, std::string&) {}
};

/**
 * Output stream serialization. This class provides stream functionality to serialize
 * objects in a way similar to that of std::cout or std::ostringstream.
 *
 * An extensive example of its usage can be seen in:
 *    http://code.google.com/p/mili/source/browse/trunk/example_binary-streams.cpp
 */

/**
* @param DebuggingPolicy : Policy for debugging, by default no debugging policy is set
*/
template < template <class> class DebuggingPolicy = NoDebugPolicyBostream >
class bostream
{
    template<class T,  bool IsContainer> struct _inserter_helper;

    template<class T,  bool IsContainer> friend struct _inserter_helper;


    template <class T>
    struct _inserter_helper<T, false>
    {
        static void call(bostream* bos, const T& x)
        {
            bos->_s.append(reinterpret_cast<const char*>(&x), sizeof(T));
        }
    };

    template <class T>
    struct _inserter_helper<T, true>
    {
        static void call(bostream* bos, const T& cont)
        {
            const uint32_t size(cont.size());
            (*bos) << size;

            typename T::const_iterator it;

            for (it = cont.begin(); it != cont.end(); ++it)
                (*bos) << *it;
        }
    };
public:
    /**
     * Standard constructor.
     */
    bostream() :
        _s()
    {
    }

    /**
     * Insert any object to the stream.
     *
     * @param x : A copy of the object being inserted.
     */
    template <class T>
    bostream& operator<< (const T& x)
    {
        // Disallow pointers in binary streams.
        template_compile_assert(!template_info<T>::is_pointer, pointers_not_allowed);

        DebuggingPolicy<T>::on_debug(_s);

        _inserter_helper<T, template_info<T>::is_container >::call(this, x);
        return *this;
    }

    /* Inserting a string inserts its size first. */

    /**
     * Insert a string to the stream.
     */
    bostream& operator<< (const std::string& s)
    {
        (*this) << uint32_t(s.size());
        _s += s;
        return *this;
    }

    /** Insert a literal string. */
    bostream& operator<< (const char* cs)
    {
        const std::string s(cs);
        return operator<< (s);
    }

    /** Concatenate a stream to this one. */
    void operator += (const bostream& other)
    {
        _s += other.str();
    }

    /** Obtain the string representing the stream. */
    const std::string& str() const
    {
        return _s;
    }

    /** Clear the stream. Enables the user to use it several times. */
    void clear()
    {
        _s.clear();
    }

private:
    /** The representation of the stream in memory. */
    std::string _s;
};

/**
 * Input stream serialization. This class provides stream functionality to deserialize
 * objects in a way similar to that of std::cin or std::istringstream.
 *
 * An extensive example of its usage can be seen in:
 *    http://code.google.com/p/mili/source/browse/trunk/example_binary-streams.cpp
 */

/**
 * @param DebuggingPolicy : Policy for debugging, by default no debugging policy is set
 */
template < template <class> class DebuggingPolicy = NoDebugPolicyBistream >
class bistream
{

    template<class T, bool IsContainer> struct _extract_helper;

    template<class T, bool IsContainer> friend struct _extract_helper;

    template<class T>
    struct _extract_helper<T, false>
    {
        static void call(bistream* bis, T& x)
        {
            if (bis->_s.size() < bis->_pos + sizeof(x))
                throw type_too_large();

            bis->_pos += bis->_s.copy(reinterpret_cast<char*>(&x), sizeof(x), bis->_pos);
        }
    };

    template<class T>
    struct _extract_helper<T, true>
    {
        static void call(bistream* bis, T& cont)
        {
            uint32_t size;
            (*bis) >> size;

            // If the elements of the container are not containers themselves (or strings),
            // then check there is enough rooom.
            if ((! template_info< typename T::value_type >::is_container) &&
                    (! template_info< typename T::value_type >::is_basic_string))
                if (bis->_s.size() < ((size * sizeof(typename T::value_type)) + bis->_pos))
                    throw stream_too_small();

            for (uint32_t i(0); i < size; i++)
            {
                typename T::value_type elem;
                (*bis) >> elem;
                insert_into(cont, elem);
            }
        }
    };
public:
    /**
     * Construct a new input stream object using a string representing a binary stream
     * as input.
     */
    bistream(const std::string& str) :
        _s(str),
        _pos(0)
    {
    }

    /**
     * Creates a new input stream object, but with no data.
     */
    bistream() :
        _s(),
        _pos(0)
    {
    }

    /**
     * Set the representation binary string.
     *
     * @param str : The new binary stream representation string.
     */
    void str(const std::string& str)
    {
        _pos = 0;
        _s = str;
    }

    /**
     * Read an element.
     *
     * @param x : A reference to the element you are reading into.
     *
     * @pre : The remaining input stream holds enough data to read the element.
     */
    template <class T>
    bistream& operator >> (T& x)
    {
        // Disallow pointers in binary streams.
        template_compile_assert(!template_info<T>::is_pointer, pointers_not_allowed);

        DebuggingPolicy<T>::on_debug(_pos, _s);

        _extract_helper<T, template_info<T>::is_container >::call(this, x);

        return *this;
    }

    /**
     * Read a string.
     *
     * @param str : A reference to the string you are reading into.
     *
     * @pre : The stream is situated in a position holding a 32 bit unsigned integer
     *        and then at least this very number of bytes remain.
     */
    bistream& operator >> (std::string& str)
    {
        uint32_t size;
        (*this) >> size;

        if (_s.size() < size + _pos)
            throw type_too_large();

        str   = _s.substr(_pos, size);

        _pos += size;
        return *this;
    }

    /** Clear the input stream. */
    void clear()
    {
        _s.clear();
        _pos = 0;
    }

    /**
     * Returns the available chars left to read.
     */
    uint32_t remainingChars() const
    {
        assert( _pos <= _s.size() );
        return _s.size() - _pos;
    }

    /**
     * Skip a given amount of chars.
     *
     * Examples:
     *    - skip(10);
     *
     * @param chars : The amount of chars to skip.
     *
     * @pre : This number should be less than or equal to remainingChars().
     */
    void skip(uint32_t chars)
    {
        assert( _pos + chars <= _s.size() );
        _pos += chars;
    }
private:
    /** The string representing the input stream. */
    std::string _s;

    /** The position the stream is reading from.  */
    uint32_t _pos;
};

/**
 * A helper class to insert containers from single elements. Use this when you know that
 * the data will later be read into a vector or some other container but you don't have
 * such a container for insertion, you want to create it on the go.
 *
 * @param T : The type of the elements in the container.
 */
template<class T, template <class> class DebuggingPolicy = NoDebugPolicyBostream >
class container_writer
{

public:
    /**
     * Default constructor.
     *
     * @param size : The amount of elements you will write.
     * @param bos : A reference to the output stream where you will create the
     *              container.
     */
    container_writer(uint32_t size, bostream<DebuggingPolicy>& bos) :
        _elements_left(size),
        _bos(bos)
    {
        _bos << uint32_t(size);
    }

    /**
     * Push an element.
     */
    container_writer& operator<<(const T& element)
    {
        if (_elements_left == 0)
            throw container_finished();

        --_elements_left;

        _bos << element;

        return *this;
    }

    /**
     * Default destructor.
     *
     * @pre : The elements inserted equals the amount of elements that were promised
     *        to be inserted at the time of creation (size parameter.)
     */
    ~container_writer()
    {
        if (_elements_left != 0)
            throw container_not_finished();
    }
private:
    /** The amount of elements you have yet to insert. */
    uint32_t    _elements_left;


    /** A reference to the output stream. */
    bostream<DebuggingPolicy>& _bos;
};

/**
 * A helper class to read from containers one by one. Use this when you want to read
 * something inserted as a container one by one, you can also use it to know how many
 * elements were inserted.
 *
 * @param T : The type of the elements in the container.
 */
template<class T, template <class> class DebuggingPolicy = NoDebugPolicyBistream >
class container_reader
{
public:
    /**
     * Standard constructor.
     *
     * @param bis : The input stream holding the data.
     */
    container_reader(bistream<DebuggingPolicy>& bis) :
        _elements_left(0),
        _bis(bis)
    {
        _bis >> _elements_left;


        if (_bis.remainingChars() < (sizeof(T) * _elements_left))
            throw stream_too_small();
    }

    /**
     * Read an element.
     */
    container_reader& operator>>(T& element)
    {
        assert(_elements_left > 0);
        --_elements_left;

        _bis >> element;

        return *this;
    }

    /**
     * Skip a given amount of elements, default: 1.
     *
     * Examples:
     *    - skip();
     *    - skip(10);
     *
     * @param elements : The amount of elements you want to skip. Default: 1.
     *
     * @pre : At least the amount of elements you want to skip remain.
     */
    void skip(uint32_t elements = 1)
    {
        if (elements > _elements_left)
            throw skip_excess();

        _elements_left -= elements;

        _bis.skip(sizeof(T) * elements);
    }

    /**
     * Signal that you have finished reading. It is the same as skipping the amount
     * of elements left.
     */
    void finished()
    {
        skip(_elements_left);
        _elements_left = 0;
    }

    /**
     * Standard destructor. Finishes the reading process if necessary.
     */
    ~container_reader()
    {
        if (_elements_left != 0)
            finished();
    }

private:
    /** The amount of elements that still haven't been read from the container. */
    uint32_t    _elements_left;

    /** A reference to the input stream. */
    bistream<DebuggingPolicy>& _bis;
};





NAMESPACE_END

#endif
