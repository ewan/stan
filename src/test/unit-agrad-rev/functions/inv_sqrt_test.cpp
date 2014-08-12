#include <stan/agrad/rev/functions/inv_sqrt.hpp>
#include <test/unit/agrad/util.hpp>
#include <gtest/gtest.h>
#include <stan/math/constants.hpp>

TEST(AgradRev,inv_sqrt) {
  AVAR a = 49.0;
  AVEC x = createAVEC(a);
  AVAR f = inv_sqrt(a);
  EXPECT_FLOAT_EQ(1 / 7.0, f.val());

  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_EQ(1U,grad_f.size());
  EXPECT_FLOAT_EQ(-0.5 / (7 * 49), grad_f[0]);

  a = 0.0;
  x = createAVEC(a);
  f = inv_sqrt(a);
  EXPECT_FLOAT_EQ(stan::math::positive_infinity(),f.val());

  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(stan::math::negative_infinity(),grad_f[0]);

  a = -50.0;
  x = createAVEC(a);
  f = inv_sqrt(a);
  std::isnan(f.val());

  f.grad(x,grad_f);
  std::isnan(grad_f[0]);
}

TEST(AgradRev,inv_sqrt_nan) {
  AVAR a = std::numeric_limits<double>::quiet_NaN();
  AVAR f = stan::agrad::inv_sqrt(a);

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  
  EXPECT_TRUE(boost::math::isnan(f.val()));
  ASSERT_EQ(1U,g.size());
  EXPECT_TRUE(boost::math::isnan(g[0]));
}
