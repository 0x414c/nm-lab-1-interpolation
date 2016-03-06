﻿#include "functions.hxx"

#include <cmath>

#include <functional>


namespace Math
{
  using std::cos;
  using std::function;
  using std::sin;
  using std::tan;


  double
  f (
    double x,
    double alpha, double beta, double gamma,
    double delta, double epsilon, double mu
  )
  {
//    return 2. * cos (x);

//    return 2. * sin (x);

//    return (
//      alpha * (sin (tan (beta / (x - gamma)))) + delta * (cos (epsilon * x))
//    );

    return (
      alpha * sin (beta / pow (x - gamma, 2.)) +
      delta * cos (epsilon / pow (x - mu, 2.))
    );
  }


  double
  d (const function<double (double)>& func, double x, double delta)
  {
    return (
      (func (x + delta) - func (x)) / delta
    );
  }


  double
  r_n (
    const function<double (double)>& f, const function<double (double)>& P_n,
    double x, double t
  )
  {
    return (
      f (x) - P_n (t)
    );
  }
}