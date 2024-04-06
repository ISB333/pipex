/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:23:30 by isb3              #+#    #+#             */
/*   Updated: 2024/04/06 11:27:11 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	parent(int fd[], t_data *d, char *env[], pid_t pid)
// {
// 	int	file;
// 	int	status;

// 	close(fd[1]);
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 	{
// 		if (WEXITSTATUS(status) != EXIT_SUCCESS)
// 			return (ff(d, 0, NULL), close(fd[0]),  errno);
// 		file = open(d->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (file == -1)
// 			return (ff(d, errno, d->files[1]), errno);
// 		// if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(file, STDOUT_FILENO) == -1
// 		// 	|| close(file) || close(fd[0]))
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(file, STDOUT_FILENO);
// 		close(file);
// 		close(fd[0]);
// 		if (execve(d->cmd_paths[1], d->args[1], env))
// 			return (ff(d, errno, d->args[1][0]), errno);
// 	}
// 	else
// 		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
// 	return (0);
// }

// int	child(int fd_in, int fd_out, char *cmd_path, char **args, char *env[])
// {
// 	int	file;
// 
	// if (dup2(file, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1
	// 	|| close(fd[1]))
// }

// ============================================================
// ============================================================
// ============================================================

// int	exec(int fd[], char *cmd_path, char **args, char *env[])
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		return (ff(NULL, errno, NULL), errno);
// 	if (pid == 0)
// 	{
// 		if (execve(cmd_path, args, env))
// 			return (ff(NULL, errno, "exec"), close(fd[0]), errno);
// 		return (0);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		// if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
//   	    //   return err("error: fatal\n");
//    		return (WIFEXITED(status) && WEXITSTATUS(status));
// 	}
// }

// int	warlord_executor(t_data *d, char *env[])
// {
// 	int		file;
// 	int		fd[2];
// 	int 	i;

// 	i = 0;
// 	if (pipe(fd) == -1)
// 		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
// 	while (d->args[i])
// 	{
// 		if (i == 0)
// 		{
// 			close(fd[0]);
// 			file = open(d->files[0], O_RDONLY);
// 			if (file == -1)
// 				return (1);
// 			dup2(file, STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[1]);
// 			exec(fd, d->cmd_paths[i], d->args[i], env);
// 				// return (printf("error\n"));
// 			i++;
// 		}
// 		close(file);
// 		while (d->args[i + 1])
// 		{
// 			// file = open(d->files[0], O_RDONLY);
// 			// if (file == -1)
// 			// 	return (1);
// 			dup2(fd[0], STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 			exec(fd, d->cmd_paths[i], d->args[i], env);
// 				// return (printf("error\n"));
// 			i++;
// 		}
// 		file = open(d->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (file == -1)
// 			return (1);
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(file, STDOUT_FILENO);
// 		// close(fd[0]);
// 		// close(fd[1]);
// 		exec(fd, d->cmd_paths[i], d->args[i], env);
// 			// return (printf("error\n"));
// 		close(file);
// 		i++;

// 	}
// 	return (0);
// }

// ============================================================
// ============================================================
// ============================================================

int	exec(int fd[], t_data *d, char *env[])
{
	int	file;

	close(fd[0]);

	if(d->it == 0)
		dup2(d->infile, STDIN_FILENO);
	else
		dup2(d->outfile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(d->cmd_paths[d->it], d->args[d->it++], env))
		return (ff(d, errno, d->args[0][0]), close(file), errno);
	return (0);
}

int	parent(int fd[], t_data *d, char *env[], pid_t pid)
{
	int	file;
	int	status;

	close(fd[1]);
	waitpid(d->child[d->it], &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != EXIT_SUCCESS)
			return (ff(d, 0, NULL), close(fd[0]),  errno);
		if(d->count--)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(d->outfile, STDOUT_FILENO);
			close(d->outfile);
			close(fd[0]);
			d->child[++d->it] = fork();
			if(d->child[d->it] == -1)
				return(0);
			if(d->child[d->it] == 0)
				exec(fd, d, env);
			else
				parent(fd, d, env, d->child[d->it]);
			// if (execve(d->cmd_paths[1], d->args[1], env))
			// 	return (ff(d, errno, d->args[1][0]), errno);
		}
		else
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(d->outfile, STDOUT_FILENO);
			close(d->outfile);
			close(fd[0]);
			if (execve(d->cmd_paths[d->it], d->args[d->it], env))
				return (ff(d, errno, d->args[1][0]), errno);
		}
	}
	else
		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
	return (0);
}

int	warlord_executor(t_data *d, char *env[])
{
	int		file;
	int		fd[2];

	if (pipe(fd) == -1)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
	d->child[d->it] = fork();
	if (d->child[d->it] == -1)
		return (ff(d, errno, NULL), errno);
	d->infile = open(d->files[0], O_RDONLY);
	if (d->infile == -1)
		return(0);
	d->outfile = open(d->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->outfile == -1)
		return(0);
	if (d->child[0] == 0)
	{
		exec(fd, d, env);
	}
	else
	{
		parent(fd, d, env, d->child[d->it]);
	}
	return (0);
}

///-> pasqualerossi multipipes management 

///-> Add path basique to env[] and test execve with path instead of env

int	main(int argc, char *argv[], char *env[])
{
	t_data	*d;
	int		status;

	if (argc < 4)
		return (printf("argc ERROR\n"), 1);
	else
	{
		if (format_check(argv))
			return (perror("wrong format"), 1);
		d = malloc(sizeof(t_data));
		if (!d)
			return (printf("mallocerr\n"), 1);
		d->cmd_paths = get_cmd_path(argv, env);
		if (!d->cmd_paths)
			return (free(d), printf("ERROR\n"), 127);
		d->args = parse_cmds(argv);
		if (!d->args)
			return (ff(d, 0, "args_parsing\n"), 1);
		d->files = parse_files(argv);
		if (!d->files)
			return (ff(d, 0, "files parsing"), 1);
		int i = 0;
		while(d->args[i])
			i++;
		d->count = i - 1;
		d->it = 0;
		return (warlord_executor(d, env));
	}
	return (0);
}
