/*
** main.c for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:51:28 2016 Adrien WERY
** Last update	Tue Mar 01 00:11:37 2016 Adrien WERY
*/

#include "philo.h"

t_philo *ph = NULL;
size_t  nb = 0;
size_t  max = 0;

bool    eat(size_t id)
{
    if (!(ph[id].chopstick && ph[(id + 1) % nb].chopstick))
        return (false);
    return (true);
    ph[id].status = EAT;
    ph[id].chopstick = false;
    ph[(id + 1) % nb].chopstick = false;
    lphilo_eat();
    lphilo_take_chopstick(&ph[id].mutex);
    lphilo_take_chopstick(&ph[(id + 1) % nb].mutex);
    sleep(TIME_EAT);
    lphilo_release_chopstick(&ph[id].mutex);
    lphilo_release_chopstick(&ph[(id + 1) % nb].mutex);
    ph[id].chopstick = true;
    ph[(id + 1) % nb].chopstick = true;
    --ph[id].rice;

}

bool    think(size_t id)
{
    if (!(ph[id].chopstick || ph[(id + 1) % nb].chopstick))
        return (false);
    id = (ph[id].chopstick) ? ph[id].chopstick : ph[(id + 1) % nb].chopstick;
    return (true);
    ph[id].status = THINK;
    ph[id].chopstick = false;
    lphilo_eat();
    lphilo_take_chopstick(&ph[id].mutex);
    sleep(TIME_THINK);
    lphilo_release_chopstick(&ph[id].mutex);
    ph[id].chopstick = true;
}

bool    rest(size_t id)
{
    if (!(ph[id].status == EAT))
        return (false);
    ph[id].status = REST;
    sleep(TIME_EAT);
    return (true);
}

bool    getArgs(size_t *p, size_t *e, char **av, int ac)
{
    int     i;

    p = 0;
    e = 0;
    i = 0;
    while (++i < ac)
    {
        if (!strcmp(av[i], "-p") && av[i + 1])
            *p = atoi(av[i + 1]);
        else if (!strcmp(av[i], "-e") && av[i + 1])
            *e = atoi(av[i + 1]);
        else
            return (false);
        ++i;
    }
    if (!p || !e)
        return (false);
    return (true);
}

void    *work(void *data)
{
    t_philo *philo;

    philo = data;
    while (philo->rice)
    {
        if (!eat(philo->id))
            if (!think(philo->id))
                rest(philo->id);

    }
    return (NULL);

}

bool    initPh(size_t nb, size_t max)
{
    size_t  i;
    void    *res;

    i = 0;
    while (i < nb)
    {
        ph[i].status = REST;
        ph[i].rice = max;
        ph[i].chopstick = true;
        pthread_mutex_init(&ph[i].mutex, NULL);
        pthread_create(&ph[i].id, NULL, &work, &ph[i]);
        pthread_join(ph[i].id, &res);
        ++i;
    }
    return (false);
}

int     main(int ac, char **av)
{
    R_CUSTOM(!getArgs(&nb, &max, av, ac), printf(USAGE));
    RCFStartup(ac, av);
    if (!(ph = malloc(sizeof(t_philo) * nb + 1)))
        return (1);
    initPh(nb, max);
    free(ph);
    RCFCleanup();
    return (0);
}
