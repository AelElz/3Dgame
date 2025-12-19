#include "parsing.h"

int	parse_first_six(t_parsing *p)
{
	int	i;
	int	count_lines;

	i = 0;
	count_lines = 0;
	while (p->file[i] && count_lines < 6)
	{
		if (!is_empty(p->file[i]))
		{
			if (contain_two_parts(p->file[i]))
			{
				p->first_six[count_lines] = ft_strdup(p->file[i]);
				remove_newline(p->first_six[count_lines]);
				count_lines++;
			}
			else
				exiting("Error: invalid element line\n", p);
		}
		i++;
	}
	if (count_lines < 6)
		exiting("Error: missing elements\n", p);
	p->first_six[count_lines] = NULL;
	return (i);
}

void	parse_map(t_parsing *p, int i)
{
	int j;

	j = i;
	while (p->file[j])
		j++;
	p->map = malloc(sizeof(char *) * (j + 1));
	if (!p->map)
		exiting("Error: malloc\n", p);
	memset(p->map, 0, sizeof(char *) * (j + 1));
	j = 0;
	while (p->file[i])
	{
		p->map[j] = ft_strdup(p->file[i]);
		// remove_newline(p->map[j]);
		j++;
		i++;
	}
	p->map[j] = NULL;
	p->has_map = 1;
}

void	parse_file(t_parsing *p)
{
	int i;

	p->first_six = malloc(sizeof(char *) * 7);
	if (!p->first_six)
		exiting("Error: malloc\n", p);
	memset(p->first_six, 0, sizeof(char *) * 7);
	i = parse_first_six(p);
	while (p->file[i] && is_empty(p->file[i]))
		i++;
	if (p->file[i])
		parse_map(p, i);
	else
	{
		p->map = NULL;
		p->has_map = 0;
	}
}

void init_elements_splited(t_elements_splited *elements_splited)
{
	elements_splited->f = NULL;
	elements_splited->c = NULL;
	elements_splited->no = NULL;
	elements_splited->so = NULL;
	elements_splited->we = NULL;
	elements_splited->ea = NULL;
}

int	is_map(char c)
{
	if (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int map_ended(char **map, int j)
{
	if (!map[j])
		return (1);
	while (map[j])
	{
		if (!is_empty(map[j]))
			return (0);
		j++;
	}
	return (1);
}

void	validate_map(t_parsing *p)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (p->map && p->map[j])
	{
		while (p->map[j][i] == ' ' || p->map[j][i] == '\t')
			i++;
		while (p->map[j][i] && p->map[j][i] != '\n')
		{
			if (!is_map(p->map[j][i]))
				exiting("Error: invalid map-----\n", p);
			i++;
		}
		if (p->map[j][i] == '\n' && map_ended(p->map, j + 1))
			break ;
		if (p->map[j][i] == '\n' && (!p->map[j + 1] || is_empty(p->map[j + 1])))
			exiting("Error: invalid map-----\n", p);
		j++;
		i = 0;
	}
}

void	main_parsing(t_parsing *p)
{
	p->first_six = NULL;
	init_elements_splited(&p->elements_splited);
	parse_file(p);
	if (!p->has_map)
		exiting("Error: missing map\n", p);
	parse_first_elements(p);
	validate_map(p);
	// parse_key_value(p);
}