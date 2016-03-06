#include "mathutils.hxx"

#include <cmath>

#include <algorithm>

#include <QDebug>


namespace Math
{
  /* double lerp (double a, double b, float w)
  {
    return (a + w * (b - a));
  }  */
  /* double lerp (double v0, double v1, double t)
  {
    return ((1. - t) * v0 + t * v1);
  } */
  double
  lerp (double x1, double y1, double x2, double y2, double x0)
  {
    return (y1 + (y2 - y1) * ((x0 - x1) / (x2 - x1)));
  }


  /* double clamp (double x, double a, double b)
  {
    return max (a, min (b, x));
  } */
  /* double saturate (double x)
  {
    return max (0., min (1., x));
  } */
  double
  clamp (double a, double b, double x)
  {
    return std::max (a, std::min (b, x));
  }


  unsigned long long
  fac_i (unsigned long long n)
  {
    unsigned long long acc (1);

    for (unsigned long long k (2); k <= n; ++k)
    {
      acc *= k;
    }

    return acc;
  }


  double
  fac_i (double n)
  {
    double acc (1.);

    for (double k (2.); k <= n; ++k)
    {
      acc *= k;
    }

    return acc;
  }


  unsigned long long
  ffac_i (unsigned long long n, unsigned long long k)
  {
//    if (n < k)
//    {
//      return 0;
//    }
//    else
    {
      return (fac_i (n) / fac_i (n - k));
    }
  }


  double
  ffac_i (double n, double k)
  {
//    if (n < k)
//    {
//      return 0.;
//    }
//    else
    {
      return (fac_i (n) / fac_i (n - k));
    }
  }


  unsigned long long
  ffac_i_i (unsigned long long n, unsigned long long k)
  {
//    if (n < k)
//    {
//      return 0;
//    }
//    else
    {
      unsigned long long acc (1);

      for (unsigned long long i (0); i < k; ++i)
      {
        acc *= n - i;
      }

      return acc;
    }
  }


  double
  ffac_i_i (double n, double k)
  {
//    if (n < double (k))
//    {
//      return 0.;
//    }
//    else
    {
      double acc (1.);

      for (double i (0.); i < k; ++i)
      {
        acc *= n - i;
      }

      return acc;
    }
  }


  double
  fac_g (double n)
  {
    return std::tgamma (n + 1.);
  }


  double
  ffac_g (double n, double k)
  {
    return (fac_g (n) / fac_g (n - k));
  }
}
