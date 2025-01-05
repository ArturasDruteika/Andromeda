#ifndef ENGINECORE__ENGINE_RUNNER__HPP
#define ENGINECORE__ENGINE_RUNNER__HPP


#if defined(_WIN32)
	#if defined(ENGINECORE_EXPORT)
		#define ENGINECORE_API __declspec(dllexport)
	#else
		#define ENGINECORE_API __declspec(dllimport)
	#endif /* ENGINECORE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define ENGINECORE_API __attribute__((visibility("default")))
#endif


namespace Andromeda
{
	namespace EngineCore
	{
		class ENGINECORE_API EngineRunner
		{
		public:
			EngineRunner();
			~EngineRunner();

			void Run();

		private:
			class EngineRunnerImpl;
			EngineRunnerImpl* m_pEngineRunnerImpl;
		};
	}
}


#endif // ENGINECORE__ENGINE_RUNNER__HPP