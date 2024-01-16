/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:46:00 by grinella          #+#    #+#             */
/*   Updated: 2024/01/15 12:46:08 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Stampa il percorso corrente (current working directory) sulla console.
int	my_pwd(t_prompt *p)
{
	char *cwd = getcwd(NULL, 0);

	if (!cwd)
	{
		cont_error(NDIR, "", 1);
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	p->envp = set_env("OLDPWD", p->envp, 0);
	p->envp = set_env("PWD", cwd, p->envp, 3);
	free(cwd);
	return (0);
}
