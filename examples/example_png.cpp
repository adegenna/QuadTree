#include <random>
#include <iostream>
#include <math.h>

#include "../src/QuadTree.h"
#include "../src/ImageData.h"


int main( ) {

    std::shared_ptr<ImageData> data = std::make_shared<ImageData>( ImageData( "../examples/chunk.bmp" ) );

    BoundingBox bbox = data->compute_bbox();

    std::cout << "sw : " << bbox.get_sw()[0] << " , " << bbox.get_sw()[1] << std::endl;
    std::cout << "nw : " << bbox.get_nw()[0] << " , " << bbox.get_nw()[1] << std::endl;
    std::cout << "ne : " << bbox.get_ne()[0] << " , " << bbox.get_ne()[1] << std::endl;
    std::cout << "se : " << bbox.get_se()[0] << " , " << bbox.get_se()[1] << std::endl;

    // bitmap_image chunk;
    // data->get_data().region( 0 , 0 , 256 , 256 , chunk );
    // chunk.save_image( "chunk.bmp" );

    QuadTree qt = QuadTree( data , data->compute_bbox() , 1000.0 );

    for ( int i=0; i<6; i++ ){
        qt.write_to_file_bf( "qt_level_" + std::to_string(i+1) + ".out" , i+1 );
    }

    return 0;

};