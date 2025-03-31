NAME := pipex
CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := src/libft/
LIBFT_FILE := libft.a
LIBFT := $(addprefix $(LIBFT_DIR),$(LIBFT_FILE))

EXECUTION_DIR := src/execution/
EXECUTION_FILES := execution.c \
				   execution_utils.c \
				   child_execution.c \
				   child_execution_utils.c \

FILL_DATA_DIR := src/fill_data/
FILL_DATA_FILES := fill_data.c \
				   fill_cmds.c \
				   fill_paths.c \
				   opening_files.c \

FREEING_DIR := src/freeing/
FREEING_FILES := free_data.c \
				 free_paths.c \
				 free_cmds.c \
				 close_all.c \

C_FILES = pipex.c \
		  $(addprefix $(FILL_DATA_DIR),$(FILL_DATA_FILES)) \
		  $(addprefix $(EXECUTION_DIR),$(EXECUTION_FILES)) \
		  $(addprefix $(FREEING_DIR),$(FREEING_FILES)) \

OBJ_DIR := .obj/
OBJ_DIR_DEBUG := .obj_debug/
OBJ_FILES := $(addprefix $(OBJ_DIR),$(C_FILES:.c=.o))

INCLUDES := -I $(LIBFT_DIR)includes/  -I includes/

.PHONY: all makelibft clean fclean re make_debug

all: makelibft $(NAME) 

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

makelibft:
	$(MAKE) -C $(LIBFT_DIR)

git:
	git submodule update --init --remote --recursive

$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)$(FILL_DATA_DIR) $(OBJ_DIR)$(EXECUTION_DIR) $(OBJ_DIR)$(FREEING_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR)$(EXECUTION_DIR):
	mkdir -p $@

$(OBJ_DIR)$(FILL_DATA_DIR):
	mkdir -p $@

$(OBJ_DIR)$(FREEING_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR);

clean_pipex:
	rm -rf $(OBJ_DIR);

fclean:
	$(MAKE) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm $(NAME) -rf

fclean_pipex:
	$(MAKE) clean_pipex
	rm $(NAME) -rf

re:
	$(MAKE) fclean
	$(MAKE) all

re_pipex:
	$(MAKE) fclean_pipex
	$(MAKE) all

debug:
	$(MAKE) OBJ_DIR="$(OBJ_DIR_DEBUG)" CFLAGS="$(CFLAGS) -g3"

clean_debug:
	$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=$(OBJ_DIR_DEBUG) clean 
	rm -rf $(OBJ_DIR_DEBUG);

fclean_debug:
	$(MAKE) clean_debug
	rm -rf $(NAME)

re_debug:
	$(MAKE) fclean_debug
	$(MAKE) debug
