#include "QTDivisionStrategy.h"


class QTDivisionScatteredData : public QTDivisionStrategy {

    public:

        QTDivisionScatteredData( std::shared_ptr<Data> data , int threshold );

        bool should_quad_divide() const;

};
