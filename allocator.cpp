#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <map>

#include "lib.h"
#include "logging_allocator.h"
#include "fixsize_logging_allocator.h"
#include "custom_array.h"




int main(int, char *[]) {
    constexpr int total = 10;

//    std::cout << "Part 1.0" << std::endl;
//    auto v = std::vector<int, logging_allocator<int>>{};
//    auto v = std::vector<int, logging_allocator<int>>{};
//    v.reserve(5);
//    for (int i = 0; i < 6; ++i) {
//        std::cout << "vector size = " << v.size() << std::endl;
//        v.emplace_back(i);
//        std::cout << std::endl;
//    }

//    std::cout << "Part 1.1" << std::endl;

//    auto m1 = std::map<int, long int,
//            std::less<long int>,
//            logging_allocator<std::pair<const int, long int>>>{};

    auto m1 = std::map<int, long int>{};
    for (int i = 0; i < total; ++i)
        m1[i] = fact(i);
    print_map(m1);

    auto m2 = std::map<int, long int,
            std::less<long int>,
            fixsize_logging_allocator<std::pair<const int, long int>,10>>{};

     for (int i = 0; i < total; ++i)
         m2[i] = fact(i);

     print_map(m2);

    CustomArray<int, total> ca1;
    for (int i = 0; i < total; ++i)
        ca1.set_elem(i, fact(i));

    print_array(ca1, total);

    CustomArray<int, total, fixsize_logging_allocator<int, total>> ca2;
    for (int i = 0; i < total; ++i)
        ca2.set_elem(i, fact(i));

    print_array(ca2, total);

    return 0;
}
