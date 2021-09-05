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

void QuadTree::write_to_file( const string& filename ) const {

    ofstream outfile_ij( filename , ios_base::app );
    
    BoundingBox bbox = get_bounding_box();

    outfile_ij << "bucket" << endl;
    outfile_ij << "sw : " << bbox.get_sw()[0] << " , " << bbox.get_sw()[1] << endl;
    outfile_ij << "nw : " << bbox.get_nw()[0] << " , " << bbox.get_nw()[1] << endl;
    outfile_ij << "ne : " << bbox.get_ne()[0] << " , " << bbox.get_ne()[1] << endl;
    outfile_ij << "se : " << bbox.get_se()[0] << " , " << bbox.get_se()[1] << endl;

    outfile_ij.close();

    if ( child_sw_ != nullptr )
        child_sw_->write_to_file( filename );

    if ( child_nw_ != nullptr )
        child_nw_->write_to_file( filename );

    if ( child_ne_ != nullptr )
        child_ne_->write_to_file( filename );

    if ( child_se_ != nullptr )
        child_se_->write_to_file( filename );

};