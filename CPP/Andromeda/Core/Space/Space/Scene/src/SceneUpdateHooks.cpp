#include "../include/SceneUpdateHooks.hpp"


namespace Andromeda::Space
{
    SceneUpdateHooks::Handle SceneUpdateHooks::Add(Callback callback)
    {
        Handle handle;
        handle.id = ++m_nextId;

        Entry entry;
        entry.id = handle.id;
        entry.Fn = std::move(callback);

        m_entries.push_back(std::move(entry));

        return handle;
    }

    void SceneUpdateHooks::Remove(Handle handle)
    {
        auto it = std::remove_if(
            m_entries.begin(),
            m_entries.end(),
            [&](const Entry& e)
            {
                return e.id == handle.id;
            });

        m_entries.erase(it, m_entries.end());
    }

    void SceneUpdateHooks::Clear()
    {
        m_entries.clear();
    }

    void SceneUpdateHooks::Run(Scene& scene, float deltaTime)
    {
        // Capture ids so callbacks can remove themselves safely.
        std::vector<uint64_t> ids;
        ids.reserve(m_entries.size());
        for (const auto& entry : m_entries)
        {
            ids.push_back(entry.id);
        }

        for (uint64_t id : ids)
        {
            auto it = std::find_if(
                m_entries.begin(),
                m_entries.end(),
                [id](const Entry& e)
                {
                    return e.id == id;
                });

            if (it != m_entries.end() && it->Fn)
            {
                it->Fn(scene, deltaTime);
            }
        }
    }
}