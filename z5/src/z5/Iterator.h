#include <iostream>
#include <memory>

template <typename T>
class out_iterator : public std::iterator<std::output_iterator_tag, T>
{
public:
    out_iterator(unsigned int N, std::ostream &stream, const std::string &delim);

    out_iterator<T> &operator=(const T &value);
    out_iterator<T> &operator++();
    out_iterator<T> &operator++(int);
    out_iterator<T> &operator*();

private:
    unsigned int _count = 1;
    unsigned int _printCount;
    std::string _delim;
    std::ostream *_stream;
};

template <typename T>
out_iterator<T> &out_iterator<T>::operator=(const T &value)
{
    if (_count < _printCount)
    {
        _count++;
    }
    else
    {
        *_stream << _delim << value;
        _count = 1;
    }
    return *this;
}

template <typename T>
out_iterator<T>::out_iterator(unsigned int N, std::ostream &stream, const std::string &delim)
{
    _printCount = N;
    _delim = delim;
    _stream = &stream;
}

template <typename T>
out_iterator<T> &out_iterator<T>::operator++(int)
{
    return *this;
}

template <typename T>
out_iterator<T> &out_iterator<T>::operator++()
{
    return *this;
}

template <typename T>
out_iterator<T> &out_iterator<T>::operator*()
{
    return *this;
}
