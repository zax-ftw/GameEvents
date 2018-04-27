#include "skse/PluginAPI.h"
#include "skse/skse_version.h"
#include "skse/PluginManager.h"

#include "skse/GameMenus.h" //remove

#include <shlobj.h>	// CSIDL_MYDOCUMENTS

#include "Events.h"
#include "Hooks.h"
#include "Papyrus.h"
#include "Serialization.h"


IDebugLog		g_Log;
const char*		kLogPath = "\\My Games\\Skyrim\\SKSE\\GameEvents.log";

const char*		PLUGIN_NAME = "GameEvents";
const UInt32		VERSION_MAJOR = 1;
const UInt32		VERSION_MINOR = 0;
const UInt32		VERSION_PATCH = 1;

PluginHandle	 g_pluginHandle = kPluginHandle_Invalid;

SKSEScaleformInterface*			g_scaleform = NULL;
SKSESerializationInterface*		g_serialization = NULL;
SKSEMessagingInterface*			g_messageInterface = NULL;
SKSEPapyrusInterface*			g_papyrus = NULL;

// ======================================================
// Messaging
// ======================================================

namespace newEvents
{

void SKSEMessageHandler(SKSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case SKSEMessagingInterface::kMessage_PostLoad: // dll load
		_DMESSAGE("Message_PostLoad");
		break;

	case SKSEMessagingInterface::kMessage_InputLoaded: //vanilla GameEvents registered 1st time after this
		_DMESSAGE("Message_InputLoaded");
		RegisterGameEventHandlers();
		break;

	case SKSEMessagingInterface::kMessage_DataLoaded: //vanilla StoryEvents registered after this
		_DMESSAGE("Message_DataLoaded");
	//	RegisterStoryEventHandlers(); //error - story dispatchers don't exist yet
		break;

	case SKSEMessagingInterface::kMessage_PreLoadGame:
		_DMESSAGE("Message_PreLoadGame");
	//	DumpPlayerSkills();
		break;

	case SKSEMessagingInterface::kMessage_PostLoadGame: //vanilla GameEvents registered 2nd time after this
		_DMESSAGE("Message_PostLoadGame");
	//	DumpPlayerSkills();
		RegisterStoryEventHandlers(); //workaround
		break;
	
	case SKSEMessagingInterface::kMessage_NewGame: //replaces "PreLoadGame" for new games
		_DMESSAGE("Message_NewGame");
	//	DumpPlayerSkills();
		RegisterStoryEventHandlers(); //workaround
		break;
	}
}

}

// ======================================================
// Initialization
// ======================================================

extern "C"
{

bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	g_Log.OpenRelative(CSIDL_MYDOCUMENTS, kLogPath);
	g_Log.SetPrintLevel(IDebugLog::kLevel_Error);

#ifdef _DEBUG
	g_Log.SetLogLevel(IDebugLog::kLevel_DebugMessage);
#else
	g_Log.SetLogLevel(IDebugLog::kLevel_Message);
#endif

	_MESSAGE("%s %i.%i.%i", PLUGIN_NAME, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =			PLUGIN_NAME;
	info->version =		VERSION_MAJOR;

	// store plugin handle so we can identify ourselves later
	g_pluginHandle = skse->GetPluginHandle();

	if(skse->isEditor)
	{
		_ERROR("loaded in editor, marking as incompatible");

		return false;
	}

	else if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
	{
		_ERROR("unsupported runtime version %08X", skse->runtimeVersion);

		return false;
	}

	// get the serialization interface and query its version
	g_serialization = (SKSESerializationInterface *)skse->QueryInterface(kInterface_Serialization);
	if(!g_serialization)
	{
		_ERROR("couldn't get serialization interface");

		return false;
	}

	if(g_serialization->version < SKSESerializationInterface::kVersion)
	{
		_ERROR("serialization interface too old (%d expected %d)", g_serialization->version, SKSESerializationInterface::kVersion);

		return false;
	}

	//Get the messaging interface and query its version
	g_messageInterface = (SKSEMessagingInterface *)skse->QueryInterface(kInterface_Messaging);
	if(!g_messageInterface)
	{ 
		_ERROR("Couldn't Get Messaging Interface");

		return false; 
	}
	if(g_messageInterface->interfaceVersion < SKSEMessagingInterface::kInterfaceVersion)
	{ 
		_ERROR("messaging interface too old (%d expected %d)", g_messageInterface->interfaceVersion, SKSEMessagingInterface::kInterfaceVersion); 
	
		return false; 
	}

	// supported runtime version
	return true;
}


bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	// register callback for SKSE messaging interface
	g_messageInterface->RegisterListener(g_pluginHandle, "SKSE", newEvents::SKSEMessageHandler);

	g_papyrus = (SKSEPapyrusInterface*)skse->QueryInterface(kInterface_Papyrus); //move to interface function above^

	// register custom papyrus functions
	g_papyrus->Register(newEvents::RegisterFuncs);

	// register callbacks and unique ID for serialization
	g_serialization->SetUniqueID(g_pluginHandle, 'EVNT');

	g_serialization->SetRevertCallback(g_pluginHandle, newEvents::Serialization_Revert);
	g_serialization->SetSaveCallback(g_pluginHandle, newEvents::Serialization_Save);
	g_serialization->SetLoadCallback(g_pluginHandle, newEvents::Serialization_Load);

	WriteHooks();

	return true;
}

};
