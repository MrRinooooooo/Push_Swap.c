
NAME		= push_swap
NAME_BONUS	= checker

CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror -ggdb

SRCS		= alg_adaptive.c \
			  alg_complex.c \
			  alg_simple.c \
			  alg_medium.c \
			  alg_medium_utils.c \
			  bench.c \
			  debugger.c \
			  disorder.c \
			  errors_checker.c \
			  flags.c \
			  list_utils.c \
			  main.c \
			  operations_push_swap.c \
			  operations_reverse_rotate.c \
			  operations_rotate.c \
			  parser.c \
			  printf_stderr.c \
			  strings_utils.c \
			  alg_complex_utils.c \
			  alg_complex_partition.c

SRCS_BONUS	= main_bonus.c \
			  get_next_line_utils_bonus.c \
			  strings_utils.c \
			  errors_checker.c \
			  operations_push_swap.c \
			  operations_reverse_rotate.c \
			  operations_rotate.c \
			  list_utils.c \
			  parser.c \
			  bench.c \
			  printf_stderr.c

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
