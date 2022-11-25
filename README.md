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
8. LEDs

The following is a design on paper to the system prior to execution: 
![image](https://user-images.githubusercontent.com/90156505/204032181-e92b2595-3571-408f-87d7-97117d18dd5e.png)

### In the section below I have included codes I have written for testing each module independently: 
1. LCD ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033297-c4c980db-b45b-44ec-b622-df62a0540bbd.png)

2. Temperature Sensor ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033343-188f54dd-995f-4fc1-a18c-040ae5521a71.png)

3. Opto-Couplers ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033377-113fcf36-dc27-4973-93e3-8e3760cff8a0.png)

4. Ethernet ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033456-93dc61bf-25a2-4ccc-8f0d-c92543a2172c.png)

5. Motors ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033530-b2cb9918-a64d-4caa-ad7b-dc7be0a724f1.png)

6. Keypad ---------------------------------------------------------------------------------------------

![image](https://user-images.githubusercontent.com/90156505/204033574-ddf775d0-e3a2-4d74-9674-d7538123d1c4.png)
