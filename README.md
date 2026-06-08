# AI companion
This is a movable AI robot with simple DC motors and powered by ESP32-S3 Sense with a round touch display to display emotions.

The objective of building this AI companion is to asist me with daily task, cheer me up when bored and show Soup's cuteness. 

<img width="260" height="372" alt="Screenshot 2026-06-03 at 8 30 08 PM" src="https://github.com/user-attachments/assets/10688ce1-3889-4c1d-8692-d50df5892054" />

## Features:
- power with battery
- cloud AI
- face recognition
- voice recognition
- touch screen

## CAD Model:
<img width="325" height="376" alt="Screenshot 2026-06-03 at 1 47 11 PM" src="https://github.com/user-attachments/assets/8cc756d2-87fd-4f70-b391-ca628628faba" />
<img width="325" height="376" alt="Screenshot 2026-06-03 at 1 48 02 PM" src="https://github.com/user-attachments/assets/54ca4ef5-f84f-4f8a-90e3-f202cd5363a1" />
<img width="325" height="376" alt="Screenshot 2026-06-03 at 1 47 23 PM" src="https://github.com/user-attachments/assets/9dc67446-b11b-49a4-8e2b-a860c7c33592" />

### Gear:

<img width="325" height="349" alt="Screenshot 2026-06-03 at 1 48 35 PM" src="https://github.com/user-attachments/assets/68de14c9-4803-4c25-a530-2382658990a7" />
<img width="325" height="349" alt="Screenshot 2026-06-03 at 1 48 39 PM" src="https://github.com/user-attachments/assets/1aa9e1f1-fa82-4d59-86e7-d8267d8b340f" />

Made in Fusion360.Liz
Access files in [CAD folder](https://github.com/LizOnAir/AI-Companion/tree/main/CAD).

## Wiring
Connect the XIAO pins onto the display headers.
Connect the speaker to the PH connector on the display.

For the motor and battery:

<img width="325" height="349" alt="Screenshot 2026-06-03 at 2 22 24 PM" src="https://github.com/user-attachments/assets/b43ad3d8-648c-4723-92b5-ff33637ad377" />

## Firmware
I used Arduino IDE
- Wake with keywords ("Hey Soup wake up")
- Greet when face recognized
- Response when asked

I trained the AI model using Edge Impulse.

Access files in [Firmware folder](https://github.com/LizOnAir/AI-Companion/tree/main/Firmware).

## Assembly
1. Put the motor into the motor carrier, screw tight with 4 screws at the holes.
2. Attach the small gear to the both side of the motor shafts.
3. Insert 4 big gears into the poles and secure them by melting the rings.
4. Insert the legs at 2 opposite direction and secure them by melting the rings.
5. Screw them onto the body.
6. Secure the camera at the fish eye.
7. Pull the wire of the motor and camera cable through the head via those cutout.
8. Attach the screen to the face.
9. Attach the speaker to the back of the head.
10. Snap the head together.
11. Snap the head to the body.

## BOM:
Here should be [everything](https://docs.google.com/spreadsheets/d/1xFMgOfsnqybYM0GKQvv2iKpGSnntPBDn0rsrXfdRsZs/edit?usp=sharing) you need to make this:
- 1x 1.28 inch TFT Screen Display Module
- 1x Cavity enclosed speaker
- 1x Seeed Studio XIAO ESP32S3 Sense
- 1x 3.7V 1500mAh Lipo Battery 103048
- 1x DC motor
- 4x M3 14mm Screws
- 6x M3 OD4.2 L 4 Heatset inserts

