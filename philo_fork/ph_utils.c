#include "philo_bonus.h"

void	clear_sem(t_phils *temp)
{
	char	*sem_name;

	sem_name = ft_itoa(temp->serial_number);
	sem_close(temp->sem_count);
	sem_unlink(sem_name);
	free(sem_name);
	sem_name = ft_itoa(temp->serial_number * -1);
	sem_close(temp->sem_time);
	sem_unlink(sem_name);
	free(sem_name);
}

void	set_sem(t_phils *phils)
{
	char	*sem_name;

	sem_name = ft_itoa(phils->serial_number);
	sem_unlink(sem_name);
	phils->sem_count = sem_open(sem_name, O_CREAT, S_IRWXU, 1);
	free(sem_name);
	sem_name = ft_itoa(phils->serial_number * -1);
	sem_unlink(sem_name);
	phils->sem_time = sem_open(sem_name, O_CREAT, S_IRWXU, 1);
	free(sem_name);
}

void	clear_lst(t_phils *lst)
{
	t_phils *temp;
	t_phils	*temp2;

	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("how many eaten");
	if (lst != 0)
	{
		temp = lst;
		while(temp->next != lst)
		{
			temp2 = temp;
			clear_sem(temp);
			temp = temp->next;
			free(temp2);
		}
		clear_sem(temp);
		free(temp);
	}
}

void	ft_error(char *str, t_phils *phils)
{
	if (str != 0)
		printf("%s\n", str);
	if (phils != 0)
		clear_lst(phils);
	
}