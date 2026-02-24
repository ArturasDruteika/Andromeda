#pragma once


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Scene/ISceneUpdateHooks.hpp"
#include "pch.hpp"


namespace Andromeda::Space
{
    class SPACE_API SceneUpdateHooks
        : public virtual ISceneUpdateHooks
    {
    public:
        SceneUpdateHooks();
        ~SceneUpdateHooks() override;

        ISceneUpdateHooks::Handle Add(ISceneUpdateHooks::Callback callback) override;
        void Remove(ISceneUpdateHooks::Handle handle) override;
        void Clear() override;
        void Run(float deltaTime) override;

    private:
        struct Entry
        {
            std::uint64_t id = 0;
            ISceneUpdateHooks::Callback fn;
        };
	
    private:
        std::uint64_t m_nextId;
        std::vector<Entry> m_entries;
    };
}