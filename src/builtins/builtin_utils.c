/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:54:32 by grinella          #+#    #+#             */
/*   Updated: 2024/01/16 18:04:01 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*cont_error(int err_type, char *param, int err) //preso dal github
{
	int	g_status;

	g_status = err;
	if (err_type == 0)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == 1)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == 2)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == 3)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == 4)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == 5)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == 6)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == 7)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == 8)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == 9)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == 10)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

/*void	change_error(char **str[2]) //preso dal github
{
	int		g_status;
	char	*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		cont_error(NDIR, str[0][1], 1);
	else if (str[0][1])
		cont_error(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}*/

int ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		i++;
	}
	return (i);
}

void	free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

char	**extend_matrix(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_matrixlen(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			free_matrix(&in);
			free_matrix(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	free_matrix(&in);
	return (out);
}
