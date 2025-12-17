#include <stdio.h>
#include <unistd.h>
#include "gnl/get_next_line.h"

char	**ft_split_idinfo(char const *s);

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int check_the_file_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	while (file[i] != '.')
		i--;
	if (ft_strcmp(&file[i], ".cub") && ft_strlen(&file[i]) == 4)
		return (0);
	// printf("file: %s\n", file);
	return (1);
}

int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (count);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '\n')
		return (1);
	return (0);
}

char	**read_map(char *file)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	// printf("%d", count_lines(file));
	map = malloc((count_lines(file) + 1) * sizeof(char *));
	// map = malloc((1024) * sizeof(char *));
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map[i++] = line;
		// free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	// free(line);
	close(fd);
	return (map);
}

int	skip_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

typedef	struct s_file_content
{
	char	*f;
	char	*c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		count;
}			t_file_content;

void	init_fcontent_struct(t_file_content *fcontent)
{
	fcontent->f = NULL;
	fcontent->c = NULL;
	fcontent->no = NULL;
	fcontent->so = NULL;
	fcontent->we = NULL;
	fcontent->ea = NULL;
	fcontent->count = 0;
	
}
t_file_content	collect_elements(char **map)
{
	int	i;
	int	n;
	t_file_content	fcontent;
	init_fcontent_struct(&fcontent);

	n = 0;
	i = 0;
	while (n <= 6)
	{
		while (is_empty(map[i]))
			i++;
		if (ft_strcmp(map[i] + skip_empty(map[i]), "F") || ft_strcmp(map[i] + skip_empty(map[i]), "C")
		|| ft_strcmp(map[i] + skip_empty(map[i]), "NO") || ft_strcmp(map[i] + skip_empty(map[i]), "SO")
		|| ft_strcmp(map[i] + skip_empty(map[i]), "WE") || ft_strcmp(map[i] + skip_empty(map[i]), "EA"))
		{
			if (ft_strcmp(map[i] + skip_empty(map[i]), "F"))
				fcontent.f = map[i] + skip_empty(map[i]);
			else if (ft_strcmp(map[i] + skip_empty(map[i]), "C"))
				fcontent.c = map[i] + skip_empty(map[i]);
			else if (ft_strcmp(map[i] + skip_empty(map[i]), "NO"))
				fcontent.no = map[i] + skip_empty(map[i]);
			else if (ft_strcmp(map[i] + skip_empty(map[i]), "SO"))
				fcontent.so = map[i] + skip_empty(map[i]);
			else if (ft_strcmp(map[i] + skip_empty(map[i]), "WE"))
				fcontent.we = map[i] + skip_empty(map[i]);
			else if (ft_strcmp(map[i] + skip_empty(map[i]), "EA"))
				fcontent.ea = map[i] + skip_empty(map[i]);
			fcontent.count++;
			i++;
		}
		n++;
	}
	return (fcontent);
}

int	contain_two_parts(char *str)
{
	int	i;
	int	parts;

	i = 0;
	parts = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i] || str[i] == '\n')
			break ;
		else if (str[i] != ' ' && str[i] != '\t' )
		parts++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	if (parts != 2)
		return (0);
	return (1);
}

typedef struct	s_elements_splited
{
	char	**f;
	char	**c;
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
}				t_elements_splited;

void	init_elements_splited(t_elements_splited *elements_splited)
{
	elements_splited->f = NULL;
	elements_splited->c = NULL;
}

int	which_element(char *element_str)
{
	t_elements_splited	elements_splited;
	// init_elements_splited(&elements_splited);

	if (ft_strcmp(element_str, "F"))
		elements_splited.f = ft_split_idinfo(element_str);
	else if (ft_strcmp(element_str, "C"))
		elements_splited.c = ft_split_idinfo(element_str);
	// else if (ft_strcmp(element_str, "NO"))
	// 	elements_splited.no = ft_split_idinfo(element_str);
	// else if (ft_strcmp(element_str, "SO"))
	// 	elements_splited.so = ft_split_idinfo(element_str);
	// else if (ft_strcmp(element_str, "WE"))
	// 	elements_splited.we = ft_split_idinfo(element_str);
	// else if (ft_strcmp(element_str, "EA"))
	// 	elements_splited.ea = ft_split_idinfo(element_str);
	printf("%s", elements_splited.f[0]);
	return (0);
}

int parse_elements(char **first_six)
{
	int	i;
	// char **elements;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(first_six[i] + skip_empty(first_six[i]), "F") || ft_strcmp(first_six[i] + skip_empty(first_six[i]), "C")
		|| ft_strcmp(first_six[i] + skip_empty(first_six[i]), "NO") || ft_strcmp(first_six[i] + skip_empty(first_six[i]), "SO")
		|| ft_strcmp(first_six[i] + skip_empty(first_six[i]), "WE") || ft_strcmp(first_six[i] + skip_empty(first_six[i]), "EA"))
		{
			if (which_element(first_six[i] + skip_empty(first_six[i])))
				return (0);
		}
		i++;
	}
	return (0);
}

int	parse_first_six(char **map)
{
	int		i;
	int		j;
	// int		count;
	char	**first_six;
// (void)map;
	first_six = malloc(sizeof(char *) * 7);
	i = 0;
	j = 0;
	while (map[i] && j < 6)
	{
		// printf("--%s", map[i]);
		while (map[i] && is_empty(map[i]))
			i++;
		if (contain_two_parts(map[i]))
			first_six[j++] = ft_strdup(map[i]);
		else
			return (1);
		i++;
	}
	first_six[j] = NULL;
	parse_elements(first_six);
	// i = 0;
	// while (first_six[i])
	// 	printf("%s", first_six[i++]);
	return (0);
}

int parse_map(char **map)
{
	// read the lines and check if the line count are 6
	// check the avabaility of contents after the count 6 means there s a map in the file 
	// check the contennts of 6 first lines for the confirmation and accord of parsing as rules of cubes
	// check the map sourrinding and check the player position
	// (void)map;
	// t_file_content	fcontent;
	// fcontent = collect_elements(map);
	printf("%d", parse_first_six(map));

	// printf("%d\n", contain_two_parts(fcontent.f));
	// printf("%s", fcontent.f);
	// printf("%s", fcontent.c);
	// printf("%s", fcontent.no);
	// printf("%s", fcontent.so);
	// printf("%s", fcontent.we);
	// printf("%s", fcontent.ea);
	// printf("%d", fcontent.count);
	return 1;
}

int count_map(char **arr){
	int i;

	i = 0;
	while(arr[i])
		i++;
	return (i);
}


void print_map(char **map)
{
	int	i;

	i = 0;
	while (i < count_map(map))
	{
		printf("%s", map[i]);
		i++;
	}
}


int main(int ac, char **av){
	
	char **map;

	if(ac != 2)
	{
		write(2, "Error: ARGS\n", 12);
		return 1;
	}
	
	if(check_the_file_extension(av[1])){
		printf("Error: Invalid file format\n");
		return 1;
	}
	// (void)map;
	map = read_map(av[1]);
	// printf("%d", count_map(map));
	if(parse_map(map)){
		printf("------------------------------- Parsing -----------------------\n");
		// print_map(map);
	}

}