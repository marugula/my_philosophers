#include "philosophers.h"

void	clear_lst(t_phils *lst)
{
	t_phils *temp;
	t_phils	*temp2;

	if (lst != 0)
	{
		temp = lst;
		while(temp->next != lst)
		{
			temp2 = temp;
			pthread_mutex_destroy(&temp->mutex);
			temp = temp->next;
			free(temp2);
		}
		pthread_mutex_destroy(&temp->mutex);
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