#include <iostream>
#include <array>
#include <cstdarg>

void message(std::ostream &stream, const char *str)
{
    stream << str;
}

template <typename T, typename... Args>
void message(std::ostream &stream, const char *str, const T &current, Args... args)
{
    for (; *str != '\0'; str++)
    {
        if (*str == '%')
        {
            stream << current;
            message(stream, str + 1, args...);
            return;
        }
        stream << *str;
    }
}

template <typename T, std::size_t N>
void add(size_t index, std::array<T, N> &targetArray)
{
}

template <typename T, std::size_t N, std::size_t M, typename... Arrays>
void add(size_t index, std::array<T, N> &targetArray, const std::array<T, M> &sourceArray, Arrays... arrays)
{

    for (const T &elem : sourceArray)
    {
        targetArray[index] = elem;
        index++;
    }

    add(index, targetArray, arrays...);
}

template <typename T, std::size_t N, typename... Arrays>
auto cat(std::array<T, N> array, Arrays... arrays)
{
    const size_t count = sizeof...(arrays) + 1;
    const size_t size = count * N;

    std::array<T, size> resultArray;

    add(0, resultArray, array, arrays...);

    return resultArray;
}

template <typename T, size_t N, size_t M>
struct Tie
{
public:
    std::array<T *, N * M> array;
    Tie<T, N, M> &operator=(const std::array<T, N * M> &rhs);
    Tie<T, N, M> &operator=(const Tie<T, N, M> &tie);
};

template <typename T, size_t N, size_t M>
Tie<T, N, M> &Tie<T, N, M>::operator=(const std::array<T, N * M> &rhs)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        *array[i] = rhs[i];
    }
    return *this;
}

template <typename T, size_t N, size_t M>
Tie<T, N, M> &Tie<T, N, M>::operator=(const Tie<T, N, M> &tie)
{
    array = tie.array;
    return *this;
}

template <typename T, std::size_t N, typename... Arrays>
auto tie(std::array<T, N> &array, Arrays &... arrays)
{
    const size_t count = sizeof...(arrays) + 1;
    Tie<T, N, count> t;

    add(0, t, array, arrays...);

    return t;
}

template <typename T, std::size_t N, std::size_t M, typename... Arrays>
void add(size_t index, Tie<T, N, M> &t, std::array<T, N> &array, Arrays &... arrays)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        t.array[i + index] = &array[i];
    }
    index += array.size();

    add(index, t, arrays...);
}

template <typename T, std::size_t N, std::size_t M>
void add(size_t index, Tie<T, N, M> &t)
{
}
