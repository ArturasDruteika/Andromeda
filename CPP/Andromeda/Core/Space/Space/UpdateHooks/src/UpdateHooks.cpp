#include "../include/UpdateHooks.hpp"


namespace Andromeda::Space
{
    UpdateHooks::UpdateHooks()
        : m_nextId{ 0 }
    {
    }

    UpdateHooks::~UpdateHooks() = default;

    UpdateHooks::Handle UpdateHooks::Add(Callback callback)
    {
        Handle handle;
        handle.id = ++m_nextId;

        Entry entry;
        entry.id = handle.id;
        entry.fn = std::move(callback);

        m_entries.push_back(std::move(entry));

        return handle;
    }

    void UpdateHooks::Remove(Handle handle)
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

    void UpdateHooks::Clear()
    {
        m_entries.clear();
    }

    void UpdateHooks::Run(float deltaTime)
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

            if (it != m_entries.end() && it->fn)
            {
                it->fn(deltaTime);
            }
        }
    }
}