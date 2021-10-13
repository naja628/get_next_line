NAME=get_next_line
OBJ=get_next_line.o get_next_line_utils.o
BONUS_OBJ=${OBJ:.o=_bonus.o}
CFLAGS=-Wall -Wextra -Werror

$(NAME):	${OBJ}
	gcc ${CFLAGS} -o get_next_line ${OBJ}

all:$(NAME) 

bonus: $(BONUS_OBJ)
	gcc ${CFLAGS} -o get_next_line ${BONUS_OBJ}

test: get_next_line_utils.o get_next_line.c
	gcc ${CFLAGS} -D TEST -o test $^

clean:
	rm -f ${OBJ}
	rm -f ${BONUS_OBJ}
	rm -f test

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
