NAME = philosophers

# Paths
SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/

# Names
SRC_NAME =	main.c \
			time.c \
			init.c \
			utils.c \
			parsing.c \
			philosophizing.c \
			tear_down.c \

TEST_SRC_NAME = test_main.c \

TEST_HEADER_NAME =	test_parse.h \
					test_utils.h \
					test_precise_wait.h \

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
TEST_SRC = $(addprefix $(TEST_PATH),$(TEST_SRC_NAME))
TEST_HEADER = $(addprefix $(TEST_PATH),$(TEST_HEADER_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
TEST_FLAGS	= -g3 -L./criterion-v2.3.3/lib -I./criterion-v2.3.3/include -lcriterion -Wl,-rpath=./criterion-v2.3.3/lib

ifeq ($(MAKECMDGOALS),test)
	CFLAGS += -D IS_TEST
endif
ifeq ($(MAKECMDGOALS),testinc)
	CFLAGS += -D IS_TEST
endif



all: $(NAME)

$(NAME): $(OBJ)
	@echo "Build $(NAME)"
	@echo CFLAGS=${CFLAGS}
	@$(CC) -g $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@rm -f $(NAME) db

test: $(OBJ) $(TEST_SRC) $(TEST_HEADER)
	@$(CC) $(CFLAGS) $(TEST_FLAGS) -o $(NAME)_test $(OBJ) -I./$(SRC_PATH) $(TEST_SRC) -lpthread

testinc: $(SRC) $(TEST_SRC) $(TEST_HEADER)
	@$(CC) $(CFLAGS) $(TEST_FLAGS) -o $(NAME)_test $(SRC) -I./$(SRC_PATH) $(TEST_SRC) -lpthread

re:	fclean all

.PHONY: all clean fclean re mlx libft db test
