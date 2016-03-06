#ifndef NEWTONPOLYNOMIAL_HXX
#define NEWTONPOLYNOMIAL_HXX

#include <cstdlib>

#include <functional>
#include <stdexcept>
#include <vector>


namespace Math
{
  class NewtonPolynomial
  {
    public:
      NewtonPolynomial (
        const std::function<double (double)>& func,
        double x_0, double x_n_1, size_t n
      ) throw (std::invalid_argument);

      double operator () (double t) const;


    private:
      std::vector<std::vector<double>> finDiffs_;

      std::vector<double> x_;

      size_t n_;
  };
}


#endif // NEWTONPOLYNOMIAL_HXX
