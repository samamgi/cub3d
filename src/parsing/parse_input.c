/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaudou <arbaudou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:24:05 by arbaudou          #+#    #+#             */
/*   Updated: 2025/09/12 15:25:46 by arbaudou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_extension(const char *filename)
{
	const char	*ext = ".cub";
	size_t		len;

	len = strlen(filename);
	if (len < 4)
		return (0);
	if (strcmp(filename + len - 4, ext) == 0)
		return (1);
	return (0);
}

static char	**add_line(char **tab, char *line)
{
	int		i;
	int		count;
	char	**new_tab;

	i = 0;
	count = 0;
	while (tab && tab[count])
		count++;
	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return (NULL);
	while (i < count)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[count] = line;
	new_tab[count + 1] = NULL;
	free(tab);
	return (new_tab);
}

static char	**read_lines_from_fd(int fd)
{
	char	*line;
	char	**tab;

	tab = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tab = add_line(tab, line);
		if (!tab)
		{
			write(2, "Error: Memory allocation failed\n", 33);
			free(line);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (tab);
}

char	**create_tab(const char *input)
{
	int		fd;
	char	**tab;

	fd = open(input, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Unable to open file\n", 27);
		return (NULL);
	}
	tab = read_lines_from_fd(fd);
	close(fd);
	return (tab);
}

int	parse_input(const char *input, t_map *map)
{
	char	**new_tab;

	if (check_extension(input) == 0)
	{
		write(2, "Error: Invalid file extension. Expected .cub\n", 46);
		return (-1);
	}
	new_tab = create_tab(input);
	if (!new_tab)
	{
		write(2, "Error: Failed to create tab from input\n", 40);
		return (-1);
	}
	map->map_data = new_tab;
	return (0);
}
