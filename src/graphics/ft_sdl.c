/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:57:01 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:57:02 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

void	ft_recompute(t_env *env)
{
	ft_run_raytracer(env);
	ft_putendl("Recomputed !");
	SDL_SetRenderDrawColor(env->sdl.sdl_rend, 223, 223, 223, 255);
	SDL_RenderClear(env->sdl.sdl_rend);
	filters(env->filter, env->data_out, env->sdl.resolution, env->object_list);
	ft_render_menu(env);
	ft_render(env);
}

void	ft_capture(t_env *env, t_vec *data_out)
{
	SDL_Surface	*surface;
	int			i;
	int			j;
	int			id;

	surface = SDL_CreateRGBSurface(0, env->sdl.win_width,
	env->sdl.win_height, 32, 0, 0, 0, 0);
	i = -1;
	while (++i < env->sdl.win_height)
	{
		j = -1;
		while (++j < env->sdl.win_width)
		{
			id = env->sdl.win_width * i + j;
			*((uint32_t *)((uint8_t *)surface->pixels
			+ i * surface->pitch
			+ j * surface->format->BytesPerPixel)) =
			((int)(data_out[id].x * 255) << 16) |
((int)(data_out[id].y * 255) << 8) | (int)(data_out[id].z * 255);
		}
	}
	SDL_SaveBMP(surface, "capture.bmp");
	SDL_FreeSurface(surface);
}

void	ft_sdl_end(t_env *env)
{
	int				quit;

	quit = 1;
	while (quit)
	{
		while (SDL_PollEvent(&(env->sdl.sdl_event)))
		{
			ft_key_event(env, &quit);
			if (ft_mouse_event(env))
				continue ;
		}
		SDL_RenderPresent(env->sdl.sdl_rend);
	}
	SDL_DestroyRenderer(env->sdl.sdl_rend);
	SDL_DestroyWindow(env->sdl.sdl_win);
	SDL_Quit();
}
