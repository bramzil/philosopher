#include "philosopher.h"

static void ft_intiate_par(par_t *par)
{
    par->die = NULL;
    par->forks = NULL;
    par->die_mtx = NULL;
    par->prnt_mtx = NULL;
}

int	ft_create_threads(par_t *par)
{
    int         i;
    pthread_t   t;

    i = -1;
    ft_intiate_par(par);
    par->die = (int *)malloc(sizeof(int));
    if (!par->die)
        return (printf("failure die alloc!\n"), -1);
    *(par->die) = 1;
    if (ft_intiate_mutex(par))
        return (-1);
    while (++i < par->ph_nb)
	{
		par->id = i;
		if (pthread_create(&t, NULL, ft_routing, (void *)par))
		    return (printf("thread_creation fails!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach fails!\n"), -1);
        usleep(100);
	}
	return (0);
}