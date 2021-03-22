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

void	ft_key_event2(t_env *env)
{
	t_object_list	*obj;

	if ((env->sdl.sdl_event).key.keysym.sym
	== SDLK_DOWN)
	{
		obj = env->object_list;
		while (obj)
		{
			obj->obj.tex_ev.y += 0.01;
			obj = obj->next;
		}
		ft_recompute(env);
	}
	if ((env->sdl.sdl_event).key.keysym.sym
	== SDLK_RIGHT)
	{
		obj = env->object_list;
		while (obj)
		{
			obj->obj.tex_ev.z += 0.002;
			obj = obj->next;
		}
		ft_recompute(env);
	}
}

void	ft_key_event(t_env *env, int *quit)
{
	t_object_list	*obj;

	if (((env->sdl.sdl_event).type == SDL_QUIT
	|| ((env->sdl.sdl_event).type == SDL_KEYDOWN
	&& (env->sdl.sdl_event).key.keysym.sym
	== SDLK_ESCAPE)))
		*quit = 0;
	if ((env->sdl.sdl_event).type == SDL_KEYDOWN)
	{
		if ((env->sdl.sdl_event).key.keysym.sym
		== SDLK_UP)
		{
			obj = env->object_list;
			while (obj)
			{
				obj->obj.tex_ev.x += 0.1;
				obj = obj->next;
			}
			ft_recompute(env);
		}
		ft_key_event2(env);
	}
}

int		ft_mouse_event2(t_env *env, int y)
{
	if (y >= 0 && y < 100)
		env->samples = (env->samples == 10) ? 1 : 10;
	else if (y >= 100 && y < 200)
	{
		ft_capture(env, env->data_out);
		return (1);
	}
	else if (y >= 200 && y < 300)
		env->bg.ambient += 0.02;
	else if (y >= 300 && y < 400)
		env->filter = 0;
	else if (y >= 400 && y < 500)
		env->filter = 1;
	else if (y >= 500 && y < 600)
		env->filter = 2;
	else if (y >= 600 && y < 700)
		env->filter = 3;
	else if (y >= 700 && y < 800)
		env->filter = 5;
	return (0);
}

int		ft_mouse_event(t_env *env)
{
	int	x;
	int	y;

	if ((env->sdl.sdl_event).type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (x <= MENU_WIDTH)
		{
			if ((env->sdl.sdl_event).button.button == SDL_BUTTON_LEFT)
			{
				if (ft_mouse_event2(env, y))
					return (1);
			}
			else if ((env->sdl.sdl_event).button.button ==
SDL_BUTTON_RIGHT && (y >= 200 && y < 300) && env->bg.ambient > 0.02)
				env->bg.ambient -= 0.02;
			ft_recompute(env);
		}
	}
	return (0);
}
