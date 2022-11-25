# Parking-System-using-Arduino
![WhatsApp Image 2022-11-25 at 19 04 50](https://user-images.githubusercontent.com/90156505/204030759-726ae5de-cfbf-436b-8b73-6becf165d515.jpg)
I developed this project for the course: Mircocontroller System Design Lab (ECNG 3509)
It was required to design a microcontroller based parking system. 
In the model, a motorized arm is used to open and close the single entry/exit gate. 
The number of empty slots is continuously displayed on the LCD at the parking entrance. 
When the total number of parking slots is complete, an excuse message is displayed and a red light is ON. 
In the contrary, when at least 1 slot is empty, a green light is ON.
The complete status of the gate: Open/Close, the number of empty slots as well as the temperature is reported to the system server via Ethernet connection. 
This communication is useful for error log, data reporting and monitoring.

The project has the following components:
1. Arduino Due
2. LCD display
3. Opto-couplers
4. Temperature sensor LM35
5. Ethernet Arduino shield
6. Keypad 
7. Motor

The following is a design on paper to the system prior to execution: 
![image](https://user-images.githubusercontent.com/90156505/204032181-e92b2595-3571-408f-87d7-97117d18dd5e.png)
