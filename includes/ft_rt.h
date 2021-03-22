/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:34:05 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 16:34:06 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RT_H
# define FT_RT_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include "SDL.h"
# include "SDL_timer.h"
# include "SDL_image.h"
# include "SDL_surface.h"
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define NUM_THD 6
# define DEPTH 6
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define MENU_WIDTH 100

# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_WHT "\x1B[37m"
# define C_RESET "\x1B[0m"

# define FD_E "Invalid file descriptor"
# define TAG_LVL_E "Invalid level of the tag"
# define TAG_CLOSE_E "Unclosed tag"
# define TAG_POS_E "Invalid possition of the tag"
# define TAG_DATA_E "Invalid possition of the data"
# define TAG_PARSE_E "Error of parsing"
# define TAG_ERR_E "Error rendering"
# define TAG_IMAGE_E "Image error"

# define TAG_0_L "rt"
# define TAG_1_L_1 "scene;camera;plane;sphere;cylinder;cone;"
# define TAG_1_L_2 "light;paraboloid;ellipsoid;cube;triangle;disk"
# define TAG_2_L_1 "position;look_at;scale;rotate;color;bound_min;"
# define TAG_2_L_2 "bound_max;vertex_0;vertex_1;vertex_2;slice;slice_vec;"
# define TAG_2_L_3 "ambient;fov;radius;angle;focus_dist;aperture;"
# define TAG_2_L_4 "specular;direction;attenuation;intensity"
# define TAG_2_L_5 ";diffuse,reflect;refract;blur;image;type"
# define TAG_3_L "x;y;z;r;g;b"

# define TAG_SCENE_L "ambient;color"
# define TAG_CAMERA_L "fov;angle;position;look_at;focus_dist;aperture"
# define TAG_SPHERE_L_1 "position;radius;rotate;scale;specular;diffuse;"
# define TAG_SPHERE_L_2 "reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_PLANE_L_1 "position;rotate;scale;specular;diffuse;"
# define TAG_PLANE_L_2 "reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_LIGHT_L "position;color;type;direction;attenuation;intensity"
# define TAG_CY_L_1 "position;radius;rotate;scale;specular;diffuse"
# define TAG_CY_L_2 ";reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_CONE_L_1 "position;angle;rotate;scale;specular;diffuse;"
# define TAG_CONE_L_2 "reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_PA_L_1 "position;angle;rotate;scale;specular;diffuse;"
# define TAG_PA_L_2 "reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_ELLIPSOID_L_1 "position;radius;angle;rotate;scale;specular;diffuse"
# define TAG_ELLIPSOID_L_2 ";reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_CUBE_L_1 "position;bound_min;bound_max;rotate;specular;diffuse"
# define TAG_CUBE_L_2 ";scale;reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_TRIANGLE_L_1 "position;vertex_0;vertex_1;vertex_2;"
# define TAG_TRIANGLE_L_2 "rotate;scale;specular;diffuse;reflect;refract;"
# define TAG_TRIANGLE_L_3 "color;blur;image;slice;slice_vec"
# define TAG_DISK_L_1 "position;radius;rotate;scale;specular;diffuse"
# define TAG_DISK_L_2 ";reflect;refract;color;blur;image;slice;slice_vec"
# define TAG_VECTOR_L "x;y;z"
# define TAG_COLOR_L "r;g;b"

# define SCENE_T 0
# define CAMERA_T 1
# define PLANE_T 2
# define SPHERE_T 3
# define CYLINDER_T 4
# define CONE_T 5
# define LIGHT_T 6
# define PARABOLOID_T 7
# define ELLIPSOID_T 8
# define CUBE_T 9
# define TRIANGLE_T 10
# define DISK_T 11

# define POSITION_T 0
# define LOOK_AT_T 1
# define SCALE_T 2
# define ROTATE_T 3
# define COLOR_T 4
# define BOUND_MIN_T 5
# define BOUND_MAX_T 6
# define VERTEX_0_T 7
# define VERTEX_1_T 8
# define VERTEX_2_T 9

# define TAGS_NUM 43

# define SPLIT_WIN 200

# define RAY_T_MIN  0.001f
# define RAY_T_MAX  1.0e30f

# define EPSILON  0.00003f

typedef enum				e_type
{
	type_none, type_plane, type_sphere, type_cylinder, type_cone, type_light,
	type_ellipsoid, type_paraboloid, type_triangle, type_cube, type_disk
}							t_type;

typedef enum				e_texture
{
	text_solid, text_gradient, text_checker
}							t_texture;

typedef enum				e_matter
{
	mat_reflect, mat_refract
}							t_matter;

typedef enum				e_light
{
	lgt_point, lgt_directional
}							t_light;

typedef struct				s_vec
{
	double					x;
	double					y;
	double					z;
}							t_vec;

typedef struct				s_mat
{
	double					m_0;
	double					m_1;
	double					m_2;
	double					m_3;
	double					m_4;
	double					m_5;
	double					m_6;
	double					m_7;
	double					m_8;
	double					m_9;
	double					m_a;
	double					m_b;
	double					m_c;
	double					m_d;
	double					m_e;
	double					m_f;
}							t_mat;

typedef struct				s_mat4
{
	double					m_0;
	double					m_1;
	double					m_2;
	double					m_3;
}							t_mat4;

typedef struct				s_ray
{
	t_vec origin;
	t_vec direction;
}							t_ray;

typedef struct				s_tex
{
	t_vec					**rgbimg;
	int						i;
	int						j;
}							t_tex;

typedef struct				s_object
{
	int						id;
	int						type;
	t_vec					position;
	t_vec					slice;
	t_vec					slice_vec;
	t_vec					main_color;
	double					blur;
	double					reflect;
	double					refract;
	double					specular;
	double					attenuation;
	double					intensity;
	double					diffuse;
	double					ambient;
	double					radius;
	double					angle;
	double					limit1;
	double					limit2;
	char					*image;
	t_vec					v;
	t_vec					rotate;
	t_vec					scale;
	t_vec					normal;
	t_vec					direction;
	t_mat					matrix;
	t_vec					v0;
	t_vec					v1;
	t_vec					v2;
	t_vec					b_min;
	t_vec					b_max;
	int						*pix;
	t_tex					*tex;
	t_vec					tex_ev;
}							t_object;

typedef struct				s_intersect
{
	t_ray					ray;
	double					t;
	double					m;
	double					dist_attenuation;
	t_object				object;
	int						type;
	int						front_face;
	t_vec					hitpoint;
	t_vec					normal;
}							t_intersect;

typedef struct				s_camera
{
	t_vec					position;
	t_vec					look_at;
	double					fov;
	double					aspect_ratio;
	double					focus_dist;
	double					aperture;
	double					lens_radius;
	t_vec					w;
	t_vec					u;
	t_vec					v;
	t_vec					horizontal;
	t_vec					vertical;
	t_vec					lower_left_corner;
	t_vec					normal;
	double					angle;
}							t_camera;

typedef struct				s_object_list
{
	t_object				obj;
	int						type;
	struct s_object_list	*next;
}							t_object_list;

typedef struct				s_sdl
{
	int						win_width;
	int						win_height;
	int						resolution;
	SDL_Window				*sdl_win;
	Uint32					render_flags;
	SDL_Renderer			*sdl_rend;
	SDL_Event				sdl_event;
}							t_sdl;

typedef struct				s_env
{
	t_object_list			*object_list;
	t_vec					xml_check;
	char					**tags[4];
	char					*filename;
	t_vec					*data_out;
	int						samples;
	int						filter;
	int						o_count;
	t_object				bg;
	t_camera				cam;
	t_sdl					sdl;
	int						split_size;
}							t_env;

typedef struct				s_parse
{
	char					*data;
	int						level;
	int						parent;
	int						i;
	int						j;
	int						index;
	int						man[TAGS_NUM];
}							t_parse;

typedef struct				s_atod
{
	int						i;
	int						sign;
	double					j;
	double					f;
	int						act;
	int						len;
	int						s;
	char					**abso;
}							t_atod;

typedef	struct				s_thread_param
{
	t_env					*env;
	t_vec					*data_out;
	int						offset;
	int						res;
	double					u;
	double					v;
	int						i;
	int						j;
	int						s;
	int						depth;
	int						refract_depth;
}							t_thread_param;

typedef struct				s_triangle_var
{
	t_vec					a;
	t_vec					b;
	t_vec					p;
	t_vec					ov0;
	double					det;
	double					invdet;
	double					u;
	double					v;
	double					t;
}							t_triangle_var;

typedef	struct				s_cube_var
{
	double					tmin;
	double					tmax;
	double					tymin;
	double					tymax;
	double					tzmin;
	double					tzmax;
}							t_cube_var;

typedef	struct				s_obj_var
{
	t_vec					quadr;
	t_vec					t;
	t_vec					p;
	double					t_tmp;
	double					k;
	double					a1;
	double					a2;
}							t_obj_var;

typedef struct				s_builder_var
{
	t_vec					position;
	t_vec					scale;
	t_vec					rotate;
	t_mat					rot_mat;
	t_mat					scale_mat;
	t_mat					x_mat;
	t_mat					y_mat;
	t_mat					z_mat;
}							t_builder_var;

typedef struct				s_light_var
{
	double					specular;
	t_object_list			*object_list;
	t_intersect				light_intersect;
	double					lambert;
}							t_light_var;

typedef struct				s_menu
{
	int						i;
	int						j;
	int						o;
	int						h;
	SDL_Surface				*surface[12];
	SDL_Texture				*textures[12];
}							t_menu;

void						ft_printf_help(void);
void						ft_parse_args(int argc, char **argv);

void						ft_object_push_back(t_object_list
**head, t_object_list *new);
void						ft_free_object_list(t_object_list **head);

char						**ft_split_whitespaces(char *str);
int							ft_parse(char *data, t_env *env, int parent);

int							ft_parse_file(t_env *env);
int							ft_strstr_index(const char
*haystack, const char *needle);
double						ft_atod(char *str);
int							ft_tab_len(char **str);
int							ft_camera(char *data, t_env *env);
int							ft_plane(char *data,
t_object_list **object_list, int *count);
int							ft_sphere(char *data,
t_object_list **object_list, int *count);
int							ft_cylinder(char *data,
t_object_list **object_list, int *count);
int							ft_cone(char *data,
t_object_list **object_list, int *count);
int							ft_scene(char *data, t_env *env);
int							ft_standard(char *data, t_object *object);
int							check_close_tag(char *str, char *orig);
double						ft_get_value(char *str,
int e, int i, int *ret);
int							isnumb(char *str);
int							ft_parse_close(char *str,
char *start, char *close, t_vec *pos);
int							ft_parse_value(char *str,
char *start, char *close, double *pos);
int							ft_color(char *coor,
t_vec *color, char *open, char *close);
t_object_list				*ft_new_object();
void						ft_compute(t_env *env);
void						ft_render(t_env *env);

void						ft_free_tags(char ***tags);
void						ft_free_2d_table(char ***tab);

char						*ft_get_error_string(int error);
void						ft_sdl_end(t_env *env);
void						ft_builder_kernel_set_arg(t_env *env);
int							ft_free_data(char **data, int ret, char *error);
int							ft_xmllint_recusive(char *data,
t_env *env, int level, int parent);
int							ft_in_tags(char **arr, char *target, int toggle);
int							ft_check_mandatory(t_env *env, t_parse *parse);
int							ft_light(char *data,
t_object_list **object_list, int *count);
void						ft_show_err(char *error);

t_vec						ft_set_vecs(double s);
t_vec						ft_add_vec(t_vec u, t_vec w);
t_vec						ft_sub_vec(t_vec u, t_vec w);
t_vec						ft_mult_vecs(t_vec u, double s);
t_vec						ft_mult_vec(t_vec u, t_vec w);
t_vec						ft_div_vecs(t_vec u, double s);
double						ft_dot_vec(t_vec v, t_vec u);
double						ft_dot_mat(t_mat4 v, t_mat4 u);
t_vec						ft_cross_vec(t_vec u, t_vec w);
double						ft_sqr_vec(t_vec v);
t_vec						ft_neg_vec(t_vec v);
t_vec						ft_norm_vec(t_vec v);
t_vec						ft_rotate_axis_z(t_vec axis, double angle);
void						ft_run_cam_builder(t_env *env);
void						ft_run_builder(t_object_list *object_list);
void						ft_build_diagonal_matrix3in4(t_vec
diag, t_mat *mat);
void						ft_mult_matrix(t_mat q,
t_mat r, t_mat *mat);
t_vec						ft_apply_linear_matrix(t_mat mat, t_vec vec3);
void						ft_build_rotation_matrix3in4(double
theta, int axis, t_mat *mat);
void						ft_run_raytracer(t_env *env);
void						ft_make_camera_ray(t_ray *camera_ray,
t_camera camera, double u, double v);
t_vec						ft_correct_color(t_vec render_color, int samples);
t_vec						ft_compute_color(t_thread_param *data,
t_intersect *intersect);
t_vec						ft_random_in_unit_disk();
double						ft_sqr_vec(t_vec vec);
double						ft_vector_magnitude(t_vec vec);
t_vec						ft_ray_hitpoint(t_ray ray, double t);
void						ft_set_face_normal(t_intersect
*intersect, t_ray ray, t_vec outward_normal);
int							ft_calc_discriminant(t_vec quadr, t_vec *t);
void						ft_swap(double *a, double *b);
int							cone_intersect(t_object cone,
t_ray ray, t_intersect *intersect);
int							cylinder_intersect(t_object
cylinder, t_ray ray, t_intersect *intersect);
int							plane_intersect(t_object plane,
t_ray ray, t_intersect *intersect);
int							sphere_intersect(t_object
sphere, t_ray ray, t_intersect *intersect);
t_vec						elips_normal(t_object
ellips, t_intersect *intr, t_vec quadr);
int							ellips_intersect(t_object
ellips, t_ray ray, t_intersect *intersect);
t_vec						parab_normal(t_object parab,
t_intersect *inter, double k);
int							parab_intersect(t_object
parab, t_ray ray, t_intersect *inter);
int							trgle_intersect(t_object
triangle, t_ray ray, t_intersect *intersect);
t_vec						triangle_normal(t_object triangle);
int							cube_intersect(t_object
cube, t_ray ray, t_intersect *intersect);
int							disk_intersect(t_object
disk, t_ray ray, t_intersect *intersect);
t_vec						cube_normal(t_object cube, t_intersect *intersect);
int							ft_triangle(char *data,
t_object_list **object_list, int *count);
int							ft_cube(char *data,
t_object_list **object_list, int *count);
int							ft_ellipsoid(char *data,
t_object_list **object_list, int *count);
int							ft_paraboloid(char *data,
t_object_list **object_list, int *count);
void						filters(int flag, t_vec
*pixels, int res, t_object_list *obj);
t_tex						*img_torgb(char *img_name);
t_vec						sphere_map(t_vec inp, double r);
int							ft_texture(t_intersect *inter, t_vec *accum_color);
void						ft_loadtex(t_env *env);
t_vec						cone_map(t_vec inp);
t_vec						plane_map(t_vec inp);
double						ft_mag_vec(t_vec vec);
double						ft_clampf(double value, double min, double max);
void						ft_compute_light(t_env *env,
t_intersect *intersect, t_vec *accum_color);
int							*intersect_pixel(int *pix, int pixel);
t_vec						ft_compute_reflect(t_thread_param
*data, t_intersect *intersect, t_vec accum_color);
t_vec						ft_compute_refract(t_thread_param
*data, t_intersect *intersect, t_vec accum_color);
int							ft_calc_intersect(t_object_list
*object_list, int id_ignore, t_intersect *intersect);
char						*ft_get_string(char *str, int e, int i);
int							ft_parse_string(char *data, char
*start, char *close, char **val);
int							ft_parse_close2(t_vec *pos,
int counter, char *color_tag, int e);
void						colh_init(t_vec *colh);
void						colh2_init(t_vec *colh);
void						ft_texture2(t_intersect *inter,
t_vec *accum_color, t_vec uv);
void						ft_sin(t_intersect *inter, t_vec
*accum_color, t_vec hp);
t_tex						*img_torgb2(t_tex *tex, unsigned
char *pixels, SDL_Surface *img);
void						cartoon(t_vec *pixels, int res);
void						sepia(t_vec *pixels, int res);
void						ft_render_menu(t_env *env);
int							ft_disk(char *data, t_object_list
**object_list, int *count);
t_vec						ft_compute_refract(t_thread_param
*data, t_intersect *intersect, t_vec accum_color);
t_vec						ft_compute_reflect(t_thread_param
*data, t_intersect *intersect, t_vec accum_color);
t_vec						ft_diffuse(t_object light, t_intersect
light_intersect, t_intersect *intersect);
void						ft_get_light_ray(t_object light,
t_intersect *light_intersect, t_intersect *intersect);
double						ft_get_specular_dot(t_env *env,
t_intersect intersect, t_intersect light_intersect);
void						blure_one_object3(t_vec *pixels,
int j, int i, t_object_list *obj);
void						ft_cb(t_vec *accum_color, t_vec uv);
void						ft_key_event(t_env *env, int *quit);
int							ft_mouse_event(t_env *env);
void						ft_recompute(t_env *env);
void						ft_capture(t_env *env, t_vec *data_out);
double						frand(void);

#endif
