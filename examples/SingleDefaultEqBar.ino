#include "NeoMatrixEqBar.h"

//matrix constants
const int MATRIX_PIN = 6;
const int MATRIX_WIDTH = 8;
const int MATRIX_HEIGHT = 4;
const int MATRIX_PIXEL_TYPE = NEO_GRB + NEO_KHZ800;
const int MATRIX_BRIGHTNESS = 10;

//animation speed
//lower values means FASTER!
const int speed = 40;

//matrix setup
const int MATRIX_OPTIONS =
    NEO_MATRIX_BOTTOM +
    NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS +
    NEO_MATRIX_PROGRESSIVE;

//declare the matrix
Adafruit_NeoMatrix matrix =
    Adafruit_NeoMatrix(
        MATRIX_WIDTH,
        MATRIX_HEIGHT,
        MATRIX_PIN,
        MATRIX_OPTIONS,
        MATRIX_PIXEL_TYPE);

/* build a Neo Matrix EQ bar
    &matrix - a pointer to the matrix.
    0 - which column
    0 - starting height
    MATRIX_HEIGHT - the EQ bar's max height;
*/
NeoMatrixEqBar eqBar = NeoMatrixEqBar(&matrix, 0, 0, MATRIX_HEIGHT);

void setup()
{
    Serial.begin(9600);
    Serial.println("start");

    //init the matrix
    matrix.begin();
    matrix.setBrightness(MATRIX_BRIGHTNESS);
    matrix.clear();
    matrix.show();

    //init the eqBar
    eqBar.begin();

    /* eq bar options */

    /* randomizes the speed of the EQ bar animation*/
    //  eqBar.randomizeSpeed(true);

    /* randomizes the peak height */
    //  eqBar.randomizePeak(true);

    /* sets the minimum peak height */
    //  eqBar.setMinHeight(2);

    /* make sure to adjust min-height as well when using max height */
    //  eqBar.setMaxHeight(0);

    /* set the color of the EQ bar using the color wheel */
    //  eqBar.setColor(20);
}

void loop()
{
    //tick the EQ bar to update it
    eqBar.tick();

    matrix.show();
    delay(speed);
    matrix.clear();
}