# include "../../includes/minishell.h"

// Stampa le variabili d'ambiente o imposta nuove variabili d'ambiente.
int	my_export(t_prompt *p)
{
    char **env;
    int g_status;

    // Se il comando export è chiamato senza argomenti, stampa tutte
    // le variabili d'ambiente.
    if (!p->cmds->next)
    {
        env = p->envp;
        while (env && *env)
            ft_putendl_fd(*env++, 1);
        return 0;
    }
    // Se il comando export è chiamato con argomenti, imposta nuove
    // variabili d'ambiente.
    g_status = 0;
    while (p->cmds->next)
    {
        char **pair = ((t_mini *)p->cmds->content)->toks;
        if (pair && *pair)
            p->envp = set_env(pair[0], pair[1], p->envp, -1);
        p->cmds = p->cmds->next;
    }
    return g_status;
}