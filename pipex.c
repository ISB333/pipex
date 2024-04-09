/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:23:30 by isb3              #+#    #+#             */
/*   Updated: 2024/04/09 10:39:22 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_data *d)
{
	close(d->pipe_fd[0]);
	if (d->it == 0)
		dup2(d->infile, STDIN_FILENO);
	if (d->it == d->count - 1)
		dup2(d->outfile, STDOUT_FILENO);
	else
		dup2(d->pipe_fd[1], STDOUT_FILENO);
}

void	parent(t_data *d)
{
	close(d->pipe_fd[1]);
	dup2(d->pipe_fd[0], STDIN_FILENO);
	close(d->pipe_fd[0]);
}

int	warlord_executor(t_data *d, char *env[])
{
	int		status;
	pid_t	pid;

	d->it++;
	if (pipe(d->pipe_fd) == -1)
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

///-> Add path basique to env[] and test execve with path instead of env

int	main(int argc, char *argv[], char *env[])
{
	t_data	*d;

	if (argc <= 4)
		return (printf("argc ERROR\n"), 1);
	else
	{
		if (format_check(argv))
			return (perror("wrong format"), 1);
		d = malloc(sizeof(t_data));
		if (!d)
			return (ft_putstr_fd("malloc\n", 1), 1);
		if (initializer(d, argv, env))
			return (-1);
		if (warlord_executor(d, env))
			return (ff(d, errno, NULL), errno);
		return (ff(d, 0, NULL), 0);
	}
	return (0);
}
