#ifndef NUMERICTYPES_HXX
#define NUMERICTYPES_HXX


//#include <cfloat> // limits of float types
//#include <cfenv> // floating-point environment access functions
//#include <cinttypes> // formatting macros, intmax_t and uintmax_t math and conversions
//#include <climits> // limits of integral types
//#include <cmath> // common mathematics functions
//#include <ccomplex> // complex number type
//#include <ctgmath>
//#include <cstddef> // typedefs for types such as size_t, NULL and others
//#include <cstdlib> // General purpose utilities: program control, dynamic memory allocation, random numbers, sort and search
#include <cstdint> // fixed-size types and limits of other types
//#include <limits> // standardized way to query properties of arithmetic types

#ifdef MULTIPRECISION_ENABLED
#include <boost/multiprecision/float128.hpp>
#endif // MULTIPRECISION_ENABLED


namespace Math
{
  using Integer8 = int8_t;
  using Integer16 = int16_t;
  using Integer32 = int32_t;
  using Integer64 = int64_t;
  using IntegerMax = intmax_t;
  using Integer = Integer64;

  using UInteger8 = uint8_t;
  using UInteger16 = uint16_t;
  using UInteger32 = uint32_t;
  using UInteger64 = uint64_t;
  using UIntegerMax = uintmax_t;
  using UInteger = UInteger64;

  using SingleFloat = float;
  using DoubleFloat = double;
  using ExtendedFloat = long double;
#ifdef MULTIPRECISION_ENABLED
  using QuadFloat = boost::multiprecision::float128;
  using Float = QuadFloat;
#else
  using Float = ExtendedFloat;
#endif // MULTIPRECISION_ENABLED
}


#endif // NUMERICTYPES_HXX
