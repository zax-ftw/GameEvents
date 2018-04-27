#include "skse/PapyrusNativeFunctions.h" // StaticFunctionTag
#include "skse/GameReferences.h"

namespace newEvents {

	bool RegisterFuncs(VMClassRegistry* registry);

	void RegisterForObjectLoaded(StaticFunctionTag* base, TESForm* thisForm, UInt32 objectType);
	void UnregisterForObjectLoaded(StaticFunctionTag* base, TESForm* thisForm, UInt32 objectType);

	void RegisterForQuestStage(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForQuestStage(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForWait(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForWait(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForItemHarvested(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForItemHarvested(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForLocationCleared(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForLocationCleared(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForBookRead(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForBookRead(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForSkillIncrease(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForSkillIncrease(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForLevelIncrease(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForLevelIncrease(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForLocationDiscovery(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForLocationDiscovery(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForQuestStatus(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForQuestStatus(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForActorKilled(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForActorKilled(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForCriticalHit(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForCriticalHit(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForDisarmed(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForDisarmed(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForWordLearned(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForWordLearned(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForSpellLearned(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForSpellLearned(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForDragonSoulGained(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForDragonSoulGained(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForSoulTrapped(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForSoulTrapped(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForShoutAttack(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForShoutAttack(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForLockPicked(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForLockPicked(StaticFunctionTag* base, TESForm* thisForm);

	void RegisterForHorseSteal(StaticFunctionTag* base, TESForm* thisForm);
	void UnregisterForHorseSteal(StaticFunctionTag* base, TESForm* thisForm);

}
