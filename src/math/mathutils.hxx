#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  Float lerp (Float x1, Float y1, Float x2, Float y2, Float x0);

  Float clamp (Float a, Float b, Float x);

  UInteger factorial__i (UInteger n);
  Float factorial__i (Float n);

  UInteger fallingFactorial__i_d (UInteger n, UInteger k);
  Float fallingFactorial__i_d (Float n, Float k);

  UInteger fallingFactorial__i (UInteger n, UInteger k);
  Float fallingFactorial__i (Float n, Float k);

  Float64 factorial__g (Float64 n);
#ifdef QUAD_PRECISION_ENABLED
  Float128 factorial__g (Float128 n);
#endif // QUAD_PRECISION_ENABLED

  Float64 fallingFactorial__g_d (Float64 n, Float64 k);
#ifdef QUAD_PRECISION_ENABLED
  Float128 fallingFactorial__g_d (Float128 n, Float128 k);
#endif // QUAD_PRECISION_ENABLED
}


#endif // MATHUTILS_HXX
