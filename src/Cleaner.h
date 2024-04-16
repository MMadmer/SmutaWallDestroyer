#pragma once

#include <Mod/CppUserModBase.hpp>

class Replacer final : public CppUserModBase
{
public:
    Replacer() = delete;

    /** Clear all invisible static mesh actors in the world. */
    static void ClearHiddenWalls();
};