#ifndef API__OBJECTS__I_OBJECT__HPP
#define API__OBJECTS__I_OBJECT__HPP


namespace Andromeda
{
	class IObject
	{
	public:
		virtual ~IObject() = default;
		
		// Getters
		virtual int GetID() const = 0;
        virtual const std::string& GetName() const = 0;
        virtual bool IsActive() const = 0;
        // Setters
        virtual void SetName(const std::string& name) = 0;
        virtual void SetActive(bool active) = 0;
	};
}


#endif // API__OBJECTS__I_OBJECT__HPP