/*-------------------------------------------------------------------------

  -------------------------------------------------------------------------*/
#ifndef NEOMATRIXEQBAR_H
#define NEOMATRIXEQBAR_H

//include necessary Adafruit libs
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class NeoMatrixEqBar
{

    /*--INSTANCE VARS --*/

    /*
        Pointer to an instance of the adafruit matrix object.
        This object is where the EQ bar will be drawn
        and it must be initialized BEFORE being being
        passed to the constructor.
    */
    Adafruit_NeoMatrix *matrix;

    /*
        Which column on the NeoMatrix the EQ bar should
        be drawn on. 0, 1, 2, 3, etc...
    */
    int column;

    /*
        The height of the EQ bar. When passed into the
        constructor, sets the starting height of the EQ bar.
        While running, this variable represents the current
        height of the EQ bar as it is to be drawn on the NeoMatrix.
    */
    int height;

    /*
        The minimum height the EQ bar is allowed to drop to. Setting
        this value to 2 means the EQ bar will never be smaller than 2
        pixels. Defaults to 1 to keep at least one dot on the matrix.
        Setting this to 0 will allow the EQ bar to disappear from the
        matrix when it hits the lowest height.
    */
    int minHeight = 1;
    /*
        The maximum height the EQ bar is allowed to reach. If you
        want the eq bar to be 2 pixels tall, you would set
        this variable to: 2. Setting this value to the height of
        the NeoMatrix allows the EQ bar to reach to the top of your
        NeoMatrix.
    */
    int maxHeight;

    /*
       Timing is a variable that allows you to change how frequently
       the EQ bar updates on ticks. The value is essentially the
       denominator of a fraction. So 1 = 1/1 (regular speed), 2 = 1/2 (50% speed),
       3 = 1/3 (33% speed), etc.. This must be a positive value. Defaults to 1,
       which is 100% speed.
    */
    int timing = 1;

    /*
       Timing for the EQ bar is done in "ticks". Calling tick() steps the EQ bar forward
       in time and updates the height of the code according to the timing. The tickCount
       is incremented each time tick() is called.
    */
    int tickCounter = 0;

    /*
       Sets the delay (number of ticks) in between speed changes, if speed has been randomized.
    */
    int speedChangeDelay = 10;

    /*
       The tick counter for speed changes if speed has been randomized. Once the speedChangeTickCount
       has exceeded the number of ticks specified by speedChangeDelay, the speed will be randomly changed
       and the speedChangeTickCount will be zeroed.
    */
    int speedChangeTickCount = 0;

    /*
       The variable for controlling if the EQ bar is ascending or descending.
    */
    boolean isAsc = true;

    /*
      The variable for conrolling whether or not the speed should be randomized.
    */
    boolean isRandomizedSpeed = false;

    /*
       The variable for controlling if the EQ bar's peaks (high points) should be randomized.
       Setting this to true will randomly change whether or not the EQ bar is ascending or descending.
    */
    boolean isRandomizedPeak = false;

    /*
       The array of colors to be used on the EQ bar. The indexes of the colors correspond to the pixel
       height. So colors[0] is the color of the first pixel on the EQ bar, colors[1] is the color of the
       second pixel on the EQ bar, etc... This array is initialized to default colors. Defaults 32 slots
       for 32 colors. Note: an EQ Bar of size 4 will only use array colors 0 - 3, NOT all 32 colors!
    */
    uint32_t *colors;

  public:
    /* No args Constructor */
    NeoMatrixEqBar();
    /* Constructor: used to initialize the EQ bar. */
    NeoMatrixEqBar(Adafruit_NeoMatrix *, int, int, int);
    /* used to begin the EQ bar */
    begin();
    /* used to tick the EQ bar, which advances the timing and causes the EQ bar to update */
    tick();
    /* sets the speed randomization to true or false */
    randomizeSpeed(boolean);
    /* sets the peak randomization to true or false */
    randomizePeak(boolean);
    /* use a color wheel value to set the colors of the eq bar */
    setColor(byte);
    /* use to set an array of colors as your EQ bar's colors */
    setColors(uint32_t *);
    /* use to set the minimum height of the EQ bar */
    setMinHeight(int);
    /* use to set the maximum height of the EQ bar */
    setMaxHeight(int);
    /* sets whether the EQ bar should be ascending or descending */
    setAscending(boolean);
    /* sets the EQ bar's timing */
    setTiming(int);
    /*Adafruit's Wheel code used for generating color columns */
    uint32_t colorWheel(byte);

  private:
    /* initializes the default colors */
    initColors();
    /* draws the current EQ bar state to the matrix */
    draw();
    /* update timing's ticks: used for checking speed changes when speed is randomized */
    tickTiming();
    /* updates the height of the EQ bar */
    updateHeight();
};

#endif