/*
** philo.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:43 2016 Adrien WERY
** Last update	Mon Mar 14 15:53:24 2016 Adrien WERY
*/

#include "philo.h"

size_t  id = 0;

void    eat(t_philo *ph)
{
    pthread_mutex_lock(&ph->mutex);
    pthread_mutex_lock(&ph->next->mutex);
    lphilo_take_chopstick(&ph->mutex);
    lphilo_take_chopstick(&ph->next->mutex);
    lphilo_eat();
    lphilo_release_chopstick(&ph->mutex);
    lphilo_release_chopstick(&ph->next->mutex);
    pthread_mutex_unlock(&ph->mutex);
    pthread_mutex_unlock(&ph->next->mutex);
    --ph->rice;
}

void    think(t_philo *ph)
{
    pthread_mutex_lock(&ph->mutex);
    lphilo_take_chopstick(&ph->mutex);
    lphilo_think();
    lphilo_release_chopstick(&ph->mutex);
    pthread_mutex_unlock(&ph->mutex);
}

void		*work(void *data)
{
    t_philo	*ph;

    ph = data;
    while (ph->rice)
    {
        if (ph->id % 2 == id)
            continue;
        think(ph);
        eat(ph);
        lphilo_sleep();
    }
    ++id;
    return (NULL);
}

bool			initPh(size_t nb, size_t max)
{
    t_philo       *ph;
    size_t		i;

    i = 0;
    if (!(ph = malloc(sizeof(t_philo) * nb)))
        return (false);
    while (i < nb)
    {
        ph[i].id = i;
        ph[i].rice = max;
        if (pthread_mutex_init(&ph[i].mutex, NULL) != 0)
            return (false);
        if (pthread_create(&ph[i].thread, NULL, &work, &ph[i]) != 0)
            return (false);
        ph[i].next = &ph[(i + 1) % nb];
        ++i;
    }
    i = 0;
    while (i < nb)
        if (pthread_join(ph[i++].thread, NULL) != 0)
            return (false);
    return (true);
}
