#include "Che.h"

int main(int argc, char * argv[])
{
    EnableVirtualTerminalSequences();
    EnableConsoleDoubleBuffer();
    InitGlobalVariables();
    
    Page *home_page;
    Route *route;

    InitHomePage(home_page);
    InitRoute(route);

    route = StartRoutine(home_page, route);

    return route->exit_status;
}
