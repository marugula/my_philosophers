#include "philo_bonus.h"

t_phils	*new_phil(t_args *args)
{
	t_phils	*ph;

	ph = malloc(sizeof(t_phils));
	if (ph == 0)
		return (NULL);
	ph->next = ph;
	ph->count_eat = 0;
	ph->args = args;
	ph->last_time_eat = 0;
	return (ph);
}


int	add_phil(t_phils *phils, t_phils *newph)
{
	t_phils	*temp;

	if (newph == 0)
		return (0);
	temp = phils;
	while (phils->next != temp)
		phils = phils->next;
	phils->next = newph;
	newph->next = temp;
	newph->serial_number = phils->serial_number + 1;
	set_sem(phils);
	return (1);
}




t_phils	*list_phils(int num_phils, t_args *args)
{
	t_phils	*phils;

	phils = new_phil(args);
	phils->serial_number = 1;
	set_sem(phils);
	if (phils == 0)
	{
		ft_error("Malloc Error\n", 0);
		return (0);
	}
	while(num_phils > 1)
	{
		if (add_phil(phils, new_phil(args)) == 0)
		{	
			ft_error("Malloc Error\n", phils);
			return (0);
		}
		num_phils--;
	}
	return (phils);
}

t_phils	*filling_lst_by_phils(int argc, char **argv, t_args *args)
{
	t_phils	*phils;

	args->num_phil = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_time_to_eat = ft_atoi(argv[5]);
	else
		args->num_time_to_eat = 0;
	if (args->num_phil == -1 || args->time_to_die == -1 || args->time_to_eat == -1\
	|| args->time_to_sleep == -1 || args->num_time_to_eat == -1)
	{
		printf("Error!\nIncorrect character\n");
		return (0);
	}
	phils = list_phils(args->num_phil, args);
	if (phils == 0)
		return (0);
	gettimeofday(&(args->start_time), NULL);
	// phils->args = args;
	return (phils);
}