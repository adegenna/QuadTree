#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "QuadTree.h"
#include "Data2D.h"

using namespace std;


QuadTree::QuadTree( const Data2D& data , const BoundingBox& bbox , int bucketsize ) 
    : data_(data) , bbox_(bbox) , k_(bucketsize) {

    if ( data_.size() > k_ ) {

        child_sw_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_sw() ) , bbox_.compute_quaddiv_sw() , k_ ) );
        child_nw_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_nw() ) , bbox_.compute_quaddiv_nw() , k_ ) );
        child_ne_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_ne() ) , bbox_.compute_quaddiv_ne() , k_ ) );
        child_se_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_se() ) , bbox_.compute_quaddiv_se() , k_ ) );

    }

};

QuadTree::~QuadTree() {

};