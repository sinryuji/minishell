# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 19:45:18 by hyeongki          #+#    #+#              #
#    Updated: 2022/10/03 21:06:12 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS =
SRCS_PATH = ./source/
SRCS_NAME = main.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)
RM = rm -rf
AR = ar rcs
NAME = minishell
READLINE_PATH = ./readline/
READLINE_FLAG = -lreadline -L$(READLINE_PATH)/lib -I$(READLINE_PATH)/include

#LIBFT_PATH = ./lib/libft/
#LIBFT = ft

# Colors
GREEN = \x1b[32m
RED = \x1b[31m
RESET = \x1b[0m

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

all : $(NAME)

$(NAME) :  $(OBJS)
	@$(CC) $(CFLAGS) $^ $(READLINE_FLAG) -o $@
	@echo "$@: $(GREEN)$@ was created$(RESET)"

clean :
	@$(RM) $(OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re : fclean all

.PHONY :
	all clean fclean re
