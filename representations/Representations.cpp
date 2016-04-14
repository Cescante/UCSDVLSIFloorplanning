/**
 * @author Fang Qiao
 * @file Representations.cpp
 * @brief
 * 
 * Contains Implementations of floorplan representations.
 * 
 * @bug No known bugs.
 */

#include"rep.h"

FPRepresentation::FPRepresentation( int count, int dimensions, int area[] )
{
    boxCount = count;
    fpDimensions = dimensions;
    fpArea = new int[3];

    for (int i = 0; i < dimensions; ++i)
    {
        fpArea[i] = area[i];
    }
}

InternalRepresentation::InternalRepresentation( int count, int dimensions, 
        int area[] )
        : FPRepresentation( count, dimensions, area )
{
}

PartialOrdering::PartialOrdering( int count, int dimensions, 
        int area[] )
        : InternalRepresentation( count, dimensions, area )
{
}

