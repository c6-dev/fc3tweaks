#pragma once
#include "ModUtils/Patterns.h"

void writePatches() {
	auto module = GetModuleHandleA("FC3_d3d11.dll");
	if (module == NULL) {
		module = GetModuleHandleA("FC3.dll");
	}
	auto skipFastTravelConfirmation = hook::make_module_pattern(module, "24 0F 00 80 7C 24 0D 00").get_first(8);
	SafeWrite8((UInt32)skipFastTravelConfirmation, 0x75);
	auto removeOnlinePopup = hook::make_module_pattern(module, "50 C7 45 90 02 00 00 00").get_first(8);
	PatchMemoryNop((UInt32)removeOnlinePopup, 7);


}