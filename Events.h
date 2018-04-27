#pragma once

#include "skse/GameObjects.h"
#include "skse/GameReferences.h"
#include "skse/PapyrusEvents.h"


// ======================================================
// New Structures
// ======================================================

namespace newEvents
{

struct TESFurnitureEvent
{
	TESObjectREFR*	character;
	TESObjectREFR*	furniture;
	UInt32			state;
};

struct TESLoadGameEvent
{
	// empty
};

struct TESLockChangedEvent
{
	TESObjectREFR*	lock;
	TESObjectREFR*	unlocker;
};

struct TESObjectLoadedEvent
{
	UInt32	formId;
	UInt8	loaded;
};

struct TESQuestInitEvent
{
	UInt32	formId;
};

struct TESQuestStageEvent
{
	void*	finishedCallback;
	UInt32	formId;
	UInt32	stage;
};

struct TESQuestStartStopEvent
{
	UInt32	formId;
};

struct TESTrackedStatsEvent
{
	BSFixedString	statName;
	UInt32			newValue;
};

struct TESWaitStartEvent
{
	float current;
	float desired;
};

struct TESWaitStopEvent
{
	//empty?
};

struct TESSwitchRaceCompleteEvent
{
	Actor* actor;
};


struct TESHarvestEvent
{
	struct ItemHarvested
	{
		TESForm*	 object;
		TESForm*	 player;
	};
};

struct LocationCleared
{
	struct Event
	{
		//empty?
	};
};

struct BookRead
{
	struct Event
	{
		TESObjectBOOK* book;
	};
};

struct SkillIncrease	
{
	struct Event
	{
		TESForm*		character;
		UInt32		avId;
	};
};

struct LevelIncrease
{
	struct Event
	{
		TESForm*		character;
		UInt32		level;
	};
};

struct Inventory
{
	struct Event
	{
		TESForm*	 character;
	};
};

struct HourPassed
{
	struct Event
	{
		UInt32 sleep;
	};
};

struct LocationDiscovery
{	
	struct Event
	{
		TESFullName*	 fullname;
	};
};

struct QuestStatus
{
	struct Event
	{
		UInt32		status;	
		TESQuest*	quest;
	};
};

struct ActorKill
{	
	struct Event
	{
		TESObjectREFR*	killer;
		TESObjectREFR*	victim;
	};
};

struct CriticalHit
{
	struct Event
	{
		TESForm*		character;
		TESObjectWEAP*	weapon;
	};
};

struct Disarmed
{
	struct Event
	{
		TESObjectREFR*	source;
		TESObjectREFR*	target;
	};
};

struct WordLearned
{
	struct Event
	{
		UInt32	first; //flag
		UInt32	unk;
		TESWordOfPower*	word;
	};
};

struct SpellsLearned
{
	struct Event
	{
		//empty?
	};
};

struct DragonSoulGained
{
	struct Event
	{
		float	souls;
	};
};

struct SoulsTrapped
{
	struct Event
	{
		TESObjectREFR*	player;
		TESObjectREFR*	target;
	};
};

struct WeaponAttack
{	
	struct Event
	{
		TESObjectWEAP	weapon; 
		Character		wielder; //unk
		
	};
};

struct ShoutAttack
{
	struct Event
	{
		TESShout*	shout;
	};
};

struct LocksPicked
{
	struct Event
	{
		//empty?
	};
};

struct Bounty
{
	struct Event
	{
		TESFaction*	faction;
		UInt32		before;
		UInt32		after;
	};
};

struct DaysJailed
{
	struct Event
	{
		UInt32	days;
		BGSLocation*	 location;
		TESFaction*	 faction;
		UInt32	bounty;
	};
};

struct GrandTheftHorse
{
	struct Event
	{
		//empty?
	};
};

struct AssaultCrime
{
	struct Event
	{
		UInt8	pad;
		TESObjectREFR*	target;
	};
};

struct MurderCrime
{
	struct Event
	{
		UInt8	pad;
		TESObjectREFR*	source;
		TESObjectREFR*	target;
	};
};

struct DefaultObjectsReadyEvent
{	
	struct Event
	{
		//g_defaultObjectManager ?
	};
};

struct BGSFootstepEvent
{
	UInt32	actorHandle;
};

struct UnknownEvent
{
	// for testing
};

}

// ======================================================
// Templates
// ======================================================

namespace newEvents
{

template <>
class BSTEventSink <TESFurnitureEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESFurnitureEvent * evn, EventDispatcher<TESFurnitureEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESLoadGameEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESLoadGameEvent * evn, EventDispatcher<TESLoadGameEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESLockChangedEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESLockChangedEvent * evn, EventDispatcher<TESLockChangedEvent> * dispatcher) = 0;
};
	
template <>
class BSTEventSink <TESObjectLoadedEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESObjectLoadedEvent * evn, EventDispatcher<TESObjectLoadedEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESQuestStageEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESQuestStageEvent * evn, EventDispatcher<TESQuestStageEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESWaitStartEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESWaitStartEvent * evn, EventDispatcher<TESWaitStartEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESWaitStopEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESWaitStopEvent * evn, EventDispatcher<TESWaitStopEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <TESHarvestEvent::ItemHarvested>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(TESHarvestEvent::ItemHarvested * evn, EventDispatcher<TESHarvestEvent::ItemHarvested> * dispatcher) = 0;
};

template <>
class BSTEventSink <LocationCleared::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(LocationCleared::Event * evn, EventDispatcher<LocationCleared::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <BookRead::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(BookRead::Event * evn, EventDispatcher<BookRead::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <SkillIncrease::Event>
{
public:
    virtual ~BSTEventSink() {}; // todo?
    virtual    EventResult ReceiveEvent(SkillIncrease::Event * evn, EventDispatcher<SkillIncrease::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <LevelIncrease::Event>
{
public:
    virtual ~BSTEventSink() {}; // todo?
    virtual    EventResult ReceiveEvent(LevelIncrease::Event * evn, EventDispatcher<LevelIncrease::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <LocationDiscovery::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(LocationDiscovery::Event * evn, EventDispatcher<LocationDiscovery::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <QuestStatus::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(QuestStatus::Event * evn, EventDispatcher<QuestStatus::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <ActorKill::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(ActorKill::Event * evn, EventDispatcher<ActorKill::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <CriticalHit::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(CriticalHit::Event * evn, EventDispatcher<CriticalHit::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <Disarmed::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(Disarmed::Event * evn, EventDispatcher<Disarmed::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <WordLearned::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(WordLearned::Event * evn, EventDispatcher<WordLearned::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <SpellsLearned::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(SpellsLearned::Event * evn, EventDispatcher<SpellsLearned::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <DragonSoulGained::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(DragonSoulGained::Event * evn, EventDispatcher<DragonSoulGained::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <SoulsTrapped::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(SoulsTrapped::Event * evn, EventDispatcher<SoulsTrapped::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <ShoutAttack::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(ShoutAttack::Event * evn, EventDispatcher<ShoutAttack::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <LocksPicked::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(LocksPicked::Event * evn, EventDispatcher<LocksPicked::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <GrandTheftHorse::Event>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(GrandTheftHorse::Event * evn, EventDispatcher<GrandTheftHorse::Event> * dispatcher) = 0;
};

template <>
class BSTEventSink <BGSFootstepEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(BGSFootstepEvent * evn, EventDispatcher<BGSFootstepEvent> * dispatcher) = 0;
};

template <>
class BSTEventSink <UnknownEvent>
{
public:
	virtual ~BSTEventSink() {}	// todo?
	virtual	EventResult ReceiveEvent(UnknownEvent * evn, EventDispatcher<UnknownEvent> * dispatcher) = 0;
};


}

// ======================================================
// Event Handlers
// ======================================================

namespace newEvents
{

/*
	TESActivateEvent
	TESActiveEffectApplyRemoveEvent
	TESActorLocationChangeEvent
	BookRead::Event
	TESCellAttachDetachEvent
	TESCellFullyLoadedEvent
	TESCombatEvent
	TESContainerChangedEvent
	TESDeathEvent
	TESDestructionStageChangedEvent
	TESEnterBleedoutEvent
	TESEquipEvent
	TESFormDeleteEvent
*/

class FurnitureEventHandler : public BSTEventSink <TESFurnitureEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESFurnitureEvent * evn, EventDispatcher<TESFurnitureEvent> * dispatcher);
};

/*
	TESGrabReleaseEvent
	TESHitEvent
	TESInitScriptEvent
*/

class LoadGameEventHandler : public BSTEventSink <TESLoadGameEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESLoadGameEvent * evn, EventDispatcher<TESLoadGameEvent> * dispatcher);
};

class LockChangedEventHandler : public BSTEventSink <TESLockChangedEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESLockChangedEvent * evn, EventDispatcher<TESLockChangedEvent> * dispatcher);
};

/*
	TESMagicEffectApplyEvent
	TESMagicWardHitEvent
	TESMoveAttachDetachEvent	
*/

class ObjectLoadedEventHandler : public BSTEventSink <TESObjectLoadedEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESObjectLoadedEvent * evn, EventDispatcher<TESObjectLoadedEvent> * dispatcher);
};

/*
	TESObjectREFRTranslationEvent
	TESOpenCloseEvent
	TESPackageEvent
	TESPerkEntryRunEvent
	TESQuestInitEvent
*/

class QuestStageEventHandler : public BSTEventSink <TESQuestStageEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESQuestStageEvent * evn, EventDispatcher<TESQuestStageEvent> * dispatcher);
};

/*
	TESResetEvent
	TESResolveNPCTemplatesEvent
	TESSceneEvent
	TESSceneActionEvent
	TESScenePhaseEvent
	TESSellEvent
	TESSleepStartEvent
	TESSleepStopEvent
	TESSpellCastEvent
	TESPlayerBowShotEvent
	TESTopicInfoEvent
	TESTrackedStatsEvent
	TESTrapHitEvent
	TESTriggerEvent
	TESTriggerEnterEvent
	TESTriggerLeaveEvent
	TESUniqueIDChangeEvent
*/

class WaitStartEventHandler : public BSTEventSink <TESWaitStartEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESWaitStartEvent * evn, EventDispatcher<TESWaitStartEvent> * dispatcher);
};

class WaitStopEventHandler : public BSTEventSink <TESWaitStopEvent>
{
public:
    virtual		EventResult    ReceiveEvent(TESWaitStopEvent * evn, EventDispatcher<TESWaitStopEvent> * dispatcher);
};

/*
	TESSwitchRaceCompleteEvent

*/

class HarvestEventHandler : public BSTEventSink <TESHarvestEvent::ItemHarvested>
{
public:
    virtual		EventResult    ReceiveEvent(TESHarvestEvent::ItemHarvested * evn, EventDispatcher<TESHarvestEvent::ItemHarvested> * dispatcher);
};

class LocationClearedEventHandler : public BSTEventSink <LocationCleared::Event>
{
public:
    virtual		EventResult    ReceiveEvent(LocationCleared::Event * evn, EventDispatcher<LocationCleared::Event> * dispatcher);
};

class BookReadEventHandler : public BSTEventSink <BookRead::Event>
{
public:
    virtual		EventResult    ReceiveEvent(BookRead::Event * evn, EventDispatcher<BookRead::Event> * dispatcher);
};

class SkillIncreaseEventHandler : public BSTEventSink <SkillIncrease::Event>
{
public:
    virtual		EventResult    ReceiveEvent(SkillIncrease::Event * evn, EventDispatcher<SkillIncrease::Event> * dispatcher);
};

class LevelIncreaseEventHandler : public BSTEventSink <LevelIncrease::Event>
{
public:
    virtual		EventResult    ReceiveEvent(LevelIncrease::Event * evn, EventDispatcher<LevelIncrease::Event> * dispatcher);
};

/*
	Inventory
	HourPassed
	DaysPassed
*/

class LocationDiscoveryEventHandler : public BSTEventSink <LocationDiscovery::Event>
{
public:
    virtual		EventResult    ReceiveEvent(LocationDiscovery::Event * evn, EventDispatcher<LocationDiscovery::Event> * dispatcher);
};

/*
	ChestsLooted
	TimesTrained
	TimesBartered
	ContractedDisease
	PoisonedWeapon
*/

class QuestStatusEventHandler : public BSTEventSink <QuestStatus::Event>
{
public:
    virtual		EventResult		ReceiveEvent(QuestStatus::Event * evn, EventDispatcher<QuestStatus::Event> * dispatcher);
};

/*
	ObjectiveState
*/

class ActorKillEventHandler : public BSTEventSink <ActorKill::Event>
{
public:
    virtual		EventResult		ReceiveEvent(ActorKill::Event * evn, EventDispatcher<ActorKill::Event> * dispatcher);
};

class CriticalHitEventHandler : public BSTEventSink <CriticalHit::Event>
{
public:
	virtual		EventResult		ReceiveEvent(CriticalHit::Event * evn, EventDispatcher<CriticalHit::Event> * dispatcher);
};

class DisarmedEventHandler : public BSTEventSink <Disarmed::Event>
{
public:
	virtual		EventResult		ReceiveEvent(Disarmed::Event * evn, EventDispatcher<Disarmed::Event> * dispatcher);
};

class WordLearnedEventHandler : public BSTEventSink <WordLearned::Event>
{
public:
	virtual		EventResult		ReceiveEvent(WordLearned::Event * evn, EventDispatcher<WordLearned::Event> * dispatcher);
};

/*
	WordUnlocked
*/

class SpellsLearnedEventHandler : public BSTEventSink <SpellsLearned::Event>
{
public:
	virtual		EventResult		ReceiveEvent(SpellsLearned::Event * evn, EventDispatcher<SpellsLearned::Event> * dispatcher);
};

class DragonSoulGainedEventHandler : public BSTEventSink <DragonSoulGained::Event>
{
public:
	virtual		EventResult		ReceiveEvent(DragonSoulGained::Event * evn, EventDispatcher<DragonSoulGained::Event> * dispatcher);
};

/*
	SoulGemsUsed
*/

class SoulsTrappedEventHandler : public BSTEventSink <SoulsTrapped::Event>
{
public:
	virtual		EventResult		ReceiveEvent(SoulsTrapped::Event * evn, EventDispatcher<SoulsTrapped::Event> * dispatcher);
};

class ShoutAttackEventHandler : public BSTEventSink <ShoutAttack::Event>
{
public:
	virtual		EventResult		ReceiveEvent(ShoutAttack::Event * evn, EventDispatcher<ShoutAttack::Event> * dispatcher);
};

/*
	ShoutMastered
	...
	...
*/

class LocksPickedEventHandler : public BSTEventSink <LocksPicked::Event>
{
public:
    virtual    EventResult		ReceiveEvent(LocksPicked::Event * evn, EventDispatcher<LocksPicked::Event> * dispatcher);
};

/*
	...
	...
	JailEscape
*/

class GrandTheftHorseEventHandler : public BSTEventSink <GrandTheftHorse::Event>
{
public:
    virtual    EventResult		ReceiveEvent(GrandTheftHorse::Event * evn, EventDispatcher<GrandTheftHorse::Event> * dispatcher);
};

class FootstepEventHandler : public BSTEventSink <BGSFootstepEvent>
{
public:
	 virtual    EventResult		 ReceiveEvent(BGSFootstepEvent * evn, EventDispatcher<BGSFootstepEvent> * dispatcher);

};

class UnknownEventHandler : public BSTEventSink <UnknownEvent>
{
public:
    virtual    EventResult		ReceiveEvent(UnknownEvent * evn, EventDispatcher<UnknownEvent> * dispatcher);
};

}

// ======================================================
// Registration holders
// ======================================================

namespace newEvents
{

extern RegistrationSetHolder<NullParameters>	 g_furnitureEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_lockChangedEventRegs;
extern RegistrationMapHolder<UInt32>	 g_objectLoadedEventRegs;
extern RegistrationSetHolder<NullParameters> g_questStageEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_waitEventRegs;

extern RegistrationSetHolder<NullParameters>	 g_harvestEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_locationClearedEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_bookReadEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_skillIncreaseEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_levelIncreaseEventRegs;
extern RegistrationSetHolder<NullParameters> g_locationDiscoveryEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_questStatusEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_actorKillEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_criticalHitEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_disarmedEventRegs;
extern RegistrationSetHolder<NullParameters> g_wordLearnedEventRegs;
extern RegistrationSetHolder<NullParameters> g_spellsLearnedEventRegs;
extern RegistrationSetHolder<NullParameters> g_dragonSoulGainedEventRegs;
extern RegistrationSetHolder<NullParameters> g_soulsTrappedEventRegs;
extern RegistrationSetHolder<NullParameters> g_shoutAttackEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_locksPickedEventRegs;
extern RegistrationSetHolder<NullParameters>	 g_grandTheftHorseEventRegs;

}

// ======================================================
// Event handlers
// ======================================================

namespace newEvents
{

extern FurnitureEventHandler				g_furnitureEventHandler;
extern LockChangedEventHandler			g_lockChangedEventHandler;
extern ObjectLoadedEventHandler			g_objectLoadedEventHandler;
extern QuestStageEventHandler			g_questStageEventHandler;
extern WaitStartEventHandler				g_waitStartEventHandler;
extern WaitStopEventHandler				g_waitStopEventHandler;

extern HarvestEventHandler				g_harvestEventHandler;
extern LocationClearedEventHandler		g_locationClearedEventHandler;
extern BookReadEventHandler				g_bookReadEventHandler;
extern SkillIncreaseEventHandler			g_skillIncreaseEventHandler;
extern LevelIncreaseEventHandler			g_levelIncreaseEventHandler;
extern LocationDiscoveryEventHandler		g_locationDiscoveryEventHandler;
extern QuestStatusEventHandler			g_questStatusEventHandler;
extern ActorKillEventHandler				g_actorKillEventHandler;
extern CriticalHitEventHandler			g_criticalHitEventHandler;
extern DisarmedEventHandler				g_disarmedEventHandler;
extern WordLearnedEventHandler			g_wordLearnedEventHandler;
extern SpellsLearnedEventHandler			g_spellsLearnedEventHandler;
extern DragonSoulGainedEventHandler		g_dragonSoulGainedEventHandler;
extern SoulsTrappedEventHandler			g_soulsTrappedEventHandler;
extern ShoutAttackEventHandler			g_shoutAttackEventHandler;
extern LocksPickedEventHandler			g_lockPickedEventHandler;
extern GrandTheftHorseEventHandler		g_grandTheftHorseEventHandler;
extern FootstepEventHandler				g_footstepEventHandler;

extern UnknownEventHandler				g_unknownEventHandler;

void RegisterGameEventHandlers();
void RegisterStoryEventHandlers();

}

// ======================================================
// Event dispatchers
// ======================================================

namespace newEvents
{

extern EventDispatcher<TESFurnitureEvent>* g_furnitureEventDispatcher;
extern EventDispatcher<TESLoadGameEvent>* g_loadGameEventDispatcher;
extern EventDispatcher<TESLockChangedEvent>* g_lockChangedEventDispatcher;
extern EventDispatcher<TESObjectLoadedEvent> * g_objectLoadedEventDispatcher;
extern EventDispatcher<TESQuestStageEvent> * g_questStageEventDispatcher;
extern EventDispatcher<TESWaitStartEvent> * g_waitStartEventDispatcher;
extern EventDispatcher<TESWaitStopEvent> * g_waitStopEventDispatcher;

extern EventDispatcher<TESHarvestEvent::ItemHarvested> * g_harvestEventDispatcher;
extern EventDispatcher<LocationCleared::Event>* g_locationClearedEventDispatcher;
extern EventDispatcher<BookRead::Event>* g_bookReadEventDispatcher;
extern EventDispatcher<SkillIncrease::Event>* g_skillIncreaseEventDispatcher;
extern EventDispatcher<LevelIncrease::Event>* g_levelIncreaseEventDispatcher;
extern EventDispatcher<LocationDiscovery::Event>* g_locationDiscoveryEventDispatcher;
extern EventDispatcher<QuestStatus::Event>* g_questStatusEventDispatcher;
extern EventDispatcher<ActorKill::Event>* g_actorKillEventDispatcher;
extern EventDispatcher<CriticalHit::Event>* g_criticalHitEventDispatcher;
extern EventDispatcher<Disarmed::Event>* g_disarmedEventDispatcher;
extern EventDispatcher<WordLearned::Event>* g_wordLearnedEventDispatcher;
extern EventDispatcher<SpellsLearned::Event>* g_spellsLearnedEventDispatcher;
extern EventDispatcher<DragonSoulGained::Event>* g_dragonSoulGainedEventDispatcher;
extern EventDispatcher<SoulsTrapped::Event>* g_soulsTrappedEventDispatcher;
extern EventDispatcher<ShoutAttack::Event>* g_shoutAttackEventDispatcher;
extern EventDispatcher<LocksPicked::Event>* g_locksPickedEventDispatcher;
extern EventDispatcher<GrandTheftHorse::Event>* g_grandTheftHorseEventDispatcher;

extern EventDispatcher<BGSFootstepEvent>* g_footstepEventDispatcher;

}