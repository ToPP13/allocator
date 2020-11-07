#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "lib.h"
#include "custom_array.h"
#include "fixsize_logging_allocator.h"
#include "stdexcept"

TEST(gtest_version, gtest_version_basic)
{
    ASSERT_GT(version(), 0);
}
constexpr int total = 3;

TEST(gtest_custom_allocator, gtest_custom_allocator_basic)
{
    fixsize_logging_allocator<int, total> a;
    for (int i = 0; i < total; ++i)
        ASSERT_NO_THROW(a.allocate(1););
    ASSERT_THROW(a.allocate(1), std::bad_alloc);
}


TEST(gtest_custom_array, gtest_custom_array_basic)
{
    CustomArray<int, total> ca1;
    for (int i = 0; i < total; ++i)
        ASSERT_NO_THROW(ca1.set_elem(i, i));
    ASSERT_THROW(ca1.set_elem(total, total), std::out_of_range);
}


TEST(gtest_custom_array, gtest_custom_array_custom_allocator_basic)
{
    CustomArray<int, total, fixsize_logging_allocator<int, total>> ca2;
    for (int i = 0; i < total; ++i)
        ASSERT_NO_THROW(ca2.set_elem(i, i));
    ASSERT_THROW(ca2.set_elem(total, total), std::out_of_range);
}
