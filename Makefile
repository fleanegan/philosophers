NAME = philosophers

# Paths
SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/

# Names
SRC_NAME =	main.c \


TEST_SRC_NAME = $(shell find $(TEST_PATH) -type f -name "*.c")
OBJ_NAME = $(SRC_NAME:.c=.o)
TEST_OBJ_NAME = $(TEST_SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
TEST_OBJ = $(TEST_OBJ_NAME)

# Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -g3 -D $(IS_TEST)

ifeq ($(MAKECMDGOALS),test)
	CFLAGS += -D IS_TEST
else
	CFLAGS += banan
endif

all: $(NAME)



$(NAME): $(OBJ)
	@echo "Build $(NAME)"
	@echo CFLAGS=${CFLAGS}
	@$(CC) -g $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@rm -f $(NAME) db

######################### tests ############################

$(TEST_PATH)%.o: $(TEST_PATH)%.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -I$(SRC_PATH) -o $@ -c $<

test: clean $(OBJ) $(TEST_OBJ)
	@$(CC) -g $(CFLAGS) $(OBJ) $(TEST_OBJ) -o $(NAME)_test

re:	fclean all

.PHONY: all clean fclean re mlx libft db test
