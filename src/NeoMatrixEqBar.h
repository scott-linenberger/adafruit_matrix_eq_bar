/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/
#ifndef EQBAR_H
#define EQBAR_H

//include necessary Adafruit libs
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class NeoMatrixEqBar{

    /*--INSTANCE VARS --*/

    /* 
        Pointer to an instance of the adafruit matrix object.
        This object is where the EQ bar will be drawn
        and it must be initialized BEFORE being being 
        passed to the constructor.
    */
    Adafruit_NeoMatrix* matrix;

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
        The maximum height the EQ bar is allowed to reach. If you 
        want the eq bar to be 2 pixels tall, you would set
        this variable to: 2. Setting this value to the height of
        the NeoMatrix allows the EQ bar to reach to the top of your
        NeoMatrix.
    */
    int maxHeight;
    

    public:
        /* Constructor: used to initialize the EQ bar. */
        NeoMatrixEqBar(Adafruit_NeoMatrix*, int, int, int);

    private:
        /*Adafruit's Wheel code used for generating color columns */
        uint32_t colorWheel(int);

};

#endif