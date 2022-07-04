double
quadratic (double x, void *params)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;
  double c = p->c;

  return a*gsl_sf_exp(x) + b*x + c;
}

double
quadratic_deriv (double x, void *params)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;

  return a*gsl_sf_exp(x) + b;
}

void
quadratic_fdf (double x, void *params, 
               double *y, double *dy)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;
  double c = p->c;

  *y = a*gsl_sf_exp(x) + b*x + c;
  *dy = a*gsl_sf_exp(x) + b;
}
