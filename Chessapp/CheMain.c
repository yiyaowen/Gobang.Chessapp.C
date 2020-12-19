#include "Che.h"

int main(int argc, char * argv[])
{
    EnableVirtualTerminalSequences();
    EnableConsoleDoubleBuffer();
    InitGlobalVariables();
    
    Page* home_page = GetDefaultHomePage();
    Route* route = GetDefaultRoute();

    route = StartRoutine(home_page, route);

    return route->exit_status;
}
