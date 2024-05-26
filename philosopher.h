#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

//******************* priority *************************//

typedef struct      priority_s
{
    
}                   priority_t;


//*************** define main struct *******************//

typedef struct		par_s
{
	int				id;
	int				*die;
	int				ph_nb;
	long			t_die;
	long			t_slp;
	long			t_teat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*die_mtx;
	pthread_mutex_t	*prnt_mtx;
}                   par_t;

//****************** function prototypes *****************//

int ft_unlock_mutex(pthread_mutex_t *forks, int ph_nb, int id);
int ft_lock_mutex(pthread_mutex_t *forks, int ph_nb, int id);
int	ft_putevent(par_t *par, char *msg, long stmp, int id);
int ft_sleeping(par_t *par, long *ref, int id);
int	ft_eating(par_t *par, long *ref, int id);
int	ft_die(par_t *par, int id, int set);
int	ft_create_threads(par_t *par);
int ft_intiate_mutex(par_t *par);
void ft_free_par(par_t *par);
void *ft_routing(void *par);

#endif