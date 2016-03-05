/*
** philo.h for PSU_2015_philo
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Mon Feb 29 14:43:09 2016 Adrien WERY
** Last update	Sat Mar 05 23:31:21 2016 Nicolas Constanty
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
# define TIME_THINK 1000
# define TIME_EAT   1000

# define R_CUSTOM(x, y) if (x) {return (y);}

typedef __SIZE_TYPE__ size_t;
typedef enum { false, true } bool;

typedef             struct s_philo
{
    pthread_t       thread;
    size_t          rice;
    bool            chopstick;
    size_t			    id;
}                   t_philo;

bool		eat(t_philo *ph, t_philo *ph_right);
bool		think(t_philo *ph, t_philo *ph_right);
bool		getArgs(size_t *p, size_t *e, char **av, int ac);
void		*work(void *data);
bool		initPh(size_t nb, size_t max);

#endif /* !PHILO_H_ */
