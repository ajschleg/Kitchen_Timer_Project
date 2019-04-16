#include "menu.h"

int getPotDivider(int maxPotValue, int numMenuOptions) {
    int divider = maxPotValue / numMenuOptions;
    // Adding 1 in any case, but maybe should just add 1 if remainder != 0?
    return divider + 1;
}
