#ifndef API__OBJECTS__I_OBJECT__HPP
#define API__OBJECTS__I_OBJECT__HPP


#include <string>


namespace Andromeda
{
	class IObject
	{
	public:
		virtual ~IObject() = default;
		
		// Getters
		virtual bool IsActive() const = 0;
		virtual int GetID() const = 0;
        virtual const std::string& GetName() const = 0;
        // Setters
		virtual void Active(bool active) = 0;
        virtual void SetName(const std::string& name) = 0;
		virtual void SetID(int id) = 0;
	};
}


#endif // API__OBJECTS__I_OBJECT__HPP