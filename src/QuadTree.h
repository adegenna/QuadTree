#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>

#include "Data2D.h"


class QuadTree {

    public:

        QuadTree( const Data2D& data , const BoundingBox& bbox , int bucketsize );
        ~QuadTree();

        BoundingBox get_bounding_box() const { return bbox_; };

        Data2D compute_bucket_neighbors( const Data2D& query );

        void write_to_file_df( const std::string& filename ) const;

        void write_to_file_bf( const std::string& filename , int level ) const;

        std::vector<std::shared_ptr<QuadTree>> get_children( ) const;

    private:

        Data2D data_;

        BoundingBox bbox_;

        int k_;

        std::shared_ptr<QuadTree> child_sw_;
        std::shared_ptr<QuadTree> child_nw_;
        std::shared_ptr<QuadTree> child_ne_;
        std::shared_ptr<QuadTree> child_se_;

};

void write_bbox_coords_to_file( const QuadTree& qt , const std::string& filename );

std::vector<QuadTree> get_qt_level_nodes( const QuadTree& qt , int level );

#endif