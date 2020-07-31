// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BouncePanel.h"
#include "ButtonBouncePanel.generated.h"

/**
 * 
 */
UCLASS()
class TRICKSHOT_API AButtonBouncePanel : public ABouncePanel
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Name")
	FString PanelName;

	virtual void BeginPlay() override;

	void TeleLocationOne();
	void TeleLocationTwo();

	FVector Location1;
	FVector Location2;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_X;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_Y;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float m_Z;
	
};
