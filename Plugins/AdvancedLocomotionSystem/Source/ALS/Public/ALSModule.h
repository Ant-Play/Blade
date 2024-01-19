// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FAutoCompleteCommand;

class ALS_API FALSModule : public FDefaultModuleImpl
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
#if ALLOW_CONSOLE
	void Console_OnRegisterAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteCommands);
#endif
};
