#include <cmath>
#include <cstddef>

#include <functional>
#include <limits>
#include <stdexcept>
#include <vector>

#ifdef QUAD_PRECISION_ENABLED
#include <boost/math/special_functions/fpclassify.hpp>
#endif // QUAD_PRECISION_ENABLED

#include "mathutils.hxx"
#include "newtonpolynomial.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  NewtonPolynomial::NewtonPolynomial (
    const std::function<Float (Float)>& func,
    Float x_0, Float x_n_1, size_t n
  ) throw (std::invalid_argument) :
    n_ (n)
  {
    if (n_ < 2)
    {
      throw std::invalid_argument ("`n_' should be greater than 1.");
    }

    if (x_0 >= x_n_1)
    {
      throw std::invalid_argument ("`x_0' should be less than `x_n_1'.");
    }

    finDiffs_ = std::vector<std::vector<Float>> (n_);

    for (size_t i (0); i < n_; ++i)
    {
      finDiffs_[i] = std::vector<Float> (n_ - i);
    }

    x_ = std::vector<Float> (n_);

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

        // FIXME: [+~] y := avg (f (x + eps), f (x - eps))
//        finDiffs_[0][k] = 0;
        finDiffs_[0][k] = Math::lerp (
          x_[k] - Epsilon, func (x_[k] - Epsilon),
          x_[k] + Epsilon, func (x_[k] + Epsilon),
          x_[k]
        );
      }
      else
      {
        finDiffs_[0][k] = y_k;
      }
    }

    for (size_t i (1); i < n_; ++i)
    {
      for (size_t j (0); j < n_ - i; ++j)
      {
        finDiffs_[i][j] = finDiffs_[i - 1][j + 1] - finDiffs_[i - 1][j];
      }
    }
  }


  Float
  NewtonPolynomial::operator () (Float t) const
  {
//    return valueAt_g_n (t);
    return valueAt_p_k (t);
  }


  Float
  NewtonPolynomial::valueAt_g_n (Float t) const
  {
    Float sum (0);

    // Var. #1: naïve summation
    for (size_t k (0); k < n_; ++k)
    {
      // Var. #1: Factorial via Gamma function, falling factorial via division
      // Overflow at k = 173 w/ Float64
      sum += fallingFactorial_g (t, Float (k)) / factorial_g (Float (k)) *
             finDiffs_[k][0];

      // Var #2: Factorials via iterative multiplication
      // Overflow at k = 173 w/ Float64
//      sum += fallingFactorial_i_i (t, Float (k)) / factorial_i (Float (k)) *
//             finDiffs_[k][0];

      // Var. #3: Factorial via iterative multiplication,
      // falling factorial via division
      // Overflow at k = 173 w/ Float64
//      sum += fallingFactorial_i (t, Float (k)) / factorial_i (Float (k)) *
//             finDiffs_[k][0];

      // Var. #4: Pairwise-like division
//      {
//        Float prod (1);

//        for (size_t i (0); i < k; ++i)
//        {
//          prod *= (t - Float (i)) / (Float (k) - Float (i));
//        }

//        sum += prod * finDiffs_[k][0];
//      }
    }

    return sum;
  }


  Float
  NewtonPolynomial::valueAt_p_k (Float t) const
  {
    // Var. #2: Kahan summation (aka compensated summation)
    Float sum (0), correction (0);

    for (size_t k (0); k < n_; ++k)
    {
      // Var. #4: Pairwise-like division
      Float prod (1);

      for (size_t i (0); i < k; ++i)
      {
        prod *= (t - Float (i)) / (Float (k) - Float (i));
      }

      prod *= finDiffs_[k][0];

      const Float correctedNextTerm (prod - correction);
      const Float newSum (sum + correctedNextTerm);
      correction = (newSum - sum) - correctedNextTerm;
      sum = newSum;
    }

    return sum;
  }
}
