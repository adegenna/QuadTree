#include "QTDivisionStrategy.h"


class QTDivisionBitmapData : public QTDivisionStrategy {

    public:

        QTDivisionBitmapData( std::shared_ptr<Data> data , int threshold );
        
        bool should_quad_divide() const;

};
