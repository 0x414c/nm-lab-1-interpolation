#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


namespace Math
{
  double lerp (double x1, double y1, double x2, double y2, double x0);

  double clamp (double a, double b, double x);

  unsigned long long fac_i (unsigned long long n);
  double fac_i (double n);

  unsigned long long ffac_i (unsigned long long t, unsigned long long k);
  double ffac_i (double t, double k);

  unsigned long long ffac_i_i (unsigned long long t, unsigned long long k);
  double ffac_i_i (double t, double k);

  double fac_g (double n);

  double ffac_g (double t, double k);
}


#endif // MATHUTILS_HXX
