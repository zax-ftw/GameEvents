#include "skse/PapyrusArgs.h"

#include "Papyrus.h"
#include "Events.h"

namespace newEvents {
	
	void RegisterForObjectLoaded(StaticFunctionTag* base, TESForm* thisForm, UInt32 objectType)
	{
		if(!thisForm)
			return;

		g_objectLoadedEventRegs.Register<TESForm>(objectType, thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForObjectLoaded(%i): %08X", objectType, thisForm->formID);
	}
	void UnregisterForObjectLoaded(StaticFunctionTag* base, TESForm* thisForm, UInt32 objectType)
	{
		if(!thisForm)
			return;

		g_objectLoadedEventRegs.Unregister<TESForm>(objectType, thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForObjectLoaded: %08X", thisForm->formID);
	}

	void RegisterForQuestStage(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_questStageEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForQuestStage: %08X", thisForm->formID);
	}
	void UnregisterForQuestStage(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_questStageEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForQuestStage: %08X", thisForm->formID);
	}

	void RegisterForWait(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_waitEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForWait: %08X", thisForm->formID);
	}
	void UnregisterForWait(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_waitEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForWait: %08X", thisForm->formID);
	}

	void RegisterForItemHarvested(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_harvestEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForItemHarvested: %08X", thisForm->formID);
	}
	void UnregisterForItemHarvested(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_harvestEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForItemHarvested: %08X", thisForm->formID);
	}

	void RegisterForLocationCleared(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locationClearedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForLocationCleared: %08X", thisForm->formID);
	}
	void UnregisterForLocationCleared(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locationClearedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForLocationCleared: %08X", thisForm->formID);
	}

	void RegisterForBookRead(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_bookReadEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForBookRead: %08X", thisForm->formID);
	}
	void UnregisterForBookRead(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_bookReadEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForBookRead: %08X", thisForm->formID);
	}

	void RegisterForSkillIncrease(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_skillIncreaseEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForSkillIncrease: %08X", thisForm->formID);
	}
	void UnregisterForSkillIncrease(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_skillIncreaseEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForSkillIncrease: %08X", thisForm->formID);
	}

	void RegisterForLevelIncrease(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_levelIncreaseEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForLevelIncrease: %08X", thisForm->formID);
	}
	void UnregisterForLevelIncrease(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_levelIncreaseEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForLevelIncrease: %08X", thisForm->formID);
	}

	void RegisterForLocationDiscovery(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locationDiscoveryEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForLocationDiscovery: %08X", thisForm->formID);
	}
	void UnregisterForLocationDiscovery(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locationDiscoveryEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForLocationDiscovery: %08X", thisForm->formID);
	}

	void RegisterForQuestStatus(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_questStatusEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForQuestStatus: %08X", thisForm->formID);
	}
	void UnregisterForQuestStatus(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_questStatusEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForQuestStatus: %08X", thisForm->formID);
	}

	void RegisterForActorKilled(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_actorKillEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForActorKilled: %08X", thisForm->formID);
	}
	void UnregisterForActorKilled(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_actorKillEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForActorKilled: %08X", thisForm->formID);
	}

	void RegisterForCriticalHit(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_criticalHitEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForCriticalHit: %08X", thisForm->formID);
	}
	void UnregisterForCriticalHit(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_criticalHitEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForCriticalHit: %08X", thisForm->formID);
	}

	void RegisterForDisarmed(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_disarmedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForDisarmed: %08X", thisForm->formID);
	}
	void UnregisterForDisarmed(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_disarmedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForDisarmed: %08X", thisForm->formID);
	}

	void RegisterForWordLearned(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_wordLearnedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForWordLearned: %08X", thisForm->formID);
	}
	void UnregisterForWordLearned(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_wordLearnedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForWordLearned: %08X", thisForm->formID);
	}

	void RegisterForSpellLearned(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_spellsLearnedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForSpellLearned: %08X", thisForm->formID);
	}
	void UnregisterForSpellLearned(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_spellsLearnedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForSpellLearned: %08X", thisForm->formID);
	}

	void RegisterForDragonSoulGained(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_dragonSoulGainedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForDragonSoulGained: %08X", thisForm->formID);
	}
	void UnregisterForDragonSoulGained(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_dragonSoulGainedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForDragonSoulGained: %08X", thisForm->formID);
	}

	void RegisterForSoulTrapped(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_soulsTrappedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForSoulTrapped: %08X", thisForm->formID);
	}
	void UnregisterForSoulTrapped(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_soulsTrappedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForSoulTrapped: %08X", thisForm->formID);
	}

	void RegisterForShoutAttack(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_shoutAttackEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForShoutAttack: %08X", thisForm->formID);
	}
	void UnregisterForShoutAttack(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_shoutAttackEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForShoutAttack: %08X", thisForm->formID);
	}

	void RegisterForLockPicked(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locksPickedEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForLockPicked: %08X", thisForm->formID);
	}
	void UnregisterForLockPicked(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_locksPickedEventRegs.Unregister<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForLockPicked: %08X", thisForm->formID);
	}

	void RegisterForHorseSteal(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_grandTheftHorseEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("RegisterForHorseSteal: %08X", thisForm->formID);
	}
	void UnregisterForHorseSteal(StaticFunctionTag* base, TESForm* thisForm)
	{
		if(!thisForm)
			return;

		g_grandTheftHorseEventRegs.Register<TESForm>(thisForm->GetFormType(), thisForm);

		_MESSAGE("UnregisterForHorseSteal: %08X", thisForm->formID);
	}
}

bool newEvents::RegisterFuncs(VMClassRegistry* registry)
{
	_MESSAGE("Registering Papyrus functions...");

	//FurnitureEvent
	//LockState

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, TESForm*, UInt32>("RegisterForObjectLoaded", "GameEvents", RegisterForObjectLoaded, registry));

	registry->RegisterFunction(
		new NativeFunction2 <StaticFunctionTag, void, TESForm*, UInt32>("UnregisterForObjectLoaded", "GameEvents", UnregisterForObjectLoaded, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForQuestStage", "GameEvents", RegisterForQuestStage, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForQuestStage", "GameEvents", UnregisterForQuestStage, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForWait", "GameEvents", RegisterForWait, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForWait", "GameEvents", UnregisterForWait, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForItemHarvested", "GameEvents", RegisterForItemHarvested, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForItemHarvested", "GameEvents", UnregisterForItemHarvested, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForLocationCleared", "GameEvents", RegisterForLocationCleared, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForLocationCleared", "GameEvents", UnregisterForLocationCleared, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForBookRead", "GameEvents", RegisterForBookRead, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForBookRead", "GameEvents", UnregisterForBookRead, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForSkillIncrease", "GameEvents", RegisterForSkillIncrease, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForSkillIncrease", "GameEvents", UnregisterForSkillIncrease, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForLevelIncrease", "GameEvents", RegisterForLevelIncrease, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForLevelIncrease", "GameEvents", UnregisterForLevelIncrease, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForLocationDiscovery", "GameEvents", RegisterForLocationDiscovery, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForLocationDiscovery", "GameEvents", UnregisterForLocationDiscovery, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForQuestStatus", "GameEvents", RegisterForQuestStatus, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForQuestStatus", "GameEvents", UnregisterForQuestStatus, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForActorKilled", "GameEvents", RegisterForActorKilled, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForActorKilled", "GameEvents", UnregisterForActorKilled, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForCriticalHit", "GameEvents", RegisterForCriticalHit, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForCriticalHit", "GameEvents", UnregisterForCriticalHit, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForDisarmed", "GameEvents", RegisterForDisarmed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForDisarmed", "GameEvents", UnregisterForDisarmed, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForWordLearned", "GameEvents", RegisterForWordLearned, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForWordLearned", "GameEvents", UnregisterForWordLearned, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForSpellLearned", "GameEvents", RegisterForSpellLearned, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForSpellLearned", "GameEvents", UnregisterForSpellLearned, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForDragonSoulGained", "GameEvents", RegisterForDragonSoulGained, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForDragonSoulGained", "GameEvents", UnregisterForDragonSoulGained, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForSoulTrapped", "GameEvents", RegisterForSoulTrapped, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForSoulTrapped", "GameEvents", UnregisterForSoulTrapped, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForShoutAttack", "GameEvents", RegisterForShoutAttack, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForShoutAttack", "GameEvents", UnregisterForShoutAttack, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForLockPicked", "GameEvents", RegisterForLockPicked, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForLockPicked", "GameEvents", UnregisterForLockPicked, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("RegisterForHorseSteal", "GameEvents", RegisterForHorseSteal, registry));

	registry->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, void, TESForm*>("UnregisterForHorseSteal", "GameEvents", UnregisterForHorseSteal, registry));

	return true;
}