#ifndef RENDERER__I_SHADER__HPP
#define RENDERER__I_SHADER__HPP


namespace Andromeda::Rendering
{
	class IShader
	{
	public:
		virtual ~IShader();

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};
}


#endif // RENDERER__I_SHADER__HPP