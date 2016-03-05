/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:35 2016 Adrien WERY
** Last update	Sun Mar 06 00:21:48 2016 Adrien WERY
*/

#include "philo.h"

bool		getArgs(size_t *p, size_t *e, char **av, size_t ac)
{
  size_t	i;
  int	    pp;
  int	    ee;

  pp = 0;
  ee = 0;
  i = 1;
  while (i < ac)
  {
    if (!strcmp(av[i], "-p") && av[i + 1])
      pp = atoi(av[i + 1]);
    else if (!strcmp(av[i], "-e") && av[i + 1])
      ee = atoi(av[i + 1]);
    else
      return (false);
    i += 2;
  }
  if (pp < 2 || ee < 1)
    return (false);
  *p = pp;
  *e = ee;
  return (true);
}

int		main(int ac, char **av)
{
  t_philo		*ph;
  size_t		nb;
  size_t		max;

  R_CUSTOM(!getArgs(&nb, &max, av, ac), write(1, USAGE, 61));
  RCFStartup(ac, av);
  R_CUSTOM(!(ph = malloc(sizeof(t_philo) * nb + 1)), 1);
  initPh(ph, nb, max);
  free(ph);
  RCFCleanup();
  return (0);
}
