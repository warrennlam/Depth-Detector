# Depth-Detector

## What is it?
This is a preliminary test of a depth tracking software that tracks an object and displays its size and distance from the camera. The inital screen allows the user to calibrate the camera by holding the object at a distance of 12" or one foot from the camera. Then, press the Ready Button/`ESC` key on the user's keyboard. From there, the code will sync this distance to calibrate the object's distance in relation to pixel size. The final screen will allow the user to see the object as it moves around and the different contours generated.

## Constraints
Currently, the code is set to track objects with the color blue. This can be changed in the file `Process.cpp` In the function `HSVConverter`, the user can choose the HSV values to select the object they want to search for.

## Example
An example of this code in action can be found through the file `DepthDetectorVideo.mp4`. It shows me going through the whole sequence and code, following the desired object.

## How to Run the Program

### 1. Clone the Repository
```bash
git clone https://github.com/warrennlam/Depth-Detector.git
```

### 2. Install OpenCV
Mac:
```bash
brew install opencv
```
Windows:
```bash
https://opencv.org/releases/
```
Install via the link

### 3. Build the Project
```bash
cd Depth-Detector/build
./Detector
```
Make sure that you are in the build folder!
