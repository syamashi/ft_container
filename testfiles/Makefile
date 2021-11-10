NAME = q.out
SRCS = $(shell echo *.cpp)
OBJDIR = ./obj/
OBJS = $(SRCS:%.cpp=$(OBJDIR)%.o)

CXX = clang++ -g -O0
CFLAGS = -Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p obj

$(OBJDIR)%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)
	rm -f out_ft out_std err_ft err_std

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	$(CXX) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft
	$(CXX) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std
	diff out_ft out_std

test0:
	$(CXX) $(SRCS) -DTEST=0 -o $(NAME)
	@./$(NAME) > out_ft 2>err_ft
	@cat out_ft

test1:
	$(CXX) $(SRCS) -DTEST=1 -o $(NAME)
	@./$(NAME) > out_std 2>err_std
	@cat out_std

val0:
	$(CXX) $(SRCS) -DTEST=0 -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > out_ft
	@make fclean -s

val1:
	$(CXX) $(SRCS) -DTEST=1 -o $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > out_std
	@make fclean -s

.PHONY: all fclean clean re test val