# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macote <macote@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:59:14 by macote            #+#    #+#              #
#    Updated: 2023/07/06 12:17:01 by macote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SOURCE = ft_isalpha.c\
         ft_isalnum.c \
         ft_isdigit.c \
         ft_isalnum.c \
         ft_isprint.c \
         ft_isascii.c \
         ft_strlen.c \
         ft_memset.c \
         ft_bzero.c \
         ft_memcpy.c \
         ft_memmove.c \
         ft_strlcpy.c \
         ft_strlcat.c \
         ft_toupper.c \
         ft_tolower.c \
         ft_strchr.c \
         ft_strrchr.c \
         ft_strncmp.c \
         ft_memchr.c \
         ft_memcmp.c \
         ft_strnstr.c \
         ft_atoi.c \
         ft_calloc.c \
         ft_strdup.c \
         ft_substr.c \
         ft_strjoin.c \
         ft_strtrim.c \
         ft_split.c \
         ft_itoa.c \
         ft_strmapi.c \
         ft_striteri.c \
         ft_putchar_fd.c \
         ft_putstr_fd.c \
         ft_putendl_fd.c \
         ft_putnbr_fd.c \
         ft_lstclear_content.c \

BONUS_ = ft_lstnew_bonus.c \
         ft_lstadd_front_bonus.c \
         ft_lstsize_bonus.c \
         ft_lstlast_bonus.c \
         ft_lstadd_back_bonus.c \
         ft_lstdelone_bonus.c \
         ft_lstclear_bonus.c \
         ft_lstiter_bonus.c \

OBJS = $(SOURCE:.c=.o)
BONUS_OBJS = $(BONUS_:.c=.o)

all: $(NAME) bonus
	
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)

bonus: $(BONUS_OBJS)

$(BONUS_OBJS):
	@$(CC) $(CFLAGS) -c $(BONUS_)
	@ar rcs $(NAME) $(BONUS_OBJS)
	@ranlib $(NAME)
	
clean:
	@rm -f $(OBJS) $(BONUS_OBJS) 

fclean: clean
	@rm -f $(NAME)

re: fclean all
	
