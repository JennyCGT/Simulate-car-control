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

For recreate the conditions of a real car, a PCB designed was developed for made a scale car the circuit with the principal components is showed:

<p align="center">
<img src="https://github.com/JennyCGT/Simulate-car-control/blob/master/circuito_001.jpg" height="400">
</p>


## Software
The dashboard was developed in LabVIEW.The user can see all the principal components of a dashboard car, the microcontroller communicate with the interface using Serial Port.

<p align="center">
<img src="https://github.com/JennyCGT/Simulate-car-control/blob/master/dash.JPG" height="400">
</p>  

