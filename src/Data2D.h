#ifndef __DATA2D_H__
#define __DATA2D_H__

#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>

#include "BoundingBox.h"


class Data2D {

    public:

        Data2D();
        ~Data2D();

        void push_back( const std::array<double,2>& xy );
        
        std::array<double,2> get_next_point();

        BoundingBox compute_bbox() const;

        Data2D compute_data_in_bbox( const BoundingBox& bbox ) const;

        int size() const { return data_.size(); };

        void write_to_csv( const std::string& filename ) const;

    private:

        std::vector< std::array<double,2> > data_;
        
        int idx_next_ = 0;

};

#endif