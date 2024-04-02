CFLAGS = -Wall -Wextra -Werror

SRCS = main.c
# SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

NAME = so_long

HEADER = so_long.h

INCLUDES = -Iincludes

.c.o:
	$(CC) -c -o $@ $< $(INCLUDES)
# $(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Link X11 and MLX, and use OpenGL and AppKit
MLX_FLAGS = -Lincludes -framework OpenGL -framework AppKit
# MLX_FLAGS = -Lmlx -lmlx -Lincludes -lXext -lX11 -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS)
# $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

# $(NAME): $(OBJS) $(HEADER)
# 	cc $(CFLAGS) -I$(HEADER) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
