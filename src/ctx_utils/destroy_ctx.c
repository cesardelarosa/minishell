
#include "structs.h"
#include "env.h"

int	destroy_ctx(t_ctx *ctx)
{
	if (ctx->env)
		env_destroy(ctx->env);
	return (ctx->status);
}
