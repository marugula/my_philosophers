#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

# define DEAD 2

typedef struct s_args
{
	sem_t			*sem_output;
	sem_t			*forks;
	sem_t			*sem_how_many_eaten;
	struct timeval	start_time;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				num_time_to_eat;
	int	num_phil;
}	t_args;

typedef struct s_philosphers
{
	long					last_time_eat;
	sem_t					*sem_time;
	int						count_eat;
	sem_t					*sem_count;
	unsigned int			serial_number;
	pid_t					pid;
	struct s_philosphers	*next;
	t_args					*args;
	pthread_t				tid;
}	t_phils;


int	ft_atoi(const char *nptr);

/* ph_utils.c */
void	clear_lst(t_phils *lst);
void	ft_error(char *str, t_phils *phils);
void	set_sem(t_phils *phils);

/* ph_filling_phils.c */
t_phils	*filling_lst_by_phils(int argc, char **argv, t_args *args);

/* ft_itoa.c */
char	*ft_itoa(int n);













#endif