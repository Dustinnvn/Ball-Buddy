<p align="center">
  <img src="Images/BBlogo.png">
</p>

<h1 align="center">Ball Buddy :softball: </h1>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#key-features">Key Features</a></li>
    <li><a href="#documentation">Documentation</a>
        <ul>
        <li><a href="#cad">CAD</a></li>
        <li><a href="#code">Code</a></li>
      </ul>
    </li>
    <li><a href="#materials">Materials</a></li>
    <li><a href="#progress">Progress</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Ball Buddy is a pet ball launcher developed in my senior design class. It is inspired by a teammates dog which has separation anxiety, which would become exacerbated after work from home is lifed. In response we created a smart ball launcher so that we could help pets keep in touch with their owners from far away.

My main repsonibilites are in charge of designing and coding the ball recovery system. For the chassis design I will be working together with one of my teammates, Jason. I will also be helping on the webapp devlopment by creating a functional backend and database to control the ball recovery system.


## Key Features 
* Autonomous ball recovery and launch
* Controllable through an app or webpage
* 180 degree rotational and launch angles
* Saftey sensors to avoid injury
* Camera to view pets and launch trajectory 

## Documentation 
The CAD designs and code are a work in progress and will have continual updates. Currently the designs are focused for the ball recovery system but will eventually include the entire Ball Buddy. The code is for both the ball recovery system and ball launcher. Additional Raspberry pi code is also featured for software debugging.

### CAD 
All current CAD designs are in the Ball System V1 and V2. V1 was the first mockup design I created for the ball recovery system. It utilized a chain and gear mechanic to have simple stepper motor utilization. This design however was unable to adjust to any future changes to the ball buddy and was scrapped for the current V2 design. The V2 design is based on a CNC/3D printer using gantry rails, pulleys and stepper motors to control the x,y, and z axis. With this new design it is possible to move the ball in any  position within the frame and have room to adjust for other parts. Most parts were redesigned from V1 but I did keep the ball setter hand and ball que. 

All parts were designed in Solidworks and can be converted to STL for printing.

### Code 
The MasterStepper is the current code used to control all 5 stepper motors in the ball recovery system. This includes motor to spin the ball que, 2 motors to lift up the X-axis, and 2 motors to control the X-axis ball setter hand. The code has funcitons to adjust distance and individual controls for each axis. It also takes serial input to move and  outputs serial data for debugging. This code is ran on a Arduino Uno R3.

Utilizing the Arduino for the brute work, I used the Raspberry Pi for the main processing of data. While our software developer worked on setting up a permanent server, I began to develop groundwork Pi code to work with our Arduino. Since I utilized serial communication for the Arduino, I used a usb connection to the Raspberry Pi for both microcontrollers to talk to each other. With communication between the two microcontrollers established, I used the html library in python to create a basic webpage that could send commands to the Pi. This let me access the Pi from a webpage that would send serial data to the arduino which could then relay data back for the Pi to process. The Pi python code was ran on a Raspberry Pi 4

## Materials 
insert_table


## Progress 

insert_png


<!-- CONTACT -->
## Contact 

Dustin Nguyen - dustinnvn@gmail.com

Project Link: [https://github.com/Dustinnvn/Ball-Buddy](https://github.com/Dustinnvn/Ball-Buddy)


