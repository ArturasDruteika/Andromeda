#include "Application.hpp"


int main(void)
{
    Andromeda::EngineCore::Application app;
    app.Init();
    app.RunMainLoop();
    app.DeInit();

    return 0;
}