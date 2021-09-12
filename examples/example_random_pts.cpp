#include <random>
#include <iostream>
#include <math.h>

#include "../src/QuadTree.h"
#include "../src/Data2D.h"


int main( ) {

    std::shared_ptr<Data2D> data = std::make_shared<Data2D>( Data2D() );

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis( 0.0 , 0.05 );

    int n_samples;
    std::cout << "enter n_samples : ";
    std::cin >> n_samples;

    for ( int i=0; i<n_samples; i++ ) {

        double xi = float(i) / n_samples;
        double yi = 0.4 * sin( 2 * M_PI * float(i)/n_samples ) + dis(gen);

        data->push_back( std::array<double,2>{ xi , yi } );

    }

    QuadTree qt = QuadTree( data , data->compute_bbox() , 8 );

    for ( int i=0; i<8; i++ ){
        qt.write_to_file_bf( "qt_level_" + std::to_string(i+1) + ".out" , i+1 );
    }

    data->write( "qt_data.out" );

    return 0;

};