#include "application.hpp"

EventManager event_manager;

int main()
{
    setup();

    Application app(
        Window(800, 600, "terrain"),
        Camera()
    );

    app.run();
}

