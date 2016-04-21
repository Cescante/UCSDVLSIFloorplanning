/**
 * @author Fang Qiao
 * @file rep_tests.cpp
 * @brief
 * 
 * @bug No known bugs.
 */

#include<string>
#include<vector>

#include<gtest/gtest.h>
#include<representations/rep.h>

std::string emty_str = ""; 
std::string ol_one = "1 2, 3 4";

TEST( OrderLayerTest, ParseEmpty )
{
    std::vector<OrderLayer> testOL;
    
    OrderLayer::ParseOrder( emty_str, testOL );

    ASSERT_EQ(testOL.size(), 0);
}

TEST( OrderLayerTest, ParseMany )
{
    std::vector<OrderLayer> testOL;
    
    OrderLayer::ParseOrder( ol_one, testOL );

    EXPECT_EQ( testOL.size(), 1 ) << "-----------Only one layer";
    EXPECT_EQ( testOL[0].start.size(), 2 ) << "two nodes begins";
    EXPECT_EQ( testOL[0].end.size(), 2 ) << "two nodes ended";

    std::vector<int> os = testOL[0].start;
    std::vector<int> oe = testOL[0].end;

    EXPECT_NE( std::find( oe.begin(), oe.end(), 1 ), oe.end() )
        << "1 ended in first layer";
    EXPECT_NE( std::find( oe.begin(), oe.end(), 2 ), oe.end() )
        << "2 ended in first layer";
    
    EXPECT_NE( std::find( os.begin(), oe.end(), 3 ), os.end() )
        << "3 began in first layer";
    EXPECT_NE( std::find( os.begin(), oe.end(), 4 ), os.end() )
        << "4 began in first layer";
}

