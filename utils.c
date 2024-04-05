/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:41:35 by isb3              #+#    #+#             */
/*   Updated: 2024/04/05 09:45:02 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	format_check(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i] && i <= 4)
	{
		if (argv[i][0] == '-')
			return (-1);
	}
	return (0);
}

void	free_memory(char **array)
{
	int	j;

	j = 0;
	while (array[j])
		j++;
	while (j-- > 0)
		free(array[j]);
	free(array);
}

int	ff(t_data *d, int err, char *msg)
{
	if (err)
		write(2, strerror(err), ft_strlen(strerror(err)));
	if (msg)
	{
		write(1, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	if (d->cmd_paths)
		free_memory(d->cmd_paths);
	if (d->files)
		free_memory(d->files);
	if (d->args)
		return (free_memory(d->args[0]), free_memory(d->args[1]), \
				free(d->args), free(d), errno);
	return (errno);
}

char	***parse_cmds(char *argv[])
{
	char	***args;
	char	**cmds;
	char	*cmd;
	int		i;
	int		k;

	i = 0;
	while (argv[i])
		i++;
	cmds = malloc((i - 2) * sizeof(char *));
	if (!cmds)
		return (NULL);
	args = malloc((i - 2) * sizeof(char **));
	if (!args)
		return (free(cmds), NULL);
	cmds[i - 3] = NULL;
	args[i - 3] = NULL;
	k = 0;
	i = 2;
	while (argv[i + 1])
	{
		cmd = ft_strjoin(argv[i++], " ");
		cmds[k++] = ft_substr(cmd, 0, ft_strlen(cmd));
		free(cmd);
	}
	i = -1;
	while (cmds[++i])
		args[i] = ft_split(cmds[i], ' ');
	return (free_memory(cmds), args);
}

char	**parse_files(char *argv[])
{
	char	**files;
	int		i;

	i = 1;
	files = malloc(3 * sizeof(char *));
	if (!files)
		return (NULL);
	files[0] = ft_substr(argv[1], 0, ft_strlen(argv[1]));
	while (argv[i])
		i++;
	files[1] = ft_substr(argv[i - 1], 0, ft_strlen(argv[i - 1]));
	files[2] = NULL;
	return (files);
}
