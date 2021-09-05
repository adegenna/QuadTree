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

void Data2D::push_back( const array<double,2>& xy ) {

    data_.push_back( xy );

};

array<double,2> Data2D::get_next_point() {

    assert( idx_next_ < data_.size() );

    return data_[ ++idx_next_ ];

};

void Data2D::write_to_csv( const string &filename ) const {
    
    ofstream outfile_ij(filename);
    
    for (int i = 0; i < data_.size(); i++) {
        outfile_ij << data_[i][0] << "," << data_[i][1] << endl;
    }
    
    outfile_ij.close();

};

Data2D Data2D::compute_data_in_bbox( const BoundingBox& bbox ) const {

    vector<array<double,2>> bbox_xy;
    
    copy_if( data_.begin() , data_.end() , back_inserter(bbox_xy) , [ bbox ]( array<double,2> xy ){ return bbox.is_in_bbox( xy ); } );

    Data2D bbox_data;

    for ( auto xyi : bbox_xy )
        bbox_data.push_back( xyi );

    return bbox_data;

};

BoundingBox Data2D::compute_bbox() const {

    array<double,2> sw{ compute_min_x() , compute_min_y() };
    array<double,2> nw{ compute_min_x() , compute_max_y() };
    array<double,2> ne{ compute_max_x() , compute_max_y() };
    array<double,2> se{ compute_max_x() , compute_min_y() };

    return BoundingBox( sw , nw , ne , se );

}

double Data2D::compute_min_x() const {

    vector<double> vx = get_vector_x();

    return *min_element( vx.begin() , vx.end() );

};

double Data2D::compute_min_y() const {

    vector<double> vy = get_vector_y();

    return *min_element( vy.begin() , vy.end() );

};

double Data2D::compute_max_x() const {

    vector<double> vx = get_vector_x();

    return *max_element( vx.begin() , vx.end() );

};

double Data2D::compute_max_y() const {

    vector<double> vy = get_vector_y();

    return *max_element( vy.begin() , vy.end() );

};

vector<double> Data2D::get_vector_x() const {

    vector<double> vx;

    for ( auto xyi : data_ ) {

        vx.push_back( xyi[0] );

    }

    return vx;

};

vector<double> Data2D::get_vector_y() const {

    vector<double> vy;

    for ( auto xyi : data_ ) {

        vy.push_back( xyi[1] );

    }

    return vy;

};