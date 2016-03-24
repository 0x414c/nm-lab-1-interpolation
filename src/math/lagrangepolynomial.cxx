#include "../globaldefines.hxx"

#ifndef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN
#include <cstddef>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef REAL_IS_BOOST_FLOAT128
#include <boost/math/special_functions/fpclassify.hpp>
#endif // REAL_IS_BOOST_FLOAT128

#include "lagrangepolynomial.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  LagrangePolynomial::LagrangePolynomial (
    const std::function<real_t (real_t)>& func,
    real_t x_0, real_t x_n_1, size_t n
  ) throw (std::invalid_argument) :
    n_ (n)
  {
    if (n_ < 2)
    {
      throw std::invalid_argument ("`n' should be greater than 1.");
    }

    if (x_0 >= x_n_1)
    {
      throw std::invalid_argument ("`x_0' should be less than `x_n_1'.");
    }

    x_ = std::vector <real_t> (n_);
    y_ = std::vector <real_t> (n_);

    const real_t h ((x_n_1 - x_0) / real_t (n_ - 1));

    for (size_t k (0); k < n_; ++k)
    {
      x_[k] = x_0 + real_t (k) * h;

      const real_t y_k (func (x_[k]));

#ifdef REAL_IS_BOOST_FLOAT128
      if (boost::math::isnan (y_k))
#else
      if (std::isnan (y_k))
#endif // REAL_IS_BOOST_FLOAT128
      {
        using Config::MathConstants::Epsilon;


        y_[k] = Math::lerp (
          x_[k] - Epsilon, func (x_[k] - Epsilon),
          x_[k] + Epsilon, func (x_[k] + Epsilon),
          x_[k]
        );
      }
      else
      {
        y_[k] = y_k;
      }
    }
  }


  real_t
  LagrangePolynomial::operator () (real_t x) const
  {
    return valueAt (x);
  }


  real_t
  LagrangePolynomial::valueAt (real_t x) const
  {
    real_t sum (0), correction (0);

    for (size_t k (0); k < n_; ++k)
    {
      real_t C_k (1);

      for (size_t i (0); i < k; ++i)
      {
        C_k *= (x - x_[i]) / (x_[k] - x_[i]);
      }

      for (size_t i (k + 1); i < n_; ++i)
      {
        C_k *= (x - x_[i]) / (x_[k] - x_[i]);
      }

      C_k *= y_[k];

      const real_t correctedNextTerm (C_k - correction);
      const real_t newSum (sum + correctedNextTerm);
      correction = (newSum - sum) - correctedNextTerm;
      sum = newSum;
    }

    return sum;
  }
}
