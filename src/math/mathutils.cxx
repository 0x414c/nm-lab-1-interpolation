#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>

#ifdef MULTIPRECISION_ENABLED
#include <boost/cstdfloat.hpp>
#include <boost/math/special_functions.hpp>
#endif // MULTIPRECISION_ENABLED

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
  factorial_i (UInteger n)
  {
    UInteger acc (1);

    for (UInteger k (2); k <= n; ++k)
    {
      acc *= k;
    }

    return acc;
  }


  Float
  factorial_i (Float n)
  {
    Float acc (1);

    for (Float k (2); k <= n; ++k)
    {
      acc *= k;
    }

    return acc;
  }


  UInteger
  fallingFactorial_i (UInteger n, UInteger k)
  {
    return (factorial_i (n) / factorial_i (n - k));
  }


  Float
  fallingFactorial_i (Float n, Float k)
  {
    return (factorial_i (n) / factorial_i (n - k));
  }


  UInteger
  fallingFactorial_i_i (UInteger n, UInteger k)
  {
    UInteger acc (1);

    for (UInteger i (0); i < k; ++i)
    {
      acc *= n - i;
    }

    return acc;
  }


  Float
  fallingFactorial_i_i (Float n, Float k)
  {
    Float acc (1);

    for (Float i (0); i < k; ++i)
    {
      acc *= n - i;
    }

    return acc;
  }


  DoubleFloat
  factorial_g (DoubleFloat n)
  {
    const DoubleFloat ret (std::tgamma (n + 1));

    //HACK: This is added to unify std::tgamma and boost::tgamma return values.
    if (std::isnan (ret) || std::isinf (ret))
    {
      return std::numeric_limits<DoubleFloat>::infinity ();
    }
    else
    {
      return ret;
    }
  }


#ifdef MULTIPRECISION_ENABLED
  QuadFloat
  factorial_g (QuadFloat n)
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


    //HACK: This is added to unify std::tgamma and boost::tgamma return values.
    const QuadFloat ret (boost::math::tgamma (n + 1, errnoPolicy ()));

    if (boost::math::isnan (ret) || boost::math::isinf (ret))
    {
      return std::numeric_limits<QuadFloat>::infinity ();
    }
    else
    {
      return ret;
    }
  }
#endif // MULTIPRECISION_ENABLED


  DoubleFloat
  fallingFactorial_g (DoubleFloat n, DoubleFloat k)
  {
    return (factorial_g (n) / factorial_g (n - k));
  }


#ifdef MULTIPRECISION_ENABLED
  QuadFloat
  fallingFactorial_g (QuadFloat n, QuadFloat k)
  {
    return (factorial_g (n) / factorial_g (n - k));
  }
#endif // MULTIPRECISION_ENABLED
}
