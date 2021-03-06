//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_EXP_HPP
#define MP_MPFR_EXP_HPP

#include <mp/mpfr/mpfr.hpp>
#include <mp/exp.hpp>

namespace mp
{
    template <>
    struct mpfr::evaluate<tag::exp>
    {
        BOOST_FORCEINLINE
        mpfr & operator()(mpfr &res, mpfr const & op) const
        {
            mpfr_exp(res.data, op.data, MPFR_RNDN);

            return res;
        }
    };
}

#endif
