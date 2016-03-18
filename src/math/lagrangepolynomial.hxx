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
        const std::function<Float (Float)>& func,
        Float x_0, Float x_n_1, size_t n
      ) throw (std::invalid_argument);

      Float operator () (Float x) const;


    private:
      Float valueAt (Float x) const;

      std::vector<Float> x_;
      std::vector<Float> y_;

      size_t n_;
  };
}


#endif // LAGRANGEPOLYNOMIAL_HXX
