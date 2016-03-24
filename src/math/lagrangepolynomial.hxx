#ifndef LAGRANGEPOLYNOMIAL_HXX
#define LAGRANGEPOLYNOMIAL_HXX


#include <cstddef>

#include <functional>
#include <stdexcept>
#include <vector>

#include "numerictypes.hxx"


namespace Math
{
  class LagrangePolynomial
  {
    public:
      LagrangePolynomial (
        const std::function<real_t (real_t)>& func,
        real_t x_0, real_t x_n_1, size_t n
      ) throw (std::invalid_argument);

      real_t operator () (real_t x) const;


    private:
      real_t valueAt (real_t x) const;

      std::vector<real_t> x_;
      std::vector<real_t> y_;

      size_t n_;
  };
}


#endif // LAGRANGEPOLYNOMIAL_HXX
