#include "philo_bonus.h"


long	get_time(struct timeval start_time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((((now.tv_sec * 1000000 + now.tv_usec) -\
	(start_time.tv_sec * 1000000 + start_time.tv_usec))/1000));
}

void	print_status_phil(t_phils *phils, char *mesage)
{
	sem_wait(phils->args->sem_output);
	if (mesage == NULL)
		printf("%ldms All the philosophers have eaten\n", get_time(phils->args->start_time));
	else
	{
		printf("%ld %d %s\n", get_time(phils->args->start_time), phils->serial_number, mesage);
		sem_post(phils->args->sem_output);
	}
}

void	*check_live(void *arg)
{
	t_phils	*phils;

	phils = (t_phils *)arg;
	while(1)
	{
		sem_wait(phils->sem_time);
		if (get_time(phils->args->start_time) - phils->last_time_eat > phils->args->time_to_die)
		{
			print_status_phil(phils, "died");
			exit(DEAD);
		}
		sem_post(phils->sem_time);
		sem_wait(phils->sem_count);
		if (phils->count_eat == phils->args->num_time_to_eat && phils->args->num_time_to_eat != 0)
		{
			sem_post(phils->args->sem_how_many_eaten);
			print_status_phil(phils, "is last one eating");
		}
		sem_post(phils->sem_count);
	}
}


void	live(t_phils *phils)
{
	int	i;

	i = 0;
	pthread_create(&phils->tid, NULL, check_live, (void *)phils);
	while (1)
	{
		if (i == 0)
		{
			if (phils->serial_number < (unsigned int)phils->args->num_phil / 2 + 1)
			{
				print_status_phil(phils, "is thinking");
				usleep(10);
			}
			i++;
		}
		else
			print_status_phil(phils, "is thinking");
		sem_wait(phils->args->forks);
		print_status_phil(phils, "has taken a fork");
		sem_wait(phils->args->forks);
		print_status_phil(phils, "has taken a fork");
		print_status_phil(phils, "is eating");
		sem_wait(phils->sem_count);
		phils->count_eat++;
		sem_post(phils->sem_count);
		sem_wait(phils->sem_time);
		phils->last_time_eat = get_time(phils->args->start_time);
		sem_post(phils->sem_time);
		usleep(phils->args->time_to_eat * 1000);
		sem_post(phils->args->forks);
		sem_post(phils->args->forks);
		print_status_phil(phils, "is sleeping");
		usleep(phils->args->time_to_sleep * 1000);
	}
}

void	kill_all(t_phils *phils)
{
	t_phils	*temp;

	temp = phils;
	while (temp->next != phils)
	{
		kill(temp->pid, SIGKILL);
		temp = temp->next;
	}
	kill(temp->pid, SIGKILL);
	clear_lst(phils);
}

void	*check_all_lives(void *arg)
{
	t_phils	*phils;
	t_phils	*temp;
	int		status;

	status = 0;
	phils = (t_phils *)arg;
	temp = phils;
	waitpid(0, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == DEAD)
		{
			kill_all(phils);
			exit(0);
		}
	}
	return (NULL);

}



void	init_live(t_phils *phils)
{
	int			i;
	// int			m_pid;
	// int			status;
	pthread_t	t_check_lives;

	gettimeofday(&phils->args->start_time, NULL);
	sem_unlink("output");
	phils->args->sem_output = sem_open("output", O_CREAT, S_IXUSR, 1);
	sem_unlink("forks");
	phils->args->forks = sem_open("forks", O_CREAT, S_IXUSR, phils->args->num_phil);
	sem_unlink("how many eaten");
	phils->args->sem_how_many_eaten = sem_open("how many eaten", O_CREAT, S_IXUSR, phils->args->num_phil);
	i = 0;
	while(i < phils->args->num_phil)
	{
		sem_wait(phils->args->sem_how_many_eaten);
		i++;
	}
	i = 0;
	while (i < phils->args->num_phil)
	{
		phils->pid = fork();
		if (phils->pid == 0)
		{
			live(phils);
			// waitpid(phils->pid, NULL, 0);
			// clear_lst(phils);
			exit(0);
		}
		else
		{
			phils = phils->next;
			i++;
		}
	}
	i = 0;
	pthread_create(&t_check_lives, NULL, check_all_lives, (void *)phils);
	while (phils->args->num_time_to_eat != 0)
	{
		sem_wait(phils->args->sem_how_many_eaten);
		i++;
		if (i == phils->args->num_time_to_eat)
		{
			print_status_phil(phils, NULL);
			kill_all(phils);
			// clear_lst(phils);
			exit (0);
		}
	}
	pthread_join(t_check_lives, NULL);


}

int main(int argc, char **argv)
{
	t_args	args;
	t_phils	*phils;
	
	if (argc < 5 || argc > 6)
	{
		ft_error("Error!\nEnter the arguments in the format: number_of_philosophers\
 time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]", 0);
		return (0);
	}
	phils = filling_lst_by_phils(argc, argv, &args);

	if (phils == NULL)
		return (0);
	// print_content_lst(phils);

	init_live(phils);












	clear_lst(phils);





	// t_args		var;
	// pthread_t	thread;
	// int			*rez;

	// var.n = 19;
	// for (int i = 0; i < 10; i++)
	// 	pthread_create(&thread, NULL, count_and_print_sqr, (void*)&var);
	// printf("from main count rezult=%d\n",var.n);
	// for (int j = 0; j < 10; j++)
	// 	pthread_join(thread, (void*)&rez);
	
	// printf("from main count rezult2=%d\n",*rez);
}