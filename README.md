# Simulate-car-control
Simulate a car control with an atmega 164p.
## Objetive
In a GUI interface simulate a car dashboard witch the user could see in real time the principal components as: lights states, gasoline level, velocity, mileage, parking camera, 
and the alarms of high temperature and low gasoline level. 

## Hardware
We simulate car´s environment using diferents elements:
<ul> <li> DC motor with a encoder for measure de velocity and the mileage and controlled by a driver(L298N) </li>
  <li> Temperature and level sensor </li>
  <li> Camara</li>
  <li> Led for simulate front,back and direction lights </li> </ul>

All the control was made with an ATMEGA 164p.

<p align="center">
<img src="https://http2.mlstatic.com/wolfelectronics-atmega164p-D_NQ_NP_672622-MEC27104024648_032018-F.webp" height="200">
</p>

## Software
The dashboard was developed in LabVIEW.The user can see all the principal components of a dashboard car, the microcontroller communicate with the interface using Serial Port.


### Main Page
In center side the three variables are shown in a real time graph and in the right side current values and average values are displayed.
<p align="center">
<img src="https://github.com/JennyCGT/Project1/blob/master/images/Capture.JPG" height="400">
</p>  

### Temperature Page, Humidity and Air Quality Page  

In center side the variables are shown in a real time big graph, in the right side current value and average value are displayed, also there is a treeview with date,time and data. This information could be exported to a CVS file called output.  
<p align="center">
<img src="https://github.com/JennyCGT/Project1/blob/master/images/Capture1.JPG" height="350">
</p>  
<p align="center">
<img src="https://github.com/JennyCGT/Project1/blob/master/images/Captureh.JPG" height="350">
</p>  
<p align="center">
<img src="https://github.com/JennyCGT/Project1/blob/master/images/Capturea.JPG" height="350">
</p>  

## MQTT Test
The file prueba_mqtt.py is a simple program to test the communication with the broker and the correct subscription to the diferent topics
