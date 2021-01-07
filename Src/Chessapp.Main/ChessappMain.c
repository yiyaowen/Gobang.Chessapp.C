#include "Page/HomePage/HomePage.h"
#include "ChessappDispatch.h"
#include "ConsoleDoubleBuffer.h"
#include "VirtualTerminalSequences.h"
#include "ChessappGlobalConfig.h"
#include "Core.h"

int main(int argc, char* argv[])
{
    char* configFilePath = DEFAULT_CONFIG_FILE_PATH;
    readConfigFilePathFromCmdArgs(configFilePath);
    readGlobalConfigFromConfigFile(configFilePath);
    enableConsoleDoubleBuffer();
    enableVirtualTerminalSequences();
    enableGlobalTuiPageStack();
    initializeGobangCore();

    Page* homePage = getNewHomePage();
    Route* routeFromMain = getNewDefaultRoute();
    routeFromMain = startRoutine(getGlobalTuiPageStack(), homePage, routeFromMain);

    releaseGobangCore();
    writeGlobalConfigToConfigFile(configFilePath);
    return routeFromMain->exitStatus;
}