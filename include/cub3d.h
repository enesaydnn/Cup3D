/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 00:00:00 by mekaplan          #+#    #+#             */
/*   Updated: 2026/09/24 00:00:00 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <sys/time.h>

# define PLANE_SCALE 0.66
# define MOVE_SPEED 3.0
# define TURN_SPEED 2.2
# define COLLISION_RADIUS 0.18

enum e_face
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

enum e_key
{
	FORWARD = 1,
	BACKWARD = 2,
	LEFTWARD = 4,
	RIGHTWARD = 8,
	TURN_LEFT = 16,
	TURN_RIGHT = 32
};

typedef struct s_image
{
	void	*handle;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		stride;
	int		endian;
}	t_image;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dx;
	double	dy;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	distance;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		steps;
	int		side;
	int		face;
	int		hit;
	int		door;
}	t_ray;

typedef struct s_bonus
{
	t_ray	*rays;
	int		*visited;
	int		selected;
	int		step;
	int		debug;
	int		show_dda;
	int		mouse_x;
	int		mouse_ready;
	int		frame;
	int		visible;
	double	anim_time;
	double	pulse;
	int		face_color;
	int		ring_color;
}	t_bonus;

typedef struct s_game
{
	char			*paths[4];
	int				floor_color;
	int				ceil_color;
	int				seen;
	t_map			map;
	t_player		player;
	void			*mlx;
	void			*window;
	t_image			frame;
	t_image			textures[4];
	int				width;
	int				height;
	int				keys;
	struct timeval	last_time;
	double			dt;
	const char		*error;
	t_bonus			bonus;
}	t_game;

size_t	str_len(const char *s);
int		str_ends(const char *s, const char *suffix);
void	*mem_zero(void *ptr, size_t size);
char	*str_copy_range(const char *s, size_t len);
int		fail(t_game *g, const char *message);
int		parse_scene(t_game *g, const char *path);
int		validate_map(t_game *g);
char	map_at(t_map *map, int x, int y);
void	init_player(t_game *g, int x, int y, char direction);
int		graphics_init(t_game *g);
void	cleanup(t_game *g);
void	pixel(t_image *img, int x, int y, int color);
int		image_color(t_image *img, int x, int y);
void	render(t_game *g);
void	cast_ray(t_game *g, t_ray *ray, int x);
void	rotate_player(t_player *p, double angle);
int		loop_frame(t_game *g);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
int		close_game(t_game *g);
int		feature_init(t_game *g);
void	feature_cleanup(t_game *g);
void	feature_hooks(t_game *g);
void	feature_focus(t_game *g);
void	feature_key(int key, t_game *g);
void	feature_update(t_game *g);
void	feature_store_ray(t_game *g, t_ray *ray, int x);
void	feature_ray_step(t_game *g, int x, int y, int column);
void	feature_draw(t_game *g);
void	feature_text(t_game *g);
int		feature_can_move(t_game *g, double x, double y);

#endif
