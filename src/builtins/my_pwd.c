#include "minishell.h"

void	pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (buff)
		printf("%s\n", buff);
	else
	{
		printf("error\n");
		g_minishell.exit_s = 1;
	}
	g_minishell.exit_s = 0;
}