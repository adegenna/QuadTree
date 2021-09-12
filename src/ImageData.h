#ifndef __IMAGEDATA_H__
#define __IMAGEDATA_H__

#include "bitmap_image.hpp" // https://github.com/ArashPartow/bitmap

#include "Data.h"


class GlobalPixelCoords{

    // convention is (x,y) = (width,height) with (x,y) being standard Cartesian axes

    public:

        GlobalPixelCoords( int width , int height );
        GlobalPixelCoords( int width , int height , int x0 , int y0 );

        int x0() const { return x0_; };
        int y0() const { return y0_; };
        int width() const { return width_; };
        int height() const { return height_; };

    private:

        int x0_ = 0;
        int y0_ = 0;
        int width_;
        int height_;
    
};


class ImageData : public Data {

    public:

        ImageData( const std::string& filename );
        ImageData( const bitmap_image& bmp , const GlobalPixelCoords& data_parent , int x0 , int y0 , int width , int height );
        ~ImageData();

        BoundingBox compute_bbox() const;

        std::unique_ptr<Data> compute_data_in_bbox( const BoundingBox& bbox ) const;

        int size() const;

        GlobalPixelCoords get_data() const { return data_; };

        void write( const std::string& filename ) const;
        
        bool is_exceeding_threshold( double threshold ) const;

    private:

        bitmap_image bmp_;
        GlobalPixelCoords data_;
        std::array<double,3> bmp_mean_;

        std::array<double,3> compute_mean() const;
        double compute_variance() const;

        std::array<double,2> convert_bmpXY_to_bboxXY( double x , double y ) const;
        std::array<double,2> convert_bmpXY_to_bboxXY( const std::array<double,2>& xy ) const;
        std::array<double,2> convert_bboxXY_to_bmpXY( double x , double y ) const;

};

void print_data_stats( const bitmap_image& bmp );

void print_xywh( int x , int y , int x0 , int y0 , int width , int height );


#endif