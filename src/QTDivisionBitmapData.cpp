#include "QTDivisionBitmapData.h"


QTDivisionBitmapData::QTDivisionBitmapData( std::shared_ptr<Data> data , int threshold ) { 

    data_      = data ; 
    threshold_ = threshold; 

};

bool QTDivisionBitmapData::should_quad_divide() const {

    return true;

};