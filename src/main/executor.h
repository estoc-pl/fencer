#ifndef FENCER_EXECUTOR_H
#define FENCER_EXECUTOR_H

#include "code_space/code_space.h"
#include "destreza/destreza.h"

void execute_code_space(CodeSpace *code_space, const Destreza *destreza, FencerError **error);

#endif //FENCER_EXECUTOR_H
