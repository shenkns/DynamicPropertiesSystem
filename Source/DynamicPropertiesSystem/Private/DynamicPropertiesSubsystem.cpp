// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicPropertiesSubsystem.h"

UDynamicPropertiesSubsystem* UDynamicPropertiesSubsystem::Get()
{
	return GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UDynamicPropertiesSubsystem>();
}

bool UDynamicPropertiesSubsystem::GetNumericProperty(UObject* Object, FName PropertyName, float& PropertyValue)
{
	if(!Object) return false;

	FProperty* Property = Object->GetClass()->FindPropertyByName(PropertyName);
	if(!Property) return false;

	if(const FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
	{
		if(const FIntProperty* IntProperty = CastField<FIntProperty>(NumericProperty))
		{
			PropertyValue = IntProperty->GetPropertyValue_InContainer(Object);

			return true;
		}

		if(const FFloatProperty* FloatProperty = CastField<FFloatProperty>(NumericProperty))
		{
			PropertyValue = FloatProperty->GetPropertyValue_InContainer(Object);

			return true;
		}

		if(const FDoubleProperty* DoubleProperty = CastField<FDoubleProperty>(NumericProperty))
		{
			PropertyValue = DoubleProperty->GetPropertyValue_InContainer(Object);

			return true;
		}
		
		return false;
	}
	
	return  false;
}

bool UDynamicPropertiesSubsystem::GetVectorProperty(UObject* Object, FName PropertyName, FVector& PropertyValue)
{
	return GetStructProperty<FVector>(Object, PropertyName, PropertyValue);
}

bool UDynamicPropertiesSubsystem::GetVector2DProperty(UObject* Object, FName PropertyName, FVector2D& PropertyValue)
{
	return GetStructProperty<FVector2D>(Object, PropertyName, PropertyValue);
}

bool UDynamicPropertiesSubsystem::SetNumericProperty(UObject* Object, FName PropertyName, float Value)
{
	if(!Object) return false;

	FProperty* Property = Object->GetClass()->FindPropertyByName(PropertyName);
	if(!Property) return false;

	if(const FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property))
	{
		float* ValuePtr = NumericProperty->ContainerPtrToValuePtr<float>(Object);
		NumericProperty->SetFloatingPointPropertyValue(ValuePtr, Value);

		return true;
	}

	return false;
}

bool UDynamicPropertiesSubsystem::SetVectorProperty(UObject* Object, FName PropertyName, FVector Value)
{
	return SetStructProperty<FVector>(Object, PropertyName, Value);
}

bool UDynamicPropertiesSubsystem::SetVector2DProperty(UObject* Object, FName PropertyName, FVector2D Value)
{
	return SetStructProperty<FVector2D>(Object, PropertyName, Value);
}
