/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Mar 07 16:39:55 2016 Adrien WERY
** Last update	Sat Mar 12 13:41:18 2016 Adrien WERY
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
  size_t		nb;
  size_t		max;

  R_CUSTOM(!getArgs(&nb, &max, av, ac), write(1, USAGE, 61));
  RCFStartup(ac, av);
  initPh(nb, max);
  RCFCleanup();
  return (0);
}
