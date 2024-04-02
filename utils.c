/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:41:35 by isb3              #+#    #+#             */
/*   Updated: 2024/04/02 11:21:37 by adesille         ###   ########.fr       */
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
	char	*cmd1;
	char	*cmd2;

	cmds = malloc(3 * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmd1 = ft_strjoin(argv[2], " ");
	cmds[0] = ft_substr(cmd1, 0, ft_strlen(cmd1));
	cmd2 = ft_strjoin(argv[3], " ");
	cmds[1] = ft_substr(cmd2, 0, ft_strlen(cmd2));
	cmds[2] = NULL;
	args = malloc(3 * sizeof(char **));
	if (!args)
		return (free(cmd1), free(cmd2), free_memory(cmds), NULL);
	args[0] = ft_split(cmds[0], ' ');
	args[1] = ft_split(cmds[1], ' ');
	args[2] = NULL;
	return (free(cmd1), free(cmd2), free_memory(cmds), args);
}

char	**parse_files(char *argv[])
{
	char	**files;

	files = malloc(3 * sizeof(char *));
	if (!files)
		return (NULL);
	files[0] = ft_substr(argv[1], 0, ft_strlen(argv[1]));
	files[1] = ft_substr(argv[4], 0, ft_strlen(argv[4]));
	files[2] = NULL;
	return (files);
}
