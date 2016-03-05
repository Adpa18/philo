/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:51:28 2016 Adrien WERY
** Last update	Sat Mar 05 22:48:08 2016 Adrien WERY
*/

#include <stdio.h>
#include "philo.h"

t_philo		*ph = NULL;
pthread_mutex_t	*mutexes;
size_t		nb = 0;
size_t		max = 0;

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
  if (!p || !e)
    return (false);
  return (true);
}

int		main(int ac, char **av)
{
  size_t	i;

  R_CUSTOM(!getArgs(&nb, &max, av, ac), printf(USAGE));
  RCFStartup(ac, av);
  R_CUSTOM(!(ph = malloc(sizeof(t_philo) * nb + 1)), 1);
  R_CUSTOM(!(mutexes = malloc(sizeof(pthread_mutex_t) * nb + 1)), 1);
  initPh(nb, max);
  check_thread:
  i = 0;
  while (i < nb)
  {
    if (ph[i].active == true)
    {
      sleep(1);
      goto check_thread;
    }
    ++i;
  }
  free(ph);
  RCFCleanup();
  return (0);
}
