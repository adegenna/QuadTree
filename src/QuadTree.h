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

        BoundingBox compute_quaddiv_sw() const;
        BoundingBox compute_quaddiv_nw() const;
        BoundingBox compute_quaddiv_ne() const;
        BoundingBox compute_quaddiv_se() const;

        bool is_in_bbox( const std::array<double,2>& xy ) const;

    private:

        void assert_valid_coordinates( const std::array<double,2>& sw , 
                                       const std::array<double,2>& nw ,
                                       const std::array<double,2>& ne ,
                                       const std::array<double,2>& se );

        std::array<double,2> sw_;
        std::array<double,2> nw_;
        std::array<double,2> ne_;
        std::array<double,2> se_;

};



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



class QuadTree {

    public:

        QuadTree( const Data2D& data , int bucketsize );
        ~QuadTree();

        BoundingBox get_bounding_box() { return bbox_; };

        Data2D compute_bucket_neighbors( const Data2D& query );

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