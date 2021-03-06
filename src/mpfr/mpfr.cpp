//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <mp/mpfr/mpfr.hpp>
#include <sstream>
#include <cstdlib>
#include <cstring>

namespace mp
{
    std::size_t mpfr::copy_count = 0;

    template <class T>
    std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
    {
      std::ostringstream oss;
      oss << f << t;
      return oss.str();
    }

    std::string mpfr::to_string(size_t n, int b, mp_rnd_t mode) const
    {
        using std::string;
        char *s, *ns = NULL;
        size_t slen, nslen;
        mp_exp_t exp;
        string out;
        
        if(mpfr_inf_p(data))
        {
            if(mpfr_sgn(data)>0) return "+@Inf@";
            else                 return "-@Inf@";
        }
        
        if(mpfr_zero_p(data)) return "0";
        if(mpfr_nan_p(data))  return "@NaN@";
        
        s  = mpfr_get_str(NULL,&exp,b,0,data,mode);
        ns = mpfr_get_str(NULL,&exp,b,n,data,mode);
       
        if(s!=NULL && ns!=NULL)
        {
            slen  = strlen(s);
            nslen = strlen(ns);
            if(nslen<=slen)
            {
                mpfr_free_str(s);
                s = ns;
                slen = nslen;
            }
            else {
                mpfr_free_str(ns);
            }
            
            // Make human eye-friendly formatting if possible
            if (exp>0 && static_cast<size_t>(exp)<slen)
            {
                if(s[0]=='-')
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+exp) ptr--;
                    
                    if(ptr==s+exp) out = string(s,exp+1);
                    else           out = string(s,exp+1)+'.'+string(s+exp+1,ptr-(s+exp+1)+1);
                    
                    //out = string(s,exp+1)+'.'+string(s+exp+1);
                }
                else
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+exp-1) ptr--;
                    
                    if(ptr==s+exp-1) out = string(s,exp);
                    else             out = string(s,exp)+'.'+string(s+exp,ptr-(s+exp)+1);
                    
                    //out = string(s,exp)+'.'+string(s+exp);
                }
                
            }else{ // exp<0 || exp>slen
                if(s[0]=='-')
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+1) ptr--;
                    
                    if(ptr==s+1) out = string(s,2);
                    else         out = string(s,2)+'.'+string(s+2,ptr-(s+2)+1);
                    
                    //out = string(s,2)+'.'+string(s+2);
                }
                else
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s) ptr--;
                    
                    if(ptr==s) out = string(s,1);
                    else       out = string(s,1)+'.'+string(s+1,ptr-(s+1)+1);
                    
                    //out = string(s,1)+'.'+string(s+1);
                }
                
                // Make final string
                if(--exp)
                {
                    if(exp>0) out += "e+"+mp::to_string<mp_exp_t>(exp,std::dec);
                    else      out += "e"+mp::to_string<mp_exp_t>(exp,std::dec);
                }
            }
            
            mpfr_free_str(s);
            return out;
        }else{
            return "conversion error!";
        }
    }
}
