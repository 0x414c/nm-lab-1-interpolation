#include <cmath>
#include <cstddef>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef QUAD_PRECISION_ENABLED
#include <boost/math/special_functions/fpclassify.hpp>
#endif // QUAD_PRECISION_ENABLED

#include "lagrangepolynomial.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  LagrangePolynomial::LagrangePolynomial (
    const std::function<Float (Float)>& func,
    Float x_0, Float x_n_1, size_t n
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

    x_ = std::vector <Float> (n_);
    y_ = std::vector <Float> (n_);

    const Float h ((x_n_1 - x_0) / Float (n_ - 1));

    for (size_t k (0); k < n_; ++k)
    {
      x_[k] = x_0 + Float (k) * h;

      const Float y_k (func (x_[k]));

#ifdef QUAD_PRECISION_ENABLED
      if (boost::math::isnan (y_k))
#else
      if (std::isnan (y_k))
#endif // QUAD_PRECISION_ENABLED
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


  Float
  LagrangePolynomial::operator () (Float x) const
  {
    return valueAt (x);
  }


  Float
  LagrangePolynomial::valueAt (Float x) const
  {
    Float sum (0), correction (0);

    for (size_t k (0); k < n_; ++k)
    {
      Float C_k (1);

      // TODO: [~~] Reuse results from previous step.
      for (size_t i (0); i < k; ++i)
      {
        C_k *= (x - x_[i]) / (x_[k] - x_[i]);
      }

      for (size_t i (k + 1); i < n_; ++i)
      {
        C_k *= (x - x_[i]) / (x_[k] - x_[i]);
      }

      C_k *= y_[k];

      const Float correctedNextTerm (C_k - correction);
      const Float newSum (sum + correctedNextTerm);
      correction = (newSum - sum) - correctedNextTerm;
      sum = newSum;
    }

    return sum;
  }
}
