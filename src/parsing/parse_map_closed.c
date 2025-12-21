#include "parsing.h"

void	free_visited(char **visited, t_map *map)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < map->height)
		free(visited[i++]);
	free(visited);
}

t_point	*allocate_stack(t_map *map, char **visited)
{
	t_point	*stack;

	stack = malloc(sizeof(t_point) * (map->width * map->height));
	if (!stack)
	{
		free_visited(visited, map);
		return (NULL);
	}
	return (stack);
}

char	**allocate_visited(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = calloc(map->width + 1, 1);
		if (!visited[i])
		{
			j = 0;
			while (j < i)
				free(visited[j++]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	check_map_closed(t_map *map, int start_x, int start_y)
{
	t_flood_data	data;
	int				stack_size;
	int				result;

	data.visited = allocate_visited(map);
	if (!data.visited)
		return (0);
	data.stack = allocate_stack(map, data.visited);
	if (!data.stack)
		return (0);
	stack_size = 0;
	data.stack_size = &stack_size;
	data.stack[stack_size++] = (t_point){start_x, start_y};
	data.visited[start_y][start_x] = 1;
	result = flood_fill_loop(map, &data);
	free(data.stack);
	free_visited(data.visited, map);
	return (result);
}

int	validate_and_set_player(t_map *map)
{
	int	player_count;
	int	player_x;
	int	player_y;

	scan_map_for_player(map, &player_count, &player_x, &player_y);
	if (player_count != 1)
	{
		if (player_count == 0)
			printf("Error: No player spawn point found\n");
		else
			printf("Error: Multiple player spawn points found\n");
		return (0);
	}
	if (!check_map_closed(map, player_x, player_y))
	{
		printf("Error: Map is not closed - player can escape\n");
		return (0);
	}
	return (1);
}
