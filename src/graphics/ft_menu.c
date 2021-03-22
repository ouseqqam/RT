/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:38 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:39 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_init_surface(SDL_Surface **surface)
{
	surface[0] = IMG_Load("./assets/images/antialiasing.png");
	surface[1] = IMG_Load("./assets/images/camera.png");
	surface[2] = IMG_Load("./assets/images/light.png");
	surface[3] = IMG_Load("./assets/images/normal.png");
	surface[4] = IMG_Load("./assets/images/sepia.png");
	surface[5] = IMG_Load("./assets/images/noise.png");
	surface[6] = IMG_Load("./assets/images/blur.png");
	surface[7] = IMG_Load("./assets/images/cartoon.png");
}

void	ft_init_menu(t_env *env, t_menu *menu)
{
	SDL_Rect	rect;
	int			i;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		ft_putstr_fd(C_RED"SDL_image could not\
		initialize! SDL_image Error:"C_RESET, 2);
		ft_putendl_fd(IMG_GetError(), 2);
		exit(1);
	}
	ft_init_surface(menu->surface);
	i = -1;
	while (++i < 8)
	{
		menu->textures[i] =
		SDL_CreateTextureFromSurface(env->sdl.sdl_rend, menu->surface[i]);
		rect = (SDL_Rect){0, 100 * i, 100, 100};
		SDL_RenderCopy(env->sdl.sdl_rend, menu->textures[i], NULL, &rect);
		SDL_FreeSurface(menu->surface[i]);
		SDL_DestroyTexture(menu->textures[i]);
	}
	IMG_Quit();
}

void	ft_render_menu(t_env *env)
{
	t_menu menu;

	menu.o = -1;
	menu.i = 0;
	menu.h = MENU_WIDTH;
	ft_init_menu(env, &menu);
	ft_putendl("Menu Rendered !");
}
