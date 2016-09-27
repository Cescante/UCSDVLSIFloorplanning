/**
 * @author Fang Qiao
 * @file Floorplan.cpp
 * @brief
 * 
 * 
 * @bug No known bugs.
 */

#include<iostream>

#include<representations/rep.h>

int main (int argc, char* argv[])
{
	// std::string cubeX = ", 0 4 2 6 | 0 4 2 6, 1 3 5 7 | 1 3 5 7, ";
	// std::string cubeY = ", 1 2 3 0 | 1 2 3 0, 5 6 7 4 | 5 6 7 4, ";
	// std::string cubeZ = ", 2 3 6 7 | 2 3 6 7, 0 1 4 5 | 0 1 4 5, ";
    //
    // std::string cubeX = ", 0 2 3 | 0 3, 1 4 | 1 2 4, ";
    // std::string cubeY = ", 0 1 2 | 0 2, 3 4 | 1 3 4, ";
    // std::string cubeZ = ", 0 1 3 | 0 1, 2 4 | 2 3 4, ";
    
    // std::string cubeX = ", 8 10 11 | 10, 12 | , 2 3 7 | 2 3 7 8 , 1 4 5 6 | "
    //     "1 4 5, | 11 , 9 | 9 12 , ";
    // std::string cubeY = ", 1 3 5 | 3 , 2 | , 8 9 11 | 5 8 9 11 , 6 7 10 12 | "
    //    "6 7 12 , | 1 , 4 | 4 2 , ";
    // std::string cubeZ = "; 1 2 3 4 | 1 2 ; | ; 5 6 7 8 9 10 | "
    //     " 3 4 5 6 7 8 9 , | , 11 12 | 9 10 11 12 , ";

    std::string cubeX = ", 7 9 10 | 9 , 11 | , 1 2 6 | 1 2 6 7 , 0 3 4 5 | "
        "0 3 4, | 10 , 8 | 5 8 11 , ";
    std::string cubeY = ", 0 2 4 | 2 , 1 | , 7 8 10 | 4 7 8 10 , 5 6 9 11 | "
        "5 9 11 , | 0 , 3 | 1 3 6 , ";
    std::string cubeZ = ", 0 1 2 3 | 0 1 , | , | , 4 5 6 7 8 9 | "
    " 2 3 4 5 6 7 8 , | , |, 10 11 | 8 9 10 11 , ";


    int boxCount = 12;
    int dim = 3;
    int* volumn = new int[3];

    volumn[0] = 6;
    volumn[1] = 6;
    volumn[2] = 5;

    PartialOrdering testPO( boxCount, dim, volumn );

    testPO.SetXOrder( cubeX );
    testPO.SetYOrder( cubeY );
    testPO.SetZOrder( cubeZ );

    std::string gplOut = testPO.ToGPL();

    std::cout << std::endl;
    std::cout << "gplOut: \n" << gplOut << std::endl;
}

