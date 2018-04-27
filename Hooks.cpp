#include "skse/SafeWrite.h"
#include "skse/GameMenus.h"

#include "Hooks.h"

TESObjectREFR*	g_pickedLock = (TESObjectREFR*)0x01B3FB88; // used by vanilla lockpicking menu
TESObjectREFR*	g_stolenHorse;
TESObjectREFR*	g_discoveredMarker;
BGSLocation*		g_clearedLocation;


// ======================================================
// Gameplay
// ======================================================

const UInt32 kClearedCheck = 0x004B15B0;
const UInt32 kClearedEnt = kClearedCheck + 0x3;
const UInt32 kClearedRet = kClearedCheck + 0x8;

__declspec(naked) void HookLocationCleared()
{
	__asm
		{
			mov		g_clearedLocation, ecx

			cmp     [esp+2Ch], 0

			jmp		[kClearedRet]
		}
}

const UInt32 kDiscoveryCheck = 0x00744660;
const UInt32 kDiscoveryEnt = kDiscoveryCheck + 0xCC;
const UInt32 kDiscoveryRet = kDiscoveryCheck + 0xD1;

__declspec(naked) void HookLocationDiscovery()
{
	__asm
		{
			mov		g_discoveredMarker, edi

			add     esp, 8
			test    edi, edi

			jmp		[kDiscoveryRet]
		}
}

const UInt32 kHorseStealCheck = 0x006CC0D0;
const UInt32 kHorseStealEnt = kHorseStealCheck + 0x326;
const UInt32 kHorseStealRet = kHorseStealCheck + 0x32B;

__declspec(naked) void HookHorseSteal()
{
	__asm
		{
			mov     eax, [esp+18h]
			mov		g_stolenHorse, eax

			mov     eax, g_thePlayer

			jmp		[kHorseStealRet]
		}
}

void WriteHooks()
{
	_MESSAGE("Writing hooks...");

	WriteRelJump(kClearedEnt, (UInt32)HookLocationCleared);
//	WriteRelJump(kDiscoveryEnt, (UInt32)HookLocationDiscovery);
	WriteRelJump(kHorseStealEnt, (UInt32)HookHorseSteal);

}