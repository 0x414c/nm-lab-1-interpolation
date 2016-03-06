#include "newtonpolynomial.hxx"

#include <cmath>
#include <cstdlib>

#include <functional>
#include <stdexcept>
#include <vector>

#include <QDebug>

#include "mathutils.hxx"
#include "numerictypes.hxx"


namespace Math
{
  NewtonPolynomial::NewtonPolynomial (
    const std::function<double (double)>& func,
    double x_0, double x_n_1, size_t n
  ) throw (std::invalid_argument) :
    n_ (n)
  {
    qDebug () << "!!" << x_0 << x_n_1 << n;

    if (n_ == 0)
    {
      throw std::invalid_argument ("`n_' should be greater than 0.");
    }

    if (x_0 > x_n_1)
    {
      throw std::invalid_argument ("`x_0' should be less or equal to `x_n_1'.");
    }

    finDiffs_ = std::vector<std::vector<double>> (n_);

    for (size_t i (0); i < n_; ++i)
    {
      finDiffs_[i] = std::vector<double> (n_ - i);
    }

    x_ = std::vector<double> (n_);

    const double h ((x_n_1 - x_0) / double ((n > 1) ? (n_ - 1) : 1));

    qDebug () << "h=" << h;

    for (size_t k (0); k < n_; ++k)
    {
      x_[k] = x_0 + double (k) * h;

      const double y_k (func (x_[k]));

      if (std::isnan (y_k))
      {
        finDiffs_[0][k] = 0.;
      }
      else
      {
        finDiffs_[0][k] = y_k;
      }

      qDebug () << "k=" << k << "x=" << x_[k] << "y=" << finDiffs_[0][k];
    }

    for (size_t i (1); i < n_; ++i)
    {
      for (size_t j (0); j < n_ - i; ++j)
      {
        finDiffs_[i][j] = finDiffs_[i - 1][j + 1] - finDiffs_[i - 1][j];

//        qDebug () << i << j << finDiffs_[i][j];
      }
    }
  }


  double
  NewtonPolynomial::operator () (double t) const
  {
    double acc (0.);

    for (size_t k (0); k < n_; ++k)
    {
      acc += ffac_g (t, double (k)) / fac_g (double (k)) * finDiffs_[k][0];
    }

    return acc;
  }
}
