NAME	=	push_swap

SRC		=	main \
			parse \
			utils \
			sort \
			move

SRCS	=	$(addprefix src/, $(addsuffix .c, $(SRC)))

OBJS	=	$(SRCS:%.c=%.o)

INCLUDE_DIR		=	./inc/
INC_FLAGS		=	-I./inc -I./inc/libft
HEADER			=	$(INCLUDE_DIR)push_swap.h

LIBFT_DIR		=	$(INCLUDE_DIR)libft/
FLAGS			=	-Wall -Wextra -Werror $(INC_FLAGS) -g3
LIBFT			=	$(LIBFT_DIR)libft.a

%.o:	%.c $(HEADER)
		cc $(FLAGS) -c $< -o $@

# RULES

all:		$(NAME)

$(LIBFT):
			make -C $(LIBFT_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			cc $(FLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
			make clean -C $(LIBFT_DIR)
			rm -f $(OBJS)

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
