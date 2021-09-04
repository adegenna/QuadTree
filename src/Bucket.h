#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>



class BoundingBox {

    public:

        BoundingBox( const std::array<double,2>& sw , 
                     const std::array<double,2>& nw ,
                     const std::array<double,2>& ne ,
                     const std::array<double,2>& se );
        ~BoundingBox();

        std::array<double,2> get_sw() { return sw_; };
        std::array<double,2> get_nw() { return nw_; };
        std::array<double,2> get_ne() { return ne_; };
        std::array<double,2> get_se() { return se_; };


    private:

        std::array<double,2> sw_;
        std::array<double,2> nw_;
        std::array<double,2> ne_;
        std::array<double,2> se_;


};



class Data2D {

    public:

        Data2D();
        ~Data2D();

        void push( const std::array<double,2>& arr );
        
        std::array<double,2> get_point2d_at_index( int idx );

        void write_to_csv( const std::string& filename ) const;

    private:

        std::vector< std::array<double,2> > data_;

};



class QuadTree {

    public:

        QuadTree();
        ~QuadTree();

        BoundingBox get_bounding_box() { return self_bbox_; };

    private:

        Data2D data_;

        BoundingBox self_bbox_;

        std::shared_ptr<QuadTree> child_sw_;
        std::shared_ptr<QuadTree> child_nw_;
        std::shared_ptr<QuadTree> child_ne_;
        std::shared_ptr<QuadTree> child_se_;
};

#endif