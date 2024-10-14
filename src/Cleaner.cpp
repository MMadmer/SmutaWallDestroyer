#include "Cleaner.h"
#include <UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <GameplayStatics.hpp>
#include <Constructs/Views/EnumerateView.hpp>

#include "BPMacros.hpp"
#include "UFunctionUtils.h"
#include "FunctionTypes.hpp"

using namespace ::RC::Unreal;

void Replacer::ClearHiddenWalls()
{
    // Find target classes
    UClass* MeshActorClass = Unreal::UObjectGlobals::StaticFindObject<UClass*>(nullptr, nullptr, STR("/Script/Engine.StaticMeshActor"));
    UClass* MeshCompClass = Unreal::UObjectGlobals::StaticFindObject<UClass*>(nullptr, nullptr, STR("/Script/Engine.StaticMeshComponent"));
    const UObject* DefaultMat = Unreal::UObjectGlobals::StaticFindObject<UObject*>(nullptr,
                                                                                   nullptr,
                                                                                   STR("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
    const UObject* BasicShapeMat = Unreal::UObjectGlobals::StaticFindObject<UObject*>(nullptr,
                                                                                      nullptr,
                                                                                      STR("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

    // Find any actor
    const UObject* ContextActor = Unreal::UObjectGlobals::FindFirstOf(STR("Actor"));
    if (!ContextActor)
    {
        Output::send<LogLevel::Warning>(STR("[WallDestroyer] Can't destroy invisible walls. Actors not found!\n"));
        return;
    }

    Unreal::TArray<AActor*> MeshActors;
    UGameplayStatics::GetAllActorsOfClass(ContextActor, MeshActorClass, MeshActors);

    int32 InvisibleWalls = 0;
    for (const auto& MeshActor : MeshActors)
    {
        const Unreal::TArray<UObject*>& MeshComponents = MeshActor->GetComponentsByClass(MeshCompClass);
        if (!MeshComponents.IsValidIndex(0)) continue;

        // Find and destroy invisible walls
        FGetMaterial GetMaterialArgs{};
        UFunctionUtils::TryCallUFunction(MeshComponents[0], STR("GetMaterial"), &GetMaterialArgs);

        if (GetMaterialArgs.ReturnValue == DefaultMat || GetMaterialArgs.ReturnValue == BasicShapeMat)
        {
            MeshActor->K2_DestroyActor();
            InvisibleWalls++;
        }
    }

    Output::send<LogLevel::Default>(STR("[WallDestroyer] Destroyed invisible walls: {}\n"), InvisibleWalls);
}