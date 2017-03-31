/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/

/*
    Constructor method: 
*/
NeoMatrixEqBar::NeoMatrixEqBar(Adafruit_NeoMatrix *_matrix, int _column, int _height, int _maxHeight)
{
    //assign instance variables...
    matrix = _matrix;
    column = _column;
    height = _height;
    maxHeight = _maxHeight;
}

/* Sets the color of the EqBar using Adafruit's Wheel code' */
NeoMatrixEqBar::setColor(int colorWheelPosition)
{
    
}

/* Adafruit's  */
uint32_t NeoMatrixEqBar::colorWheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }

    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }

    WheelPos -= 170;
    return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
