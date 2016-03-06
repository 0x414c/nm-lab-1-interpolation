#ifndef FUNCTIONS_HXX
#define FUNCTIONS_HXX


#include <functional>


namespace Math
{
  using std::function;


  double f (
    double x,
    double alpha, double beta, double gamma,
    double delta, double epsilon, double mu
  );

  double d (const function<double (double)>& func, double x, double delta);

  double r_n (
    const function<double (double)>& f, const function<double (double)>& P_n,
    double x, double t
  );


  enum struct FunctionType : int
  {
    _ = 0, f = 1, P_n = 2, r_n = 4, d_f = 8, d_P_n = 16
  };
}


#endif // FUNCTIONS_HXX
