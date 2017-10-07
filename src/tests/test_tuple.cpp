#include "doctest.h"

#include "nifty/meta/tuple.hpp"
#include "nifty/meta/integral_constant.hpp"

template<std::size_t INDEX>
struct TestTuple__Foo : public nifty::meta::SizeT<INDEX>{

};

TEST_CASE("test generate tuple ") {

    typedef typename nifty::meta::GenerateTuple<4,TestTuple__Foo>::type FooTuple;
    FooTuple foo_bar_tuple;

 
    CHECK_EQ(std::decay<decltype(std::get<0>(foo_bar_tuple))>::type::value,0);
    CHECK_EQ(std::decay<decltype(std::get<1>(foo_bar_tuple))>::type::value,1);
    CHECK_EQ(std::decay<decltype(std::get<2>(foo_bar_tuple))>::type::value,2);
    CHECK_EQ(std::decay<decltype(std::get<3>(foo_bar_tuple))>::type::value,3);

}





TEST_CASE("test uniform tuple ") {

    typedef typename nifty::meta::GenerateUniformTuple<4,TestTuple__Foo<2>>::type FooTuple;
    FooTuple foo_bar_tuple;

 
    CHECK_EQ(std::decay<decltype(std::get<0>(foo_bar_tuple))>::type::value,2);
    CHECK_EQ(std::decay<decltype(std::get<1>(foo_bar_tuple))>::type::value,2);
    CHECK_EQ(std::decay<decltype(std::get<2>(foo_bar_tuple))>::type::value,2);
    CHECK_EQ(std::decay<decltype(std::get<3>(foo_bar_tuple))>::type::value,2);

}