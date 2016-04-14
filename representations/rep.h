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
        InternalRepresentation( int count, int dimensions, int area[] ); 
        virtual std::string ToGPL() =0;  
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
        class Layer
        {
            public:
                std::vector<int> start;
                std::vector<int> end;
        };

    protected:
        std::vector<Layer> _xOrder;
        std::vector<Layer> _yOrder;
        std::vector<Layer> _zOrder;
        std::vector<Layer> ParseOrder( std::string spec );

    public:
        PartialOrdering( std::string spec );
        PartialOrdering( int count, int dimensions, int area[] );
        std::string ToGPL() override;
        void SetXOrder( std::string spec );
        void SetYOrder( std::string spec );
        void SetZOrder( std::string spec );

        // These should be in the base class.
        std::string Serialize();
        static PartialOrdering* Deserialize( std::string spec );};
#endif
