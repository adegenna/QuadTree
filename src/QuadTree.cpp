#include "QuadTree.h"
#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;



BoundingBox::BoundingBox( const std::array<double,2>& sw , 
                          const std::array<double,2>& nw ,
                          const std::array<double,2>& ne ,
                          const std::array<double,2>& se)
    : sw_(sw) , nw_(nw) , ne_(ne) , se_(se) {

    assert_valid_coordinates( sw , nw , ne , se );

};

BoundingBox::~BoundingBox() {

};

void BoundingBox::assert_valid_coordinates( const std::array<double,2>& sw , 
                                            const std::array<double,2>& nw ,
                                            const std::array<double,2>& ne ,
                                            const std::array<double,2>& se ) {

    assert( (sw[0] == nw[0]) && (sw[1] < nw[1]) );
    assert( (sw[1] == se[1]) && (sw[0] < se[0]) );
    assert( (ne[0] == se[0]) && (ne[1] == nw[1]) );

};

bool BoundingBox::is_in_bbox( const std::array<double,2>& xy ) const {

    return ( ( xy[0] <= se_[0] ) && ( xy[0] > sw_[0] ) && 
             ( xy[1] <= ne_[1] ) && ( xy[1] > se_[1] ) );

};

BoundingBox BoundingBox::compute_quaddiv_sw() const {

    return BoundingBox( sw_ , mpt_left() , center() , mpt_bottom() );

};

BoundingBox BoundingBox::compute_quaddiv_nw() const {

    return BoundingBox( mpt_left() , nw_ , mpt_top() , center() );

};

BoundingBox BoundingBox::compute_quaddiv_ne() const {

    return BoundingBox( center() , mpt_top() , ne_ , mpt_right() );

};

BoundingBox BoundingBox::compute_quaddiv_se() const {

    return BoundingBox( mpt_bottom() , center() , mpt_right() , se_ );

};

std::array<double,2> BoundingBox::mpt_left() const {

    return std::array<double,2> { sw_[0] , 0.5 * ( sw_[1] + nw_[1] ) };

};

std::array<double,2> BoundingBox::mpt_right() const {

    return std::array<double,2> { se_[0] , 0.5 * ( se_[1] + ne_[1] ) };

};

std::array<double,2> BoundingBox::mpt_top() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , nw_[1] };

};

std::array<double,2> BoundingBox::mpt_bottom() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , sw_[1] };

};

std::array<double,2> BoundingBox::center() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , 0.5 * ( se_[1] + ne_[1] ) };

};



Data2D::Data2D() {
    
};

Data2D::~Data2D() {

};

void Data2D::push_back( const std::array<double,2>& xy ) {

    data_.push_back( xy );

};

std::array<double,2> Data2D::get_next_point() {

    assert( idx_next_ < data_.size() );

    return data_[ ++idx_next_ ];

};

void Data2D::write_to_csv( const std::string &filename ) const {
    
    ofstream outfile_ij(filename);
    
    for (int i = 0; i < data_.size(); i++) {
        outfile_ij << data_[i][0] << "," << data_[i][1] << endl;
    }
    
    outfile_ij.close();

};

Data2D Data2D::compute_data_in_bbox( const BoundingBox& bbox ) const {

    Data2D bbox_data;

    copy_if( data_.begin() , data_.end() , back_inserter( bbox_data ) , [ bbox ]( std::array<double,2> xy ){ return bbox.is_in_bbox( xy ); } );

    return bbox_data;

};



QuadTree::QuadTree( const Data2D& data , int bucketsize ) 
    : data_(data) , bbox_(data.compute_bbox()) , k_(bucketsize) {

    if ( data_.size() > k_ ) {

        child_sw_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_sw() ) , bbox_.compute_quaddiv_sw() , k_ ) );
        child_nw_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_nw() ) , bbox_.compute_quaddiv_nw() , k_ ) );
        child_ne_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_ne() ) , bbox_.compute_quaddiv_ne() , k_ ) );
        child_se_ = make_shared<QuadTree>( QuadTree( data_.compute_data_in_bbox( bbox_.compute_quaddiv_se() ) , bbox_.compute_quaddiv_se() , k_ ) );

    }

};

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

