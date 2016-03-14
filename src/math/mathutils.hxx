#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  Float lerp (Float x1, Float y1, Float x2, Float y2, Float x0);

  Float clamp (Float a, Float b, Float x);

  UInteger factorial_i (UInteger n);
  Float factorial_i (Float n);

  UInteger fallingFactorial_i (UInteger t, UInteger k);
  Float fallingFactorial_i (Float t, Float k);

  UInteger fallingFactorial_i_i (UInteger t, UInteger k);
  Float fallingFactorial_i_i (Float t, Float k);

  Float64 factorial_g (Float64 n);
#ifdef QUAD_PRECISION_ENABLED
  Float128 factorial_g (Float128 n);
#endif // QUAD_PRECISION_ENABLED

  Float64 fallingFactorial_g (Float64 t, Float64 k);
#ifdef QUAD_PRECISION_ENABLED
  Float128 fallingFactorial_g (Float128 t, Float128 k);
#endif // QUAD_PRECISION_ENABLED
}


#endif // MATHUTILS_HXX
