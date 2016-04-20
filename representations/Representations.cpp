/**
 * @author Fang Qiao
 * @file Representations.cpp
 * @brief
 * 
 * Contains Implementations of floorplan representations.
 * 
 * @bug No known bugs.
 */

#include<Utilities/Utilities.h>

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
 *
 * TODO error codes
 */
int OrderLayer::ParseOrder( std::string spec, std::vector<OrderLayer> &outOrder )
{
    spec = trim( spec );

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

        // parse nodes and add new layer to output order.
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

        outOrder.push_back( newLayer );
    }
            
    return 0;
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
std::string PartialOrdering::ToGPL()
{
    return "Not Implemented";
}

/**
 * @brief
 *
 * xOrder mutator.
 */
int PartialOrdering::SetXOrder( std::string spec )
{
    return OrderLayer::ParseOrder( spec, _xOrder );
}

/**
 * @brief
 *
 * yOrder mutator.
 *
 */
int PartialOrdering::SetYOrder( std::string spec )
{
    return OrderLayer::ParseOrder( spec, _yOrder );
}

/**
 * @brief
 *
 * zOrder mutator.
 */
int PartialOrdering::SetZOrder( std::string spec )
{
    return OrderLayer::ParseOrder( spec, _zOrder );
}

/**
 * @brief
 *
 * TODO
 */
std::string Serialize( PartialOrdering inOrder )
{
    inOrder.ToGPL();

    return "Not Implemented";
}

/**
 * @brief
 *
 * TODO
 */
PartialOrdering* PartialOrdering::Deserialize( std::string spec )
{
    PartialOrdering* newPOrdering =  new PartialOrdering(1, 2, NULL);
    
    throw "Not Implemented, spec: " + spec;

    return newPOrdering;
}

