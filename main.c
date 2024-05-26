#include "philosopher.h"

int main()
{
	par_t				par;

	par.ph_nb = 3;
	par.t_die	= 900;
	par.t_slp = 500;
	par.t_teat = 700;
	if (ft_create_threads(&par))
		return (-1);
	while (1)
		if (ft_die(&par, 0, 0) <= 0)
			break ;
	return (0);
}