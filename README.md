# Invitation-Card-for-the-2024-Xi-an-Jiaotong-Liverpool-University-Graduation-Ceremony

## Design Description
The invitation card is primarily themed in shades of purple, which is the 
signature color of Xi'an Jiaotong-Liverpool University. It incorporates a 
profusion of bubbles as decorative elements. Each bubble can be seen as a 
representation of hope, or dreams, or as a vessel for memories, encapsulating 
the cherished moments of university life. 

The card has three phases: the Floating Envelope Phase, the Envelope Phase, 
and the Card Display Phase. 

### Floating Envelope Phase 
Feature list:  
 Background: gradient purple to amplify the spatial perception 
 Envelope: use a timer and glTranslatef() to translate the envelope up 
and down. The envelope can interact with the keyboard to rotate, pan, 
and zoom in 
 Bubble: use a timer and change the radius to Enlarge/shrink the bubble 
 Use a timer and the function glRasterPos2f() to create chat messages 
that appear like bullets. Parameters can be adjusted to control the 
speed of the bullet chat. 
 Falling star: Draw a pentagram using geometric creation and rotation, 
generate random numbers to randomly generate the stars, and use 
translation transformation to make them fall
### The Envelope Phase
Feature list:  
 Envelope: The envelope can be opened on both sides by translation 
 Star: The stars appear based on the coordinate position of the 
interaction with the left mouse button 
 Doctoral Cap: The Doctoral Cap appears based on the coordinate 
position of the interaction with the right mouse button 
### Card Display Phase
Feature list:  
 Lightboard: The lightboard consists of five quadrilateral bases of 
different colors, "XJTLU" letter bulbs, and circular bulbs. By using a 
timer, it continuously changes between the illuminated and off states 
 Paper flight: There are two types of paper airplanes: non-interactive 
and interactive. Non-interactive airplanes fly towards the lower left 
direction at different speeds and slopes. Interactive airplanes can be 
controlled in terms of their movement using keyboard interactions. 
When moving to the left, they are affected by gravity and will descend. 
 Bubbles of different campuses: There are a total of three bubbles. The 
middle bubble represents the central building of the North Campus. 
The left bubble shows an aerial view of the Taicang Campus, and the 
right bubble shows an aerial view of the South Campus. Keyboard 
interactions can be used to control the bubble layers as well as to zoom 
in and out. 
 Rotation bubbles: The rotating bubble spins around the campus 
bubbles, and as the bubble layers switch, the rotating bubble also 
changes accordingly, providing a highlighting effect 
 Balloons: Using keyboard interactions, the balloons will be released 
from the bottom of the card and continuously fly upwards.

## Instructions 
This interactive invitation card has several functions in different phases:
### Floating Envelope Phase 
1. Press "j/J" to accelerate the barrage speed, and "u/U" to decelerate it. 
2. Click "z/Z" to rotate and enlarge the envelope. 

### The Envelope Phase
1. Click the mouse right button to show Doctoral Cap 
2. Click the mouse left button to show the Star 
3. Click "o/O" to open the envelope.
4. 
### Card Display Phase
1. Click "f/F" to release balloons from the bottom of the card. 
2.  Control the interactive paper airplane on the card using the keyboard: 
Press "w/W" to move it upwards. 
Press "s/S" to move it downwards. 
Press "a/A" to move it to the left. 
Press "d/D" to move it to the right. 
When moving to the left, it will gradually descend due to gravity. 
3. Press "l/L" to emphasize the Taicang bubble on the left, then press ”n/N” to 
zoom in, and ”b/B” to zoom out. 
4. Press "m/M" to emphasize the North Campus-Central building bubble  
5. Press "r/R" to emphasize the South Campus bubble on the left, then 
press ”v/V” to zoom in, and ”c/C” to zoom out.
