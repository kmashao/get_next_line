/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmashao <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 08:58:41 by kmashao           #+#    #+#             */
/*   Updated: 2018/07/01 18:28:20 by kmashao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		readline(const int fd, char **line, int ret)
{
	char *buff;
	char *hold;
	char *temp;

	temp = NULL;
	buff = ft_strnew(BUFF_SIZE);
	if ((read(fd, temp, 0) < 0))
		return (-1);
	hold = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		hold = ft_strjoin(*line, buff);
		free((*line));
		(*line) = hold;
		if (ft_strchr(buff, '\n'))
			break ;
		ft_strclr(buff);
	}
	free(buff);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	char		*hold;
	static char	*res[2147483647];
	int			ret;

	ret = 1;
	hold = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (res[fd])
	{
		(*line) = res[fd];
		res[fd] = ft_strchr((*line), '\n');
	}
	else
		(*line) = ft_strnew(0);
	if (!res[fd])
		ret = readline(fd, line, ret);
	if ((hold = ft_strchr((*line), '\n')))
	{
		res[fd] = ft_strdup(hold + 1);
		ft_strclr(hold);
	}
	if (ret > 0 || ft_strlen((*line)) > 0)
		ret = 1;
	return (ret);
}
