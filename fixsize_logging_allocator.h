#ifndef FIXSIZE_LOGGING_ALLOCATOR_H
#define FIXSIZE_LOGGING_ALLOCATOR_H

#endif // FIXSIZE_LOGGING_ALLOCATOR_H

#include <memory>
#include <iostream>

template<typename T, int N>
struct fixsize_logging_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = fixsize_logging_allocator<U, N>;
    };
    ~fixsize_logging_allocator() = default;

//    template<typename U>
//    fixsize_logging_allocator(const logging_allocator<U>&):allocated_elements_num(0), mem_pointer(nullptr) {
//#ifndef USE_PRETTY
//        std::cout << "Constructor from: [n = " << n << "]" << std::endl;
//#else
//        std::cout << __PRETTY_FUNCTION__ << "template consructor [n = " << N << "]" << std::endl;
//#endif
//    }

    fixsize_logging_allocator(): allocated_elements_num(0), mem_pointer(nullptr)
    {
#ifndef USE_PRETTY
        std::cout << "Constructor: [n = " << n << "]" << std::endl;
#else
//        std::cout << __PRETTY_FUNCTION__ << "consructor [n = " << N << "]" << std::endl;
#endif
    }

    T *allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
//        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if ((allocated_elements_num==0) && (n>0))
        {
            auto p = reinterpret_cast<T *>(std::malloc(N * sizeof(T)));
            mem_pointer = std::shared_ptr<T>(p);
        }
        if ((n+allocated_elements_num)>N)
        {
            // change logic in future
            throw std::bad_alloc();
        }

        auto ret_pointer = mem_pointer.get()+allocated_elements_num;
        allocated_elements_num += n;
        return ret_pointer;
    }



    void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (n>allocated_elements_num)
            throw std::bad_alloc();
        allocated_elements_num -= n;

        if (allocated_elements_num == 0)
            std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif

        new(p) U(std::forward<Args>(args)...);
    }

//    };

    template<typename U>
    void destroy(U *p) {
#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~U();
    }

    private:
    std::size_t allocated_elements_num;
    std::shared_ptr<T> mem_pointer;
};
