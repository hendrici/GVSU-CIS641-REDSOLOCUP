/*
 * CS_Driver.c
 *
 * Created on: Oct 29, 2024
 * Author: Isaiah Hendrick
 */

/* Custom includes */
#include "CS_Driver.h"

/**
 * @brief Initializes the MCLK and HSMCLK to use a 48 MHz crystal.
 *
 * This function configures the flash wait states and sets up the HFXT to use a
 * 48 MHz crystal as the clock source for the MCLK and HSMCLK.
 *
 * @param void
 *
 * @return void
 */
void CS_Init_48MHz(void)  {
    /* set flash wait-state to 1 for banks 0 and 1 */
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

    /* HFXT will use 48MHz crystal, assign to MCLK and HSMCLK */
    PJ->SEL0 |= BIT2 | BIT3;
    PJ->SEL1 &= ~(BIT2 | BIT3);
    CS->KEY = CS_KEY_VAL ;
    CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE;

    while(CS->IFG & CS_IFG_HFXTIFG) CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;     // make sure HFXT is stable, if not, clear interrupt flag and wait

    /* MCLK & HSMCLK = HFXT, do not use divider */
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK | CS_CTL1_SELS_MASK | CS_CTL1_SELA_MASK | CS_CTL1_DIVHS_MASK) | CS_CTL1_SELM__HFXTCLK | CS_CTL1_SELS__HFXTCLK;
    CS->CTL1 = CS->CTL1 | CS_CTL1_DIVA_2 |CS_CTL1_DIVS_2;
    CS->KEY = 0;
}
