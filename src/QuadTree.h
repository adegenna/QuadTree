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

        void write_to_file( const std::string& filename ) const;

    private:

        Data2D data_;

        BoundingBox bbox_;

        int k_;

        std::shared_ptr<QuadTree> child_sw_;
        std::shared_ptr<QuadTree> child_nw_;
        std::shared_ptr<QuadTree> child_ne_;
        std::shared_ptr<QuadTree> child_se_;

};

#endif