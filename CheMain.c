#include "Che.h"

int main()
{
    EnableVirtualTerminalSequences();
    InitGlobalVariables();

    while (1) { 

        DisplayHome();

        GetValidHomeOption();

        SwitchToSelectedOption();

    }

    return EXIT_SUCCESS;
}
