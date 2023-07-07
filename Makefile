NAME    := minishell
CFLAGS  := -Wall -Wextra -Werror -g
LDFLAGS := -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

HEADERS := -I./include -I/Users/$(USER)/.brew/opt/readline/include
LIBFT   := ./libft
LIBS    := $(LIBFT)/libft.a

SRCS    := src/main.c \
			src/parsing/parse.c \
			src/parsing/fill_cmd.c \
			src/parsing/interpret_dollar_sign.c \
			src/parsing/parse_utils.c \
			src/parsing/trim_quotes.c \
			src/commands/commands.c \
			src/commands/echo.c \
			src/commands/exit.c \
			src/commands/env.c \
			src/commands/export.c \
			src/commands/unset.c \
			src/commands/pwd.c \
			src/commands/cd.c \
			src/commands/path.c \
			src/commands/commands_utils.c \
			src/commands/export_utils.c \
			src/commands/heredoc.c \

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