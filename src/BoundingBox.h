#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include <stdlib.h>
#include <array>
#include <vector>
#include <memory>


class BoundingBox {

    public:

        BoundingBox( const std::array<double,2>& sw , 
                     const std::array<double,2>& nw ,
                     const std::array<double,2>& ne ,
                     const std::array<double,2>& se );
        ~BoundingBox();

        std::array<double,2> get_sw() { return sw_; };
        std::array<double,2> get_nw() { return nw_; };
        std::array<double,2> get_ne() { return ne_; };
        std::array<double,2> get_se() { return se_; };

        BoundingBox compute_quaddiv_sw() const;
        BoundingBox compute_quaddiv_nw() const;
        BoundingBox compute_quaddiv_ne() const;
        BoundingBox compute_quaddiv_se() const;

        bool is_in_bbox( const std::array<double,2>& xy ) const;

    private:

        void assert_valid_coordinates( const std::array<double,2>& sw , 
                                       const std::array<double,2>& nw ,
                                       const std::array<double,2>& ne ,
                                       const std::array<double,2>& se );

        std::array<double,2> sw_;
        std::array<double,2> nw_;
        std::array<double,2> ne_;
        std::array<double,2> se_;

        std::array<double,2> mpt_left() const;
        std::array<double,2> mpt_right() const;
        std::array<double,2> mpt_top() const;
        std::array<double,2> mpt_bottom() const;
        std::array<double,2> center() const;

};

#endif