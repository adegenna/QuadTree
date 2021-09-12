#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>

#include "Data.h"


class QuadTree {

    public:

        QuadTree( std::shared_ptr<Data> data , const BoundingBox& bbox , int threshold );
        ~QuadTree();

        BoundingBox get_bounding_box() const { return bbox_; };
        
        void write_to_file_df( const std::string& filename ) const;

        void write_to_file_bf( const std::string& filename , int level ) const;

        void write_to_file_bf_with_data_value( const std::string& filename , int level ) const;

        std::vector<std::shared_ptr<QuadTree>> get_children( ) const;

        std::shared_ptr<Data> get_data() const { return data_; };

    private:

        std::shared_ptr<Data> data_;

        BoundingBox bbox_;

        int k_;

        std::shared_ptr<QuadTree> child_sw_;
        std::shared_ptr<QuadTree> child_nw_;
        std::shared_ptr<QuadTree> child_ne_;
        std::shared_ptr<QuadTree> child_se_;

};

void write_bbox_coords_to_file( const QuadTree& qt , const std::string& filename );

void write_bbox_and_data_value_to_file( const QuadTree& qt , const std::string& filename );

std::vector<QuadTree> get_qt_level_nodes( const QuadTree& qt , int level );

#endif