NAME	=	pipex

SRC		=	main \
			utils \
			child \
			heredoc

SRCS	=	$(addprefix src/, $(addsuffix .c, $(SRC)))

OBJS	=	$(SRCS:%.c=%.o)

INC_DIR		=	./inc/
LIBFT_DIR		=	$(INC_DIR)42-libft/
GNL_DIR			=	$(INC_DIR)42-gnl/

INC_FLAGS		=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
HEADER			=	$(INC_DIR)pipex.h

FLAGS			=	-Wall -Wextra -Werror $(INC_FLAGS) -g3
LIBFT			=	$(LIBFT_DIR)libft.a
GNL				=	$(GNL_DIR)get_next_line.a

%.o:	%.c $(HEADER)
		cc $(FLAGS) -c $< -o $@

# RULES

all:		$(NAME)

$(LIBFT):
			make -C $(LIBFT_DIR)

$(GNL):
			make -C $(GNL_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(GNL)
			cc $(FLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -l:get_next_line.a -o $(NAME)

clean:
			make clean -C $(LIBFT_DIR)
			make clean -C $(GNL_DIR)
			rm -f $(OBJS)

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			make fclean -C $(GNL_DIR)
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
