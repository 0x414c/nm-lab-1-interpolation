#ifndef FUNCTIONS_HXX
#define FUNCTIONS_HXX


#include <functional>

#include "numerictypes.hxx"


namespace Math
{
  using std::function;


  real_t f (
    real_t x,
    real_t alpha, real_t beta, real_t gamma,
    real_t delta, real_t epsilon, real_t mu
  );

  real_t d (const function<real_t (real_t)>& func, real_t x, real_t delta);

  real_t r_n (
    const function<real_t (real_t)>& f, const function<real_t (real_t)>& P_n,
    real_t x, real_t t
  );


  enum struct FunctionType : int
  {
    None = 0,
    f = (1 << 0), P_n = (1 << 1), r_n = (1 << 2),
    d_f = (1 << 3), d_P_n = (1 << 4), L_n = (1 << 5),
    All = f | P_n | r_n | d_f | d_P_n | L_n
  };
}


#endif // FUNCTIONS_HXX
