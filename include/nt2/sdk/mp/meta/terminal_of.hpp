//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_META_TERMINAL_OF_HPP
#define NT2_SDK_MP_META_TERMINAL_OF_HPP

namespace boost { namespace dispatch {
    namespace meta
    {
        /*
        template <typename Expression>
        struct semantic_of<nt2::mp::expr<Expression> >
        {
            typedef nt2::mp::backend::mpfr type;
        };    
        
        template <typename Backend>
        struct semantic_of<nt2::mp::float_<Backend> >
        {
            typedef Backend type;
        };

        template <>
        struct terminal_of<nt2::mp::backend::mpfr>
        {
            typedef nt2::mp::float_<nt2::mp::backend::mpfr> type;
        };
        */
    }
}}

#endif
