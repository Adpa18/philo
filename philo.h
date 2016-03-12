/*
** philo.h for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Mar 07 16:40:03 2016 Adrien WERY
** Last update	Wed Mar 09 13:50:17 2016 Adrien WERY
*/

#ifndef PHILO_H_
# define PHILO_H_

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "extern.h"

# define USAGE "./philo -p [numbers of philosophers] -e [max eat occurence]\n"

# define R_CUSTOM(x, y) if (x) {return (y);}

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

enum state
{
    NOT,
    EAT,
    THINK,
    REST
};

typedef             struct s_philo
{
    size_t          id;
    pthread_t       thread;
    pthread_mutex_t mutex;
    size_t          rice;
    struct s_philo  *next;
}                   t_philo;

bool		initPh(size_t nb, size_t max);

#endif /* !PHILO_H_ */
