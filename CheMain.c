#include "CheTUI.h"
#include "CheGlobal.h"

extern DEFAULT_FLAT_BOARD Board;
extern DEFAULT_FLAT_POSITION Pos;

int main()
{
    while (1) { 

        DisplayHome();
        GetValidHomeOption();
        SwitchToSelectedOption();

    }

    return 0;
}
