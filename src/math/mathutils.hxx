#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  Float lerp (Float x1, Float y1, Float x2, Float y2, Float x0);

  Float clamp (Float a, Float b, Float x);

  UInteger factorial_i (UInteger n);
  Float factorial_i (Float n);

  UInteger fallingFactorial_i (UInteger t, UInteger k);
  Float fallingFactorial_i (Float t, Float k);

  UInteger fallingFactorial_i_i (UInteger t, UInteger k);
  Float fallingFactorial_i_i (Float t, Float k);

  DoubleFloat factorial_g (DoubleFloat n);
#ifdef MULTIPRECISION_ENABLED
  QuadFloat factorial_g (QuadFloat n);
#endif // MULTIPRECISION_ENABLED

  DoubleFloat fallingFactorial_g (DoubleFloat t, DoubleFloat k);
#ifdef MULTIPRECISION_ENABLED
  QuadFloat fallingFactorial_g (QuadFloat t, QuadFloat k);
#endif // MULTIPRECISION_ENABLED
}


#endif // MATHUTILS_HXX
