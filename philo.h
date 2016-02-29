/*
** philo.h for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:43:09 2016 Adrien WERY
** Last update	Mon Feb 29 23:48:35 2016 Adrien WERY
*/

#ifndef PHILO_H_
# define PHILO_H_

# include <pthread.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "extern.h"

# define USAGE "./philo -p [numbers of philosophers] -e [max eat occurence]\n"
# define TIME_THINK 4
# define TIME_EAT   2
# define NB_RICE    10

# define R_CUSTOM(x, y) if (x) {return (y);}

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

enum state
{
    EAT,
    THINK,
    REST
};

typedef             struct s_philo
{
    pthread_t       id;
    pthread_mutex_t mutex;
    enum state      status;
    size_t          rice;
    bool            chopstick;
}                   t_philo;

#endif /* !PHILO_H_ */
