.PHONY : clean, fclean, re
.SUFFIXES :

NAME = ft_ls

SRC =	main.c\
		flag.c\
		list.c\
		listnext.c\
		outils.c\
		aff.c\
		nextaff.c\
		flagl.c\

CFLAG = -Wall -Werror -Wextra
HFLAG = -L./libft -lft -I./libft/includes 

all : $(NAME)

$(NAME) :
	gcc $(CFLAG) $(HFLAG) $(SRC) -o $(NAME)

clean :
	rm -f

fclean : clean
	rm -f $(NAME)

re : fclean all