#include "Che.h"

int main(int argc, char * argv[])
{
    EnableVirtualTerminalSequences();
    EnableConsoleDoubleBuffer();
    InitGlobalVariables();

    while (1) { 

        autodisplay(DisplayHome());

        GetValidHomeOption();

        SwitchToSelectedOption();

    }

    return EXIT_SUCCESS;
}
