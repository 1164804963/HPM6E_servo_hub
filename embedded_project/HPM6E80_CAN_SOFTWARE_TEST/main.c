#include "board.h"
#include "test_can_software.h"

int main(void)
{
    board_init();
    int result = can_software_run();
    while (1)
    {
        board_delay_ms(1000U);
    }
    return result;
}
