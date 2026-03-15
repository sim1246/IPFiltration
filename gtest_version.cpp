#include "gtest/gtest.h"


#include "ip_filter.h"
// Assuming you have a function or class to test from your src directory (needs appropriate include and linking)


TEST(gtest_version, AddressConstruct) {
    IpAddress a({ "1","1","2","4" });
    EXPECT_TRUE(a && a.o1 ==1 && a.o2 == 1 && a.o3 == 2 && a.o4 == 4);
}

TEST(gtest_version, AddressConstructWrong) {
    IpAddress a({ "1","1","2","500" });
    EXPECT_FALSE(a);
}

TEST(gtest_version, AddressComparing)
{
    EXPECT_TRUE(IpAddress(1, 1, 234, 8) < IpAddress(1, 1, 234, 9));
}

TEST(gtest_version, AddressComparing1)
{
    EXPECT_TRUE(IpAddress(1, 1, 234, 8) < IpAddress(1, 1, 235, 9));
}

TEST(gtest_version, AddressComparing3)
{
    EXPECT_TRUE(IpAddress(1, 1, 234, 8) < IpAddress(1, 2, 234, 8));
}

TEST(gtest_version, AddressComparing4)
{
    EXPECT_TRUE(IpAddress(1, 1, 234, 8) < IpAddress(2, 1, 234, 9));
}

TEST(gtest_version, AddressFilterAny1)
{
    EXPECT_TRUE(FilterFunc(IpAddress(1, 1, 234, 8), AndFunc, 256));
}

TEST(gtest_version, AddressFilterAny2)
{
    EXPECT_TRUE(FilterFunc(IpAddress(1, 1, 234, 8), AndFunc, 256, 256));
}

TEST(gtest_version, AddressFilterAny3)
{
    EXPECT_TRUE(FilterFunc(IpAddress(1, 1, 234, 8), AndFunc, 1, 256 , 234 ));
}

TEST(gtest_version, AddressFilterAny4)
{
    EXPECT_FALSE(FilterFunc(IpAddress(1, 1, 234, 8), AndFunc, 2));
}

TEST(gtest_version, AddressFilterAny5)
{
    EXPECT_TRUE(FilterFunc(IpAddress(100, 150, 234, 8), AndFunc, 100, 150));
}

TEST(gtest_version, AddressFilterAny6)
{
    EXPECT_FALSE(FilterFunc(IpAddress(1, 1, 234, 8), AndFunc, 2, 2, 2, 2));
}

TEST(gtest_version, AddressFilterAny7)
{
    EXPECT_FALSE(FilterFunc(IpAddress(1, 1, 234, 8), OrFunc, 9, 9, 9, 9));
}

TEST(gtest_version, AddressFilterAny8)
{
    EXPECT_TRUE(FilterFunc(IpAddress(1, 1, 234, 8), OrFunc, 8, 8, 8, 8));
}




