#include "../globaldefines.hxx"

#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN

#include <algorithm>
#include <iostream>
#include <limits>

#ifdef REAL_IS_BOOST_FLOAT128
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/gamma.hpp>
#endif // REAL_IS_BOOST_FLOAT128

#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  real_t
  lerp (real_t x1, real_t y1, real_t x2, real_t y2, real_t x0)
  {
    return (y1 + (y2 - y1) * ((x0 - x1) / (x2 - x1)));
  }


  real_t
  clamp (real_t a, real_t b, real_t x)
  {
    return std::max (a, std::min (b, x));
  }


  uinteger_t
  factorial__i (uinteger_t n)
  {
    uinteger_t prod (1);

    for (uinteger_t i (2); i <= n; ++i)
    {
      prod *= i;
    }

    return prod;
  }


  real_t
  factorial__i (real_t n)
  {
    real_t prod (1);

    for (real_t i (2); i <= n; ++i)
    {
      prod *= i;
    }

    return prod;
  }


  uinteger_t
  fallingFactorial__i_d (uinteger_t n, uinteger_t k)
  {
    return (factorial__i (n) / factorial__i (n - k));
  }


  real_t
  fallingFactorial__i_d (real_t n, real_t k)
  {
    return (factorial__i (n) / factorial__i (n - k));
  }


  uinteger_t
  fallingFactorial__i (uinteger_t n, uinteger_t k)
  {
    uinteger_t prod (1);

    for (uinteger_t i (0); i < k; ++i)
    {
      prod *= n - i;
    }

    return prod;
  }


  real_t
  fallingFactorial__i (real_t n, real_t k)
  {
    real_t prod (1);

    for (real_t i (0); i < k; ++i)
    {
      prod *= n - i;
    }

    return prod;
  }


#ifdef REAL_IS_BUILTIN
  real_builtin_t
  factorial__g (real_builtin_t n)
  {
    const real_builtin_t ret (std::tgamma (n + REAL_BUILTIN_C (1.)));

    // HACK: Unifies std::tgamma and boost::tgamma return values
    // due to strange bug in std::tgamma.
    if (std::isnan (ret) || std::isinf (ret))
    {
      return std::numeric_limits<real_builtin_t>::infinity ();
    }
    else
    {
      return ret;
    }
  }
#else
#ifdef REAL_IS_BOOST_FLOAT128
  boost::multiprecision::float128
  factorial__g (boost::multiprecision::float128 n)
  {
    using boost::math::policies::policy;
    using boost::math::policies::errno_on_error;
    using boost::math::policies::domain_error;
    using boost::math::policies::evaluation_error;
    using boost::math::policies::overflow_error;
    using boost::math::policies::pole_error;

    using errnoPolicy = policy<
      domain_error<errno_on_error>,
      pole_error<errno_on_error>,
      overflow_error<errno_on_error>,
      evaluation_error<errno_on_error>
    >;


    // HACK: This is added to unify std::tgamma and boost::tgamma return values
    // due to strange bug in std::tgamma.
    const boost::multiprecision::float128 ret (
      boost::math::tgamma (n + REAL_EXTERNAL_C (1.), errnoPolicy ())
    );

    if (boost::math::isnan (ret) || boost::math::isinf (ret))
    {
      return std::numeric_limits<boost::multiprecision::float128>::infinity ();
    }
    else
    {
      return ret;
    }
  }
#endif // REAL_IS_BOOST_FLOAT128
#endif // REAL_IS_BUILTIN


#ifdef REAL_IS_BUILTIN
  real_builtin_t
  fallingFactorial__g_d (real_builtin_t n, real_builtin_t k)
  {
    return (factorial__g (n) / factorial__g (n - k));
  }
#else
#ifdef REAL_IS_BOOST_FLOAT128
  boost::multiprecision::float128
  fallingFactorial__g_d (
    boost::multiprecision::float128 n, boost::multiprecision::float128 k
  )
  {
    return (factorial__g (n) / factorial__g (n - k));
  }
#endif // REAL_IS_BOOST_FLOAT128
#endif // REAL_IS_BUILTIN
}
