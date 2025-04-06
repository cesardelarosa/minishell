#ifndef CTX_H
#define CTX_H

#include "structs.h"

t_ctx init_ctx(char **envp);
int destroy_ctx(t_ctx *ctx);

#endif