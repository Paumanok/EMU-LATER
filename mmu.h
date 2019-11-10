#ifndef MMU_H__
#define MMU_H__
#include "common.h"
#include "core.h"

void mmu_ctrl(NES* nes);

int write_internal_ram(NES* nes);
int internal_memory(NES* nes);
int mapper_0(NES* nes);

#endif //MMU_H__
