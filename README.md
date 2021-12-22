# Brain Controlled Arm
Arduino-based robotic arm controlled by brain waves.

Uses [Brain][1] library to process EEG data extracted from a [NeuroSky][2] board. The processed data is then used to determine what angle information to send to the servo motor that controls the arm movement.  

A nRF24L01 wireless transceiver module is used to communicate between the EEG reader and robotic arm microcontrollers.

## Circuit diagrams

<img src="assets/circuit_diagram_1.png" width="600"> 

<img src="assets/circuit_diagram_2.png" width="600"> 

[1]: https://github.com/kitschpatrol/Brain
[2]: http://neurosky.com/
