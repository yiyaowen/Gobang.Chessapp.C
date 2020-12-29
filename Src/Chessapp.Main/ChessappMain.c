#include "Page/HomePage/HomePage.h"
#include "ChessappDispatch.h"
#include "ConsoleDoubleBuffer.h"
#include "VirtualTerminalSequences.h"

int main()
{
    enableConsoleDoubleBuffer();
    enableVirtualTerminalSequences();
    enableGlobalTuiPageStack();

    Page* homePage = getNewHomePage();
    Route* routeFromMain = getNewDefaultRoute();
    routeFromMain = startRoutine(getGlobalTuiPageStack(), homePage, routeFromMain);

    return routeFromMain->exitStatus;
}