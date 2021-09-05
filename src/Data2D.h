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

        double compute_min_x() const;
        double compute_min_y() const;
        double compute_max_x() const;
        double compute_max_y() const;

        std::vector<double> get_vector_x() const;
        std::vector<double> get_vector_y() const;

    private:

        std::vector< std::array<double,2> > data_;
        
        int idx_next_ = 0;

};

#endif