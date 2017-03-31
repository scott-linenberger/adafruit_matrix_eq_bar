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

//create an array for our EQ bars
NeoMatrixEqBar eqBars[8];

//used to crawl the color wheel
int colorCount = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("start");

  //init the matrix
  matrix.begin();
  matrix.setBrightness(MATRIX_BRIGHTNESS);
  matrix.clear();
  matrix.show();

  //build the EQ bars, one for each column of our matrix
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    /* build a Neo Matrix EQ bar
      &matrix - a pointer to the matrix.
      0 - which column
      0 - starting height
      MATRIX_HEIGHT - the EQ bar's max height;
    */
    NeoMatrixEqBar eqBar = NeoMatrixEqBar(&matrix, i, 0, MATRIX_HEIGHT);
    //init the eqBar
    eqBar.begin();
    eqBar.randomizeSpeed(true);

    //add to the array
    eqBars[i] = eqBar;
  }

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
  //create a changing array of colors based on the color count
  uint32_t colors[] = {
    eqBars[0].colorWheel(colorCount + 60),
    eqBars[0].colorWheel(colorCount + 50),
    eqBars[0].colorWheel(colorCount + 40),
    eqBars[0].colorWheel(colorCount)    
  };

  //tick the EQ bars to update them
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    eqBars[i].setColors(colors);
    eqBars[i].tick();
  }

  matrix.show();
  delay(speed);
  matrix.clear();

  colorCount++;

  if (colorCount > 255) {
    colorCount == 0;
  }

}
