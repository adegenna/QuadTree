#include "ImageData.h"

using namespace std;

ImageData::ImageData( const std::string& filename , int x0 , int y0 ) 
 : x0_(x0) , y0_(y0) {
    
    data_ = bitmap_image( filename );
    
    datatype_ = "ImageData";

};

ImageData::ImageData( const std::string& filename ) {

    data_ = bitmap_image( filename );

    datatype_ = "ImageData";

};

ImageData::ImageData( const bitmap_image& data_bmp , int x0 , int y0 , int width , int height )
 : x0_(x0) , y0_(y0) {

    data_bmp.region( x0_ , y0_ , width , height , data_ );

    datatype_ = "ImageData";

};


ImageData::~ImageData() {

};

BoundingBox ImageData::compute_bbox( ) const {

    return BoundingBox( array<double,2>{ double( x0_ + data_.height() ) , double( y0_ ) } ,
                        array<double,2>{ double( x0_ ) , double( y0_ ) } , 
                        array<double,2>{ double( x0_ ) , double( y0_ + data_.width() ) } ,
                        array<double,2>{ double( x0_ + data_.height() ) , double( y0_ + data_.width() ) } );

};

unique_ptr<Data> ImageData::compute_data_in_bbox( const BoundingBox& bbox ) const {

    return make_unique<ImageData>( ImageData( data_ , bbox.get_nw()[0] , bbox.get_nw()[1] , 
                                              bbox.get_se()[0] - bbox.get_nw()[0] , 
                                              bbox.get_se()[1] - bbox.get_nw()[1] ) );

};

int ImageData::size() const{

    return data_.width() * data_.height();

};


void ImageData::write( const std::string& filename ) const {

    data_.save_image( filename );

};