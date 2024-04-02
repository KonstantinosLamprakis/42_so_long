CFLAGS = -Wall -Wextra -Werror

# SRCS = main.c
SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

NAME = so_long

LIBMLX = ../MLX42

HEADERS = -I so_long.h -I $(LIBMLX)/include

LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	cc $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
