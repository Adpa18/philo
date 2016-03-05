/*
** philo.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:43 2016 Adrien WERY
** Last update	Sun Mar 06 00:06:42 2016 Adrien WERY
*/

#include "philo.h"

bool		eat(t_philo *ph, t_philo *ph_right)
{
  if (!(ph->chopstick && ph_right->chopstick))
    return (false);
  lphilo_eat();
  ph->chopstick = false;
  pthread_mutex_lock(&ph->mutex);
  lphilo_take_chopstick(&ph->mutex);
  ph_right->chopstick = false;
  pthread_mutex_lock(&ph_right->mutex);
  lphilo_take_chopstick(&ph_right->mutex);
  usleep(TIME_EAT);
  lphilo_release_chopstick(&ph->mutex);
  pthread_mutex_unlock(&ph->mutex);
  ph->chopstick = true;
  lphilo_release_chopstick(&ph_right->mutex);
  pthread_mutex_unlock(&ph_right->mutex);
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
    pthread_mutex_lock(&ph->mutex);
    lphilo_take_chopstick(&ph->mutex);
    lphilo_think();
    usleep(TIME_THINK);
    lphilo_release_chopstick(&ph->mutex);
    pthread_mutex_unlock(&ph->mutex);
    ph->chopstick = true;
  }
  else
  {
    ph_right->chopstick = false;
    pthread_mutex_lock(&ph_right->mutex);
    lphilo_take_chopstick(&ph_right->mutex);
    lphilo_think();
    usleep(TIME_THINK);
    lphilo_release_chopstick(&ph_right->mutex);
    pthread_mutex_unlock(&ph_right->mutex);
    ph_right->chopstick = true;
  }
  return (true);
}

void		*work(void *data)
{
  t_philo	*philo;

  philo = data;
  while (philo->rice)
  {
      think(philo, philo->next);
      eat(philo, philo->next);
  }
  return (NULL);
}

bool			initPh(t_philo *ph, size_t nb, size_t max)
{
  size_t		i;

  i = 0;
  while (i < nb)
  {
    ph[i].rice = max;
    ph[i].chopstick = true;
    pthread_mutex_init(&ph[i].mutex, NULL);
    pthread_create(&ph[i].thread, NULL, &work, &ph[i]);
    ph[i].next = &ph[(i + 1) % nb];
    ++i;
  }
  i = 0;
  while (i < nb)
    pthread_join(ph[i++].thread, NULL);
  return (false);
}
