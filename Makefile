NAME    := minishell
CFLAGS  := -Wall -Wextra -Werror -g
LDFLAGS := -L/Users/macote/.brew/Cellar/readline/8.2.1 -lreadline

HEADERS := -I ./include
LIBFT   := ./libft
LIBS    := $(LIBFT)/libft.a

SRCS    := src/main.c \
			src/parsing/parse.c \
			src/commands/commands.c \
			src/commands/echo.c \
			src/commands/exit.c \

OBJS    := ${SRCS:.c=.o}

all: lib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

lib:
	@make -C $(LIBFT) all

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJSLIB)
	@rm -f $(LIBS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: clean all

.PHONY: all, clean, fclean, re