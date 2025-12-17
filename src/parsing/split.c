#include "gnl/get_next_line.h"
#include <stdio.h>

// static int	words(char const *s)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
// 		i++;
// 	while (s[i])
// 	{
// 		if (s[i] != ' ' && s[i] != '\t' &&
//             (!s[i + 1] || s[i + 1] == ' ' || s[i + 1] == '\t'))
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

static char	**freeing(char **m, int i)
{
	while (i-- > 0)
		free(m[i]);
	free(m);
	return (NULL);
}

static char const	*skip(char const *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

char	**ft_split_idinfo(char const *s)
{
	int		i;
	int		len;
	char	**m;

	i = 0;
	if (!s)
		return (NULL);
	m = malloc(sizeof(char *) * 3);
	if (!m)
		return (NULL);
	while (*s)
	{
		len = 0;
		s = skip(s);
		if (*s == '\0' || *s == '\n')
			break ;
		while (s[len] != ' ' && s[len] != '\t' && s[len])
			len++;
		m[i] = ft_substr(s, 0, len);
		if (m[i++] == NULL)
			return (freeing (m, i));
		s += len;
	}
	m[i] = NULL;
	return (m);
}