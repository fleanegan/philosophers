NAME = philosophers

# Paths
SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/

# Names
SRC_NAME =	main.c \


TEST_SRC_NAME = $(shell find $(TEST_PATH) -type f -name "*.c")
TEST_HEADER_NAME = $(shell find $(TEST_PATH) -type f -name "*.h")
OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
TEST_FLAGS	= -g3 -L./criterion-v2.3.3/lib -I./criterion-v2.3.3/include -lcriterion -Wl,-rpath=./criterion-v2.3.3/lib

ifeq ($(MAKECMDGOALS),test)
	CFLAGS += -D IS_TEST
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

test: $(OBJ) $(TEST_SRC_NAME) $(TEST_HEADER_NAME)
	@$(CC) $(TEST_FLAGS) $(CFLAGS) $(OBJ) -I./$(SRC_PATH) $(TEST_SRC_NAME) -o $(NAME)_test
	@./$(NAME)_test

re:	fclean all

.PHONY: all clean fclean re mlx libft db test
