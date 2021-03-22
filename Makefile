NAME = RT
LIBFT_FILE = libft.a
SDL_ARCHIVE = packages/SDL2-2.0.12.tar.gz
SDL_IMAGE_ARCHIVE = packages/SDL2_image-2.0.5.tar.gz

LIBFT_DIR = ./libft
GRAPHICS_DIR = ./src/graphics
PARSER_DIR = ./src/parser
OBJECTS_DIR = ./src/objects
INC_DIR = ./includes/
LIBFT_INC = $(LIBFT_DIR)/
SDL_DIR = ./lib/SDL2-2.0.12/
SDL_DIR_TMP = ./SDL2-2.0.12/
SDL_IMAGE_DIR = ./lib/SDL2_image-2.0.5/
SDL_INC = $(SDL_DIR)include
SDL_LIB = $(SDL_DIR)lib
SDL_IMAGE_INC = $(SDL_IMAGE_DIR)
SDL_IMAGE_LIB = $(SDL_IMAGE_DIR)lib
OBJ_DIR = ./obj

LFLAG = `$(SDL_DIR)sdl2-config --cflags --libs` -lSDL2_image -lm -lpthread

LIBFT = $(LIBFT_DIR)/$(LIBFT_FILE)

HEADERS = $(INC_DIR)ft_rt.h

GRAPHICS_FILES = ft_events.c ft_rt.c ft_vector2.c ft_vector3.c ft_random.c ft_shader2.c ft_matrix2.c ft_material.c ft_camera.c ft_compute.c ft_free.c ft_help.c ft_matrix.c ft_object.c ft_vector.c ft_color.c ft_helpers.c ft_filters.c ft_texture.c ft_sdl.c ft_shader.c ft_intersect.c ft_colh.c ft_texture2.c ft_imgload.c filters2.c ft_menu.c

PARSER_FILES = ft_checker2.c ft_checker.c ft_file_parser_2.c ft_file_parser.c ft_file_parser_3.c ft_objects_parser_2.c ft_objects_parser.c ft_objects_parser_3.c ft_utils.c ft_whitespaces.c ft_xmllint.c

OBJECTS_FILES = ft_cone.c ft_cylinder.c ft_plane.c ft_sphere.c ft_ellipsoid.c ft_paraboloid.c ft_triangle.c ft_cube.c ft_disk.c

OBJ_GRAPHICS = $(addprefix $(OBJ_DIR)/, $(GRAPHICS_FILES:%.c=%.o))
OBJ_PARSER = $(addprefix $(OBJ_DIR)/, $(PARSER_FILES:%.c=%.o))
OBJ_OBJECTS = $(addprefix $(OBJ_DIR)/, $(OBJECTS_FILES:%.c=%.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LIBFT_INC) -I $(SDL_INC) -I $(SDL_IMAGE_INC)

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: lib $(NAME)

$(SDL_DIR):
	@mkdir -p lib
	@tar -xf $(SDL_ARCHIVE) -C lib
	@printf "RT:  %-25s$(C_CYAN)[extracted]$(C_NONE)\n" $@

$(SDL_IMAGE_DIR):
	@tar -xf $(SDL_IMAGE_ARCHIVE) -C lib
	@printf "RT:  %-25s$(C_CYAN)[extracted]$(C_NONE)\n" $@

$(SDL_LIB):
	@mkdir $(SDL_LIB)
	@printf "\n$(C_CYAN)[configuring SDL]$(C_NONE)\n"
	@cd $(SDL_DIR); ./configure --prefix=`pwd`/lib
	@printf "$(C_CYAN)[compiling SDL]$(C_NONE)\n"
	@make -C $(SDL_DIR)
	@make -C $(SDL_DIR) install >/dev/null
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(SDL_IMAGE_LIB):
	@mkdir $(SDL_IMAGE_LIB)
	@printf "\n$(C_CYAN)[configuring SDL_image]$(C_NONE)\n"
	@cd $(SDL_IMAGE_DIR); ./configure --prefix=`pwd`/../$(SDL_DIR_TMP)/lib
	@printf "$(C_CYAN)[compiling SDL_image]$(C_NONE)\n"
	@make -C $(SDL_IMAGE_DIR)
	@make -C $(SDL_IMAGE_DIR) install >/dev/null
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o: $(GRAPHICS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o:  $(PARSER_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o:  $(OBJECTS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(NAME): $(LIBFT) $(SDL_DIR) $(SDL_LIB) $(SDL_IMAGE_DIR) $(SDL_IMAGE_LIB) $(OBJ_DIR) $(OBJ_OBJECTS) $(OBJ_PARSER) $(OBJ_GRAPHICS)
	@$(CC) $(OBJ_OBJECTS) $(OBJ_PARSER) $(OBJ_GRAPHICS) $(LIBFT) $(LFLAG) -o $(NAME)
	@printf "RT:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

lib:
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "RT:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf ./lib
	@make -C $(LIBFT_DIR) fclean
	@printf "RT:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all