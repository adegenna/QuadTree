#include <cassert>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "Data2D.h"


using namespace std;


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