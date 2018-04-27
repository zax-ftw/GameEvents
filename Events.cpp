#include "skse/GameEvents.h" // structs
#include "skse/GameRTTI.h" // DYNAMIC_CAST
#include "skse/PapyrusArgs.h"
#include "skse/Utilities.h"	// DumpClass

#include "Events.h"
#include "Hooks.h"

//#include "skse/GameEvents.cpp"

template <typename T> void SetVMValue(VMValue * val, T arg)
{
	VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
	PackValue(val, &arg, registry);
}

template <> void SetVMValue<bool> (VMValue * val, bool arg)						{ val->SetBool(arg); }
template <> void SetVMValue<SInt32> (VMValue * val, SInt32 arg)					{ val->SetInt(arg); }
template <> void SetVMValue<float> (VMValue * val, float arg)					{ val->SetFloat(arg); }
template <> void SetVMValue<BSFixedString> (VMValue * val, BSFixedString arg)	{ val->SetString(arg.data); }

// ======================================================
// Generic Functors
// ======================================================

class EventQueueFunctor0 : public IFunctionArguments
{
public:
	EventQueueFunctor0(BSFixedString & a_eventName)
		: eventName(a_eventName.data) {}

	virtual bool	Copy(Output * dst)
	{
		dst->Resize(0);
		return true;
	}

	void			operator() (const EventRegistration<NullParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &eventName, this);
	}

private:
	BSFixedString	eventName;
};

template <typename T1>
class EventQueueFunctor1 : public IFunctionArguments
{
public:
	EventQueueFunctor1(BSFixedString & a_eventName, T1 a_arg1)
		: eventName(a_eventName.data), arg1(a_arg1) {}

	virtual bool	Copy(Output * dst)
	{
		dst->Resize(1);
		SetVMValue(dst->Get(0), arg1);

		return true;
	}

	void			operator() (const EventRegistration<NullParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &eventName, this);
	}

private:
	BSFixedString	eventName;
	T1				arg1;
};

template <typename T1, typename T2>
class EventQueueFunctor2 : public IFunctionArguments
{
public:
	EventQueueFunctor2(BSFixedString & a_eventName, T1 a_arg1, T2 a_arg2)
		: eventName(a_eventName.data), arg1(a_arg1), arg2(a_arg2) {}

	virtual bool	Copy(Output * dst)
	{
		dst->Resize(2);
		SetVMValue(dst->Get(0), arg1);
		SetVMValue(dst->Get(1), arg2);

		return true;
	}

	void			operator() (const EventRegistration<NullParameters> & reg)
	{
		VMClassRegistry * registry = (*g_skyrimVM)->GetClassRegistry();
		registry->QueueEvent(reg.handle, &eventName, this);
	}

private:
	BSFixedString	eventName;
	T1				arg1;
	T2				arg2;
};

// ======================================================
// ReceiveEvent
// ======================================================

namespace newEvents
{

EventResult FurnitureEventHandler::ReceiveEvent(TESFurnitureEvent * evn, EventDispatcher<TESFurnitureEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: FurnitureEvent"); //OnSit, OnGetUp

	BSFixedString eventName = evn->state ? BSFixedString("OnFurnitureLeave") : BSFixedString("OnFurnitureEnter");
	Actor* pActor = DYNAMIC_CAST(evn->character, TESObjectREFR, Actor);

	g_furnitureEventRegs.ForEach(
		EventQueueFunctor2<Actor*, TESObjectREFR*>(eventName, pActor, evn->furniture)
	);

    return kEvent_Continue;
}

EventResult LoadGameEventHandler::ReceiveEvent(TESLoadGameEvent * evn, EventDispatcher<TESLoadGameEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LoadGameEvent");

	return kEvent_Continue;
}


EventResult LockChangedEventHandler::ReceiveEvent(TESLockChangedEvent * evn, EventDispatcher<TESLockChangedEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LockChanged"); //OnLockStateChanged
	
	g_lockChangedEventRegs.ForEach(
		EventQueueFunctor2<TESObjectREFR*, TESObjectREFR*>(BSFixedString("OnLockChanged"), evn->lock, evn->unlocker)
	);
	
    return kEvent_Continue;
}

EventResult ObjectLoadedEventHandler::ReceiveEvent(TESObjectLoadedEvent * evn, EventDispatcher<TESObjectLoadedEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: ObjectLoaded");

	BSFixedString eventName = (evn->loaded) ? BSFixedString("OnObjectLoaded") : BSFixedString("OnObjectUnloaded");

	TESObjectREFR* object = DYNAMIC_CAST(LookupFormByID(evn->formId), TESForm, TESObjectREFR);
	UInt32 type = object->baseForm->GetFormType();

//	_DMESSAGE("Loaded: %i, Type: %i", evn->loaded, type);

	g_objectLoadedEventRegs.ForEach(
		type,
		EventQueueFunctor1<TESObjectREFR*>(eventName, object)
	);

    return kEvent_Continue;
}

EventResult QuestStageEventHandler::ReceiveEvent(TESQuestStageEvent * evn, EventDispatcher<TESQuestStageEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: QuestStage");
	
	TESQuest* pQuest = DYNAMIC_CAST(LookupFormByID(evn->formId), TESForm, TESQuest);

	g_questStageEventRegs.ForEach(
		EventQueueFunctor2<TESQuest*, UInt32>(BSFixedString("OnQuestStageChanged"), pQuest, evn->stage)
    );

    return kEvent_Continue;
}

EventResult WaitStartEventHandler::ReceiveEvent(TESWaitStartEvent * evn, EventDispatcher<TESWaitStartEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: WaitStart");

	g_waitEventRegs.ForEach(
		EventQueueFunctor2<float, float>(BSFixedString("OnWaitStart"), evn->current, evn->desired)
    );

    return kEvent_Continue;
}

EventResult WaitStopEventHandler::ReceiveEvent(TESWaitStopEvent * evn, EventDispatcher<TESWaitStopEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: WaitStop");

	g_waitEventRegs.ForEach(
		EventQueueFunctor0(BSFixedString("OnWaitStop"))
    );

    return kEvent_Continue;
}

EventResult HarvestEventHandler::ReceiveEvent(TESHarvestEvent::ItemHarvested * evn, EventDispatcher<TESHarvestEvent::ItemHarvested> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: ItemHarvest");

	g_harvestEventRegs.ForEach(
		EventQueueFunctor1<TESForm*>(BSFixedString("OnItemHarvested"), evn->object) //PlayerOnly
    );  

    return kEvent_Continue;
}

EventResult LocationClearedEventHandler::ReceiveEvent(LocationCleared::Event * evn, EventDispatcher<LocationCleared::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LocationCleared");

	DumpClass(g_clearedLocation, 10);

	g_locationClearedEventRegs.ForEach(
		EventQueueFunctor1<BGSLocation*>(BSFixedString("OnLocationCleared"), g_clearedLocation)
    );

    return kEvent_Continue;
}

EventResult BookReadEventHandler::ReceiveEvent(BookRead::Event * evn, EventDispatcher<BookRead::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: BookRead"); //OnRead

    g_bookReadEventRegs.ForEach(
		EventQueueFunctor1<TESObjectBOOK*>(BSFixedString("OnBookRead"), evn->book)
    );  

    return kEvent_Continue;
}

EventResult SkillIncreaseEventHandler::ReceiveEvent(SkillIncrease::Event * evn, EventDispatcher<SkillIncrease::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: SkillIncrease");

    g_skillIncreaseEventRegs.ForEach(
		EventQueueFunctor1<UInt32>(BSFixedString("OnSkillIncrease"), evn->avId)
    );    
    return kEvent_Continue;
}

EventResult LevelIncreaseEventHandler::ReceiveEvent(LevelIncrease::Event * evn, EventDispatcher<LevelIncrease::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LevelIncrease");

    g_levelIncreaseEventRegs.ForEach(
        EventQueueFunctor1<UInt32>(BSFixedString("OnLevelIncrease"), evn->level)
    );    
    return kEvent_Continue;
}

EventResult LocationDiscoveryEventHandler::ReceiveEvent(LocationDiscovery::Event * evn, EventDispatcher<LocationDiscovery::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LocationDiscovery");

	BSFixedString pName = evn->fullname->name;
	
    g_locationDiscoveryEventRegs.ForEach(
		EventQueueFunctor1<BSFixedString>(BSFixedString("OnLocationDiscovery"), pName)
    );

    return kEvent_Continue;
}

EventResult QuestStatusEventHandler::ReceiveEvent(QuestStatus::Event * evn, EventDispatcher<QuestStatus::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: QuestStatus");

	BSFixedString eventName = evn->status ? BSFixedString("OnQuestStarted") : BSFixedString("OnQuestCompleted");

    g_questStatusEventRegs.ForEach(
		 EventQueueFunctor1<TESQuest*>(eventName, evn->quest)
    );

    return kEvent_Continue;
}

EventResult ActorKillEventHandler::ReceiveEvent(ActorKill::Event * evn, EventDispatcher<ActorKill::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: ActorKill"); //OnDeath,

	Actor* pVictim = DYNAMIC_CAST(evn->victim, TESObjectREFR, Actor);
	Actor* pKiller = DYNAMIC_CAST(evn->killer, TESObjectREFR, Actor);

	g_actorKillEventRegs.ForEach(
		EventQueueFunctor2<Actor*, Actor*>(BSFixedString("OnActorKilled"), pVictim, pKiller)
	);

    return kEvent_Continue;
}


EventResult CriticalHitEventHandler::ReceiveEvent(CriticalHit::Event * evn, EventDispatcher<CriticalHit::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: CriticalHit");

	Actor* pSource = DYNAMIC_CAST(evn->character, TESForm, Actor);

    g_criticalHitEventRegs.ForEach(
		EventQueueFunctor2<Actor*, TESObjectWEAP*>(BSFixedString("OnCriticalHit"), pSource, evn->weapon) //PlayerOnly ???
    );  

    return kEvent_Continue;
}

EventResult DisarmedEventHandler::ReceiveEvent(Disarmed::Event * evn, EventDispatcher<Disarmed::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: Disarmed");

	Actor* pTarget = DYNAMIC_CAST(evn->target, TESObjectREFR, Actor);
	Actor* pSource = DYNAMIC_CAST(evn->source, TESObjectREFR, Actor);

    g_disarmedEventRegs.ForEach(
		EventQueueFunctor2<Actor*, Actor*>(BSFixedString("OnDisarmed"), pTarget, pSource) //Player+NPC
    );  

    return kEvent_Continue;
}

EventResult WordLearnedEventHandler::ReceiveEvent(WordLearned::Event * evn, EventDispatcher<WordLearned::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: WordLearned");

    g_wordLearnedEventRegs.ForEach(
		EventQueueFunctor1<TESWordOfPower*>(BSFixedString("OnWordLearned"), evn->word) //PlayerOnly
    );  

    return kEvent_Continue;
}

EventResult SpellsLearnedEventHandler::ReceiveEvent(SpellsLearned::Event * evn, EventDispatcher<SpellsLearned::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: SpellLearned");

	SpellItem* spell = *(SpellItem**)((char*)evn + 29);

    g_spellsLearnedEventRegs.ForEach(
		EventQueueFunctor1<SpellItem*>(BSFixedString("OnSpellLearned"), spell) //PlayerOnly
    );  

    return kEvent_Continue;
}

EventResult DragonSoulGainedEventHandler::ReceiveEvent(DragonSoulGained::Event * evn, EventDispatcher<DragonSoulGained::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: DragonSoulGained");

    g_dragonSoulGainedEventRegs.ForEach(
		EventQueueFunctor1<float>(BSFixedString("OnDragonSoulGained"), evn->souls) //PlayerOnly
    );  

    return kEvent_Continue;
}

EventResult SoulsTrappedEventHandler::ReceiveEvent(SoulsTrapped::Event * evn, EventDispatcher<SoulsTrapped::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: SoulTrapped");

	Actor* pTarget = DYNAMIC_CAST(evn->target, TESObjectREFR, Actor);
	Actor* pPlayer = DYNAMIC_CAST(evn->player, TESObjectREFR, Actor);

    g_soulsTrappedEventRegs.ForEach(
		EventQueueFunctor2<Actor*, Actor*>(BSFixedString("OnSoulTrapped"), pTarget, pPlayer)
    );  

    return kEvent_Continue;
}

EventResult ShoutAttackEventHandler::ReceiveEvent(ShoutAttack::Event * evn, EventDispatcher<ShoutAttack::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: ShoutAttack");

    g_shoutAttackEventRegs.ForEach(
		EventQueueFunctor1<TESShout*>(BSFixedString("OnPlayerShoutAttack"), evn->shout) //PlayerOnly
    );  

    return kEvent_Continue;
}

EventResult LocksPickedEventHandler::ReceiveEvent(LocksPicked::Event * evn, EventDispatcher<LocksPicked::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: LockPicked");

	g_locksPickedEventRegs.ForEach(
		EventQueueFunctor1<TESObjectREFR*>(BSFixedString("OnLockPicked"), g_pickedLock) //PlayerOnly
	);

    return kEvent_Continue;
}

EventResult GrandTheftHorseEventHandler::ReceiveEvent(GrandTheftHorse::Event * evn, EventDispatcher<GrandTheftHorse::Event> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: GrandTheftHorse");

//	TESObjectREFR* horse = *(TESObjectREFR**)((char*)evn + 13);
	Actor* horse = DYNAMIC_CAST(g_stolenHorse, Character, Actor); 

	g_grandTheftHorseEventRegs.ForEach(
		EventQueueFunctor1<Actor*>(BSFixedString("OnHorseSteal"), horse)
	);

    return kEvent_Continue;
}

EventResult FootstepEventHandler::ReceiveEvent(BGSFootstepEvent * evn, EventDispatcher<BGSFootstepEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: FootstepEvent");

    return kEvent_Continue;
}

EventResult UnknownEventHandler::ReceiveEvent(UnknownEvent * evn, EventDispatcher<UnknownEvent> * dispatcher)
{
	_DMESSAGE("ReceiveEvent: %p", dispatcher);

    return kEvent_Continue;
}

}

// ======================================================
// Registration holders
// ======================================================

namespace newEvents
{

RegistrationSetHolder<NullParameters>	g_furnitureEventRegs;
RegistrationSetHolder<NullParameters>	g_lockChangedEventRegs;
RegistrationMapHolder<UInt32>			g_objectLoadedEventRegs;
RegistrationSetHolder<NullParameters>	g_questStageEventRegs;
RegistrationSetHolder<NullParameters>	g_waitEventRegs;

RegistrationSetHolder<NullParameters>	g_harvestEventRegs;
RegistrationSetHolder<NullParameters>	g_locationClearedEventRegs;
RegistrationSetHolder<NullParameters>	g_bookReadEventRegs;
RegistrationSetHolder<NullParameters>	g_skillIncreaseEventRegs;
RegistrationSetHolder<NullParameters>	g_levelIncreaseEventRegs;
RegistrationSetHolder<NullParameters>	g_locationDiscoveryEventRegs;
RegistrationSetHolder<NullParameters>	g_questStatusEventRegs;
RegistrationSetHolder<NullParameters>	g_actorKillEventRegs;
RegistrationSetHolder<NullParameters>	g_criticalHitEventRegs;
RegistrationSetHolder<NullParameters>	g_disarmedEventRegs;
RegistrationSetHolder<NullParameters>	g_wordLearnedEventRegs;
RegistrationSetHolder<NullParameters>	g_spellsLearnedEventRegs;
RegistrationSetHolder<NullParameters>	g_dragonSoulGainedEventRegs;
RegistrationSetHolder<NullParameters>	g_soulsTrappedEventRegs;
RegistrationSetHolder<NullParameters>	g_shoutAttackEventRegs;
RegistrationSetHolder<NullParameters>	g_locksPickedEventRegs;
RegistrationSetHolder<NullParameters>	g_grandTheftHorseEventRegs;

}

// ======================================================
// Event handlers
// ======================================================

namespace newEvents
{

FurnitureEventHandler			g_furnitureEventHandler;
LoadGameEventHandler				g_loadGameEventHandler;
LockChangedEventHandler			g_lockChangedEventHandler;
ObjectLoadedEventHandler			g_objectLoadedEventHandler;
QuestStageEventHandler			g_questStageEventHandler;
WaitStartEventHandler			g_waitStartEventHandler;
WaitStopEventHandler				g_waitStopEventHandler;

HarvestEventHandler				g_harvestEventHandler;
LocationClearedEventHandler		g_locationClearedEventHandler;
BookReadEventHandler				g_bookReadEventHandler;
SkillIncreaseEventHandler		g_skillIncreaseEventHandler;
LevelIncreaseEventHandler		g_levelIncreaseEventHandler;
LocationDiscoveryEventHandler	g_locationDiscoveryEventHandler;
QuestStatusEventHandler			g_questStatusEventHandler;
ActorKillEventHandler			g_actorKillEventHandler;
CriticalHitEventHandler			g_criticalHitEventHandler;
DisarmedEventHandler				g_disarmedEventHandler;
WordLearnedEventHandler			g_wordLearnedEventHandler;
SpellsLearnedEventHandler		g_spellsLearnedEventHandler;
DragonSoulGainedEventHandler	g_dragonSoulGainedEventHandler;
SoulsTrappedEventHandler			g_soulsTrappedEventHandler;
ShoutAttackEventHandler			g_shoutAttackEventHandler;
LocksPickedEventHandler			g_lockPickedEventHandler;
GrandTheftHorseEventHandler		g_grandTheftHorseEventHandler;
FootstepEventHandler				g_footstepEventHandler;

UnknownEventHandler				g_unknownEventHandler;

}

// ======================================================
// Event dispatchers
// ======================================================

namespace newEvents
{

// EventDispatcher<BGSEventProcessedEvent>* g_eventProcessedEventDispatcher = (EventDispatcher<BGSEventProcessedEvent>*)								0x012E4C30;
// EventDispatcher<TESActivateEvent>* g_activateEventDispatcher = (EventDispatcher<TESActivateEvent>*)												0x012E4C60;
// EventDispatcher<TESActiveEffectApplyRemoveEvent>* g_activeEffectApplyRemoveEventDispatcher = (EventDispatcher<TESActiveEffectApplyRemoveEvent>*)	0x012E4C90;
// EventDispatcher<TESActorLocationChangeEvent>* g_actorLocationChangeEventDispatcher = (EventDispatcher<TESActorLocationChangeEvent>*)				0x012E4CC0;
// EventDispatcher<TESBookReadEvent>* g_bookReadEventDispatcher = (EventDispatcher<TESBookReadEvent>*)												0x012E4CF0;
// EventDispatcher<TESCellAttachDetachEvent>* g_cellAttachDetachEventDispatcher = (EventDispatcher<TESCellAttachDetachEvent>*)						0x012E4D20;
// EventDispatcher<TESCellFullyLoadedEvent>* g_cellFullyLoadedEventDispatcher = (EventDispatcher<TESCellFullyLoadedEvent>*)							0x012E4D50;
// EventDispatcher<TESCellReadyToApplyDecalsEvent>* g_cellReadyToApplyDecalsEventDispatcher = (EventDispatcher<TESCellReadyToApplyDecalsEvent>*)		0x012E4D80;
// EventDispatcher<TESCombatEvent>* g_combatEventDispatcher = (EventDispatcher<TESCombatEvent>*)														0x012E4DB0;
// EventDispatcher<TESContainerChangedEvent>* g_containerChangedEventDispatcher = (EventDispatcher<TESContainerChangedEvent>*)						0x012E4DE0;
// EventDispatcher<TESDeathEvent>* g_deathEventDispatcher = (EventDispatcher<TESDeathEvent>*)														0x012E4E10;
// EventDispatcher<TESDestructionStageChangedEvent>* g_destructionStageChangedEventDispatcher = (EventDispatcher<TESDestructionStageChangedEvent>*)	0x012E4E40
// EventDispatcher<TESEnterBleedoutEvent>* g_enterBleedoutEventDispatcher = (EventDispatcher<TESEnterBleedoutEvent>*)								0x012E4E70
// EventDispatcher<TESEquipEvent>* g_equipEventDispatcher = (EventDispatcher<TESEquipEvent>*)														0x012E4EA0
// EventDispatcher<TESFormDeleteEvent>* g_formDeleteEventDispatcher = (EventDispatcher<TESFormDeleteEvent>*)											0x012E4ED0
EventDispatcher<TESFurnitureEvent>* g_furnitureEventDispatcher = (EventDispatcher<TESFurnitureEvent>*)												0x012E4F00;
// EventDispatcher<TESGrabReleaseEvent>* g_Dispatcher = (EventDispatcher<TESGrabReleaseEvent>*)														0x012E4F30;
// EventDispatcher<TESHitEvent>* g_hitEventDispatcher = (EventDispatcher<TESHitEvent>*)																0x012E4F60;
// EventDispatcher<TESInitScriptEvent>* g_initScriptEventDispatcher = (EventDispatcher<TESInitScriptEvent>*)											0x012E4F90;
EventDispatcher<TESLoadGameEvent>* g_loadGameEventDispatcher = (EventDispatcher<TESLoadGameEvent>*)													0x012E4FC0;
EventDispatcher<TESLockChangedEvent>* g_lockChangedEventDispatcher = (EventDispatcher<TESLockChangedEvent>*)											0x012E4FF0;
// EventDispatcher<TESMagicEffectApplyEvent>* g_Dispatcher = (EventDispatcher<TESMagicEffectApplyEvent>*)											0x012E5020;
// EventDispatcher<TESMagicWardHitEvent>* g_Dispatcher = (EventDispatcher<TESMagicWardHitEvent>*)													0x012E5050;
// EventDispatcher<TESMoveAttachDetachEvent>* g_Dispatcher = (EventDispatcher<TESMoveAttachDetachEvent>*)											0x012E5080;
EventDispatcher<TESObjectLoadedEvent>* g_objectLoadedEventDispatcher = (EventDispatcher<TESObjectLoadedEvent>*)										0x012E50B0;
// EventDispatcher<TESObjectREFRTranslationEvent>* g_Dispatcher = (EventDispatcher<TESObjectREFRTranslationEvent>*)									0x012E50E0;
// EventDispatcher<TESOpenCloseEvent>* g_Dispatcher = (EventDispatcher<TESOpenCloseEvent>*)															0x012E5110;
// EventDispatcher<TESPackageEvent>* g_Dispatcher = (EventDispatcher<TESPackageEvent>*)																0x012E5140;
// EventDispatcher<TESPerkEntryRunEvent>* g_Dispatcher = (EventDispatcher<TESPerkEntryRunEvent>*)													0x012E5170;
// EventDispatcher<TESQuestInitEvent>* g_Dispatcher = (EventDispatcher<TESQuestInitEvent>*)															0x012E51A0;
EventDispatcher<TESQuestStageEvent>* g_questStageEventDispatcher = (EventDispatcher<TESQuestStageEvent>*)											0x012E51D0;
// EventDispatcher<TESQuestStageItemDoneEvent>* g_Dispatcher = (EventDispatcher<TESQuestStageItemDoneEvent>*)										0x012E5200;
// EventDispatcher<TESQuestStartStopEvent>* g_Dispatcher = (EventDispatcher<TESQuestStartStopEvent>*)												0x012E5230;
// EventDispatcher<TESResetEvent>* g_Dispatcher = (EventDispatcher<TESResetEvent>*)																	0x012E5260
// EventDispatcher<TESResolveNPCTemplatesEvent>* g_Dispatcher = (EventDispatcher<TESResolveNPCTemplatesEvent>*)										0x012E5290
// EventDispatcher<TESSceneEvent>* g_Dispatcher = (EventDispatcher<TESSceneEvent>*)																	0x012E52C0
// EventDispatcher<TESSceneActionEvent>* g_Dispatcher = (EventDispatcher<TESSceneActionEvent>*)														0x012E52F0
// EventDispatcher<TESScenePhaseEvent>* g_Dispatcher = (EventDispatcher<TESScenePhaseEvent>*)														0x012E5320
// EventDispatcher<TESSellEvent>* g_Dispatcher = (EventDispatcher<TESSellEvent>*)																	0x012E5350
EventDispatcher<TESSleepStartEvent>* g_sleepStartEventDispatcher = (EventDispatcher<TESSleepStartEvent>*)											0x012E4580;
// EventDispatcher<TESSleepStopEvent>* g_Dispatcher = (EventDispatcher<TESSleepStopEvent>*)															0x012E53B0
// EventDispatcher<TESSpellCastEvent>* g_Dispatcher = (EventDispatcher<TESSpellCastEvent>*)															0x012E53E0
// EventDispatcher<TESPlayerBowShotEvent>* g_Dispatcher = (EventDispatcher<>*)																		0x012E5410
// EventDispatcher<TESTopicInfoEvent>* g_Dispatcher = (EventDispatcher<TESPlayerBowShotEvent>*)														0x012E5440
// EventDispatcher<TESTrackedStatsEvent>* g_trackedStatsEventDispatcher = (EventDispatcher<TESTrackedStatsEvent>*)									0x012E5470
// EventDispatcher<TESTrapHitEvent>* g_Dispatcher = (EventDispatcher<TESTrapHitEvent>*)																0x012E54A0
// EventDispatcher<TESTriggerEvent>* g_Dispatcher = (EventDispatcher<TESTriggerEvent>*)																0x012E54D0
// EventDispatcher<TESTriggerEnterEvent>* g_Dispatcher = (EventDispatcher<TESTriggerEnterEvent>*)													0x012E5500
// EventDispatcher<TESTriggerLeaveEvent>* g_Dispatcher = (EventDispatcher<TESTriggerLeaveEvent>*)													0x012E5530
// EventDispatcher<TESUniqueIDChangeEvent>* g_changeUniqueIDEventDispatcher = (EventDispatcher<TESUniqueIDChangeEvent>*)								0x012E5560;
EventDispatcher<TESWaitStartEvent>* g_waitStartEventDispatcher = (EventDispatcher<TESWaitStartEvent>*)												0x012E5590;
EventDispatcher<TESWaitStopEvent>* g_waitStopEventDispatcher =	(EventDispatcher<TESWaitStopEvent>*) 												0x012E55C0;
// EventDispatcher<TESSwitchRaceCompleteEvent>* g_switchRaceCompleteEventDispatcher = (EventDispatcher<TESSwitchRaceCompleteEvent>*)					0x012E55F0;

EventDispatcher<TESHarvestEvent::ItemHarvested>* g_harvestEventDispatcher = (EventDispatcher<TESHarvestEvent::ItemHarvested>*)			0x012E5A74;
// EventDispatcher<Inventory::Event>* g_inventoryEventDispatcher = (EventDispatcher<>*)													0x012E5FB0;
EventDispatcher<BookRead::Event>* g_bookReadEventDispatcher = (EventDispatcher<BookRead::Event>*)										0x012E736C;
EventDispatcher<LocationCleared::Event>* g_locationClearedEventDispatcher = (EventDispatcher<LocationCleared::Event>*)					0x012E7610;
// EventDispatcher<ObjectiveState::Event>* g_objectiveStateEventDispatcher = (EventDispatcher<>*)										0x01B10FE0;
EventDispatcher<QuestStatus::Event>* g_questStatusEventDispatcher = (EventDispatcher<QuestStatus::Event>*)								0x01B113A0;
// EventDispatcher<DaysPassed>* g_daysPassedEventDispatcher = (EventDispatcher<>*)														0x01B2E728;
// EventDispatcher<ActorItemEquipped::Event>* g_actorItemEquippedEventDispatcher = (EventDispatcher<>*)									0x01B38B14;
EventDispatcher<ActorKill::Event>* g_actorKillEventDispatcher = (EventDispatcher<ActorKill::Event>*)										0x01B38B48;
EventDispatcher<Disarmed::Event>* g_disarmedEventDispatcher = (EventDispatcher<Disarmed::Event>*)										0x01B38B7C;
// EventDispatcher<AssaultCrime::Event>* g_assaultCrimeEventDispatcher = (EventDispatcher<>*)											0x01B38BE4;
// EventDispatcher<MurderCrime::Event>* g_murderCrimeEventDispatcher = (EventDispatcher<>*)												0x01B38C18;
EventDispatcher<GrandTheftHorse::Event>* g_grandTheftHorseEventDispatcher = (EventDispatcher<GrandTheftHorse::Event>*)					0x01B38C4C;
EventDispatcher<DragonSoulGained::Event>* g_dragonSoulGainedEventDispatcher = (EventDispatcher<DragonSoulGained::Event>*)				0x01B38F2C;
EventDispatcher<CriticalHit::Event>* g_criticalHitEventDispatcher = (EventDispatcher<CriticalHit::Event>*)								0x01B38FD0;
// EventDispatcher<ContractedDisease::Event>* g_contractedDiseaseEventDispatcher = (EventDispatcher<>*)									0x01B38F9C;
EventDispatcher<SoulsTrapped::Event>* g_soulsTrappedEventDispatcher = (EventDispatcher<SoulsTrapped::Event>*)							0x01B39028;
EventDispatcher<SpellsLearned::Event>* g_spellsLearnedEventDispatcher = (EventDispatcher<SpellsLearned::Event>*)							0x01B3905C;
EventDispatcher<SkillIncrease::Event>* g_skillIncreaseEventDispatcher = (EventDispatcher<SkillIncrease::Event>*)							0x01B397D0;
EventDispatcher<LevelIncrease::Event>* g_levelIncreaseEventDispatcher = (EventDispatcher<LevelIncrease::Event>*)							0x01B39804;
// EventDispatcher<Pickpocket::Event>* g_pickpocketEventDispatcher = (EventDispatcher<>*)												0x01B39AF0;
// EventDispatcher<ItemStolen::Event>* g_itemStolenEventDispatcher = (EventDispatcher<>*													0x01B39B24;
EventDispatcher<LocationDiscovery::Event>* g_locationDiscoveryEventDispatcher = (EventDispatcher<LocationDiscovery::Event>*)				0x01B39B58;
// EventDispatcher<FinesPaid::Event>* g_finesPaidEventDispatcher = (EventDispatcher<>*)													0x01B39B8C;
// EventDispatcher<Jailing::Event>* g_jailingEventDispatcher = (EventDispatcher<>*)														0x01B39BC0;
// EventDispatcher<JailEscape::Event>* g_jailEscapeEventDispatcher = (EventDispatcher<>*)												0x01B39BF4;
// EventDispatcher<Bounty::Event>* g_bountyEventDispatcher = (EventDispatcher<>*)														0x01B39C28;
// EventDispatcher<WeaponAttack::Event>	g_weaponAttackEventDispatcher = (EventDispatcher<>*)												0x01B39C5C;
EventDispatcher<ShoutAttack::Event>* g_shoutAttackEventDispatcher = (EventDispatcher<ShoutAttack::Event>*)								0x01B39C90;
// EventDispatcher<PoisonedWeapon::Event>* g_poisonedWeaponEventDispatcher = (EventDispatcher<>*)										0x01B39CC4;
// EventDispatcher<DaysJailed::Event>* g_daysJailedEventDispatcher = (EventDispatcher<>*)												0x01B39CF8;
EventDispatcher<WordLearned::Event>* g_wordLearnedEventDispatcher = (EventDispatcher<WordLearned::Event>*)								0x01B39D2C;
// EventDispatcher<WordUnlocked::Event>* g_wordUnlockedEventDispatcher = (EventDispatcher<>*)											0x01B39D60;
// EventDispatcher<ShoutMastered::Event>* g_shoutMasteredEventDispatcher = (EventDispatcher<>*)											0x01B39D94;
// EventDispatcher<SpellAttack::Event> g_spellAttackEventDispatcher = (EventDispatcher<>*)												0x01B3B04C;
// EventDispatcher<Trespass::Event>* g_trespassEventDispatcher = (EventDispatcher<>*)													0x01B3B2A8;
// EventDispatcher<TimesBartered::Event>* g_timesBarteredEventDispatcher = (EventDispatcher<>*)											0x01B3E480;
// EventDispatcher<ChestsLooted::Event>* g_chestsLootedEventDispatcher = (EventDispatcher<>*)											0x01B3E788;
// EventDispatcher<ItemsPickpocketed::Event>* g_itemsPickpocketedEventDispatcher = (EventDispatcher<>*)									0x01B3E7BC;
// EventDispatcher<ItemCrafted::Event>* g_itemCraftedEventDispatcher = (EventDispatcher<>*)												0x01B3E7F4;
// EventDispatcher<SoulGemsUsed::Event>* g_soulGemsUsedEventDispatcher = (EventDispatcher<>*)											0x01B3FAC8;
EventDispatcher<LocksPicked::Event>* g_locksPickedEventDispatcher = (EventDispatcher<LocksPicked::Event>*)								0x01B3FBBC;
// EventDispatcher<HourPassed::Event>* g_hourPassedEventDispatcher = (EventDispatcher<>*)												0x01B3FDE4;
// EventDispatcher<TimesTrained::Event>* g_timesTrainedEventDispatcher = (EventDispatcher<>*)											0x01B40130;

// EventDispatcher<DefaultObjectsReadyEvent::Event>																						0x01B107B4;
EventDispatcher<BGSFootstepEvent>* g_footstepEventDispatcher = *(EventDispatcher<BGSFootstepEvent>**)									0x01B2E9C0;
// EventDispatcher<AVInputEvent>*& g_inputEventDispatcher = *(EventDispatcher<AVInputEvent>**)											0x01B2E724;
// BSMusicEvent																															0x01B2E330;
// MenuOpenCloseEvent																													0x01B3E364;
// MenuModeChangeEvent																													0x01B3E394;
// MenuKinect???																															0x01B3E3C4;
// PositionPlayerEvent ?
// UserEventEnabledEvent ?
// BSTEventSink<BSThreadEvent::ThreadEvent>*	 g_threadEventDispatcher	 = *(EventDispatcher<BSThreadEvent::ThreadEvent>*)					0x01B4AE14;

}

// ======================================================
// Event registration
// ======================================================

namespace newEvents
{

void RegisterGameEventHandlers()
{
	_MESSAGE("Registering game event handlers...");

//	g_furnitureEventDispatcher->AddEventSink(&g_furnitureEventHandler);
	g_loadGameEventDispatcher->AddEventSink(&g_loadGameEventHandler);
//	g_lockChangedEventDispatcher->AddEventSink(&g_lockChangedEventHandler);
	g_objectLoadedEventDispatcher->AddEventSink(&g_objectLoadedEventHandler);
//	g_questStageEventDispatcher->AddEventSink(&g_questStageEventHandler);
	g_waitStartEventDispatcher->AddEventSink(&g_waitStartEventHandler);
	g_waitStopEventDispatcher->AddEventSink(&g_waitStopEventHandler);
}

void RegisterStoryEventHandlers()
{
	_MESSAGE("Registering story event handlers...");

	g_harvestEventDispatcher->AddEventSink(&g_harvestEventHandler);
	g_bookReadEventDispatcher->AddEventSink(&g_bookReadEventHandler);
	g_locationClearedEventDispatcher->AddEventSink(&g_locationClearedEventHandler);
	g_skillIncreaseEventDispatcher->AddEventSink(&g_skillIncreaseEventHandler);
	g_levelIncreaseEventDispatcher->AddEventSink(&g_levelIncreaseEventHandler);
//	g_inventoryEventDispatcher
//	g_hourPassedEventDispatcher
//	g_daysPassedEventDispatcher
	g_locationDiscoveryEventDispatcher->AddEventSink(&g_locationDiscoveryEventHandler);
//	g_chestsLootedEventDispatcher
//	g_timesTrainedEventDispatcher
//	g_timesBarteredEventDispatcher 
//	g_contractedDiseaseEventDispatcher
//	g_poisonedWeaponEventDispatcher
	g_questStatusEventDispatcher->AddEventSink(&g_questStatusEventHandler);
//	g_objectiveStateEventDispatcher->AddEventSink(&g_objectiveStateEventHandler);
	g_actorKillEventDispatcher->AddEventSink(&g_actorKillEventHandler);
	g_criticalHitEventDispatcher->AddEventSink(&g_criticalHitEventHandler);
	g_disarmedEventDispatcher->AddEventSink(&g_disarmedEventHandler);
	g_wordLearnedEventDispatcher->AddEventSink(&g_wordLearnedEventHandler);
//	g_wordUnlockedEventDispatcher
	g_spellsLearnedEventDispatcher->AddEventSink(&g_spellsLearnedEventHandler);
	g_dragonSoulGainedEventDispatcher->AddEventSink(&g_dragonSoulGainedEventHandler);
//	g_soulGemsUsedEventDispatcher
	g_soulsTrappedEventDispatcher->AddEventSink(&g_soulsTrappedEventHandler);
	g_shoutAttackEventDispatcher->AddEventSink(&g_shoutAttackEventHandler);
//	g_shoutMasteredEventDispatcher
//	g_actorItemEquippedEventDispatcher
//	g_itemCraftedEventDispatcher
//	g_pickpocketEventDispatcher
	g_locksPickedEventDispatcher->AddEventSink(&g_lockPickedEventHandler);
//	g_bountyEventDispatcher
//	g_trespassEventDispatcher
//	g_finesPaidEventDispatcher
//	g_daysJailedEventDispatcher
//	g_itemsPickpocketedEventDispatcher
//	g_itemStolenEventDispatcher
//	g_jailingEventDispatcher
//	g_jailEscapeEventDispatcher
	g_grandTheftHorseEventDispatcher->AddEventSink(&g_grandTheftHorseEventHandler);
//	g_assaultCrimeEventDispatcher
//	g_murderCrimeEventDispatcher

}

}