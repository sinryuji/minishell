# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 19:45:18 by hyeongki          #+#    #+#              #
#    Updated: 2022/10/25 22:14:32 by jiwahn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address
SRCS_PATH := ./source/
SRCS_NAME := main.c ft_echo.c ft_pwd.c ft_cd.c ft_export.c ft_unset.c ft_env.c ft_exit.c built_in.c env_01.c env_02.c env_03.c error.c util.c signal.c execute.c parser.c scanner.c scanner_utils.c token_utils.c syntax.c expander.c expand_env.c split_field.c expand_path.c remove_quote.c redir_01.c redir_02.c redir_03.c execute_pipe.c execute_utils_01.c tree_utils_01.c tree_utils_02.c execute_utils_02.c process.c parse_cmd.c parse_list.c parse_pipeline.c syntax_check_lr.c syntax_check_node.c
SRCS := $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS := $(SRCS:.c=.o)
RM := rm -f
AR := ar rcs
NAME := minishell
READLINE_LIB := -lreadline -L$(shell brew --prefix readline)/lib
READLINE_INC := -I$(shell brew --prefix readline)/include
READLINE_PATH := ./readline
LIBFT_PATH := ./libft/
LIBFT := libft.a
LIBFT_FLAG := $(LIBFT_PATH)$(LIBFT)

# Colors
GREEN := \x1b[32m
RED := \x1b[31m
RESET := \x1b[0m

%.o : %.c
	@$(CC) $(CFLAGS) -c $< $(READLINE_INC) -o $@
	@echo "$(GREEN).$(RESET)\c"

.PHONY:	all
all : $(NAME)

$(NAME) :  $(OBJS)
	@make -C $(LIBFT_PATH) bonus
	@$(CC) $(CFLAGS) $^ $(READLINE_LIB) $(LIBFT_FLAG) -o $@
	@echo "$@: $(GREEN)$@ was created$(RESET)"

.PHONY:	clean
clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

.PHONY:	fclean
fclean : clean
	@$(RM) $(LIBFT_PATH)$(LIBFT)
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

.PHONY:	re
re :
	$(MAKE) -j6 fclean
	$(MAKE) -j6 all

