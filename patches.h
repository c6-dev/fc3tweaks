#pragma once
#include "ModUtils/Patterns.h"
#include "calls.h"
UInt32 quickSellConfirmationCBAddr = NULL;
UInt32 quickSellRetnAddr = NULL;


__declspec(naked) void SkipQuickSellConfirmation() {
	__asm {
		push 0
		mov eax, dword ptr ds:[esi+0x6C]
		push eax
		mov ecx, esi
		call quickSellConfirmationCBAddr
		cmp dword ptr[esp+0x40], 0
		jmp quickSellRetnAddr
	}
}

void writePatches() {

	auto module = GetModuleHandleA("FC3_d3d11.dll");
	if (module == NULL) {
		module = GetModuleHandleA("FC3.dll");
	}

	auto skipFastTravelConfirmation = hook::make_module_pattern(module, "24 0F 00 80 7C 24 0D 00").get_first(8);
	SafeWrite8((UInt32)skipFastTravelConfirmation, 0x75);

	auto removeOnlinePopup = hook::make_module_pattern(module, "50 C7 45 90 02 00 00 00").get_first(8);
	PatchMemoryNop((UInt32)removeOnlinePopup, 7);

	auto skipQuickSellConfirmation = hook::make_module_pattern(module, "68 63 EA 01").get_first(-14);
	quickSellRetnAddr = (UInt32)hook::make_module_pattern(module, "68 63 EA 01").get_first(63);
	quickSellConfirmationCBAddr = (UInt32)hook::make_module_pattern(module, "83 E4 F8 83 EC 1C 53 8B D9 8B 43 6C 56 57 3B 45 08").get_first(-3); 
	WriteRelJump((UInt32)skipQuickSellConfirmation, (UInt32)SkipQuickSellConfirmation);

}