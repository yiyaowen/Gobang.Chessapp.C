#include "Che.h"

int main(int argc, char * argv[])
{
    EnableVirtualTerminalSequences();
    EnableConsoleDoubleBuffer();
    InitGlobalVariables();

    while (1) { 

        autodisplay(DisplayHomePage());

        GetValidHomeOption();

        SwitchToSelectedHomeOption();

    }

    return EXIT_SUCCESS;
}
