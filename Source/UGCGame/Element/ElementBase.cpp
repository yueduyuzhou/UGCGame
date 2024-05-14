// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementBase.h"
#include "Net/UnrealNetwork.h"
#include "../Common/MethodUnit.h"
#include "../Common/UGCGameType.h"
#include "../UGCGamePlayerController.h"
#include "UGCGame/UI/Game/DetailPanel/Details/UI_DetailVector.h"

// Sets default values
AElementBase::AElementBase()
	:bControlled(false)
	,ControllerID(INDEX_NONE)
	, LocationUI(nullptr)
	, RotationUI(nullptr)
	, ScaleUI(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AElementBase::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called every frame
void AElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AUGCGamePlayerState * MyPlayerState = MethodUnit::GetPlayerState(GetWorld()))
	{
		if (MyPlayerState->TPlayerID == ControllerID)
		{
			if (AUGCGamePlayerController * MyPlayerController = MethodUnit::GetPlayerControllerByPlayerID(GetWorld(), ControllerID))
			{
				if (MyPlayerState->GetModifyType() == ETransformationType::TT_Translation)
				{
					FVector TraceStart, Direction;
					MyPlayerController->GetMouseLocationAndDrection(TraceStart, Direction);
					MyPlayerState->UpdateElementLocationOnServer(TraceStart, Direction);
				}
				else if(MyPlayerState->GetModifyType() == ETransformationType::TT_Rotation)
				{
					float RotationX, RotationY;
					MyPlayerController->GetInputMouseDelta(RotationX, RotationY);
					//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("%f %f"), RotationX, RotationY));
					MyPlayerState->UpdateElementRotationOnServer(RotationX, RotationY);
				}
			}
		}
	}

	UpdateVectorUI();
}

void AElementBase::SetElementID(const int32& InElementID)
{
	ID = InElementID;
}

const TArray<EEditDetailType>& AElementBase::GetEditDetails()
{
	return EditDetails;
}

void AElementBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AElementBase, ControllerID);
}

bool AElementBase::TakeControl(const int32& InControlID)
{
	if (InControlID != INDEX_NONE)
	{
		ControllerID = InControlID;
		bControlled = true;

		return true;
	}
	return false;
}

void AElementBase::ReturnControl()
{
	ControllerID = INDEX_NONE;
	bControlled = false;
}

void AElementBase::DestoryElement()
{
	Destroy();
}

void AElementBase::UpdateVectorUI()
{
	if (LocationUI)
	{
		LocationUI->UpdateVectorText(GetActorLocation());
	}
	if (RotationUI)
	{
		RotationUI->UpdateVectorText(GetActorRotation().Vector());
	}
	if (ScaleUI)
	{
		ScaleUI->UpdateVectorText(GetActorScale());
	}
}

void AElementBase::RegisterDetailVectorByType(UUI_DetailVector* InUI)
{
	if (InUI)
	{
		if (InUI->GetDetailType() == EEditDetailType::DETAIL_LOCATION)
		{
			LocationUI = InUI;
		}
		else if (InUI->GetDetailType() == EEditDetailType::DETAIL_ROTATION)
		{
			RotationUI = InUI;
		}
		else if (InUI->GetDetailType() == EEditDetailType::DETAIL_SCALE)
		{
			ScaleUI = InUI;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[class AElementBase]: RegisterDetailVectorByType, InUI Is Null"));
	}
}

