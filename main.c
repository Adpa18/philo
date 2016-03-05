/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:35 2016 Adrien WERY
** Last update	Sun Mar 06 00:08:33 2016 Adrien WERY
*/

#include "philo.h"

bool		getArgs(size_t *p, size_t *e, char **av, int ac)
{
  int		i;

  *p = 0;
  *e = 0;
  i = 1;
  while (i < ac)
  {
    if (!strcmp(av[i], "-p") && av[i + 1])
      *p = atoi(av[i + 1]);
    else if (!strcmp(av[i], "-e") && av[i + 1])
      *e = atoi(av[i + 1]);
    else
      return (false);
    i += 2;
  }
  if (*p < 2 || *e < 1)
    return (false);
  return (true);
}

int		main(int ac, char **av)
{
  t_philo		*ph;
  size_t		nb;
  size_t		max;

  R_CUSTOM(!getArgs(&nb, &max, av, ac), printf(USAGE));
  RCFStartup(ac, av);
  R_CUSTOM(!(ph = malloc(sizeof(t_philo) * nb + 1)), 1);
  initPh(ph, nb, max);
  free(ph);
  RCFCleanup();
  return (0);
}
