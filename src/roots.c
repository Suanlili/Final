#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_sf_exp.h>

#include "demo_fn.h"
#include "demo_fn.c"

int
main (void)
{
  int status1, status2;
  int iter = 0, max_iter = 100;
  const gsl_root_fsolver_type *T1;
  const gsl_root_fdfsolver_type *T2;
  gsl_root_fsolver *s1;
  gsl_root_fdfsolver *s2;
  double r = 0/*, r_expected = sqrt (5.0)*/;
  double x0, x = 0;
  double x_lo = 0, x_hi = 1.5;
  gsl_function F;
  gsl_function_fdf FDF;
  struct quadratic_params params = {1.0, -4.0, 0.0};

  F.function = &quadratic;
  F.params = &params;

  FDF.f = &quadratic;
  FDF.df = &quadratic_deriv;
  FDF.fdf = &quadratic_fdf;
  FDF.params = &params;

  T1 = gsl_root_fsolver_bisection;  //这里可以用来更改迭代的方法
  s1 = gsl_root_fsolver_alloc (T1);
  gsl_root_fsolver_set (s1, &F, x_lo, x_hi);

  T2 = gsl_root_fdfsolver_newton;
  s2 = gsl_root_fdfsolver_alloc (T2);
  gsl_root_fdfsolver_set (s2, &FDF, x);

  //注释中内容用于生成data.txt
  /*printf ("using %s and %s method\n", 
          gsl_root_fsolver_name (s1),
	  gsl_root_fdfsolver_name(s2));

  printf ("|| Brent|%5s [%9s, %9s] %9s %10s %9s|   Newton|%10s %10s %10s||\n",
          "iter", "lower", "upper", "root", 
          "err", "err(est)","root","err","err(est)");*/

  do
    {
      iter++;
      status1 = gsl_root_fsolver_iterate (s1);
      r = gsl_root_fsolver_root (s1);
      x_lo = gsl_root_fsolver_x_lower (s1);
      x_hi = gsl_root_fsolver_x_upper (s1);
      status1 = gsl_root_test_interval (x_lo, x_hi,
                                       0, 0.001);
      status2 = gsl_root_fdfsolver_iterate (s2);
      x0 = x;
      x = gsl_root_fdfsolver_root (s2);
      status2 = gsl_root_test_delta (x, x0, 0, 1e-3);

      //注释中内容用于生成data.txt
      /*if (status1 == GSL_SUCCESS && status2 == GSL_SUCCESS)
        printf ("Both converged:\n");
      else if (status1 == GSL_SUCCESS || status2 == GSL_SUCCESS)
        printf ("One Converged:\n");

      printf ("            %5d [%.7f, %.7f] %.7f %+.7f %.7f|         %10.7f %10.7f %10.7f\n",
              iter, x_lo, x_hi,
              r, r - r_expected, 
              x_hi - x_lo,
	      x, x-r_expected, x-x0);*/
      //该命令用于生成data.dat
      printf("%d %lf %lf\n",iter, x_lo, x);
    }
  while ((status1 == GSL_CONTINUE || status2 == GSL_CONTINUE) && iter < max_iter);

  gsl_root_fsolver_free (s1);
  gsl_root_fdfsolver_free (s2);

  return status1;
}
