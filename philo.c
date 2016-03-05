/*
** philo.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:51:28 2016 Adrien WERY
** Last update	Sat Mar 05 23:26:30 2016 Nicolas Constanty
*/

#include "philo.h"

extern t_philo		*ph;
extern pthread_mutex_t	*mutexes;
extern size_t		nb;
extern size_t		max;

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
    pthread_create(&ph[i].thread, NULL, &work, &ph[i]);
    ++i;
  }
  i = 0;
  while (i < nb)
    pthread_join(ph[i++].thread, NULL);
  return (false);
}
