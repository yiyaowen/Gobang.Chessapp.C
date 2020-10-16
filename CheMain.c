#include "Che.h"

int main()
{
    InitGlobalVariables();

    while (1) { 

        DisplayHome();

        GetValidHomeOption();

        SwitchToSelectedOption();

    }

    return EXIT_SUCCESS;
}
