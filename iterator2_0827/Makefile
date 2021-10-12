NAME = q.out
SRCS = main.cpp
OBJDIR = ./obj/
OBJS = $(SRCS:%.cpp=$(OBJDIR)%.o)

CC = clang++ -g -O0
CFLAGS = #-Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	clang++ $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_std
	@cat out_std
	clang++ $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_ft
	@cat out_ft

test0:
	g++ $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_std
	@cat out_std

val:
	@make re -s
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
	@make fclean -s

.PHONY: all fclean clean re test val