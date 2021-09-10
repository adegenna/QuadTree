#include "QTDivisionScatteredData.h"


QTDivisionScatteredData::QTDivisionScatteredData( std::shared_ptr<Data> data , int threshold ) { 

    data_      = data ; 
    threshold_ = threshold; 

};

bool QTDivisionScatteredData::should_quad_divide() const {

    return ( data_->size() > threshold_ );

};