/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:27:39 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/25 16:33:36 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_ints(char *s)
{
	size_t	i;
	size_t	count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) || s[i] == ' ' || s[i] == '-')
		{
			if (flag && s[i] == ' ')
				flag = 0;
			if (!flag && s[i] != ' ')
			{
				flag = 1;
				count++;
			}
			i++;
		}
		else
			handle_error(ERROR_INVALID_MAP);
	}
	return (count);
}

static void		split_line_to_map(char *line, t_map *s_map)
{
	size_t	count;
	size_t	i;
	size_t	j;
	long	curr_num;
	int		num_len;

	i = 0;
	j = 0;
	count = count_ints(line);
	if (!(s_map->map[s_map->rows] = (int *)malloc(sizeof(int) * count)))
		handle_error(ERROR_MALLOC);
	printf("%zu count\n", count);
	while (line[i])
	{
		num_len = 0;
		while (line[i] == ' ')
			i++;
		printf("%zu i \n", i);
		if (line[i])
		{
			curr_num = ft_atoilong(&line[i]);
			if (curr_num > 2147483647 || curr_num < -2147483648)
				handle_error(ERROR_INVALID_MAP);
			s_map->map[s_map->rows][j++] = ft_atoi(&line[i]);
		}
		while (line[i] != ' ' && line[i])
		{
			if (line[i] == '-')
				num_len--;
			num_len++;
			i++;
		}
		printf("%d numlen\n", num_len);
		if (num_len >= 11)
			handle_error(ERROR_INVALID_MAP);
	}
	if (s_map->cols && s_map->cols != (int)j)
		handle_error(ERROR_INVALID_MAP);
	s_map->rows++;
	s_map->cols = j;
}

static void		malloc_row(t_map *s_map)
{
	int		**temp;
	int		i;

	if (!(temp = (int **)malloc(sizeof(int *) * s_map->rows)))
		handle_error(ERROR_MALLOC);
	ft_memcpy(temp, s_map->map, sizeof(int **) * s_map->rows);
	if (s_map->rows)
		free(s_map->map);
	if (!(s_map->map = (int **)malloc(sizeof(int *) * s_map->rows + 1)))
		handle_error(ERROR_MALLOC);
	i = 0;
	while (i < s_map->rows)
	{
		s_map->map[i] = temp[i];
		i++;
	}
	free(temp);
}

void			make_map(char *filename, t_map *s_map)
{
	int		fd;
	char	*line;

	s_map->rows = 0;
	s_map->cols = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(ERROR_READING_FILE);
	while (get_next_line(fd, &line) > 0)
	{
		malloc_row(s_map);
		split_line_to_map(line, s_map);
		free(line);
	}
	close(fd);
}
