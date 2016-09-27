/**
 * @author Fang Qiao
 * @file Representations.cpp
 * @brief
 * 
 * Contains Implementations of floorplan representations.
 * 
 * @bug No known bugs.
 */

#include<iostream>
#include<stdio.h>

#include<Utilities/Utilities.h>

#include"rep.h"

FPRepresentation::FPRepresentation( int count, int dimensions, int volume[] )
{
    boxCount = count;
    fpDimensions = dimensions;

    for (int i = 0; i < dimensions; ++i)
    {
        fpVolume.push_back(volume[i]);
    }
}

InternalRepresentation::InternalRepresentation( int count, int dimensions, 
        int volume[] )
        : FPRepresentation( count, dimensions, volume )
{
}

BlockRepresentation::BlockRepresentation( int count, int dimensions, 
        int volume[] )
        : FPRepresentation( count, dimensions, volume )
{
}

/**
 * @brief
 *
 * Add a discrete block description to a BlockRepresentation.
 */
void BlockRepresentation::AddBlock( int id, int position[], 
        int dimensions[] )
{
    Block newBlock;

    newBlock.id = id;
    newBlock.fpDimensions = fpDimensions;
    newBlock.position = std::vector<int>(position, position + fpDimensions);
    newBlock.blockDimensions
        = std::vector<int>(dimensions, dimensions + fpDimensions);
    
    for (int i = 0; i < fpDimensions; ++i)
    {
        newBlock.position[i] = position[i];
        newBlock.blockDimensions[i] = dimensions[i];
    }

    all_blocks.push_back( newBlock );

    std::cout << "pushing back block " << newBlock.id << std::endl;
}

/**
 * @brief
 *
 * Output block plot specifications.
 */
std::string BlockRepresentation::ToGPL()
{
    std::string gplOut = "";
    for (std::vector<Block>::iterator blockIter = all_blocks.begin();
            blockIter != all_blocks.end(); ++blockIter)
    {
        char blkstr[256];
        Block currBlock = *blockIter;
        sprintf( blkstr, "%d %d %d %d %d %d %d %d %d", currBlock.id,
           currBlock.position[0], currBlock.position[1], currBlock.position[2],
           currBlock.blockDimensions[0], currBlock.blockDimensions[1],
           currBlock.blockDimensions[2], (currBlock.id % COLOR_RANGE) + 1,
           (currBlock.id % COLOR_RANGE) + 1 );

        gplOut = gplOut + blkstr + "\r\n";
    }

    return gplOut;
}

/**
 * @brief
 *
 * The ParseOrder function parses strings into OrderLayer representation.
 *
 * spec format: <end node> <end node> ..., <start node> <start node> | ...
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
            // If this is the final layer, no new node is expected.
            // Remove the final delimiter.
            if (layer[layer.length() - 1] == ',')
            {
                nodes.push_back("");
            }
            else
            {
                throw "need two sets of nodes for a layer";
                std::cout << "ParseOrder: need two sets of noes for a layer"
                    << std::endl;
            }
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
            std::string currId = trim( *idIter );
            if (currId.length() > 0)
            {
                newLayer.end.push_back( std::stoi( currId ) );
            }
        }
        for (std::vector<std::string>:: iterator idIter = startNodes.begin();
                idIter != startNodes.end(); ++idIter)
        {
            std::string currId = trim( *idIter );
            if (currId.length() > 0)
            {
                newLayer.start.push_back( std::stoi( currId ) );
            }
        }

        outOrder.push_back( newLayer );
    }
            
    return 0;
}

/**
 * @brief
 *
 * Compute block position and dimension along one axis.
 */
void OrderLayer::ToBlockSpec( OrderLayer layer, int boxCount, int axis,
        int layerCount, int pos[], int dim[] )
{
    for (std::vector<int>:: iterator sbIter = layer.start.begin();
           sbIter != layer.start.end(); ++sbIter)
    { 
        int currId = *sbIter;
        pos[axis * boxCount + currId] = layerCount;
    }
    for (std::vector<int>:: iterator ebIter = layer.end.begin();
           ebIter != layer.end.end(); ++ebIter)
    {
        int currId = *ebIter;
        int span = layerCount - pos[axis * boxCount + currId];
        dim[axis * boxCount + currId] = span;
    }
}

/**
 * @brief
 *
 * TODO
 */
//PartialOrdering::PartialOrdering( std::string spec )
//{
//    throw "Not implemented, spec: " + spec;
//}

PartialOrdering::PartialOrdering( int count, int dimensions, 
        int volume[] )
        : InternalRepresentation( count, dimensions, volume )
{
}

/**
 * @brief
 *
 * Converts a PartialOrdering to a BlockRepresentation, to generate gnuplot
 * specs.
 *
 * TODO: Remove hard-coded dimensions!!!!
 */
std::string PartialOrdering::ToGPL()
{    
    BlockRepresentation blocks( boxCount, fpDimensions, &fpVolume[0] );

    // Compute block positions and dimensions.
    int pos[fpDimensions * boxCount];
    int dim[fpDimensions * boxCount];
    int* currPos = new int[fpDimensions];
    int* currDim = new int[fpDimensions];

    for (size_t l = 0; l < _xOrder.size(); ++l)
    {
        OrderLayer::ToBlockSpec( _xOrder[l], boxCount, 0, l, pos, dim );
    }

    for (size_t l = 0; l < _yOrder.size(); ++l)
    {
        OrderLayer::ToBlockSpec( _yOrder[l], boxCount, 1, l, pos, dim );
    }

    for (size_t l = 0; l < _zOrder.size(); ++l)
    {
        OrderLayer::ToBlockSpec( _zOrder[l], boxCount, 2, l, pos, dim );
    }

    // Populate BlockRepresentation
    for (int i = 0; i < boxCount; ++i)
    {
            
        currPos[0] = pos[0 * boxCount + i];
        currPos[1] = pos[1 * boxCount + i];
        currPos[2] = pos[2 * boxCount + i];

        currDim[0] = dim[0 * boxCount + i];
        currDim[1] = dim[1 * boxCount + i];
        currDim[2] = dim[2 * boxCount + i];

        blocks.AddBlock( i, currPos, currDim );
    }

    delete[] currPos;
    delete[] currDim;
    return blocks.ToGPL();
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
std::string PartialOrdering::Serialize( PartialOrdering inOrder )
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

/**
 * @brief
 *
 * TODO
 */
CornerLinks::CornerLinks( int count, int dimensions, 
        int volume[] )
        : InternalRepresentation( count, dimensions, volume )
{
}


/**
 * @brief
 *
 * Parse and create ConerLinks from string spec.
 *
 * TODO: Hash maps from node corners to links and back.
 */
int CornerLinks::SetCorners( std::string spec )
{
    spec = trim( spec );

    std::vector<std::string> links;
    links = split( spec, '|', links ); // get links
    int linkId = 0;
    
    for (std::vector<std::string>::iterator linkIter = links.begin();
            linkIter != links.end(); ++linkIter)
    {
        LinkedCorners currLink;
        currLink.id = ++linkId;
            
        std::string link = trim( *linkIter );

        // get corners in link
        std::vector<std::string> corners;
        corners = split( link, ',', corners );

        for (std::vector<std::string>::iterator cornerIter
                = corners.begin(); cornerIter != corners.end(); ++cornerIter)
        {
            std::string corner = trim( *cornerIter );
            std::vector<std::string> blockCorner;
            blockCorner = split( corner, ' ', blockCorner );
            int currId = std::stoi( blockCorner[0] );
            int currCorner = std::stoi( blockCorner[1], nullptr, 2 );

            std::pair<int, int> currpair = std::make_pair( currId, currCorner );
            currLink.corners.push_back( currpair );
        }

        _linksList.push_back( currLink );
    }

    return 1;
}

/**
 * @brief
 *
 * The ToGPL function for corner links to output to gnuplot floor plan.
 */
std::string CornerLinks::ToGPL()
{
    return "not implemented";
}
