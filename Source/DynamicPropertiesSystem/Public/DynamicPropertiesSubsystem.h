// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/UnrealTypePrivate.h"

#include "DynamicPropertiesSubsystem.generated.h"

UCLASS()
class DYNAMICPROPERTIESSYSTEM_API UDynamicPropertiesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	static UDynamicPropertiesSubsystem* Get();

	template<typename T>
	static bool GetStructProperty(UObject* Object, FName PropertyName, T& PropertyValue);

	template<typename T>
	static bool SetStructProperty(UObject* Object, FName PropertyName, T Value);

	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool GetNumericProperty(UObject* Object, FName PropertyName, float& PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool GetVectorProperty(UObject* Object, FName PropertyName, FVector& PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool GetVector2DProperty(UObject* Object, FName PropertyName, FVector2D& PropertyValue);

	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool SetNumericProperty(UObject* Object, FName PropertyName, float Value);
	
	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool SetVectorProperty(UObject* Object, FName PropertyName, FVector Value);

	UFUNCTION(BlueprintCallable, Category = "DynamicProperties")
	static bool SetVector2DProperty(UObject* Object, FName PropertyName, FVector2D Value);
};

template <typename T>
bool UDynamicPropertiesSubsystem::GetStructProperty(UObject* Object, FName PropertyName, T& PropertyValue)
{
	if(!Object) return false;

	FProperty* Property = Object->GetClass()->FindPropertyByName(PropertyName);
	if(!Property) return false;

	if(const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
	{
		if (StructProperty->Struct == TBaseStructure<T>::Get())
		{
			PropertyValue = *StructProperty->ContainerPtrToValuePtr<T>(Object);

			return true;
		}

		return false;
	}
	
	return  false;
}

template <typename T>
bool UDynamicPropertiesSubsystem::SetStructProperty(UObject* Object, FName PropertyName, T Value)
{
	if(!Object) return false;

	FProperty* Property = Object->GetClass()->FindPropertyByName(PropertyName);
	if(!Property) return false;

	if(FStructProperty* StructProp = CastField<FStructProperty>(Property))
	{
		if (StructProp->Struct == TBaseStructure<T>::Get())
		{
			T* ValuePtr = StructProp->ContainerPtrToValuePtr<T>(Object);
			*ValuePtr = Value;

			return true;
		}

		return false;
	}
	
	return  false;
}
