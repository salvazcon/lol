/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:58:40 by saazcon-          #+#    #+#             */
/*   Updated: 2023/11/15 17:55:56 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char *ft_calloc(unsigned int size, unsigned int nbr)
{
	char *str;
	int i;

	str = malloc(size * nbr);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (int)size * (int)nbr)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if(!str)
		return (i);
	while(str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s1, int letter)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if((unsigned char)s1[i] == (unsigned char)letter)
			return (1);
		i++;
	}
	return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *line;
	int len;
	int i;
	int j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	line = ft_calloc(sizeof(char), len + 1);
	if(!line)
		return (NULL);
	while(s1[i])
	{
		line[i] = s1[i];
		i++;
	}
	while(s2[j])
	{
		line[i + j] = s2[j];
		j++;
	}
	line[i + j] = '\0';
	free(s1);
	return(line);
}

char	*ft_read_line(int fd)
{
	char *buff;
	char *line;
	int readed;
	
	line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = 1;
	while(readed > 0 && !ft_strchr(buff, '\n'))
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if(readed == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char *get_next_line(int fd)
{
	char *line;
	
	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(fd);
	if(!line)
		return (NULL);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		lineas;

	lineas = 5;
	fd = open("./mierdon", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}