#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>

#ifdef QUAD_PRECISION_ENABLED
#include <boost/cstdfloat.hpp>
#include <boost/math/special_functions.hpp>
#endif // QUAD_PRECISION_ENABLED

#include "../config.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"


namespace Math
{
  Float
  lerp (Float x1, Float y1, Float x2, Float y2, Float x0)
  {
    return (y1 + (y2 - y1) * ((x0 - x1) / (x2 - x1)));
  }


  Float
  clamp (Float a, Float b, Float x)
  {
    return std::max (a, std::min (b, x));
  }


  UInteger
  factorial__i (UInteger n)
  {
    UInteger prod (1);

    for (UInteger i (2); i <= n; ++i)
    {
      prod *= i;
    }

    return prod;
  }


  Float
  factorial__i (Float n)
  {
    Float prod (1);

    for (Float i (2); i <= n; ++i)
    {
      prod *= i;
    }

    return prod;
  }


  UInteger
  fallingFactorial__i_d (UInteger n, UInteger k)
  {
    return (factorial__i (n) / factorial__i (n - k));
  }


  Float
  fallingFactorial__i_d (Float n, Float k)
  {
    return (factorial__i (n) / factorial__i (n - k));
  }


  UInteger
  fallingFactorial__i (UInteger n, UInteger k)
  {
    UInteger prod (1);

    for (UInteger i (0); i < k; ++i)
    {
      prod *= n - i;
    }

    return prod;
  }


  Float
  fallingFactorial__i (Float n, Float k)
  {
    Float prod (1);

    for (Float i (0); i < k; ++i)
    {
      prod *= n - i;
    }

    return prod;
  }


  Float64
  factorial__g (Float64 n)
  {
    const Float64 ret (std::tgamma (n + 1));

    // HACK: Unifies std::tgamma and boost::tgamma return values
    // due to strange bug in std::tgamma.
    if (std::isnan (ret) || std::isinf (ret))
    {
      return std::numeric_limits<Float64>::infinity ();
    }
    else
    {
      return ret;
    }
  }


#ifdef QUAD_PRECISION_ENABLED
  Float128
  factorial__g (Float128 n)
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
    const Float128 ret (boost::math::tgamma (n + 1, errnoPolicy ()));

    if (boost::math::isnan (ret) || boost::math::isinf (ret))
    {
      return std::numeric_limits<Float128>::infinity ();
    }
    else
    {
      return ret;
    }
  }
#endif // QUAD_PRECISION_ENABLED


  Float64
  fallingFactorial__g_d (Float64 n, Float64 k)
  {
    return (factorial__g (n) / factorial__g (n - k));
  }


#ifdef QUAD_PRECISION_ENABLED
  Float128
  fallingFactorial__g_d (Float128 n, Float128 k)
  {
    return (factorial__g (n) / factorial__g (n - k));
  }
#endif // QUAD_PRECISION_ENABLED
}
