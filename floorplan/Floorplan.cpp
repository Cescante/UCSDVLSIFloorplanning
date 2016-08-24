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
    std::string cubeX = ", 0 2 3 | 0 3, 1 4 | 1 2 4, ";
    std::string cubeY = ", 0 1 2 | 0 2, 3 4 | 1 3 4, ";
    std::string cubeZ = ", 0 1 3 | 0 1, 2 4 | 2 3 4, ";


    int boxCount = 5;
    int dim = 3;
    int* volumn = new int[3];

    volumn[0] = 1;
    volumn[1] = 1;
    volumn[2] = 1;

    PartialOrdering testPO( boxCount, dim, volumn );

    testPO.SetXOrder( cubeX );
    testPO.SetYOrder( cubeY );
    testPO.SetZOrder( cubeZ );

    std::string gplOut = testPO.ToGPL();

    std::cout << "gplOut: " << gplOut << std::endl;
}

