NAME = q.out
SRCS = testfiles/main.cpp
OBJDIR = ./obj/
OBJS = $(SRCS:%.cpp=$(OBJDIR)%.o)

CC = clang++ -g -O0
CFLAGS = -Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)
	rm -f out_ft out_std

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	$(CC) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft
	$(CC) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std
	diff out_ft out_std

test0:
	$(CC) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft
	@cat out_ft

test1:
	$(CC) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std
	@cat out_std

val0:
	$(CC) $(SRCS) -DTEST=0 -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > out_ft
	@make fclean -s

val1:
	$(CC) $(SRCS) -DTEST=1 -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > out_std
	@make fclean -s

.PHONY: all fclean clean re test val