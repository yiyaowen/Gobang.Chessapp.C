#include "CheTUI.h"
#include "CheGlobal.h"

int main()
{
    InitGlobalVariables();
    DisplayHome();

    while (1) { 

        GetValidHomeOption();

        SwitchToSelectedOption();

    }

    return 0;
}
