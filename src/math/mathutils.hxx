#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "../globaldefines.hxx"

#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  real_t lerp (real_t x1, real_t y1, real_t x2, real_t y2, real_t x0);

  real_t clamp (real_t a, real_t b, real_t x);

  uinteger_t factorial__i (uinteger_t n);
  real_t factorial__i (real_t n);

  uinteger_t fallingFactorial__i_d (uinteger_t n, uinteger_t k);
  real_t fallingFactorial__i_d (real_t n, real_t k);

  uinteger_t fallingFactorial__i (uinteger_t n, uinteger_t k);
  real_t fallingFactorial__i (real_t n, real_t k);

#ifdef REAL_IS_BUILTIN
  real_builtin_t factorial__g (real_builtin_t n);
#else
#ifdef REAL_IS_BOOST_FLOAT128
  boost::multiprecision::float128 factorial__g (
    boost::multiprecision::float128 n
  );
#endif // REAL_IS_BOOST_FLOAT128
#endif // REAL_IS_BUILTIN

#ifdef REAL_IS_BUILTIN
  real_builtin_t fallingFactorial__g_d (real_builtin_t n, real_builtin_t k);
#else
#ifdef REAL_IS_BOOST_FLOAT128
  boost::multiprecision::float128 fallingFactorial__g_d (
    boost::multiprecision::float128 n, boost::multiprecision::float128 k
  );
#endif // REAL_IS_BOOST_FLOAT128
#endif // REAL_IS_BUILTIN
}


#endif // MATHUTILS_HXX
