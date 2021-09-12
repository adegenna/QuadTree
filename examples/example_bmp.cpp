#include <random>
#include <iostream>
#include <math.h>

#include "../src/QuadTree.h"
#include "../src/ImageData.h"


int main( ) {

    std::string bmp_file;
    std::cout << ".bmp filepath : ";
    std::cin >> bmp_file;

    std::shared_ptr<ImageData> data = std::make_shared<ImageData>( ImageData( bmp_file ) );

    QuadTree qt = QuadTree( data , data->compute_bbox() , 1000.0 );

    for ( int i=0; i<6; i++ ){
        qt.write_to_file_bf_with_data_value( "qt_level_" + std::to_string(i+1) + ".out" , i+1 );
    }

    return 0;

};