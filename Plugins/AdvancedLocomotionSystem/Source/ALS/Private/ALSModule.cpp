// Copyright Epic Games, Inc. All Rights Reserved.

#include "ALSModule.h"

#if WITH_EDITOR
#include "MessageLogModule.h"
#endif

#if ALLOW_CONSOLE
#include "Engine/Console.h"
#endif

#include "Utility/AlsLog.h"

IMPLEMENT_MODULE(FALSModule, ALS)

#define LOCTEXT_NAMESPACE "ALSModule"

void FALSModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FDefaultModuleImpl::StartupModule();
#if ALLOW_CONSOLE
	UConsole::RegisterConsoleAutoCompleteEntries.AddRaw(this, &FALSModule::Console_OnRegisterAutoCompleteEntries);
#endif

#if WITH_EDITOR
	auto& MessageLog{FModuleManager::LoadModuleChecked<FMessageLogModule>(FName{TEXTVIEW("MessageLog")})};

	FMessageLogInitializationOptions Options;
	Options.bShowFilters = true;
	Options.bAllowClear = true;
	Options.bDiscardDuplicates = true;

	MessageLog.RegisterLogListing(AlsLog::MessageLogName, LOCTEXT("MessageLogLabel", "ALS"), Options);
#endif
}

void FALSModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
#if ALLOW_CONSOLE
	UConsole::RegisterConsoleAutoCompleteEntries.RemoveAll(this);
#endif

	FDefaultModuleImpl::ShutdownModule();
}

#if ALLOW_CONSOLE
void FALSModule::Console_OnRegisterAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteCommands)
{
	const auto CommandColor{GetDefault<UConsoleSettings>()->AutoCompleteCommandColor};

	auto* Command{&AutoCompleteCommands.AddDefaulted_GetRef()};
	Command->Command = FString{TEXTVIEW("Stat Als")};
	Command->Desc = FString{TEXTVIEW("Display ALS performance statistics")};
	Command->Color = CommandColor;

	Command = &AutoCompleteCommands.AddDefaulted_GetRef();
	Command->Command = FString{TEXTVIEW("ShowDebug Als.Curves")};
	Command->Desc = FString{TEXTVIEW("Displays animation curves")};
	Command->Color = CommandColor;

	Command = &AutoCompleteCommands.AddDefaulted_GetRef();
	Command->Command = FString{TEXTVIEW("ShowDebug Als.State")};
	Command->Desc = FString{TEXTVIEW("Displays character state")};
	Command->Color = CommandColor;

	Command = &AutoCompleteCommands.AddDefaulted_GetRef();
	Command->Command = FString{TEXTVIEW("ShowDebug Als.Shapes")};
	Command->Desc = FString{TEXTVIEW("Displays debug shapes")};

	Command = &AutoCompleteCommands.AddDefaulted_GetRef();
	Command->Command = FString{TEXTVIEW("ShowDebug Als.Traces")};
	Command->Desc = FString{TEXTVIEW("Displays animation traces")};

	Command = &AutoCompleteCommands.AddDefaulted_GetRef();
	Command->Command = FString{TEXTVIEW("ShowDebug Als.Mantling")};
	Command->Desc = FString{TEXTVIEW("Displays mantling debug")};
	Command->Color = CommandColor;
}
#endif

#undef LOCTEXT_NAMESPACE
