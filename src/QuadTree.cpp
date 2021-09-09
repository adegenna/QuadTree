#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "QuadTree.h"
#include "Data.h"

using namespace std;


QuadTree::QuadTree( shared_ptr<Data> data , const BoundingBox& bbox , int bucketsize ) 
    : data_(data) , bbox_(bbox) , k_(bucketsize) {

    if ( data_->size() > k_ ) {

        child_sw_ = make_shared<QuadTree>( QuadTree( data_->compute_data_in_bbox( bbox_.compute_quaddiv_sw() ) , bbox_.compute_quaddiv_sw() , k_ ) );
        child_nw_ = make_shared<QuadTree>( QuadTree( data_->compute_data_in_bbox( bbox_.compute_quaddiv_nw() ) , bbox_.compute_quaddiv_nw() , k_ ) );
        child_ne_ = make_shared<QuadTree>( QuadTree( data_->compute_data_in_bbox( bbox_.compute_quaddiv_ne() ) , bbox_.compute_quaddiv_ne() , k_ ) );
        child_se_ = make_shared<QuadTree>( QuadTree( data_->compute_data_in_bbox( bbox_.compute_quaddiv_se() ) , bbox_.compute_quaddiv_se() , k_ ) );

    }

};

QuadTree::~QuadTree() {

};

void QuadTree::write_to_file_df( const string& filename ) const {

    // write first
    if ( child_sw_ != nullptr )
        write_bbox_coords_to_file( *child_sw_ , filename );

    if ( child_nw_ != nullptr )
        write_bbox_coords_to_file( *child_nw_ , filename );

    if ( child_ne_ != nullptr )
        write_bbox_coords_to_file( *child_ne_ , filename );

    if ( child_se_ != nullptr )
        write_bbox_coords_to_file( *child_se_ , filename );

    // recursive calls
    if ( child_sw_ != nullptr )
        child_sw_->write_to_file_df( filename );

    if ( child_nw_ != nullptr )
        child_nw_->write_to_file_df( filename );

    if ( child_ne_ != nullptr )
        child_ne_->write_to_file_df( filename );

    if ( child_se_ != nullptr )
        child_se_->write_to_file_df( filename );

};

void QuadTree::write_to_file_bf( const string& filename , int level ) const {

    vector<QuadTree> nodes = get_qt_level_nodes( *this , level );

    for ( auto ni : nodes ) {

        write_bbox_coords_to_file( ni , filename );

    }

};

vector<shared_ptr<QuadTree>> QuadTree::get_children( ) const {

    return vector<shared_ptr<QuadTree>> { child_sw_ , child_nw_ , child_ne_ , child_se_ };

};

vector<QuadTree> get_qt_level_nodes( const QuadTree& qt , int level ) {

    assert( level > 0 );

    vector<QuadTree> parents { qt };
    vector<QuadTree> children;

    for ( int i=0; i<level; i++ ) {

        children.clear();

        for ( auto nj : parents ) {
            
            if ( nj.get_children()[0] != nullptr ) {
                for ( auto ck : nj.get_children() )
                    children.push_back( *ck );
            }
            
            else {
                children.push_back( nj );
            }
            
        }

        parents = children;

    }

    return children;

};



void write_bbox_coords_to_file( const QuadTree& qt , const std::string& filename ) {

    ofstream outfile_ij( filename , ios_base::app );
    
    BoundingBox bbox = qt.get_bounding_box();

    outfile_ij << "bucket" << endl;
    outfile_ij << "sw : " << bbox.get_sw()[0] << " , " << bbox.get_sw()[1] << endl;
    outfile_ij << "nw : " << bbox.get_nw()[0] << " , " << bbox.get_nw()[1] << endl;
    outfile_ij << "ne : " << bbox.get_ne()[0] << " , " << bbox.get_ne()[1] << endl;
    outfile_ij << "se : " << bbox.get_se()[0] << " , " << bbox.get_se()[1] << endl;

    outfile_ij.close();

};