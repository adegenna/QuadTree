#include <cassert>

#include "BoundingBox.h"


BoundingBox::BoundingBox( const std::array<double,2>& sw , 
                          const std::array<double,2>& nw ,
                          const std::array<double,2>& ne ,
                          const std::array<double,2>& se)
    : sw_(sw) , nw_(nw) , ne_(ne) , se_(se) {

    assert_valid_coordinates( sw , nw , ne , se );

};

BoundingBox::~BoundingBox() {

};

void BoundingBox::assert_valid_coordinates( const std::array<double,2>& sw , 
                                            const std::array<double,2>& nw ,
                                            const std::array<double,2>& ne ,
                                            const std::array<double,2>& se ) {

    assert( (sw[0] == nw[0]) && (sw[1] < nw[1]) );
    assert( (sw[1] == se[1]) && (sw[0] < se[0]) );
    assert( (ne[0] == se[0]) && (ne[1] == nw[1]) );

};

bool BoundingBox::is_in_bbox( const std::array<double,2>& xy ) const {

    return ( ( xy[0] <= se_[0] ) && ( xy[0] > sw_[0] ) && 
             ( xy[1] <= ne_[1] ) && ( xy[1] > se_[1] ) );

};

BoundingBox BoundingBox::compute_quaddiv_sw() const {

    return BoundingBox( sw_ , mpt_left() , center() , mpt_bottom() );

};

BoundingBox BoundingBox::compute_quaddiv_nw() const {

    return BoundingBox( mpt_left() , nw_ , mpt_top() , center() );

};

BoundingBox BoundingBox::compute_quaddiv_ne() const {

    return BoundingBox( center() , mpt_top() , ne_ , mpt_right() );

};

BoundingBox BoundingBox::compute_quaddiv_se() const {

    return BoundingBox( mpt_bottom() , center() , mpt_right() , se_ );

};

std::array<double,2> BoundingBox::mpt_left() const {

    return std::array<double,2> { sw_[0] , 0.5 * ( sw_[1] + nw_[1] ) };

};

std::array<double,2> BoundingBox::mpt_right() const {

    return std::array<double,2> { se_[0] , 0.5 * ( se_[1] + ne_[1] ) };

};

std::array<double,2> BoundingBox::mpt_top() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , nw_[1] };

};

std::array<double,2> BoundingBox::mpt_bottom() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , sw_[1] };

};

std::array<double,2> BoundingBox::center() const {

    return std::array<double,2> { 0.5 * ( se_[0] + sw_[0] ) , 0.5 * ( se_[1] + ne_[1] ) };

};
