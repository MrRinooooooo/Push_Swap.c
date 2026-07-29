
NAME		= push_swap
 
CC			= cc
CFLAGS		= -g # -Wall -Wextra -Werror
 
SRCS		= alg_adaptive.c \
			  alg_complex.c \
			  alg_simple.c \
			  disorder.c \
			  errors_checker.c \
			  flags.c \
			  list_utils.c \
			  main.c \
			  operations_push_swap.c \
			  operations_reverse_rotate.c \
			  operations_rotate.c \
			  parser.c \
			  strings_utils.c

#alg_medium.c 
			   
OBJS		= $(SRCS:.c=.o)
 
%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@
 
all: $(NAME)
 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
 
clean:
	rm -f $(OBJS)
 
fclean: clean
	rm -f $(NAME)
 
re: fclean all
 
.PHONY: all clean fclean re