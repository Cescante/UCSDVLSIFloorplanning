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
#include<Utilities/Utilities.h>

std::string emty_str = ""; 
std::string ol_one  = "1 2, 3 4";
std::string ol_many = "1 2, 3 4 | 5 6, 7 8";

std::string cubeX = ", 0 | 0, ";
std::string cubeY = ", 0 | 0, ";
std::string cubeZ = ", 0 | 0, ";
std::string cubeGPL = "0 0 0 1 1 1 1";

TEST( OrderLayerTest, ParseEmpty )
{
    std::vector<OrderLayer> testOL;
    
    OrderLayer::ParseOrder( emty_str, testOL );

    ASSERT_EQ( 0, testOL.size() );
}

TEST( OrderLayerTest, ParseOne )
{
    std::vector<OrderLayer> testOL;
    
    OrderLayer::ParseOrder( ol_one, testOL );

    EXPECT_EQ( 1, testOL.size() ) << "----------- Only one layer";
    EXPECT_EQ( 2, testOL[0].end.size() ) << "two nodes ended";
    EXPECT_EQ( 2, testOL[0].start.size() ) << "two nodes begins";
    
    std::vector<int> oe = testOL[0].end;
    std::vector<int> os = testOL[0].start;

    EXPECT_NE( std::find( oe.begin(), oe.end(), 1 ), oe.end() )
        << "1 ended in first layer";
    EXPECT_NE( std::find( oe.begin(), oe.end(), 2 ), oe.end() )
        << "2 ended in first layer";
    
    EXPECT_NE( std::find( os.begin(), os.end(), 3 ), os.end() )
        << "3 began in first layer";
    EXPECT_NE( std::find( os.begin(), os.end(), 4 ), os.end() )
        << "4 began in first layer";
}

TEST( OrderLayerTest, ParseMany )
{
    std::vector<OrderLayer> testOL;
    
    OrderLayer::ParseOrder( ol_many, testOL );

    EXPECT_EQ( 2, testOL.size() ) << "----------- Two layers";
    EXPECT_EQ( 2, testOL[1].end.size() ) << "two nodes ended";
    EXPECT_EQ( 2, testOL[1].start.size() ) << "two nodes begins";
    
    std::vector<int> oe = testOL[1].end;
    std::vector<int> os = testOL[1].start;

    EXPECT_NE( std::find( oe.begin(), oe.end(), 5 ), oe.end() )
        << "5 ended in first layer";
    EXPECT_NE( std::find( oe.begin(), oe.end(), 6 ), oe.end() )
        << "6 ended in first layer";
    
    EXPECT_NE( std::find( os.begin(), os.end(), 7 ), os.end() )
        << "7 began in first layer";
    EXPECT_NE( std::find( os.begin(), os.end(), 8 ), os.end() )
        << "8 began in first layer";
}

TEST( PartialOrderingTest, CubeGPLTest )
{
    int boxCount = 1;
    int dim = 3;
    int* volume = new int[3];

    volume[0] = 1;
    volume[1] = 1;
    volume[2] = 1;

    PartialOrdering testPO( boxCount, dim, volume );

    testPO.SetXOrder( cubeX );
    testPO.SetYOrder( cubeY );
    testPO.SetZOrder( cubeZ );

    std::string gplOut = testPO.ToGPL();
    gplOut = trim(gplOut);

    ASSERT_EQ( cubeGPL, gplOut );
}
