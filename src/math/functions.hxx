#ifndef FUNCTIONS_HXX
#define FUNCTIONS_HXX


#include <functional>

#include "numerictypes.hxx"


namespace Math
{
  using std::function;


  Float f (
    Float x,
    Float alpha, Float beta, Float gamma,
    Float delta, Float epsilon, Float mu
  );

  Float d (const function<Float (Float)>& func, Float x, Float delta);

  Float r_n (
    const function<Float (Float)>& f, const function<Float (Float)>& P_n,
    Float x, Float t
  );


  enum struct FunctionType : int
  {
    _ = 0, f = 1, P_n = 2, r_n = 4, d_f = 8, d_P_n = 16
  };
}


#endif // FUNCTIONS_HXX
