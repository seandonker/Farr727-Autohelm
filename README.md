# Farr727-Autohelm
Tiller push/pull based autohelm for a sailboat. Project includes C++ code, CAD files, circuit board files, and pictures. 
This design was started in June, 2021 and it is almost complete, just requiring a few more 3D printed parts, the GUI design to be finished,
and final PID tuning on the boat. 

Commercial auto helms are available for boats using a tiller instead of a wheel (wheel or rudder moving auto helms are much more common) but they are expensive
for the quality of product you get. They are often loud, have primitive controls, and require a separate power source on the boat (which our boat does not have).
The goal of this project was to create an autohelm that was fully battery operated, had a better user interface experience, and was very quiet in operation. 

This project features two main design elements; the controller and the tiller arm receiver. The controller's main function is to sense the boat's
heading and send that data to the tiller arm receiver where it will be translated into rudder movement to correct for any deviations in the boat's course. 
The receiver takes the data sent by the controller and uses a PID loop to determine the correct amount of stepper motor rotation which translates into how
far the tiller moves left or right. A simple diagram of the system can be seen below.  
![IMG_0014](https://user-images.githubusercontent.com/121892380/211075521-193c2be1-065a-43e9-989c-7a9a6bd88152.JPG)

<b>CONTROLLER<br>
   ----------
The controller unit features a relatively powerful arm microcontroller (Teensy 4.0) that runs a 9-axis IMU heading routine. The teensy also communicates with the bluetooth radio (nrf2401+) in order to send the error in the heading, PID values, and tilt angle of the boat to the receiver. The controller also features four momentary buttons for user input along with an e-paper display and a real time clock as the pesky lift bridge in port stanley only opens every 30 minutes! It uses a wireless charging coil for charging in order to keep it as water tight as possible and the two internal 18650 batteries should last 8+ hours.
<p float="left">
  <img src="https://user-images.githubusercontent.com/121892380/210914668-cd4ef4ab-563b-482b-93ef-31b50ed1c9d5.jpg" width="180" />
  <img src="https://user-images.githubusercontent.com/121892380/210915485-e98aab29-ede7-4280-8e8f-d90ad4688586.jpg" width="180" /> 
  <img src="https://user-images.githubusercontent.com/121892380/210914699-9443a2a8-9326-496b-9267-04300021ea79.jpg" width="180" /> 
  <img src="https://user-images.githubusercontent.com/121892380/211074864-240973e2-788b-49d9-847b-579dc2844317.jpg" width="180" /> 
  <img src="https://user-images.githubusercontent.com/121892380/210914710-5abbca31-395f-491c-9223-368d248c31f9.jpg" width="180" /> 
</p>

<b>TILLER ARM RECEIVER<br>
   -------------------
The tiller arm receiver has a more power efficient and slower microcontroller (Teensy LC) as its main function is to receive the PID data, run the PID loop, and create the desired pulses for the stepper motor driver and none of those routines require much processing. The trinamic 2209 stepper motor driver was used because of its patented quiet step function so the motor operates almost silently. To power the unit, 12 18650 batteries were used in a 6s2p configuration to provide a maximum of 25.2 volts for the motor driver. This high voltage allows the motor to spin faster as the high voltage overcomes the back EMF reducing the risk of stalling and stuttering. The microcontroller monitors the voltage of the battery pack through a voltage divider and periodically sends back the value to be displayed on the control unit. 
<p float="left">
  <img src="https://user-images.githubusercontent.com/121892380/211089859-366ed124-19c5-4137-8fcb-ffda074a8cf4.jpg" width="250" />
  <img src="https://user-images.githubusercontent.com/121892380/211087014-2091acc4-ef81-4114-ab59-10ca04f46ff1.jpg" width="250" />
  <img src="https://user-images.githubusercontent.com/121892380/222808660-f863f8d0-dad8-48e3-bd90-84df4c73f221.jpg" width="250" />
  <img src="https://user-images.githubusercontent.com/121892380/211087033-18189b5c-aa84-4c96-986b-88a4c8463b72.jpg" width="275" />
  <img src="https://user-images.githubusercontent.com/121892380/211087054-d004be87-71da-4902-a3eb-5f1a337102f1.jpg" width="275" />
</p>
  
<b>FINISHING TOUCHES<br>
   -----------------
Before the system can be tested, the GUI has to be roughly completed in order to change PID values on the fly. As for 3D printed parts, a mounting bracket where the controller can slide into needs to be designed. After testing the system and tuning of the motor current on the motor driver, a cover for the tiller arm will be designed and printed as well. The final step will likely be making the GUI look more professional with graphics and better element alignment.  

