#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include "Cleaner.h"
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>

#include "UnrealDef.hpp"

using namespace RC::Unreal;

class Optimizer final : public CppUserModBase
{
public:
    Optimizer()
    {
        ModName = STR("Smuta wall destroyer");
        ModVersion = STR("1.0");
        ModDescription = STR("Target of this mod is clear smuta's maps from the invisible walls.");
        ModAuthors = STR("Madmer");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        Output::send<LogLevel::Default>(STR("[WallDestroyer] Mod loaded\n"));

        RC::UObjectGlobals::RegisterHook(STR("/Script/Engine.PlayerController:ClientRestart"),
                                         [](UnrealScriptFunctionCallableContext& Context, void* _)-> void {
                                         },
                                         [](UnrealScriptFunctionCallableContext& Context, void* _)-> void {
                                             Replacer::ClearHiddenWalls();
                                         },
                                         nullptr);
    }

    auto on_update() -> void override
    {
    }
};

#define MY_AWESOME_MOD_API __declspec(dllexport)

extern "C"
{
MY_AWESOME_MOD_API RC::CppUserModBase* start_mod()
{
    return new Optimizer();
}

MY_AWESOME_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
{
    delete mod;
}
}
