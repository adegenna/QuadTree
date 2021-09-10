#ifndef __QTDIVISIONSTRATEGY_H__
#define __QTDIVISIONSTRATEGY_H__

#include <stdlib.h>
#include "Data.h"


class QTDivisionStrategy {

    public:

        virtual bool should_quad_divide() const = 0;

    protected:

        std::shared_ptr<Data> data_;
        
        int threshold_;
        
};


#endif