/**
 * @author Fang Qiao
 * @file Representations.cpp
 * @brief
 * 
 * Contains Implementations of floorplan representations.
 * 
 * @bug No known bugs.
 */

#include<Utilties/Utilities.h>

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

/**
 * @brief
 *
 * The ParseOrder function parses strings into OrderLayer representation.
 */
std::vector<OrderLayer> OrderLayer::ParseOrder( std::string spec )
{
    spec = trim( spec );

    std::vector<OrderLayer> ordering;

    std::vector<std::string> layers;
    layers = split( spec, '|', layers ); // get layers

    for (std::vector<std::string>::iterator orderIter = layers.begin();
            orderIter != layers.end(); ++orderIter)
    {
        std::string layer = trim( *orderIter );
        
        // get ending blocks and starting blocks
        std::vector<std::string> nodes;
        nodes = split( layer, ',', nodes );

        if( nodes.size() != 2 )
        {
            throw "need to sets of nodes for a layer";
        }

        OrderLayer newLayer;
        std::vector<std::string> endNodes;
        endNodes = split( trim( nodes[0] ), ' ', endNodes );
        std::vector<std::string> startNodes;
        startNodes = split( trim( nodes[1] ), ' ', startNodes );

        for (std::vector<std::string>:: iterator idIter = endNodes.begin();
                idIter != endNodes.end(); ++ idIter)
        {
            newLayer.end.push_back( std::stoi( trim( *idIter ) ) );
        }
        for (std::vector<std::string>:: iterator idIter = startNodes.begin();
                idIter != startNodes.end(); ++ idIter)
        {
            newLayer.end.push_back( std::stoi( trim( *idIter ) ) );
        }
    }
            
    return ordering;
}

/**
 * @brief
 *
 * TODO
 */
PartialOrdering::PartialOrdering( std::string spec )
{
    throw "Not implemented, spec: " + spec;
}

/**
 * @brief
 *
 * TODO
 */
std::string PartialOrdering::ToGPL()
{
    return "Not Implemented";
}

PartialOrdering::PartialOrdering( int count, int dimensions, 
        int area[] )
        : InternalRepresentation( count, dimensions, area )
{
}
 
/**
 * @brief
 *
 * TODO
 */
PartialOrdering* PartialOrdering::Deserialize( std::string spec )
{
    PartialOrdering* newPOrdering =  new PartialOrdering(1, 2, (int[2]){3, 3});
    
    throw "Not Implemented, spec: " + spec;

    return newPOrdering;
}

