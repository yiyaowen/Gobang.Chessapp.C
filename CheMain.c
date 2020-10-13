#include "CheTUI.h"
#include "CheGlobal.h"

int main()
{
    while (1) { 

        DisplayHome();

        GetValidHomeOption();

        SwitchToSelectedOption();

    }

    return 0;
}
