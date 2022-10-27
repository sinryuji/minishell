# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 00:26:55 by hyeongki          #+#    #+#              #
#    Updated: 2022/10/27 15:21:14 by jiwahn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS_PATH = ./source/
SRCS_NAME = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
       ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
       ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	   ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	   ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_strndup.c ft_nbrlen_base.c ft_itoa_base.c ft_max.c ft_min.c ft_ullen_base.c ft_ultoa_base.c \
	   ft_puterr.c ft_atol.c ft_split_free.c ft_pow.c get_next_line.c ft_atoi_hex.c ft_perror_exit.c \
	   ft_strcmp.c
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)
BONUS_SRCS_NAME = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_SRCS = $(addprefix $(SRCS_PATH), $(BONUS_SRCS_NAME))
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
RM = rm -f
NAME = libft.a
AR = ar rcs

# Colors
GREEN = \x1b[32m
RED = \x1b[31m
RESET = \x1b[0m

ifdef BONUS_FLAG
	OBJ = $(OBJS) $(BONUS_OBJS)
else
	OBJ = $(OBJS)
endif

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(NAME) : $(OBJ)
	@$(AR) $@ $^
	@echo "\n$(NAME): $(GREEN)$(NAME) was created$(RESET)"


all : $(NAME)

clean : 
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"


fclean : clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re : fclean all

bonus :
		@make BONUS_FLAG=1 all

.PHONY :
	all clean fclean re bonus
