#include "Che.h"

int main(int argc, char * argv[])
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
