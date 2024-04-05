CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line_utils.c get_next_line.c \
main.c main_utils.c validation.c validation_utils.c \
main_utils2.c

OBJS = $(SRCS:.c=.o)

NAME = so_long

HEADERS = -I so_long.h -I mlx

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) mlx so_long.h
	$(MAKE) -C mlx/
	cc $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) clean -C mlx/
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
