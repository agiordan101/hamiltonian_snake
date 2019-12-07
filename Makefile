NAME = snake

SRCS_PATH = srcs
SRCS_FILES =	main.c\
				game.c\
				algo.c\
				hamiltonian_cycle.c
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS_PATH = objs
OBJS_FILES = $(SRCS_FILES:%.c=%.o)
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_FILES))

CC = gcc
CFLAGS += -Wall -Werror -Wextra -I./include -I./libft/include 

LIBFT = libft
LIB = $(LIBFT)/$(LIBFT).a

all: directory $(NAME)

$(NAME): $(OBJS)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
		$(CC) $(CFLAGS) -c $< -o $@
directory:
	@mkdir $(OBJS_PATH) 2> /dev/null || true

clean:
		rm -f $(OBJ)
		make clean -C $(LIBFT)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean re
