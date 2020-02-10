#include <iostream>
#include <cstring>

template <typename T>
class Vector
{
private:
    T *_data_begin;
    T *_data_end;
    size_t _size;

public:
    Vector() : _data_begin(nullptr), _size(0)
    {
        std::cout << "Vector()" << std::endl;
    }

    Vector(const Vector<T> &vector)
    {
        _data_begin = new T(vector._size);
        _size = vector._size;
        for (int i = 0; i <= _size; ++i)
        {
            _data_begin[i] = vector._data_begin[i];
        }
        std::cout << "Copy Constructor" << std::endl;
    }

    Vector(Vector<T> &&vector) : _data_begin(vector._data_begin), _size(vector._size)
    {
        vector._data_begin = nullptr;
        vector._size = 0;
        std::cout << "Move Constructor" << std::endl;
    }

    ~Vector()
    {
        delete[] _data_begin;
        std::cout << "Destroy" << std::endl;
    }

    void push_back(const T &new_val);
    void push_back(T &&new_val);
    void pop_back();
    void resize(size_t new_size);
    void print();
    void print_size();
    T *begin();
    T *end();
    size_t size();
    void erase(T *first, T *last);
    Vector<T> &operator=(const Vector<T> &vector);
    Vector<T> &operator=(Vector<T> &&vector);
    void swap(Vector<T> &vector);
};

template <typename T>
void Vector<T>::push_back(const T &new_val)
{
    resize(_size + 1);
    _data_begin[_size - 1] = new_val;
    std::cout << "push_back copy: " << std::endl;
}

template <typename T>
void Vector<T>::push_back(T &&new_val)
{
    resize(_size + 1);
    _data_begin[_size - 1] = std::move(new_val);
    std::cout << "push_back move" << std::endl;
}

template <typename T>
void Vector<T>::resize(size_t new_size)
{
    T *tmp_ptr = new T[new_size];
    size_t i;
    for (i = 0; i < new_size - 1; i++)
    {
        tmp_ptr[i] = std::move(_data_begin[i]);
    }
    delete[] _data_begin;
    _data_begin = tmp_ptr;
    _size = new_size;
    _data_end = _data_begin + _size;
}

template <typename T>
void Vector<T>::print()
{
    for (int i = 0; i < _size; i++)
        std::cout << "data_elem " << _data_begin[i] << std::endl;
}

template <typename T>
void Vector<T>::print_size()
{
    std::cout << "_size: " << _size << std::endl;
}

template <typename T>
T *Vector<T>::begin()
{
    return _data_begin;
}

template <typename T>
T *Vector<T>::end()
{
    return _data_end;
}

template <typename T>
size_t Vector<T>::size()
{
    return _size;
}

template <typename T>
void Vector<T>::pop_back()
{
    _size--;
    resize(_size);
}

template <typename T>
void Vector<T>::erase(T *first, T *last)
{
    ptrdiff_t size_diff_2 = last - first;
    size_t i = 0;
    T *tmp = new T[_size - size_diff_2];

    if (size_diff_2 > _size)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    for (auto iterator = begin(); iterator != first; iterator++)
    {
        tmp[i] = std::move(*iterator);
        i++;
    }

    for (auto iterator = last; iterator != end(); iterator++)
    {
        tmp[i] = std::move(*iterator);
        i++;
    }
    delete[] _data_begin;
    _data_begin = tmp;
    _size = _size - size_diff_2;
    _data_end = _data_begin + _size;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector)
{
    std::cout << "Copy assigment" << std::endl;
    delete[] _data_begin;
    _data_begin = new T(vector._size);
    _size = vector._size;
    for (int i = 0; i <= _size; ++i)
    {
        _data_begin[i] = vector._data_begin[i];
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&vector)
{
    std::cout << "Move assigment" << std::endl;
    this->swap(vector);
    return *this;
}

template <typename T>
void swap(Vector<T> &a, Vector<T> &b)
{
    a.swap(b);
}

template <typename T>
void Vector<T>::swap(Vector<T> &vector)
{
    std::swap(_data_begin, vector._data_begin);
    std::swap(_size, vector._size);
    std::swap(_data_end, vector._data_end);
}