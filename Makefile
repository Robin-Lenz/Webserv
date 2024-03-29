NAME := Webserve
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -I .

SRC_DIR := .
OBJ_DIR := ./obj

SRC_FILES := $(shell find src -type f -name '*.c' -o -name '*.cpp' -o -name '*.h')
OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.cpp=.o))
OBJ_DIRS := $(sort $(dir $(OBJ_FILES)))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIRS) 
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	$(CXX) $^ -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re