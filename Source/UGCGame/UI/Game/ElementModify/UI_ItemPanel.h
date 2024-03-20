// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_ItemPanel.generated.h"

class UUniformGridPanel;
class UUI_Item;
class UUI_Settings;

/**
 * 
 */
UCLASS()
class UGCGAME_API UUI_ItemPanel : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* ItemArray;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_Item> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_Settings> SettingsClass;

protected:
	virtual void NativeConstruct();

protected:
	void LayoutItem();
};
