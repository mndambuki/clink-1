// Copyright (c) 2016 Martin Ridgers
// License: http://opensource.org/licenses/MIT

#pragma once

//------------------------------------------------------------------------------
template <typename T>
class array_base
{
public:
    class iter
    {
    public:
                    iter(T* t) : m_t(t)               { }
        void        operator ++ ()                    { ++m_t; }
        T&          operator * () const               { return *m_t; }
        bool        operator != (const iter& i) const { return i.m_t != m_t; }

    private:
        T*          m_t;
    };

                    array_base(T* ptr, unsigned int size, unsigned int capacity);
    iter            begin() const    { return m_ptr; }
    iter            end() const      { return m_ptr + m_size; }
    unsigned int    size() const     { return m_size; }
    unsigned int    capacity() const { return m_size; }
    bool            empty() const    { return !m_size; }
    bool            full() const     { return (m_size == m_capacity); }
    T*              front() const    { return m_ptr; }
    T*              back() const     { return empty() ? nullptr : (m_ptr + m_size - 1); }
    T*              push_back()      { return full() ? nullptr : (m_ptr + m_size++); }
    const T*        operator [] (unsigned int index) const;

protected:
    T*              m_ptr;
    unsigned int    m_size;
    unsigned int    m_capacity;
};

//------------------------------------------------------------------------------
template <typename T>
array_base<T>::array_base(T* ptr, unsigned int size, unsigned int capacity)
: m_ptr(ptr)
, m_size(size)
, m_capacity(capacity)
{
}

//------------------------------------------------------------------------------
template <typename T>
const T* array_base<T>::operator [] (unsigned int index) const
{
    return (index >= capacity()) ? nullptr : (m_ptr + index);
}



//------------------------------------------------------------------------------
template <typename T, unsigned int SIZE>
class fixed_array
    : public array_base<T>
{
public:
                fixed_array() : array_base(m_buffer, 0, SIZE) {}

private:
    T           m_buffer[SIZE];
};
