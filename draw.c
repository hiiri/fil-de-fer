#include "fdf.h"
#include "math.h" //remove

/*
int	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
	double	xdir;
	double	ydir;
	double	y_pixel;
	double	x_pixel;
	int		pixels;

	xdir = x2 - x1;
	ydir = y2 - y1;
	pixels = sqrt((xdir * xdir) + (ydir * ydir));
	xdir /= pixels;
	ydir /= pixels;
	x_pixel = xdir;
	y_pixel = ydir;
	while (pixels)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x_pixel, y_pixel, color);
		printf("Drew pixel at x %f y %f\n", x_pixel, y_pixel);
		x_pixel += xdir;
		y_pixel += ydir;
		--pixels;
	}
	return (0);
} */

static void	line_x(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int dir_x;
	int dir_y;
	int	yi;
	int D;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	dir_x = x1 - x0;
	dir_y = y1 - y0;
	yi = 1;
	if (dir_y < 0)
	{
		yi = -1;
		dir_y *= -1;
	}
	D = 2 * dir_y - dir_x;
	pixel_y = y0;
	pixel_x = x0;
	
	while (pixel_x < x1)
	{
		mlx_pixel_put(mlx->init, mlx->window, pixel_x, pixel_y, 0xFFFF);
		if (D > 0)
		{
			y += yi;
			D -= 2*dir_x;
		}
		D += 2*dir_y;
		pixel_x++;
	}
}

static void	line_y(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int dir_x;
	int dir_y;
	int	xi;
	int D;
	int	x;
	int	pixel_x;
	int	pixel_y;

	x = 0;
	dir_x = x1 - x0;
	dir_y = y1 - y0;
	xi = 1;
	if (dir_x < 0)
	{
		xi = -1;
		dir_x *= -1;
	}
	D = 2 * dir_x - dir_y;
	pixel_y = y0;
	pixel_x = x0;
	
	while (pixel_y < y1)
	{
		mlx_pixel_put(mlx->init, mlx->window, pixel_x, pixel_y, 0xFFFF);
		if (D > 0)
		{
			x += xi;
			D -= 2*dir_y;
		}
		D += 2*dir_x;
		pixel_y++;
	}
}

static void	plot_line(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	if (abs(y1 - y0) < abs(x1 - x0))
		if (x0 > x1)
			line_x(mlx, x1, y1, x0, y0);
		else
			line_x(mlx, x0, y0, x1, y1);
	else
		if (y0 > y1)
			line_y(mlx, x1, y1, x0, y0);
		else
			line_y(mlx, x0, y0, x1, y1);
}

void	draw_map(t_mlx *mlx, t_map *s_map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < s_map->rows) // maybe add y-1 or y+1 if too many/too few rows
	{
		x = 0;
		plot_line(mlx, x * mlx->zoom, y * mlx->zoom, (x + 1) * mlx->zoom, y * mlx->zoom);
		plot_line(mlx, x * mlx->zoom, y * mlx->zoom, x * mlx->zoom, (y + 1) * mlx->zoom);
		while (x < s_map->cols) // maybe add x-1 or x+1 if too many/too few cols
		{
			plot_line(mlx, x * mlx->zoom, y * mlx->zoom, x * mlx->zoom, (y + 1) * mlx->zoom);
			plot_line(mlx, x * mlx->zoom, y * mlx->zoom, (x + 1) * mlx->zoom, y * mlx->zoom);
			x++;
		}
		y++;
	}
}
