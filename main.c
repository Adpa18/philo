/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:51:28 2016 Adrien WERY
** Last update	Sat Mar 05 21:26:16 2016 Nicolas Constanty
*/

#include <stdio.h>
#include "philo.h"

t_philo		*ph = NULL;
pthread_mutex_t	*mutexes;
size_t		nb = 0;
size_t		max = 0;

bool		eat(t_philo *ph, t_philo *ph_right)
{
  if (!(ph->chopstick && ph_right->chopstick))
    return (false);
  lphilo_eat();
  ph->chopstick = false;
  pthread_mutex_lock(&mutexes[ph->id]);
  lphilo_take_chopstick(&mutexes[ph->id]);
  ph_right->chopstick = false;
  pthread_mutex_lock(&mutexes[ph_right->id]);
  lphilo_take_chopstick(&mutexes[ph_right->id]);
  usleep(TIME_EAT);
  lphilo_release_chopstick(&mutexes[ph->id]);
  pthread_mutex_unlock(&mutexes[ph->id]);
  ph->chopstick = true;
  lphilo_release_chopstick(&mutexes[ph_right->id]);
  pthread_mutex_unlock(&mutexes[ph_right->id]);
  ph_right->chopstick = true;
  --ph->rice;
  lphilo_sleep();
  usleep(TIME_EAT);
  return (true);
}

bool		think(t_philo *ph, t_philo *ph_right)
{
  if (!(ph->chopstick || ph_right->chopstick))
    return (false);
  if (ph->chopstick)
  {
    ph->chopstick = false;
    pthread_mutex_lock(&mutexes[ph->id]);
    lphilo_take_chopstick(&mutexes[ph->id]);
    lphilo_think();
    usleep(TIME_THINK);
    lphilo_release_chopstick(&mutexes[ph->id]);
    pthread_mutex_unlock(&mutexes[ph->id]);
    ph->chopstick = true;
  }
  else
  {
    ph_right->chopstick = false;
    pthread_mutex_lock(&mutexes[ph_right->id]);
    lphilo_take_chopstick(&mutexes[ph_right->id]);
    lphilo_think();
    usleep(TIME_THINK);
    lphilo_release_chopstick(&mutexes[ph_right->id]);
    pthread_mutex_unlock(&mutexes[ph_right->id]);
    ph_right->chopstick = true;
  }
  return (true);
}

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

void		*work(void *data)
{
  t_philo	*philo;
  size_t	id;

  philo = data;
  philo->active = true;
  id = philo->id + 1;
  if (id >= nb)
    id = 0;
  while (philo->rice)
  {
      think(philo, &ph[id]);
      eat(philo, &ph[id]);
  }
  philo->active = false;
  return (NULL);
}

bool			initPh(size_t nb, size_t max)
{
  size_t		i;
  pthread_attr_t	attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  i = 0;
  while (i < nb)
  {
    ph[i].rice = max;
    ph[i].id = i;
    ph[i++].chopstick = true;
  }
  i = 0;
  while (i < nb)
    pthread_mutex_init(&mutexes[i++], NULL);
  i = 0;
  while (i < nb)
  {
    pthread_create(&ph[i].thread, &attr, &work, &ph[i]);
    ++i;
  }
  i = 0;
  while (i < nb)
    pthread_join(ph[i++].thread, NULL);
  return (false);
}

int		main(int ac, char **av)
{
  size_t	i;

  R_CUSTOM(!getArgs(&nb, &max, av, ac), printf(USAGE));
  RCFStartup(ac, av);
  if (!(ph = malloc(sizeof(t_philo) * nb + 1)))
    return (1);
  if (!(mutexes = malloc(sizeof(pthread_mutex_t) * nb + 1)))
    return (1);
  initPh(nb, max);
  check_thread:
  i = 0;
  while (i < nb)
  {
    if (ph[i].active == true)
    {
      usleep(200);
      goto check_thread;
    }
    ++i;
  }
  free(ph);
  RCFCleanup();
  return (0);
}
