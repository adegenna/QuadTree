#ifndef __QTSCREATOR_H__
#define __QTSCREATOR_H__

#include "QTDivisionStrategy.h"
#include "Data.h"

class QTSCreator {

    public:

        QTSCreator( std::shared_ptr<Data> data , int threshold );
        
        std::unique_ptr<QTDivisionStrategy> factory_make_qts() const;

    private:

        std::shared_ptr<Data> data_;

        int threshold_;

};


#endif