# Adafruit NeoMatrix Equalizer Bar
An Equalizer Bar animation for an Adafruit Matrix.

```
//includ the NeoMatrixEqBar library
#include "NeoMatrixEqBar.h"

//matrix constants for a NeoPixel Featherwing
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

//declare an EQ bar
NeoMatrixEqBar eqBar;

void setup() {
  //init the matrix
  matrix.begin();
  matrix.setBrightness(MATRIX_BRIGHTNESS);
  matrix.clear();
  matrix.show();

  //new eqBar at column 0, height 0
  eqBar = NeoMatrixEqBar(&matrix, 0, 0, MATRIX_HEIGHT);
  eqBar.begin();
}

void loop(){
    eqBar.tick();
    delay(speed);
    matrix.clear();
}

```

## Required Arduino Libraries  
The NeoMatrix EqBar is an animation for Adafruit NeoMatrices. The code was written 
and tested specifically using the [NeoPixel Featherwing][NEOPIXEL_FEATHERWING]. Because
this library was written using Adafruit's code found [here][GITHUB_ADAFRUIT], you will need to have the 
following libraries installed in your Arduino IDE: 

 1. [Adafruit GFX][LIB_GFX]
 2. [Adafruit NeoMatrix][LIB_NEOMATRIX]
 3. [Adafruit NeoPixel][LIB_NEOPIXEL]

## Methods  

`NeoMatrixEqBar()` - No arguments, default constructor
>This lets the NeoMatrixEqBar be declared as a global variable. Cannot be used to create a working Eq Bar.

`NeoMatrixEqBar(Adafruit_NeoMatrix *, int, int, int)` - Standard constructor.
>Adafruit_NeoMatrix * - pointer to an initialized matrix object.  
>int - column the Eq bar will be in. 
>int - height: starting height of the Eq Bar. 
>int - max height: the maximum height the Eq bar can grow to. Should be less than or equal to the height of your matrix and greater than 0.  

`begin()` - starts the Eq bar
> This method must be called after the standard construtor is called. This method initializes the default colors. 

`tick()` - controls the timing and updates for the Eq bar  
> Must be called to update the Eq bar. Each tick calls `update()` that can advance the Eq bar up or down based on the timing variable.

`randomizeSpeed(boolean)` -  sets the speed of the animation to randomized or not. 
> Setting the speed of the Eq bar as random will cause the timing variable to be randomly updated, which will change the speed of the animation randomly. 

`randomizePeak(boolean)` - sets the maximum height of the animation to randomized or not.  
> Setting the peak random will change the `isAsc` variable randomly, causing the Eq Bar to move up and down randomly instead of tracking all the way up, then all the way down. 

`setColor(byte)` - sets the color for all pixels on the Eq bar. 0 - 255  
> Sets the color for all pixels in the Eq bar using the color wheel. 

`setMinHeight(int)` - sets the minimum height of the Eq bar. The Eq bar will not fall below the minimum height setting.
> Sets the mimumm height variable.  

`setMaxHeight(int)` - sets the maximum height of the Eq bar. The Eq bar will not go above the maximum height setting.
> Sets the maximum height variable. 

`setAscending(boolean)` - sets whether or not the animation is ascending. 
> Setting this to true will cause the Eq bar to animate up. Setting this to false will cause the Eq bar to animate down. Once the maximum or minimum heights are reached, direction will change accordingly. 

`setTiming(int)` - sets the timing of the animation. This can be used to slow down the animation. 
> The value provided acts as the denominator in setting the timing at a fraction of normal speed. That is, providing 1 is the same as setting the timing to default. Providing 2 sets the speed to 1/2. Providing 3 sets the timing to 1/3 and so on. Timing is affected by skipping updates between ticks. For example, setting the timing to using 4 means the Eq bar will only be updated every 4th tick. 

## Usage  

### Adding the library to your sketch  
You will need to add the NeoMatrixEqBar library to your sketch. First install the NeoMatrixEqBar library in your Arduino IDE. Inside of the Arduino IDE, click Sketch->Include Libarary->NeoMatriEq

### Declaring Variables
The examples below use the [NeoPixel Featherwing][NEOPIXEL_FEATHERWING]. The NeoMatrix EQ Bar needs an instance of an `Adafruit_NeoMatrix`. You will need to declare your `Adafruit_NeoMatrix` like normal, before the `setup` method in your sketch. 

**IMPORTANT:** the constructor for the Eq Bar requires a pointer to your `Adafruit_NeoMatrix`. You do not need any understanding of pointers, you just need to know that you **MUST** put an ampersand `&` in front of the name of your matrix. If your matrix objec is named `matrix` you will pass it to the Eq bar constructor by calling it `&matrix`. 

**Declare your `Adafruit_NeoMatrix`**
```
//matrix constants
const int MATRIX_PIN = 6;
const int MATRIX_WIDTH = 8;
const int MATRIX_HEIGHT = 4;
const int MATRIX_PIXEL_TYPE = NEO_GRB + NEO_KHZ800;
const int MATRIX_BRIGHTNESS = 10;

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
```

Once your `Adafruit_NeoMatrix` has been declared, you can begin declaring NeoMatrix Eq Bar variables.
It is recommended that you declare your EQ bar variables at the top of your sketch, outside of your sketch's methods, making them available to the whole sketch, just like the `Adafruit_NeoMatrix`. You can declare your Eq Bars one at a time or put them into an array. 

*Note: * using an array makes looping over your Eq Bars so they can all be updated and ticked a lot easier.

**Setting up separate Eq Bar variables**
```
NeoMatrixEqBar eqBar1;
NeoMatrixEqBar eqBar2;
NeoMatrixEqBar eqBar3;
```

**Setting up an array of Eq Bar variables**
```
//this creates an empty array with a size of 8
NeoMatrixEqBar eqBars[8];
```

### The setup method  
Inside of the setup method, you will need to initialize the `Adafruit_NeoMatrix` as usual. 
The code below starts the matrix, sets the brightness from a variable we declared, clears the 
matrix and calls `show()` to display out cleared matrix. 

```
  //init the matrix
  matrix.begin();
  matrix.setBrightness(MATRIX_BRIGHTNESS);
  matrix.clear();
  matrix.show();
```

Once your matrix has been initialized, you can begin creating Eq Bars. 
```
NeoMatrixEqBar eqBar1;
//more code....

void setup(){
    //matrix init code...

    //assign the eqBar
    eqBar1 = NeoMatrixEqBar(&matrix, 0, 0, MATRIX_HEIGHT);

    //call begin on the eq bar
    eqBar1.begin();

    //now you can begin calling methods on the eq bar...
    //for example, randomizing the animation speed
    eqBar.randomizeSpeed(true);
}
```

If you declared and array of Eq Bars, you could just as easily use a for loop
to create an Eq Bar for each index in the array. 

```
NeoMatrixEqBar eqBars[8];
//...

void setup(){
    //matrix init code...

    //create an Eq Bar for each column in our matrix
    for(int i = 0; i < MATRIX_WIDTH; i++) {
        NeoMatrixEqBar eqBar = NeoMatrixEqBar(&matrix, i, 0, MATRIX_HEIGHT);

        //call begin
        eqBar.begin();

        //now you can begin calling methods on the eq bar...
        //for example, randomizing the animation speed
        eqBar.randomizeSpeed(true);

        //assign it to your array
        eqBars[i] = eqBar;
    }

}
```

### Updating the Eq Bar  
In order for your Eq bar to show animations, you must update it using the `tick` method. For example, if you can call `tick` inside of your `loop` method and then follow it with a delay to control the animation speed. 

**IMPORTANT:** if you do not call `tick`, the Eq bar will not update.

```
//matrix and eq bar init and setup code...

void loop() {
    //call tick to update the animation
    eqBar1.tick();

    //wait time between ticks. shorter delays == faster speeds
    delay(100);

    //clear out the display
    matrix.clear();
}
```


[NEOPIXEL_FEATHERWING]: https://www.adafruit.com/products/2945
[GITHUB_ADAFRUIT]: https://github.com/adafruit?
[LIB_GFX]: https://github.com/adafruit/Adafruit-GFX-Library
[LIB_NEOPIXEL]: https://github.com/adafruit/Adafruit_NeoPixel
[LIB_NEOMATRIX]: https://github.com/adafruit/Adafruit_NeoMatrix