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
    None = 0,
    f = (1 << 0), P_n = (1 << 1), r_n = (1 << 2), d_f = (1 << 3), d_P_n = (1 << 4),
    All = f | P_n | r_n | d_f | d_P_n
  };
}


#endif // FUNCTIONS_HXX
