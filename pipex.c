/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:23:30 by isb3              #+#    #+#             */
/*   Updated: 2024/04/08 12:44:45 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_data *d)
{
	close(d->fd[0]);
	if (d->it == 0)
		dup2(d->infile, STDIN_FILENO);
	if (d->it == d->count - 1)
	{
		dup2(d->outfile, STDOUT_FILENO);
		close(d->fd[1]);
	}
	else
		dup2(d->fd[1], STDOUT_FILENO);
}

void	parent(t_data *d)
{
	close(d->fd[1]);
	close(d->fd[0]);
	dup2(d->fd[0], STDIN_FILENO);
}

int	warlord_executor(t_data *d, char *env[])
{
	int	status;
	pid_t pid;

	d->it++;
	if (pipe(d->fd) == -1)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
	pid = fork();
	if (pid == -1)
		return (ff(d, errno, NULL), errno);
	if (pid == 0)
	{
		child(d);
		execve(d->cmd_paths[d->it], d->args[d->it], env);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		parent(d);
		if (d->it < d->count - 1)
			warlord_executor(d, env);
	}
	return (0);
}


int	initializer(t_data *d, char	*argv[], char *env[])
{
	d->infile = 0;
	d->outfile = 0;
	d->cmd_paths = get_cmd_path(argv, env);
	if (!d->cmd_paths)
		return (free(d), printf("ERROR\n"), 127);
	d->args = parse_cmds(argv);
	if (!d->args)
		return (ff(d, 0, "args_parsing\n"), 1);
	if (parse_files(argv, d))
		return (ff(d, 0, "files parsing"), 1);
	int i = 0;
	while (d->args[i])
		i++;
	d->count = i;
	d->it = -1;
	d->temp = -1;
	return (0);
}

///-> Add path basique to env[] and test execve with path instead of env

int	main(int argc, char *argv[], char *env[])
{
	t_data	*d;
	int		status;

	if (argc <= 4)
		return (printf("argc ERROR\n"), 1);
	else
	{
		if (format_check(argv))
			return (perror("wrong format"), 1);
		d = malloc(sizeof(t_data));
		if (!d)
			return (ft_putstr_fd("malloc\n", 1), 1);
		initializer(d, argv, env);
		if (warlord_executor(d, env))
			return (ff(d, errno, NULL), errno);
		return (ff(d, 0, NULL), 0);
	}
	return (0);
}
