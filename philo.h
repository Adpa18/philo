/*
** philo.h for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:43:09 2016 Adrien WERY
** Last update	Sun Mar 06 00:59:43 2016 Nicolas Constanty
*/

#ifndef PHILO_H_
# define PHILO_H_

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "extern.h"

# define USAGE "./philo -p [numbers of philosophers] -e [max eat occurence]\n"
# define TIME_THINK 10
# define TIME_EAT   10

# define R_CUSTOM(x, y) if (x) {return (y);}

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

typedef             struct s_philo
{
    pthread_t       thread;
    pthread_mutex_t mutex;
    size_t          rice;
    bool            chopstick;
    void            *next;
}                   t_philo;

bool		initPh(size_t nb, size_t max);

#endif /* !PHILO_H_ */
