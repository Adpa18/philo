/*
** philo.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:43 2016 Adrien WERY
** Last update	Tue Mar 08 17:03:02 2016 Adrien WERY
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
    t_philo	*philo;

    philo = data;
    while (philo->rice)
    {
        if (philo->id % 2 == id)
            continue;
        think(philo);
        eat(philo);
        lphilo_sleep();
    }
    ++id;
    return (NULL);
}

bool			initPh(size_t nb, size_t max)
{
    t_philo       ph[nb];
    size_t		i;

    i = 0;
    while (i < nb)
    {
        ph[i].id = i;
        ph[i].rice = max;
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
