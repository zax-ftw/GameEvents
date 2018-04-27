#include "Serialization.h"
#include "Events.h"


const UInt32 kSerializationDataVersion = 1;

namespace newEvents
{

void Serialization_Revert(SKSESerializationInterface * intfc)
{
	_MESSAGE("Reverting event registrations...");
/*
	g_furnitureEventRegs.Clear();
	g_lockChangedEventRegs.Clear();
*/
	g_objectLoadedEventRegs.Clear();
	g_questStageEventRegs.Clear();
	g_waitEventRegs.Clear();

	g_harvestEventRegs.Clear();
	g_locationClearedEventRegs.Clear();
	g_bookReadEventRegs.Clear();
	g_skillIncreaseEventRegs.Clear();
	g_levelIncreaseEventRegs.Clear();
	g_locationDiscoveryEventRegs.Clear();
	g_questStatusEventRegs.Clear();
	g_actorKillEventRegs.Clear();
	g_criticalHitEventRegs.Clear();
	g_disarmedEventRegs.Clear();
	g_wordLearnedEventRegs.Clear();
	g_spellsLearnedEventRegs.Clear();
	g_dragonSoulGainedEventRegs.Clear();
	g_soulsTrappedEventRegs.Clear();
	g_shoutAttackEventRegs.Clear();
	g_locksPickedEventRegs.Clear();
	g_grandTheftHorseEventRegs.Clear();
}

void Serialization_Save(SKSESerializationInterface * intfc)
{
	_MESSAGE("Saving event registrations...");
/*
	g_furnitureEventRegs.Save(intfc, 'FURN', kSerializationDataVersion);
	g_lockChangedEventRegs.Save(intfc, 'LCKC', kSerializationDataVersion);
*/
	g_objectLoadedEventRegs.Save(intfc, 'LOAD', kSerializationDataVersion);
	g_questStageEventRegs.Save(intfc, 'STGE', kSerializationDataVersion);
	g_waitEventRegs.Save(intfc, 'WAIT', kSerializationDataVersion);

	g_harvestEventRegs.Save(intfc, 'HVST', kSerializationDataVersion);
	g_locationClearedEventRegs.Save(intfc, 'CLRD', kSerializationDataVersion);
	g_bookReadEventRegs.Save(intfc, 'BOOK', kSerializationDataVersion);
	g_skillIncreaseEventRegs.Save(intfc, 'SKIL', kSerializationDataVersion);
	g_levelIncreaseEventRegs.Save(intfc, 'LVLU', kSerializationDataVersion);
	g_locationDiscoveryEventRegs.Save(intfc, 'DISC', kSerializationDataVersion);
	g_questStatusEventRegs.Save(intfc, 'QSTS', kSerializationDataVersion);
	g_actorKillEventRegs.Save(intfc, 'KILL', kSerializationDataVersion);
	g_criticalHitEventRegs.Save(intfc, 'CRIT', kSerializationDataVersion);
	g_disarmedEventRegs.Save(intfc, 'DSRM', kSerializationDataVersion);
	g_wordLearnedEventRegs.Save(intfc, 'WORD', kSerializationDataVersion);
	g_spellsLearnedEventRegs.Save(intfc, 'SPEL', kSerializationDataVersion);
	g_dragonSoulGainedEventRegs.Save(intfc, 'DRGN', kSerializationDataVersion);
	g_soulsTrappedEventRegs.Save(intfc, 'SOUL', kSerializationDataVersion);
	g_shoutAttackEventRegs.Save(intfc, 'SHOU', kSerializationDataVersion);
	g_locksPickedEventRegs.Save(intfc, 'LOCK', kSerializationDataVersion);
	g_grandTheftHorseEventRegs.Save(intfc, 'HRSE', kSerializationDataVersion);
}

void Serialization_Load(SKSESerializationInterface * intfc)
{
	_MESSAGE("Loading event registrations...");

	UInt32 type, version, length;

	while (intfc->GetNextRecordInfo(&type, &version, &length))
	{
		switch (type)
		{
/*
		case 'FURN':
			g_furnitureEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'LCKC':
			g_lockChangedEventRegs.Load(intfc, kSerializationDataVersion);
			break;
*/
		case 'LOAD':
			g_objectLoadedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'STGE':
			g_questStageEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'WAIT':
			g_waitEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'HVST':
			g_harvestEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'CLRD':
			g_locationClearedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'BOOK':
			g_bookReadEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'SKIL':
			g_skillIncreaseEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'LVLU':
			g_levelIncreaseEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'DISC':
			g_locationDiscoveryEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'QSTS':
			g_questStatusEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'KILL':
			g_actorKillEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'CRIT':
			g_criticalHitEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'DSRM':
			g_disarmedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'WORD':
			g_wordLearnedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'SPEL':
			g_spellsLearnedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'DRGN':
			g_dragonSoulGainedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'SOUL':
			g_soulsTrappedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'SHOU':
			g_shoutAttackEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'LOCK':
			g_locksPickedEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		case 'HRSE':
			g_grandTheftHorseEventRegs.Load(intfc, kSerializationDataVersion);
			break;

		default:
			_WARNING("Unhandled chunk type in Serialization_Load: %08X (%.4s)", type, &type);
			continue;
		}
	}
}

}