
#include "structs.h"
#include "libft.h"

t_ctx	init_ctx(char **envp)
{
	t_ctx	ctx;

	ctx.status = 0;
	ctx.envp = envp;
	ctx.env = env_init(envp);
	if (!ctx.env)
	{
		ft_putstr_fd("minishell: env_init failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ctx);
}