#ifndef SPACE__OBJECTS__OBJECT__HPP
#define SPACE__OBJECTS__OBJECT__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Objects/IObject.hpp"
#include "pch.hpp"


namespace Andromeda::Space
{
    class SPACE_API Object
        : public virtual IObject
    {
    public:
        Object();
		~Object() override;

        // Getters
        bool IsActive() const override;
        int GetID() const override;
        const std::string& GetName() const override;
        // Setters
        void Active(bool active) override;
        void SetName(const std::string& name) override;

    private:
        bool m_isActive;
        int m_id;
        std::string m_name;
        static std::atomic<int> s_nextId;
    };
}


#endif // SPACE__OBJECTS__OBJECT__HPP