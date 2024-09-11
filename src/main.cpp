#include "application.hpp"

EventManager event_manager;

int main()
{
    Application app(
        "terrain", 800, 600, 
        Camera()
    );

    app.run();
}

