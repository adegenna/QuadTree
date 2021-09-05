#include "../src/QuadTree.h"
#include <random>
#include <iostream>
#include <math.h>


int main( ) {

    Data2D data = Data2D();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis( 0.0 , 0.05 );

    int n_samples;
    std::cout << "enter n_samples : ";
    std::cin >> n_samples;

    for ( int i=0; i<n_samples; i++ ) {

        double xi = float(i) / n_samples;
        double yi = 0.4 * sin( 2 * M_PI * float(i)/n_samples ) + dis(gen);

        data.push_back( std::array<double,2>{ xi , yi } );

    }

    QuadTree qt = QuadTree( data , data.compute_bbox() , 8 );

    qt.write_to_file( "qt.out" );

    data.write_to_csv( "qt_data.out" );

    return 0;

};