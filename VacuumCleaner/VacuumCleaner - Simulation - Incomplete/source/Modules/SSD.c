#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SSD.h"

/* SSD_Update period */
#define SSD_PERIOD_MS   (10)

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (4)


/* SSD Symbols port data values */
static tByte SSD_Data[N_SSD_SYMBOLS] =
{
    0b00001000,
    0b01001000,
    0b01001001,
    0b00000000,
};

/* Current SSD to be updated */
static tSSD SSD_current = SSD_LOW;

//Indicator of what SSDs should be powered on at the time
static tSSD SSD_current_level = SSD_MEDIUM;

/* SSD values */
static tSSD_Symbol SSD_Values[N_SSD] = {SSD_NULL};

static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol);

void SSD_Init(tSSD ssd)
{
    /* Initialize SSD data pins */
    GPIO_InitPort(SSD_DATA_PORT_CR, GPIO_OUT);
    SSD_Out(ssd, SSD_NULL);

    /* Initialize SSD control pin and turn SSD OFF*/
    switch(ssd)
    {
        case SSD_HIGH:
            GPIO_InitPortPin(SSD_HIGH_CR, SSD_HIGH_PIN, GPIO_OUT);
            break;
        case SSD_MEDIUM:
            GPIO_InitPortPin(SSD_MEDIUM_CR, SSD_MEDIUM_PIN, GPIO_OUT);
            break;
        case SSD_LOW:
            GPIO_InitPortPin(SSD_LOW_CR, SSD_LOW_PIN, GPIO_OUT);
            break;
        /* Should not be here */
        default:
            break;
    }
    SSD_SetState(ssd, SSD_OFF);
}

void SSD_Update(void)
{
    static tWord SSD_counter = 0;

    /* Check if it is time for the SSD_Update to run */
    SSD_counter += TMR_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS){
        return;
    }

    SSD_counter = 0;

    /* display current SSD value of the current SSD */
    SSD_Out(SSD_current, SSD_Values[SSD_current]);

    if (SSD_current == SSD_HIGH)
    {
        SSD_current = SSD_LOW;
    } else
    {
        SSD_current++;
    }
}

tSSD_Symbol SSD_GetValue(tSSD ssd)
{
    return SSD_Values[ssd];
}

void SSD_SetValue(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    SSD_Values[ssd] = ssd_symbol;
}

void SSD_SetCurrentLevel(tSSD ssd)
{
    SSD_current_level = ssd;
}

tSSD_State SSD_GetState(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;
    switch(ssd)
    {
        case SSD_LOW:
            ret = GPIO_ReadPortPin(SSD_LOW_DR, SSD_LOW_PIN);
            break;
        case SSD_MEDIUM:
            ret = GPIO_ReadPortPin(SSD_MEDIUM_DR, SSD_MEDIUM_PIN);
            break;
        case SSD_HIGH:
            ret = GPIO_ReadPortPin(SSD_HIGH_DR, SSD_HIGH_PIN);
            break;
        /* Should not be here */
        default:
            break;
    }
    return ret;
}

void SSD_SetState(tSSD ssd, tSSD_State state)
{
    switch (ssd)
    {
        case SSD_LOW:
            GPIO_WritePortPin(SSD_LOW_DR, SSD_LOW_PIN, state);
            break;
        case SSD_MEDIUM:
            GPIO_WritePortPin(SSD_MEDIUM_DR, SSD_MEDIUM_PIN, state);
            break;
        case SSD_HIGH:
            GPIO_WritePortPin(SSD_HIGH_DR, SSD_HIGH_PIN, state);
            break;
        /* Should not be here */
        default:
            break;
    }
}

static void SSD_Out(tSSD ssd, tSSD_Symbol ssd_symbol)
{
    /* Turn off SSDs */
    SSD_SetState(SSD_LOW, SSD_OFF);
    SSD_SetState(SSD_MEDIUM, SSD_OFF);
    SSD_SetState(SSD_HIGH, SSD_OFF);

    /* Output ssd_symbol on selected ssd */
    GPIO_WritePort(SSD_DATA_PORT_DR, SSD_Data[ssd_symbol]);

    /* Turn ssd ON */
    if(ssd <= SSD_current_level) SSD_SetState(ssd, SSD_ON);
}
