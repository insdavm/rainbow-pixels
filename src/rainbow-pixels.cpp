/**
 * rainbow-pixels
 * 
 * ...cycles a single WS2812B RGB LED (like the Adafruit NeoPixels)
 * through the visible color spectrum.
 *
 * @author Austin <github.com/insdavm>
 * @date 2017.02.18
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define   PIN           3                                 /* the pin that our LEDs are on */
#define   NUM_PIXELS    9                                 /* the number of WS2812B LEDs in our strand */

Adafruit_NeoPixel p = Adafruit_NeoPixel(NUM_PIXELS, PIN);          /* create a NeoPixel object consisting of one pixel */
uint8_t rgb[3];                                           /* declare an array of 8-bit integers to hold our color values */


void setup()
{
  p.begin();
  p.show();
  p.setBrightness(255);
}

void loop()
{

  /* 
   * rgb[0] is synonymous with red,
   * rgb[1] "                " green,
   * rbg[2] "                " blue. 
   */
  rgb[0] = 255;
  rgb[1] = 0;
  rgb[2] = 0;

  /* 
   * loop through each combination of 
   *     RED   /  GREEN    (dC = 0, iC = 1)
   *     GREEN /  BLUE     (dC = 1, iC = 2)
   *     BLUE  /  RED      (dC = 2, iC = 0)
   */
  for ( int dC = 0; dC < 3; dC++ ) {

    /*
     * make the incrementing color (iC) be one more than
     * the decrementing color (dC) or, if the iC is 2 (blue), 
     * then the dC should wrap around to 0 (red).
     */
    int iC = dC == 2 ? 0 : dC + 1;

    /*
     * now that our incrementing and decrementing colors have
     * been identified, increment and decrement respectively 
     * each one by a value of 1 for 255 times (the range of 
     * possible values for each color)
     */
    for ( int i = 0; i < 255; i++ ) {

      rgb[dC]--;
      rgb[iC]++;

      for ( int a = 0; a < NUM_PIXELS; a++ ) {
	p.setPixelColor(a, rgb[0], rgb[1], rgb[2]);
      }
      
      p.show();
      delay(30);
      
    } 
  }
}
