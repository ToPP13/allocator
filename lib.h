#pragma once

#include <iostream>
#include <vector>
#include <map>

int version();


#define USE_PRETTY 1


// calculate factorial of int
long int fact(int N);

template<typename T, typename U>
void print_map(std::map<T, U> & mp)
{
    for (auto map_pair : mp)
        std::cout << map_pair.first << " " << map_pair.second << std::endl;
}

template<typename T, typename U, typename LS, typename ALL>
void print_map(std::map<T, U, LS, ALL> & mp)
{
    for (auto map_pair : mp)
        std::cout << map_pair.first << " " << map_pair.second << std::endl;
}

