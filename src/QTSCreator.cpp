#include "QTSCreator.h"
#include "QTDivisionScatteredData.h"
#include "QTDivisionBitmapData.h"


QTSCreator::QTSCreator( std::shared_ptr<Data> data , int threshold ) 
 : data_(data) , threshold_(threshold) {

};


std::unique_ptr<QTDivisionStrategy> QTSCreator::factory_make_qts() const {

    if ( data_->get_datatype() == "Data2D" )
        return std::make_unique<QTDivisionScatteredData>( QTDivisionScatteredData( data_ , threshold_ ) );
    else if  ( data_->get_datatype() == "ImageData" )
        return std::make_unique<QTDivisionBitmapData>( QTDivisionBitmapData( data_ , threshold_ ) );

};