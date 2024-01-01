/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:32:32 by duzegbu           #+#    #+#             */
/*   Updated: 2023/12/04 01:33:13 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *input;

    // Main shell loop
    while (1) {
        // Display prompt
        input = readline("minishell$ ");
        
        // Check for EOF (Ctrl-D)
        if (!input) {
            printf("\n");  // Add a new line for visual clarity
            break;
        }

        // TODO: Implement parsing and execution of the input here

        // Free input obtained from readline
        free(input);
    }

    return 0;
}
