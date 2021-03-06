#ifndef STAN__MATH__MATRIX__QUAD_FORM_DIAG_HPP
#define STAN__MATH__MATRIX__QUAD_FORM_DIAG_HPP

#include <stan/math/matrix/Eigen.hpp>
#include <boost/math/tools/promotion.hpp>
#include <stan/math/error_handling/matrix/check_square.hpp>
#include <stan/math/error_handling/check_equal.hpp>

namespace stan {
  namespace math {
    
    using Eigen::Dynamic;
    using Eigen::Matrix;
    using boost::math::tools::promote_args;
    
    template <typename T1, typename T2, int R, int C>
    inline Matrix
    <typename promote_args<T1,T2>::type, Dynamic, Dynamic>
    quad_form_diag(const Matrix<T1, Dynamic, Dynamic>& mat,
          const Matrix<T2, R, C>& vec) {
      if (vec.cols() != 1 && vec.rows() != 1)
        throw std::domain_error("error in call to quad_form_diag: vec must be a vector");
      stan::math::check_square("quad_form_diag(%1%)",mat,"mat",(double*)0);
      int size = vec.size();
      stan::math::check_equal("quad_form_diag(%1%)",mat.rows(), size, "matrix size",
                              (double*)0);
      Matrix<typename promote_args<T1,T2>::type, Dynamic, Dynamic>
        result(size, size);
      for (int i = 0; i < size; i++) {
        result(i,i) = vec(i)*vec(i)*mat(i,i);
        for (int j = i+1; j < size; ++j) {
          typename promote_args<T1,T2>::type temp = vec(i)*vec(j);
          result(j,i) = temp*mat(j,i);
          result(i,j) = temp*mat(i,j);
        }
      }
      return result;
    }

  }
}
#endif
