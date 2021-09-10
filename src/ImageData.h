#ifndef __IMAGEDATA_H__
#define __IMAGEDATA_H__

#include "bitmap_image.hpp" // https://github.com/ArashPartow/bitmap

#include "Data.h"

class ImageData : public Data {

    public:

        ImageData( const std::string& filename );
        ImageData( const std::string& filename , int x0 , int y0 );
        ImageData( const bitmap_image& v , int x0 , int y0 , int width , int height );
        ~ImageData();

        BoundingBox compute_bbox() const;

        std::unique_ptr<Data> compute_data_in_bbox( const BoundingBox& bbox ) const;

        int size() const;

        bitmap_image get_data() const { return data_; };

        void write( const std::string& filename ) const;
        
        bool is_exceeding_threshold( double threshold ) const;

    private:

        bitmap_image data_;
        int x0_ = 0;
        int y0_ = 0;

        std::array<double,3> compute_mean() const;
        double compute_variance() const;

};



#endif