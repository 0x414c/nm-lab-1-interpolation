#include "../globaldefines.hxx"

#ifndef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN
#include <cstddef>

#include <functional>
#include <limits>
#include <stdexcept>
#include <vector>

#ifdef REAL_IS_BOOST_FLOAT128
#include <boost/math/special_functions/fpclassify.hpp>
#endif // REAL_IS_BOOST_FLOAT128

#include "mathutils.hxx"
#include "newtonpolynomial.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  NewtonPolynomial::NewtonPolynomial (
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

    finDiffs_ = std::vector<std::vector<real_t>> (n_);

    for (size_t i (0); i < n_; ++i)
    {
      finDiffs_[i] = std::vector<real_t> (n_ - i);
    }

    x_ = std::vector<real_t> (n_);

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


  real_t
  NewtonPolynomial::operator () (real_t t) const
  {
    return valueAt__p_c (t);
//    return valueAt__g_n (t);
  }


  real_t
  NewtonPolynomial::valueAt__p_c (real_t t) const
  {
    // Var. #2: Kahan summation (aka compensated summation)
    real_t sum (finDiffs_[0][0]), correction (0), prod (1);

    for (size_t k (1); k < n_; ++k)
    {
      // Var. #4: Pairwise-like division
      prod *= (t - real_t (k - 1)) / real_t (k);

      const real_t correctedNextTerm (prod * finDiffs_[k][0] - correction);
      const real_t newSum (sum + correctedNextTerm);
      correction = (newSum - sum) - correctedNextTerm;
      sum = newSum;
    }

    return sum;
  }


  real_t
  NewtonPolynomial::valueAt__g_n (real_t t) const
  {
    real_t sum (0);

    // Var. #1: Naïve summation
    for (size_t k (0); k < n_; ++k)
    {
      // Var. #1: Factorial via Gamma function, falling factorial via division
      // Overflow at k = 173 w/ float64_t
      sum += fallingFactorial__g_d (t, real_t (k)) / factorial__g (real_t (k)) *
             finDiffs_[k][0];

      // Var #2: Factorials via iterative multiplication
      // Overflow at k = 173 w/ float64_t
//      sum += fallingFactorial__i (t, real_t (k)) / factorial_i (real_t (k)) *
//             finDiffs_[k][0];

      // Var. #3: Factorial via iterative multiplication,
      // falling factorial via division
      // Overflow at k = 173 w/ float64_t
//      sum += fallingFactorial__i_d (t, real_t (k)) / factorial_i (real_t (k)) *
//             finDiffs_[k][0];

      // Var. #4: Pairwise-like division
//      {
//        real_t prod (1);

//        for (size_t i (0); i < k; ++i)
//        {
//          prod *= (t - real_t (i)) / (real_t (k) - real_t (i));
//        }

//        sum += prod * finDiffs_[k][0];
//      }
    }

    return sum;
  }
}
