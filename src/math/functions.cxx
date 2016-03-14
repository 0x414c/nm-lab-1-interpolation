#include "functions.hxx"

#include <cmath>

#include <functional>

#include "numerictypes.hxx"


namespace Math
{
  using std::cos;
  using std::function;
  using std::pow;
  using std::sin;


  Float
  f (
    Float x,
    Float alpha, Float beta, Float gamma,
    Float delta, Float epsilon, Float mu
  )
  {
    return (
      alpha * sin (beta / pow (x - gamma, 2)) +
      delta * cos (epsilon / pow (x - mu, 2))
    );
  }


  Float
  d (const function<Float (Float)>& func, Float x, Float delta)
  {
    return ((func (x + delta) - func (x)) / delta);
  }


  Float
  r_n (
    const function<Float (Float)>& f, const function<Float (Float)>& P_n,
    Float x, Float t
  )
  {
    return (f (x) - P_n (t));
  }
}
