# rainbow-pixels
#### Cycle a WS2812B RGB LED through the visible color spectrum

This example program demonstrates the use of a couple of ```for``` loops to cycle a [WS2812B](https://www.adafruit.com/product/1655) Red/Green/Blue Light Emitting Diode (LED) through the visible color spectrum (that is, ROYGBIV).  We're using the [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel) to interact with the WS2812B.

### How Color is Set
The color of the LED is set by calling the ```setPixelColor()``` method, and supplying it with four values:

1. the LED number (starting from 0)
2. red value (0-255)
3. green value (0-255)
4. blue value (0-255)

Just like with paint, we can control how much red, green, and blue we put into our mixture, and can adjust them accordingly to make any color we want.  For example, to make solid red, our "RGB" values would be ```255, 0, 0``` (full red, no green, no blue).  To make purple (a mixture of red and blue), we could use ```255, 0, 255``` (full red, no green, full blue).

### Traversing the Rainbow!

To smoothly transition along the visible color spectrum, we have to understand the pattern that our RGB ratios must follow in order to transition along the color spectrum: ```red -> orange -> yellow -> green -> blue -> indigo -> violet```.  Take a look at the graphic below:

![Visual Reference](https://github.com/insdavm/rainbow-pixels/raw/master/Guide.png)

On top, we have the rainbow, from red to violet, repeated twice.  Below, we have colored lines indicating where each color (red, green, or blue) should be on the 0-255 scale.  For example, look at the green area on the rainbow.  Just below it, you'll see the red line has descended into the ```0``` value, and the green has steadily climbed from ```0``` (when the color was all red), up to ```255```, giving us a full green color.   Next we move from green to blue, which means the green descends from ```255``` to ```0``` all while the blue color ascends from ```0``` to ```255```.  **_At any given time, only two colors are moving, while the 3<sup>rd</sup> color is at 0_**

#### Only Two Colors Are Moving At Any Given Time

And we'll give those two colors names:

* Decrementing Color (or ```dC```)
* Incrementing Color (or ```iC```)

These colors are just what they seem.  ```dC``` is decrementing, meaning it starts at ```255``` and ends at ```0```.  Conversely, the incrementing color, ```iC```, steadily increments from ```0``` to ```255```.  And the 3<sup>rd</sup> color?  It's at 0 during this time because, remember, only 2 colors are "moving" at any given time (refer back to the lines on the graphic if you're confused).

#### Which Colors Decrement and Increment?

Our loop makes three rotations to cycle through the entire color spectrum.

###### Loop One

dC | iC | Off-Color
---|---|---
Red | Green | Blue

###### Loop Two

dC | iC | Off-Color
---|---|---
Green | Blue | Red

###### Loop Three

dC | iC | Off-Color
---|---|---
Blue | Red | Green

**Do you see the pattern?**

### How It Looks In Code

The code stores the RGB color values in an array called ```rgb```.

* ```rgb[0]``` = red
* ```rgb[1]``` = green
* ```rgb[2]``` = blue

To make the color **blue**, we would need to set the values like so:

```c
rgb[0] = 0;
rgb[1] = 0;
rgb[2] = 255;
```

To make one color increment and another decrement along the 0-255 scale range at the same time, we can use a ```for``` loop that runs 255 times.  At the start of the loop, we will set the decrementing color (```dC```) to ```255```, and decrease it by 1 after each execution of the loop.  Conversely, we'll start the incrementing color (```iC```) at ```0``` and add 1 to it every time the loop executes.

Loop Cycle | dC Value | iC Value
---|---|---
0 | 255 | 0
1 | 254 | 1
2 | 253 | 2
... | ... | ...
253 | 2 | 253
254 | 1 | 254
255 | 0 | 255

After we set the dC and iC to the appropriate values for the loop cycle that we're on, we need to tell the LED what color to be.  We'll do that with ```setPixelColor()``` and ```show()```.  We also need to include a small delay at the end of each loop cycle.  If we ran this loop as fast as the computer could execute it, it'd be a really quick transition through the rainbow.  We'll add a 30 millisecond delay after each loop cycle with ```delay(30)``` to slow it down.  You can make this number bigger to slow the loop down even more!

Now that we know how to take two colors and mix them to blend from one major color on the spectrum to another, we have to figure out how to decide which two colors to mix!

#### Choosing What Colors dC and iC Are and Nesting the Loops

The loop above runs 255 times, one time for each value that a color can be (from 0-255).  That loop will run inside of another loop, which runs 3 times (one time for each color combination (**_ref_** *Which Colors Increment and Decrement?* above).  And these two loops run inside even another loop which infinitely repeats while the program is running!  Put it all together, and our nested loops look like this:

```c
/* this loop runs infinitely */
mainLoop() 
{

	/* this loop runs three times */
	threeLoops()
	{
	
		/*
	   	 * Each time this loop executes, we increase dC by 1 and make iC equal
		 * dC plus one.  If, however, dC equals 2 (blue), then we wrap around
		 * and make iC equal to 0 (red).
		 */
		 
		
		/* this loops runs 255 times */
		twoHundredAndFiftyFiveLoops()
		{
			
			/*
			 * Each time this loop executes, we increase iC by 1 and decrease dC by 1,
			 * then we set the color of the LED to this new color
			 */
	
		}
	
	}

}
```

### Do It

Now look at each line of the code and figure out how it works! 


