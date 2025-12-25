#ifndef SPACE__OBJECTS__OBJECT__HPP
#define SPACE__OBJECTS__OBJECT__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Objects/IObject.hpp"


namespace Andromeda::Space
{
    class SPACE_API Object
        : public virtual IObject
    {
    public:
        Object();
		~Object() override;

        // Getters
        bool IsActive() const;
        int GetID() const;
        const std::string& GetName() const;
        // Setters
        void Active(bool active);
        void SetName(const std::string& name);

    private:
        bool m_isActive;
        int m_id;
        std::string m_name;
    };
}


#endif // SPACE__OBJECTS__OBJECT__HPP