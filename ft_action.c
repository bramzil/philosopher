#include "philosopher.h"

void ft_free_par(par_t *par)
{
	free(par->die);
	free(par->die_mtx);
	free(par->prnt_mtx);
	free(par->forks);
}

int	ft_putevent(par_t *par, char *msg, long stmp, int id)
{
	(void)par;
	usleep(id + 20);
	// if (pthread_mutex_lock(par->prnt_mtx))
	// 	return (printf("thread: %d fails to lock prnt_mtx\n", id));
	printf("%ld  %d  %s\n", stmp, id, msg);
	// if (pthread_mutex_unlock(par->prnt_mtx))
	// 	return (printf("thread: %d fails to unlock prnt_mtx\n", id));
	return (0);
}

int	ft_sleeping(par_t *par, long *ref, int id)
{
	struct timeval		stmp;

	gettimeofday(&stmp, NULL);
	if ((*ref + par->t_die) < (stmp.tv_usec / 1000))
		return(-1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "sleeping\n", (stmp.tv_usec / 1000), id))
		return (ft_die(par, id, 1), -1);
	usleep(par->t_slp);
	return (0);
}

int	ft_eating(par_t *par, long *ref, int id)
{
	struct timeval		stmp;

	gettimeofday(&stmp, NULL);
	if ((*ref + par->t_die) < (stmp.tv_usec / 1000))
		return(-1);
	if (ft_lock_mutex(par->forks, par->ph_nb, id))
		return (-1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "has take fork\n", (stmp.tv_usec / 1000), id))
		return (ft_die(par, id, 1), -1);
	gettimeofday(&stmp, NULL);
	if (ft_putevent(par, "eating\n", (stmp.tv_usec / 1000), id))
		return (ft_die(par, id, 1), -1);
	usleep(par->t_teat);
	gettimeofday(&stmp, NULL);
	*ref = (stmp.tv_usec / 1000);
	if (ft_unlock_mutex(par->forks, par->ph_nb, id))
		return (-1);
	return (0);
}