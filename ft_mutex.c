#include "philosopher.h"

int	ft_die(par_t *par, int id, int set)
{
	int			tmp;

	usleep((id + 20) / par->ph_nb);
	if (pthread_mutex_lock(par->die_mtx))
		return (printf("fail to lock die mtx!\n"), -1);
	if (set)
		*(par->die) -= 1;
	tmp = *(par->die);
	if (pthread_mutex_unlock(par->die_mtx))
		return (printf("fail to unlock die mtx!\n"), -1);
	return (tmp);
}

int ft_lock_mutex(pthread_mutex_t *forks, int ph_nb, int id)
{
	usleep((id + 20) / ph_nb);
	if ((id + ph_nb)% 2)
	{
		if (pthread_mutex_lock(&forks[id]) || \
			pthread_mutex_lock(&forks[(id + 1) % ph_nb]))
			write(1, "fail to lock mutex %d\n", 19);
	}
	else
		if (pthread_mutex_lock(&forks[(id - 1) % ph_nb]) || \
			pthread_mutex_lock(&forks[id]))
			write(1, "fail to lock mutex!\n", 19);
	return (0);
}

int ft_unlock_mutex(pthread_mutex_t *forks, int ph_nb, int id)
{
	usleep((id + 20) / ph_nb);
	if ((id + ph_nb) % 2)
	{
		if (pthread_mutex_unlock(&forks[(id + 1) % ph_nb]) || \
			pthread_mutex_unlock(&forks[id]))
			printf("fail to unlock mutex!\n");
	}
	else
		if (pthread_mutex_unlock(&forks[id]) || \
			pthread_mutex_unlock(&forks[(id - 1) % ph_nb]))
			printf("fail to unlock mutex!\n");
	return (0);
}

int ft_intiate_mutex(par_t *par)
{
	int				i;

	i = -1;
	par->die_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!par->die_mtx || pthread_mutex_init(par->die_mtx, NULL))
		return (printf("issue in initiate of die_mtx!\n"), -1);
	par->prnt_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!par->prnt_mtx || pthread_mutex_init(par->prnt_mtx, NULL))
		return (printf("issue in initiate of prnt_mtx!\n"), -1);
	par->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * par->ph_nb);
	if (!par->forks)
		return (printf("failure in allocation forks!\n"), -1);
	while (++i  < par->ph_nb)
		if (pthread_mutex_init(&(par->forks[i]), NULL))
			return (printf("issue in intiate of fork's mtx!\n"), -1);
	return (0);
}
