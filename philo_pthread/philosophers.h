#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	pthread_mutex_t	output_mutex;
	struct timeval	start_time;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				num_time_to_eat;
	int				num_phil;
}	t_args;

typedef struct s_philosphers
{
	long					last_time_eat;
	unsigned int			serial_number;
	int						count_eat;
	pthread_mutex_t			mutex;
	pthread_mutex_t			time_mutex;
	pthread_mutex_t			count_mutex;
	pthread_t				tid;
	struct s_philosphers	*next;
	t_args					*args;
}	t_phils;


int	ft_atoi(const char *nptr);

/* ph_utils.c */
void	clear_lst(t_phils *lst);
void	ft_error(char *str, t_phils *phils);

/* ph_filling_phils.c */
t_phils	*filling_lst_by_phils(int argc, char **argv, t_args *args);














#endif