/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:53 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 18:56:53 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_sdl_init(char *title, t_sdl *sdl)
{
	SDL_Surface *surface;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		ft_putendl_fd(C_RED"Error initializing SDL"C_RESET, 2);
		exit(1);
	}
	if (!(sdl->sdl_win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, sdl->win_width + MENU_WIDTH,
sdl->win_height, SDL_WINDOW_SHOWN)))
	{
		ft_putstr_fd(C_RED"Error Creating Window SDL: "C_RESET, 2);
		ft_putendl_fd(SDL_GetError(), 2);
		exit(1);
	}
	if (!(sdl->sdl_rend = SDL_CreateRenderer(sdl->sdl_win, -1, 0)))
	{
		ft_putstr_fd(C_RED"Error Creating Renderer SDL: "C_RESET, 2);
		ft_putendl_fd(SDL_GetError(), 2);
		exit(1);
	}
	surface = IMG_Load("./assets/icons/cube.png");
	SDL_SetWindowIcon(sdl->sdl_win, surface);
	SDL_FreeSurface(surface);
	IMG_Quit();
}

void	ft_render(t_env *env)
{
	int id;
	int i;
	int j;

	i = -1;
	while (++i < env->sdl.win_height)
	{
		j = -1;
		while (++j < env->sdl.win_width)
		{
			id = env->sdl.win_width * i + j;
			SDL_SetRenderDrawColor(env->sdl.sdl_rend,
			(255 * env->data_out[id].x),
			(255 * env->data_out[id].y),
			(255 * env->data_out[id].z), 255);
			SDL_RenderDrawPoint(env->sdl.sdl_rend, j + MENU_WIDTH, i);
		}
	}
	ft_putendl("Done !");
}

void	lest_free(t_env *env)
{
	int i;

	while (env->object_list)
	{
		i = 0;
		if (env->object_list->obj.pix != NULL)
		{
			free(env->object_list->obj.pix);
		}
		if (env->object_list->obj.image != NULL
			&& ft_strcmp(env->object_list->obj.image, "sin")
			&& ft_strcmp(env->object_list->obj.image, "cb"))
		{
			while (i < (env->object_list->obj.tex->i - 1))
			{
				free(env->object_list->obj.tex->rgbimg[i]);
				i++;
			}
			free(env->object_list->obj.tex->rgbimg);
		}
		env->object_list = env->object_list->next;
	}
}

int		ft_parsing_files(t_env *env, char **argv)
{
	if (ft_parse_file(env))
	{
		env->sdl.resolution = env->sdl.win_width * env->sdl.win_height;
		env->data_out = (t_vec *)malloc(sizeof(t_vec) * env->sdl.resolution);
		ft_loadtex(env);
		ft_compute(env);
		ft_sdl_init(argv[1], &(env->sdl));
		SDL_SetRenderDrawColor(env->sdl.sdl_rend, 223, 223, 223, 255);
		SDL_RenderClear(env->sdl.sdl_rend);
		filters(4, env->data_out, env->sdl.resolution, env->object_list);
		ft_render_menu(env);
		ft_render(env);
		ft_sdl_end(env);
		lest_free(env);
		free(env->data_out);
		return (1);
	}
	else
		ft_show_err(TAG_ERR_E);
	return (0);
}

int		main(int argc, char **argv)
{
	t_env env;

	env.sdl.win_width = 1200;
	env.sdl.win_height = 800;
	env.samples = 1;
	env.filter = 0;
	env.xml_check = (t_vec){0, 0, 0};
	env.sdl.render_flags = SDL_RENDERER_PRESENTVSYNC
	| SDL_RENDERER_ACCELERATED;
	if (argc > 1)
	{
		env.object_list = NULL;
		env.o_count = 0;
		env.filename = argv[1];
		if (ft_parsing_files(&env, argv) == 1)
		{
			ft_free_tags(env.tags);
			ft_free_object_list(&(env.object_list));
		}
	}
	else
		ft_printf_help();
	return (0);
}
