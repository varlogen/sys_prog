#include <iostream>

class Person
{
public:
    unsigned int id;
    std::string name;
    friend bool operator<(const Person &person1, const Person &person2);
    bool operator==(const Person &p) const;

private:
};

bool operator<(const Person &person1, const Person &person2)
{
    return (person1.id < person2.id);
}

bool Person::operator==(const Person &p) const
{
    return id == p.id;
}

namespace std
{
template <>
struct hash<Person>
{
    std::size_t operator()(const Person &person) const
    {
        using std::hash;
        using std::size_t;
        using std::string;

        return std::hash<unsigned int>()(person.id);
    }
};
}

template <typename Iter>
void sort(Iter begin, Iter end)
{
    size_t size = end - begin;

    if (size > 1)
    {
        Iter left_end = begin + size / 2;
        Iter left_idx = begin;
        Iter right_idx = left_end;

        sort(begin, left_end);
        sort(right_idx, end);

        typedef typename std::iterator_traits<Iter>::value_type valueType;
        std::vector<valueType> vector(size);
        size_t idx = 0;

        while ((left_idx != left_end) && (right_idx != end))
        {
            if (*left_idx < *right_idx)
            {
                vector[idx] = *left_idx;
                idx++;
                left_idx++;
            }
            else
            {
                vector[idx] = *right_idx;
                idx++;
                right_idx++;
            }
        }

        if (left_idx == left_end)
            std::copy(right_idx, end, &vector[idx]);
        if (right_idx == end)
            std::copy(left_idx, left_end, &vector[idx]);

        for (const valueType &elem : vector)
        {
            *begin = std::move(elem);
            begin++;
        }
    }
}