#ifndef NEWTONPOLYNOMIAL_HXX
#define NEWTONPOLYNOMIAL_HXX


#include <cstddef>

#include <functional>
#include <stdexcept>
#include <vector>

#include "numerictypes.hxx"


namespace Math
{
  class NewtonPolynomial
  {
    public:
      NewtonPolynomial (
        const std::function<Float (Float)>& func,
        Float x_0, Float x_n_1, size_t n
      ) throw (std::invalid_argument);

      Float operator () (Float t) const;


    private:
      Float valueAt__p_c (Float t) const;
      Float valueAt__g_n (Float t) const;

      std::vector<std::vector<Float>> finDiffs_;

      std::vector<Float> x_;

      size_t n_;
  };
}


#endif // NEWTONPOLYNOMIAL_HXX
