# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leothoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 16:08:49 by leothoma          #+#    #+#              #
#    Updated: 2025/04/08 16:08:50 by leothoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

COMP = cc

FLAGS = -Wall -Wextra -g3 -I ./

SRC =	main.c \
	parsing_utils.c \
	init.c \
	routine.c \
	time_utils.c \
	routine_helpers.c \

OBJS = ${SRC:.c=.o}

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: ${OBJS}
	$(CC) ${OBJS} ${FLAGS} -o $(NAME)

all: ${NAME}

clean:
	rm -f ${OBJS} 

fclean: clean;
	rm -f philo

re: fclean all
		
.PHONY: all, clean, fclean, re
