/*
** philo.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Sat Mar 05 23:28:43 2016 Adrien WERY
** Last update	Mon Mar 07 16:38:56 2016 Adrien WERY
*/

#include "philo.h"

void    eat(t_philo *ph)
{
    ph->chopstick = false;
    ph->next->chopstick = false;
    pthread_mutex_lock(&ph->mutex);
    pthread_mutex_lock(&ph->next->mutex);
    lphilo_eat();
    lphilo_take_chopstick(&ph->mutex);
    lphilo_take_chopstick(&ph->next->mutex);
    usleep(TIME_EAT);
    lphilo_release_chopstick(&ph->mutex);
    lphilo_release_chopstick(&ph->next->mutex);
    pthread_mutex_unlock(&ph->mutex);
    pthread_mutex_unlock(&ph->next->mutex);
    ph->chopstick = true;
    ph->next->chopstick = true;
    --ph->rice;
}

void    think(t_philo *ph)
{
    ph->chopstick = false;
    pthread_mutex_lock(&ph->mutex);
    lphilo_think();
    lphilo_take_chopstick(&ph->mutex);
    usleep(TIME_THINK);
    lphilo_release_chopstick(&ph->mutex);
    pthread_mutex_unlock(&ph->mutex);
    ph->chopstick = true;
}

void		*work(void *data)
{
    t_philo	*philo;

    philo = data;
    while (philo->rice)
    {
        if (philo->chopstick && philo->next->chopstick)
        {
            philo->status = EAT;
            eat(philo);
        }
        else if (philo->chopstick)
        {
            philo->status = THINK;
            think(philo);
        }
        else if (philo->next->chopstick)
        {
            philo->status = THINK;
            think(philo->next);
        }
        else if (philo->status == EAT)
        {
            lphilo_sleep();
            usleep(TIME_EAT);
        }
    }
    return (NULL);
}

bool			initPh(size_t nb, size_t max)
{
    t_philo       ph[nb];
    size_t		i;

    i = 0;
    while (i < nb)
    {
        ph[i].rice = max;
        ph[i].status = NOT;
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
