NAME = philo_bonus

SRC = philo_bonus.c ft_atoi.c ph_utils.c ph_filling_phils.c ft_itoa.c

OBJ = $(SRC:%.c=%.o)

LIB = libft/libft.a

HEADER = philo_bonus.h

LIB_HEAD = libft/libft.h

FLAGS = -Wall -Wextra -Werror 

DA_FLAGS = -Wall -Wextra -Werror -fsanitize=address

DT_FLAGS = -Wall -Wextra -Werror -fsanitize=thread

.PHONY : all da dt clean fclean re

all: $(NAME)

da: $(OBJ) $(HEADER)
	cc $(DA_FLAGS) $(SRC) -o $(NAME)

dt: $(OBJ) $(HEADER)
	cc $(DT_FLAGS) $(SRC) -o $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc $(FLAGS) $(SRC) -o $(NAME)

$(OBG): %.o : %.c $(HEADER)
	cc $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
