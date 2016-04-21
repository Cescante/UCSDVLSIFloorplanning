/**
 * @author Fang Qiao
 * @file rep.h
 * @brief
 * 
 * Contains the Internal declarations of the Floorplan Representation Library.
 *
 * @bug No known bugs.
 */

#ifndef REP_H
#define REP_H

#include <string>
#include <vector>

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
        int* fpArea;
    
    public:
        FPRepresentation();
        FPRepresentation( int count, int dimensions, int area[] );
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
        InternalRepresentation( int count, int dimensions, int area[] ); 
        virtual std::string ToGPL() =0;  
};


/**
 * @brief
 *
 * The OrderLayer class.
 *
 * TODO: Show probably be in an internal header and use json.
 */
class OrderLayer
{
     public:
        std::vector<int> end;
        std::vector<int> start;

        static int ParseOrder( std::string spec,
            std::vector<OrderLayer> &outOrder );
};

/**
 * @brief
 *
 * The PartialOrdering class.
 *
 * Implements the logic of a PartialOrdering representation.
 */
class PartialOrdering : public InternalRepresentation
{
    protected:
        std::vector<OrderLayer> _xOrder;
        std::vector<OrderLayer> _yOrder;
        std::vector<OrderLayer> _zOrder;

    public:
        PartialOrdering( std::string spec );
        PartialOrdering( int count, int dimensions, int area[] );
        std::string ToGPL() override;
        int SetXOrder( std::string spec );
        int SetYOrder( std::string spec );
        int SetZOrder( std::string spec );

        // These should be in the base class.
        std::string Serialize( PartialOrdering inOrder );
        static PartialOrdering* Deserialize( std::string spec );
};
#endif
