/**
 * @author Fang Qiao
 * @file rep.h
 * @brief
 * 
 * Contains the Internal declarations of the Floorplan Representation Library.
 *
 * @bug Block id sanity check!!!
 */

#ifndef REP_H
#define REP_H

#include <string>
#include <vector>

#define COLOR_RANGE         10

/**
 * @brief
 *
 * The FPRepresentation class.
 *
 * Base class for all floorplan representations.
 */
class FPRepresentation
{
    protected:
        int boxCount;
        int fpDimensions;
        std::vector<int> fpVolume;
    
    public:
        FPRepresentation();
        FPRepresentation( int count, int dimensions, int volume[] );
};

/**
 * @brief
 *
 * The InternalRepresentation class.
 *
 * Base class for all representations with full output/validation functionalities.
 *
 * Reducible from all other representations. Reducible to all other
 * representations.
 */
class InternalRepresentation : public FPRepresentation
{
    public:
        InternalRepresentation();
        InternalRepresentation( int count, int dimensions, int volume[] ); 
        virtual std::string ToGPL() =0;  
};

/**
 * @brief
 *
 * Discrete block representation, for output.
 */
class BlockRepresentation : public FPRepresentation
{
    private:
        /**
         * @brief
         *
         * A block for real output.
         */
        class Block
        {
            public:
                int id;
                int fpDimensions;
                std::vector<int> position;
                std::vector<int> blockDimensions;
        };
        std::vector<Block> all_blocks;

    public:
        // static const std::string cubeFileHeader;
        BlockRepresentation( int count, int dimensions, int volume[] );
        void AddBlock( int id, int position[], int dimensions[] );
        std::string ToGPL();
};

/**
 * @brief
 *
 * The OrderLayer class.
 *
 * Implements the logic for a layer in the PartialOrder representation.
 *
 * TODO: Should probably be in an internal header and use json.
 */
class OrderLayer
{
     public:
        std::vector<int> end;
        std::vector<int> start;

        static int ParseOrder( std::string spec,
            std::vector<OrderLayer> &outOrder );
        static void ToBlockSpec( OrderLayer layer, int boxCount, int axis,
            int layerCount, int pos[], int dim[] );
};

/**
 * @brief
 *
 * The PartialOrdering class.
 *
 * Implements the logic of a PartialOrdering representation.
 *
 * TODO: Currently hard coded to 3D!
 * TODO: Need to make this dimension-agnostic! (nested vectors with init())
 */
class PartialOrdering : public InternalRepresentation
{
    protected:
        std::vector<OrderLayer> _xOrder;
        std::vector<OrderLayer> _yOrder;
        std::vector<OrderLayer> _zOrder;

    public:
        // PartialOrdering( std::string spec );
        PartialOrdering( int count, int dimensions, int volume[] );
        std::string ToGPL() override;
        int SetXOrder( std::string spec );
        int SetYOrder( std::string spec );
        int SetZOrder( std::string spec );

        // These should be in the base class.
        std::string Serialize( PartialOrdering inOrder );
        static PartialOrdering* Deserialize( std::string spec );
};

/**
 * @brief
 *
 * The LinkedCorners class.
 *
 * Implements the logic for a set of linked corners in the
 * CornerLinks representation.
 *
 * TODO: Should probably be in an internal header and use json.
 */
class LinkedCorners
{
    public:
        int id;
        /* contains: (block id, corner of block).*/
        std::vector<std::pair<int,int>> corners;
};

/**
 * @brief
 *
 * The CornerLinks class.
 *
 * Implements the logic of a CornerLinks representation.
 */
class CornerLinks : public InternalRepresentation
{
    protected:
        std::vector<LinkedCorners> _linksList;

    public:
        // CornerLinks( std::string spec );
        CornerLinks( int count, int dimensions, int volume[] );
        std::string ToGPL() override;
        int SetCorners( std::string spec);
};
#endif
