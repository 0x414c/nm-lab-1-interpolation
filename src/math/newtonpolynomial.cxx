#include <cmath>
#include <cstddef>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef MULTIPRECISION_ENABLED
#include <boost/math/special_functions/fpclassify.hpp>
#endif // MULTIPRECISION_ENABLED

#include "mathutils.hxx"
#include "newtonpolynomial.hxx"
#include "numerictypes.hxx"


namespace Math
{
  NewtonPolynomial::NewtonPolynomial (
    const std::function<Float (Float)>& func,
    Float x_0, Float x_n_1, size_t n
  ) throw (std::invalid_argument) :
    n_ (n)
  {
    std::clog << '!' << x_0 << ' ' << x_n_1 << ' ' << n << std::endl;

    if (n_ == 0)
    {
      throw std::invalid_argument ("`n_' should be greater than 0.");
    }

    if (x_0 > x_n_1)
    {
      throw std::invalid_argument ("`x_0' should be less or equal to `x_n_1'.");
    }

    finDiffs_ = std::vector<std::vector<Float>> (n_);

    for (size_t i (0); i < n_; ++i)
    {
      finDiffs_[i] = std::vector<Float> (n_ - i);
    }

    x_ = std::vector<Float> (n_);

    const Float h ((x_n_1 - x_0) / Float ((n > 1) ? (n_ - 1) : 1));

//    std::clog << "h=" << h << std::endl;

    for (size_t k (0); k < n_; ++k)
    {
      x_[k] = x_0 + Float (k) * h;

      const Float y_k (func (x_[k]));

#ifdef MULTIPRECISION_ENABLED
      if (boost::math::isnan (y_k))
#else
      if (std::isnan (y_k))
#endif // MULTIPRECISION_ENABLED
      {
        finDiffs_[0][k] = 0;
      }
      else
      {
        finDiffs_[0][k] = y_k;
      }

//      std::clog << "k=" << k << ", x=" << x_[k] << ", y=" << finDiffs_[0][k] << std::endl;
    }

    for (size_t i (1); i < n_; ++i)
    {
      for (size_t j (0); j < n_ - i; ++j)
      {
        finDiffs_[i][j] = finDiffs_[i - 1][j + 1] - finDiffs_[i - 1][j];

//        std::clog << i << ' ' << j << ' ' << finDiffs_[i][j] << std::endl;
      }
    }
  }


  Float
  NewtonPolynomial::operator () (Float t) const
  {
    Float acc (0);

    for (size_t k (0); k < n_; ++k)
    {
      acc += fallingFactorial_g (t, Float (k)) / factorial_g (Float (k)) *
             finDiffs_[k][0];
    }

    return acc;
  }
}
