# Depth-Detector

## What is it?
This is a preliminary test of a depth tracking software that tracks an object displaying its size and distance from the camera. The inital screen allows the user to calibrate the camera by holding the object at a distance of 12" or one foot from the camera, then pressing the  ready button/`ESC` key on the user's keyboard. From there, the code will sync this distnace to calibrate the object's distance in relation to pixel size. The final screen will allow the user to see the object as it moves around as well as the different contours generated.

## Constraints
Currently, the code is set to track objects with the color blue. This can be changed in the file `Process.cpp` In the function `HSVConverter` the user can choose the HSV values to select the object they want to search for.