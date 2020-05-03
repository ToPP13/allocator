#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#include <memory>
#include <stdexcept>


template<typename T>
void print_array(T array, size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        std::cout << i << " " << array.get(i) << std::endl;
}


template<typename T, size_t N, typename ALLOCATOR = std::allocator<T>>
class CustomArray
{
public:
    CustomArray(): mem_pointer(nullptr)
    {
        auto ptr = _allocator.allocate(N);
        mem_pointer = std::shared_ptr<T>(ptr);
        for (size_t i=0; i < N; i++)
            _allocator.construct(mem_pointer.get() + i, T());

    }
    ~CustomArray()
    {
        for (size_t i=0; i < N; i++)
            _allocator.destroy(mem_pointer.get() + i);
        _allocator.deallocate(mem_pointer.get(), N);
    }
    bool set_elem(std::size_t n, const T &t)
    {
        if (n >= N)
            throw std::out_of_range{""};
        _allocator.construct(mem_pointer.get() + n, t);
        return true;
    }

    T get(std::size_t n)
    {
        return *(mem_pointer.get() + n);
    }
private:
    std::shared_ptr<T> mem_pointer;
    ALLOCATOR _allocator;
};

#endif // CUSTOM_ARRAY_H
