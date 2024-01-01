#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

struct {
    int error_code;
    const char *error_file;
    int exit_status;
} g_shell_data;

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_long(unsigned long long res, int sign)
{
	if (res > 9223372036854775807 && sign == 1)
		return (0);
	else if (res > 9223372036854775808UL && sign == -1)
		return (0);
	return (1);
}

int	is_valid(const char *str, int sign)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (res > res * 10 + (str[i] - 48))
			return (0);
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (check_long(res, sign));
}

#include <stdio.h>

void error_message(void) {
    // Print an error message based on the error code
    switch (g_shell_data.error_code) {
        case 1:
            printf("Error: Numeric value required in %s\n", g_shell_data.error_file);
            break;
        case 2:
            printf("Error: Too many arguments provided\n");
            break;
        // Add more cases as needed for different error codes
        default:
            printf("Unknown error\n");
    }
}


int parse_exit_argument(const char *str) {
    int i = 0;
    int sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    if (is_numeric(str + i) == 0 || is_valid(str + i, sign) == 0) {
        g_shell_data.error_code = 1;
        g_shell_data.error_file = str;
        error_message();
        exit(g_shell_data.exit_status);
    }

    return atoi(str);
}

void shell_exit(char **args) {
    int exit_value = g_shell_data.exit_status;

    if (args[1]) {
        if (parse_exit_argument(args[1]) && !args[2]) {
            exit_value = parse_exit_argument(args[1]);
            g_shell_data.exit_status = exit_value;
            exit(exit_value);
        }

        if (args[2]) {
            g_shell_data.error_code = 2; // TOO_MANY_ARGS
            error_message();
            return;
        }
    }

    // Clean up and exit
    printf("Exiting the shell with status: %d\n", exit_value);
    exit(exit_value);
}

/*int main(void) {
    // Test
    char *test_args[] = {"shell", "123", NULL};
    shell_exit(test_args);

    return 0;
}*/