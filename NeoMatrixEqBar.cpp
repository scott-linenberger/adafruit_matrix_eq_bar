/*-------------------------------------------------------------------------

  -------------------------------------------------------------------------*/
#include "NeoMatrixEqBar.h"
NeoMatrixEqBar::NeoMatrixEqBar()
{
}

/* Constructor method: */
NeoMatrixEqBar::NeoMatrixEqBar(Adafruit_NeoMatrix *_matrix, int _column, int _height, int _maxHeight)
{
    //assign instance variables...
    matrix = _matrix;
    column = _column;
    height = _height;
    maxHeight = _maxHeight;
}

/* initialization method */
NeoMatrixEqBar::begin()
{
    initColors();
}

/* used to tick the EQ bar, which advances the timing and causes the EQ bar to update */
NeoMatrixEqBar::tick()
{

    //if speed is randomzied, update the timing ticks...
    if (isRandomizedSpeed)
    {
        tickTiming();
    }

    //check timing against the tick count, update if timing matches
    if (tickCounter == 0 || tickCounter % timing == 0)
    {
        updateHeight();
    }

    //draw the EQ bar to the matrix
    draw();

    //update the tick counter
    tickCounter++;
}

/* update timing's ticks: used for checking speed changes when speed is randomized */
NeoMatrixEqBar::tickTiming()
{

    //time to change speed
    if (speedChangeTickCount > speedChangeDelay)
    {
        //reset speed change ticks to 0
        speedChangeTickCount = 0;

        //set the change count between 10 an 100
        //this randomizes how often speed changes
        speedChangeDelay = random(10, 101);

        //change the timing, which controls speed to a value between 1 and 4
        timing = random(1, 4);
    }

    //increment the speed change tick
    speedChangeTickCount++;
}

/* updates the height of the EQ bar */
NeoMatrixEqBar::updateHeight()
{
    if (height >= maxHeight)
    {
        isAsc = false;
    }

    if (height < minHeight + 1)
    {
        isAsc = true;
    }

    if (isRandomizedPeak)
    {
        if (height > minHeight + 1 && height < maxHeight)
        {
            isAsc = random(0, 100) % 2 == 0;
        }
    }

    isAsc ? height++ : height--;
}

/* draws the current EQ bar state to the matrix */
NeoMatrixEqBar::draw()
{
    for (int i = 0; i < height; i++)
    {
        matrix->drawPixel(column, i, colors[i]);
    }
}

/* initializes the colors array */
NeoMatrixEqBar::initColors()
{
    if (maxHeight == 0)
    {
        return;
    }

    //break the color wheel equally over each pixel
    int incrementSize = 255 / maxHeight;
    int currentColorPos = 0;

    //add a color for each pixel
    for (int i = 0; i < maxHeight; i++)
    {
        /* add the color to the colors array */
        colors[i] = colorWheel(currentColorPos);

        /* increment the color position */
        currentColorPos += incrementSize;
    }

    //add default colors for the remaining postions
    for (int k = maxHeight; k < 32 - maxHeight; k++)
    {
        colors[k] = colorWheel(100);
    }
}

/* Adafruit's  color wheel code */
uint32_t NeoMatrixEqBar::colorWheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return matrix->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }

    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return matrix->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }

    WheelPos -= 170;
    return matrix->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/* Sets an array of colors to be used as the EQ bar's colors */
NeoMatrixEqBar::setColors(uint32_t *_colors)
{
  colors = _colors;
}

/* Sets the color of the EqBar using Adafruit's Wheel code' */
NeoMatrixEqBar::setColor(byte colorWheelPosition)
{
    //return if value is invalid
    if (colorWheelPosition < 0 || colorWheelPosition > 255)
    {
        return;
    }

    uint32_t color = colorWheel(colorWheelPosition);

    /* copy colors into our colors array */
    for (int i = 0; i < 32; i++)
    {
        colors[i] = color;
    }
}

/* sets the speed randomization to true or false */
NeoMatrixEqBar::randomizeSpeed(boolean isRandomized)
{
    isRandomizedSpeed = isRandomized;
}

/* sets the peak randomization to true or false */
NeoMatrixEqBar::randomizePeak(boolean isRandomized)
{
    isRandomizedPeak = isRandomized;
}

/* sets whether the EQ bar should be ascending or descending */
NeoMatrixEqBar::setAscending(boolean _isAsc)
{
    isAsc = _isAsc;
}

/* use to set the minimum height of the EQ bar */
NeoMatrixEqBar::setMinHeight(int _minHeight)
{
    minHeight = _minHeight;
}

/* use to set the maximum height of the EQ bar */
NeoMatrixEqBar::setMaxHeight(int _maxHeight)
{
    maxHeight = _maxHeight;
}

/* sets the EQ bar's timing */
NeoMatrixEqBar::setTiming(int _timing)
{
    timing = _timing;
}
