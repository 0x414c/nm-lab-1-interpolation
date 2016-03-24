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
        const std::function<real_t (real_t)>& func,
        real_t x_0, real_t x_n_1, size_t n
      ) throw (std::invalid_argument);

      real_t operator () (real_t t) const;


    private:
      real_t valueAt__p_c (real_t t) const;
      real_t valueAt__g_n (real_t t) const;

      std::vector<std::vector<real_t>> finDiffs_;

      std::vector<real_t> x_;

      size_t n_;
  };
}


#endif // NEWTONPOLYNOMIAL_HXX
