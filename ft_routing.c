#include "philosopher.h"

void *ft_routing(void *par)
{
	int				i;
	int				id;
	long			ref;
	par_t			*loc;
	struct timeval	stmp;

	i = -1;
	loc = ((par_t*)par);
	id = loc->id;
	if (!((id + loc->ph_nb) % 2))
		usleep (20);
	gettimeofday(&stmp, NULL);
	ref = (stmp.tv_usec / 1000);
	while (++i < 2)
	{
		gettimeofday(&stmp, NULL);
		if (ft_putevent(loc, "thinking\n", (stmp.tv_usec / 1000), id))
			return (ft_die(loc, id, 1), (void*)-1);
		if (ft_eating(loc, &ref, id))
			break ;
		if (ft_sleeping(loc, &ref, id))
			break ;
	}
	ft_die(loc, id, 1);
	gettimeofday(&stmp, NULL);
	if (!ft_putevent(loc, "die\n", (stmp.tv_usec / 1000), id))
		return ((void*)-1);
	return (0);
}