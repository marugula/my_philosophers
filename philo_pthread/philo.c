#include "philosophers.h"

long	get_time(struct timeval start_time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((((now.tv_sec * 1000000 + now.tv_usec) -\
	(start_time.tv_sec * 1000000 + start_time.tv_usec))/1000));
}

void	print_status_phil(t_phils *phils, char *mesage)
{
	pthread_mutex_lock(&phils->args->output_mutex);
	if (mesage == NULL)
		printf("%ldms All the philosophers have eaten\n", get_time(phils->args->start_time));
	else
	{
		printf("%ldms %d %s\n", get_time(phils->args->start_time), phils->serial_number, mesage);
		pthread_mutex_unlock(&phils->args->output_mutex);
	}
}


void	*live(void *arg)
{
	t_phils	*phils;
	int		i;

	i = 0;
	phils = (t_phils*)arg;
	while (1)
	{
		if (i == 0)
		{
			if (phils->serial_number % 2 == 1)
			// if ((phils->serial_number % 2 == 0 && phils->args->num_phil % 2 == 0) \
			// || (phils->serial_number % 2 == 1 && phils->args->num_phil % 2 == 1))
			{
				print_status_phil(phils, "is thinking");
				usleep(phils->args->time_to_eat * 1000);
			}
			i++;
		}
		else
			print_status_phil(phils, "is thinking");
		pthread_mutex_lock(&phils->mutex);
		print_status_phil(phils, "has taken a fork");
		pthread_mutex_lock(&phils->next->mutex);
		print_status_phil(phils, "has taken a fork");
		print_status_phil(phils, "is eating");
		pthread_mutex_lock(&phils->time_mutex);
		phils->last_time_eat = get_time(phils->args->start_time);
		pthread_mutex_unlock(&phils->time_mutex);
		pthread_mutex_lock(&phils->count_mutex);
		phils->count_eat++;
		pthread_mutex_unlock(&phils->count_mutex);
		usleep(phils->args->time_to_eat * 1000);
		pthread_mutex_unlock(&phils->next->mutex);
		pthread_mutex_unlock(&phils->mutex);
		print_status_phil(phils, "is sleeping");
		usleep(phils->args->time_to_sleep * 1000);
	}
	return (phils);
}

void	init_live(t_phils *phils)
{
	long			now;
	struct timeval	start_time;
	int				i;
	t_phils			*temp;

	gettimeofday(&start_time, NULL);
	temp = phils;
	while(temp->next != phils)
	{
		temp->args->start_time = start_time;
		temp = temp->next;
	}
	for (int i = 0; i < 10; i++)
	{
		now = get_time(phils->args->start_time);
		printf("now=%ld\n", now);
		usleep(phils->args->time_to_sleep);
	}
	i = phils->args->num_phil;
	temp = phils;
	while(i > 0)
	{
		pthread_create(&temp->tid, NULL, live, (void *)temp);
		temp = temp->next;
		i--;
	}
	temp = phils;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&temp->time_mutex);
		now  = get_time(temp->args->start_time);
		if (now - temp->last_time_eat > temp->args->time_to_die)
		{
			print_status_phil(temp, "died");
			break ;
		}
		pthread_mutex_unlock(&temp->time_mutex);
		pthread_mutex_lock(&temp->count_mutex);
		if (phils->args->num_time_to_eat != 0)
		{
			if (temp->count_eat >= temp->args->num_time_to_eat)
				i++;
			else
				i = 0;
			if (i >= temp->args->num_phil)
			{
				print_status_phil(temp, NULL);
				break ;
			}
		}
		pthread_mutex_unlock(&temp->count_mutex);


		temp = temp->next;
	}
	i = phils->args->num_phil;
	temp = phils;
	while(i > 0)
	{
		pthread_detach(temp->tid);
		temp = temp->next;
		i--;
	}

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
	pthread_mutex_init(&args.output_mutex, NULL);

	if (phils == NULL)
		return (0);

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