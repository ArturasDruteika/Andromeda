#ifndef CORE__ENGINE_RUNNER__HPP
#define CORE__ENGINE_RUNNER__HPP


#if defined(_WIN32)
	#if defined(CORE_EXPORT)
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API __declspec(dllimport)
	#endif /* CORE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
// GCC
#define CORE_API __attribute__((visibility("default")))
#endif


namespace Andromeda
{
	namespace Core
	{
		class CORE_API EngineRunner
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


#endif // CORE__ENGINE_RUNNER__HPP