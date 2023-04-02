#pragma once
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
namespace bbKeys
{
	TCHAR const* const BrakeIntensity = TEXT("BrakeIntensity");
	TCHAR const* const UrgentLeft = TEXT("UrgentTurnLeft");
	TCHAR const* const UrgentRight = TEXT("UrgentTurnRight");
	TCHAR const* const AmountofTurn = TEXT("AmountTurned");
	TCHAR const* const ForceofTurn = TEXT("ForceOfTurn");
	TCHAR const* const TotalForceofTurn = TEXT("TotalForceTurned");

	TCHAR const* const CornerLeft = TEXT("CornerTurnLeft");
	TCHAR const* const CornerRight = TEXT("CornerTurnRight");
	TCHAR const* const OvertakeRight = TEXT("OvertakeRight");
	TCHAR const* const OvertakeLeft = TEXT("OvertakeLeft");
	TCHAR const* const Accelerate = TEXT("Accelerate");
	TCHAR const* const Brake = TEXT("Brake");

	TCHAR const* const Loop = TEXT("IsOnLoop");

	TCHAR const* const ItemText = TEXT("ItemName");

}