#ifndef NUMERICTYPES_HXX
#define NUMERICTYPES_HXX

/*
 * This is a (very) simple and lighweight (thus limited)
 * alternative to the `boost/cstdfloat' (which doesn't work on MinGW's GCC).
 * See the N3626 proposal for more info.
 */

#include <cmath> // For `float_t' and `double_t'.
#include <cstdint> // For fixed-width integer types.

#include <limits>

#ifdef QUAD_PRECISION_ENABLED
#include <boost/multiprecision/float128.hpp>
#endif // QUAD_PRECISION_ENABLED


namespace Math
{
  static_assert (
    std::numeric_limits<float>::is_iec559,
    "Fundamental type `float' does not conform to the IEEE 754 standard."
  );

  static_assert (
    std::numeric_limits<double>::is_iec559,
    "Fundamental type `double' does not conform to the IEEE 754 standard."
  );

  static_assert (
    std::numeric_limits<long double>::is_iec559,
    "Fundamental type `long double' does not conform to the IEEE 754 standard."
  );

#ifdef QUAD_PRECISION_ENABLED
  static_assert (
    std::numeric_limits<boost::multiprecision::float128>::is_iec559,
    "External type `boost::multiprecision::float128' does not"
    " conform to the IEEE 754 standard."
  );
#endif // QUAD_PRECISION_ENABLED


  /* FLT_EVAL_METHOD (implementation defined macro):
     Specifies the precision in which all floating-point arithmetic
     operations other than assignment and cast are done.
     Value    Explanation
     negative implementation-defined behavior
     -1       the default precision is not known (-mfpmath=both)
      0       all operations and constants evaluate in the range and precision
              of the type used.
              Additionally, `float_t' and `double_t are equivalent to
              `float' and `double' respectively (-mfpmath=sse)
      1       all operations and constants evaluate in the range and
              precision of `double'.
              Additionally, both `float_t' and `double_t' are
              equivalent to `double'
      2       all operations and constants evaluate in the range
              and precision of `long double'.
              Additionally, both `float_t' and `double_t' are equivalent
              to `long double' (-mfpmath=387)

     ??? This ought to change with the setting of the fp control word;
     the value provided by the compiler assumes the widest setting.
  */

  // Most efficient floating-point type at least as wide as `float' (32 bits).
  // The actual width depends on `FLT_EVAL_METHOD'.
  using Float32Fast = std::float_t;

  // Most efficient floating-point type at least as wide as `double' (64 bits).
  // The actual width depends on `FLT_EVAL_METHOD'.
  using Float64Fast = std::double_t;

  // Fixed-width IEEE 754 compliant floating point types.
  using Float32 = float;
  using Float64 = double;
  // NOTE: Extended float is a nasty thing. The real width of `long double'
  // can be either 96 or 128 bits according to GCC's alignment switches
  // (`-m96bit-long-double' and `-m128bit-long-double'). These adds padding
  // only, not any extra precision (and can lead to ABI compatibility issues).
  // NOTE: The precision of the x87 FPU can be adjusted w/ `-mpc{32, 64, 80}'
  // switches (these will not change the actual width of `long double' type).
  using Float80 = long double; // Or `__float80'?
#ifdef QUAD_PRECISION_ENABLED
  using Float128 = boost::multiprecision::float128;
#endif // QUAD_PRECISION_ENABLED

  // "Generic" floating point type.
#ifdef QUAD_PRECISION_ENABLED
  using Float = Float128;
#else
  using Float = Float80;
#endif // QUAD_PRECISION_ENABLED


  // Fixed-width integer types.
  using Integer8 = int8_t;
  using Integer16 = int16_t;
  using Integer32 = int32_t;
  using Integer64 = int64_t;

  // Fastest fixed-width integer types w/ width of at least as specified.
  using Integer8Fast = int_fast8_t;
  using Integer16Fast = int_fast16_t;
  using Integer32Fast = int_fast32_t;
  using Integer64Fast = int_fast64_t;

  // Maximum-width integer type.
  using IntegerMax = intmax_t;

  // "Generic" integer type.
  using Integer = IntegerMax;

  // Fixed-width unsigned integer types.
  using UInteger8 = uint8_t;
  using UInteger16 = uint16_t;
  using UInteger32 = uint32_t;
  using UInteger64 = uint64_t;

  // Fastest fixed-width unsigned integer types w/ width of at least as specified.
  using UInteger8Fast = uint_fast8_t;
  using UInteger16Fast = uint_fast16_t;
  using UInteger32Fast = uint_fast32_t;
  using UInteger64Fast = uint_fast64_t;

  // Maximum-width unsigned integer type.
  using UIntegerMax = uintmax_t;

  // "Generic" unsigned integer type.
  using UInteger = UIntegerMax;
}


#endif // NUMERICTYPES_HXX
