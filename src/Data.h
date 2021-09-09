#ifndef __DATA_H__
#define __DATA_H__

#include <stdlib.h>

#include "BoundingBox.h"

class Data {

    public:

        virtual BoundingBox compute_bbox() const = 0;

        virtual std::unique_ptr<Data> compute_data_in_bbox( const BoundingBox& bbox ) const = 0;

        virtual int size() const = 0;

};



#endif