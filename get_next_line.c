/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wanisha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:36:35 by wanisha           #+#    #+#             */
/*   Updated: 2021/01/26 22:20:22 by wanisha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_search_for_slash_n(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_n_or_not(char *buf, char **line)
{
	int		i;
	char	*ptr_to_slash_zero;

	if (buf)
	{
		ptr_to_slash_zero = *line;
		if ((i = ft_search_for_slash_n(buf)) != -1)
		{
			buf[i] = '\0';
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			free(ptr_to_slash_zero);
			ft_strcpy(buf, &buf[++i]);
			return (1);
		}
		else
		{
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			free(ptr_to_slash_zero);
			buf[0] = '\0';
		}
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	int			number_of_bytes_actually_read;
	static char	*buf;

	i = 0;
	if (BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((i = ft_n_or_not(buf, line) != 0))
		return (i);
	if (buf)
		free(buf);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((number_of_bytes_actually_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[number_of_bytes_actually_read] = '\0';
		if ((i = ft_n_or_not(buf, line) != 0))
			return (i);
	}
	free(buf);
	buf = NULL;
	return (0);
}
