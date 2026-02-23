#pragma once


#include "pch.hpp"


namespace Andromeda::Space
{
    class Scene;

    class SceneUpdateHooks
    {
    public:
        using Callback = std::function<void(Scene&, float)>;

        struct Handle
        {
            uint64_t id = 0;
        };

        Handle Add(Callback callback);
        void Remove(Handle handle);
        void Clear();
        void Run(Scene& scene, float deltaTime);

    private:
        struct Entry
        {
            uint64_t id = 0;
            Callback Fn;
        };

        uint64_t m_nextId = 0;
        std::vector<Entry> m_entries;
    };
}