#include "ImageData.h"

using namespace std;

ImageData::ImageData( const std::string& filename ) 
 : bmp_( bitmap_image( filename ) ) , data_( GlobalPixelCoords( bmp_.width() , bmp_.height() ) ) {

     bmp_mean_ = compute_mean();

};

ImageData::ImageData( const bitmap_image& bmp_parent , const GlobalPixelCoords& data_parent , int x0 , int y0 , int width , int height )
 : data_( data_parent ) {
    
    std::array<double,2> dxy = convert_bboxXY_to_bmpXY( x0 - data_.x0() , y0 - data_.y0() );

    // These two conditionals are hacks that fix edge cases, though they shouldn't be necessary...

    if ( dxy[0] + width > bmp_parent.width() ) {
        dxy[0] = bmp_parent.width() - width;
    }

    if ( dxy[1] + height > bmp_parent.height() ){
        dxy[1] = bmp_parent.height() - height;
    }

    bmp_parent.region( dxy[0] , dxy[1] , width , height , bmp_ );

    bmp_mean_ = compute_mean();
    
    data_ = GlobalPixelCoords( width , height , x0 , y0 ); // reset parent data for next recursive calls

};

// /home/adegennaro/Desktop/flow2.bmp
ImageData::~ImageData() {

};

BoundingBox ImageData::compute_bbox( ) const {

    return BoundingBox( array<double,2>{ double( data_.x0() ) , double( data_.y0() - data_.height() ) } , 
                        array<double,2>{ double( data_.x0() ) , double( data_.y0() ) } , 
                        array<double,2>{ double( data_.x0() + data_.width() ) , double( data_.y0() ) } , 
                        array<double,2>{ double( data_.x0() + data_.width() ) , double( data_.y0() - data_.height() ) } );

};

unique_ptr<Data> ImageData::compute_data_in_bbox( const BoundingBox& bbox ) const {

    return make_unique<ImageData>( ImageData( bmp_ , data_ , 
                                              bbox.get_nw()[0] , bbox.get_nw()[1] , 
                                              bbox.get_se()[0] - bbox.get_nw()[0] , 
                                              bbox.get_nw()[1] - bbox.get_se()[1] ) );

};

int ImageData::size() const{

    return data_.width() * data_.height();

};


void ImageData::write( const std::string& filename ) const {

    ofstream outfile( filename , ios_base::app );
    outfile << "rgb_mean : " << bmp_mean_[0] << "," << bmp_mean_[1] << "," << bmp_mean_[2];
    outfile.close();

};


bool ImageData::is_exceeding_threshold( double threshold ) const {

    if ( compute_variance() > threshold )
        return true;
    return false;

};

array<double,3> ImageData::compute_mean() const {

    array<double,3> mean{ 0.0 , 0.0 , 0.0 };

    for (unsigned int x = 0; x < uint(bmp_.width()); ++x) {

        for (unsigned int y = 0; y < uint(bmp_.height()); ++y) {
        
            rgb_t p_xy = bmp_.get_pixel( x , y );

            mean[0] += p_xy.red / ( double(bmp_.pixel_count()) );
            mean[1] += p_xy.green / ( double(bmp_.pixel_count()) );
            mean[2] += p_xy.blue / ( double(bmp_.pixel_count()) );

      }
  
   }

   if ( (bmp_.width() == 0) && (bmp_.height() == 0) ){
       cout << endl << "PIXELS : " << bmp_.pixel_count() << " , (width,height) : " << bmp_.width() << "," << bmp_.height() << endl;
   }

   return mean;

};

double ImageData::compute_variance() const {

    array<double,3> mean = compute_mean();

    double var = 0.0;

    for (unsigned int x = 0; x < uint(bmp_.width()); ++x) {

        for (unsigned int y = 0; y < uint(bmp_.height()); ++y) {
        
            rgb_t p_xy = bmp_.get_pixel( x , y );

            var += ( pow( p_xy.red - mean[0] , 2 ) + pow( p_xy.green - mean[1] , 2 ) + pow( p_xy.blue - mean[2] , 2 ) ) / ( double(bmp_.pixel_count()) );

      }
  
   }
    
   return var;

};

std::array<double,2> ImageData::convert_bmpXY_to_bboxXY( double x , double y ) const {

    return std::array<double,2> { x , -y };

};

std::array<double,2> ImageData::convert_bmpXY_to_bboxXY( const std::array<double,2>& xy ) const {

    return std::array<double,2> { xy[0] , -xy[1] };

};

std::array<double,2> ImageData::convert_bboxXY_to_bmpXY( double x , double y ) const {

    return std::array<double,2> { x , -y };

};



GlobalPixelCoords::GlobalPixelCoords( int width , int height ) 
 : width_(width) , height_(height) {

};

GlobalPixelCoords::GlobalPixelCoords( int width , int height , int x0 , int y0 ) 
 : x0_(x0) , y0_(y0) , width_(width) , height_(height) {

};



void print_data_stats( const bitmap_image& bmp ) {

    cout << "data.width : " << bmp.width() << " , data.height : " << bmp.height() << endl;

};

void print_xywh( int x , int y , int x0 , int y0 , int width , int height ) {

    cout << "(x,y) : (" << x << "," << y << ") (x0,y0) : (" << x0 << "," << y0 << ") width : " << width << " height : " << height << endl;

};