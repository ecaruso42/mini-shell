# include "../../includes/minishell.h"

// Rimuove variabili d'ambiente.
int	my_unset(t_prompt *p)
{
    int g_status = 0;

    // Rimuove le variabili d'ambiente specificate come argomenti.
    while (p->cmds->next)
    {
        char **var = ((t_mini *)p->cmds->content)->toks;
        if (var && *var)
            p->envp = unset_env(*var, p->envp);
        p->cmds = p->cmds->next;
    }

    return g_status;
}
