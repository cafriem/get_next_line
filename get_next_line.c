/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 11:23:55 by cafriem           #+#    #+#             */
/*   Updated: 2022/07/01 18:11:37 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	c;
	size_t	c1;
	char	*res;

	c = 0;
	c1 = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	res = (char *)malloc((len) + 1);
	if (res == NULL)
		return (NULL);
	while (s[c] != '\0')
	{
		if (c >= start && c1 < len)
		{
			res[c1] = s[c];
			c1++;
		}
		c++;
	}
	res[c1] = '\0';
	free (s);
	return (res);
}

void	ft_open(char **old, char *new, int size, int fd)
{
	while (ft_strchr(*old, '\n') == NULL)
	{
		size = read(fd, new, BUFFER_SIZE);
		if (size < BUFFER_SIZE)
		{
			new[size] = '\0';
			*old = ft_strjoin(*old, new);
			break ;
		}
		*old = ft_strjoin(*old, new);
	}
}

char	*ft_openfile(int fd, char *old)
{
	char	*new;
	int		size;

	size = 0;
	new = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (old == NULL)
	{
		old = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		size = read(fd, old, BUFFER_SIZE);
		if (size == -1)
		{
			free (old);
			free (new);
			return (NULL);
		}
	}
	ft_open (&old, new, size, fd);
	free (new);
	return (old);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		c;

	c = 0;
	while (buffer[c] != '\n' && buffer[c] != '\0')
		c++;
	line = (ft_calloc ((c + 2), sizeof(char)));
	c = 0;
	while (buffer[c] != '\n' && buffer[c] != '\0')
	{
		line[c] = buffer[c];
		c++;
	}
	if (buffer[c] == '\n')
		line[c] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_openfile(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = ft_line(buffer);
	if (line[0] == '\0')
	{
		free (line);
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_substr(buffer, ft_strlen(line), ft_strlen(buffer));
	return (line);
}

// #include <stdio.h>
// int	main()
// {
// 	char	*m;
// 	int		fd;
// 	fd = open("testing 1.txt", O_RDONLY);
// 	m = get_next_line(fd); //1
// 	printf ("%s", m);
// 	free (m);
// // 	// m = get_next_line(fd); //2
// // 	// free (m);
// // 	// m = get_next_line(fd); //3
// // 	// free (m);
// // 	// m = get_next_line(fd); //4
// // 	// free (m);
// // 	// m = get_next_line(fd); //5
// // 	// free (m);
// // 	// m = get_next_line(fd); //6
// // 	// free (m);
// // 	// m = get_next_line(fd); //7
// // 	// free (m);
// // 	// m = get_next_line(fd); //8
// // 	// free (m);
// // 	// m = get_next_line(fd); //9
// // 	// free (m);
// }
// 　　　。　　　　•　 　ﾟ　　。 　　.

// 　　　.　　　 　　.　　　　　。　　 。　. 　

// .　　 。　　　• . 　　 • 　　　　•

// 　　ﾟ　　 Red was not An Impostor.　 ඞ。　.

// 　　'　　　 1 Impostor remains 　 　　。

// 　　ﾟ　　　.　　　. 　　　　.　 .