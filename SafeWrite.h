#pragma once
#include "types.h"
void SafeWrite8(UInt32 addr, UInt32 data);
void SafeWrite32(UInt32 addr, UInt32 data);
void WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt);


