/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:44:32 by adesille          #+#    #+#             */
/*   Updated: 2024/04/02 14:02:46 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path(char *env[])
{
	char	**path;
	char	*trimm_path;
	int		i;

	i = 0;
	while (env[i] && (!strstr(env[i], "PATH") || !strstr(env[i], "bin")))
		i++;
	if (!env[i])
		return (NULL);
	trimm_path = ft_strtrim(env[i], "PATH=/");
	path = ft_split(trimm_path, ':');
	return (free(trimm_path), path);
}

char	*path_finder(char *cmd, char *env[])
{
	char	**path;
	char	**full_cmd;
	char	*test_path;
	int		i;

	path = extract_path(env);
	if (!path)
		return (NULL);
	i = -1;
	full_cmd = ft_split(cmd, ' ');
	cmd = ft_strjoin("/", full_cmd[0]);
	free_memory(full_cmd);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
			return (free(cmd), free_memory(path), test_path);
		free(test_path);
	}
	return (free(cmd), free_memory(path), NULL);
}

char	**get_cmd_path(char *argv[], char *env[])
{
	char	**cmd_paths;
	int		i;
	int		k;

	i = 2;
	while (argv[i])
		i++;
	cmd_paths = malloc((i - 2) * sizeof(char *));
	if (!cmd_paths)
		return (NULL);
	cmd_paths[i - 3] = NULL;
	k = 0;
	i = 2;
	while (argv[i + 1])
	{
		cmd_paths[k] = path_finder(argv[i++], env);
		if (!cmd_paths[k++])
			return (free(cmd_paths), ft_putstr_fd("command not found : ", 1), ft_putstr_fd(argv[i], 1), NULL);
	}
	return (cmd_paths);
}

void	printer(t_data *d)
{
	int	k = -1;

	printf("\n=== cmds_paths ===\n");
	while (d->cmd_paths[++k])
		printf("%s\n", d->cmd_paths[k]);
	k = -1;
	printf("\n=== file ===\n");
	while (d->files[++k])
		printf("file %d = %s\n", k, d->files[k]);
	int i = -1;
	k = 0;
	printf("\n=== args_split 1 ===\n");
	while(d->args[++i])
	{
		k = 0;
		while(d->args[i][k])
			printf("%s\n", d->args[i][k++]);
		if (i == 0)
			printf("\n=== args_split 2 ===\n");
	}
	printf("\n--------------------------------------------------------------\n");
}
