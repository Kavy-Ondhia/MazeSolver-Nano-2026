<h1 align="center">MazeSolver-Nano-2026 🏎️💨</h1>

A high-performance line-following and maze-solving robot built on the Arduino Nano platform. This project utilizes PID control and magnetic encoders for precision navigation.

![Project Status](https://img.shields.io/badge/Status-Development-orange)
![Platform](https://img.shields.io/badge/Platform-Arduino_Nano-blue)

<div align="center">
  <table style="width:100%; border-collapse: collapse; border: none; table-layout: fixed;">
    <tr>
      <td rowspan="2" style="width: 60%; border: none; padding: 2px;">
        <img src="media/prototype_1.jpg" 
             style="width: 420px; height: 504px; object-fit: cover; border-radius: 8px;" 
             alt="Prototype Side View" />
      </td>
      <td style="width: 40%; border: none; padding: 2px;">
        <img src="media/prototype_2.jpg" 
             style="width:220px; height: 250px; object-fit: cover; border-radius: 8px;" 
             alt="Prototype Front View" />
      </td>
    </tr>
    <tr>
      <td style="border: none; padding: 2px;">
        <img src="media/prototype_3.jpg" 
             style="width:220px; height: 250px; object-fit: cover; border-radius: 8px;" 
             alt="Prototype Top View" />
      </td>
    </tr>
  </table>
</div>

## 🛠 Prototyping & PCB Manufacturing Phase
The project has moved from theoretical design to **active hardware-in-the-loop (HIL) testing**. I am currently validating a breadboard prototype to finalize signal routing and power stability for the custom PCB fabrication.

### **Current Progress:**
* **Prototype Controller:** Arduino Nano (ATmega328P) using a logic-stable common ground architecture.
* **Dual Motor Drive:** Integrated the **DRV8833 Dual H-Bridge** for the prototype phase, utilizing PWM-direct control to manage motor velocity and direction.
* **Sensor Integration:** Successfully calibrated a **QTR-8RC 8-channel array**. Pin mapping has been optimized (A0–A5, D7, D13) to prevent conflicts with motor PWM timers.
* **Precise Navigation:** Magnetic encoders are mapped to **Hardware Interrupt pins (D2, D3)** to ensure zero-loss pulse counting for PID speed control and distance tracking.

### **PCB Design Priorities:**
* **Signal Integrity:** Separating high-current motor traces from sensitive Encoder and Sensor signal lines to reduce Electromagnetic Interference (EMI).
* **Power Rail Optimization:** Implementing a **Buck Converter** to efficiently step down LiPo battery voltage for the logic circuit, significantly reducing heat compared to linear regulators.
* **Modular Footprint:** The PCB layout is being designed with a modular header to support both **DRV8833** and **TB6612FNG** driver footprints for testing flexibility.

## 👥 Development Team
* **Kavy Ondhia** (@Kavy-Ondhia) - Firmware Architecture & Logic
* **Karunya Jajoo** (@karunya-jajoo) - Hardware Schematic & PCB Design

## 🛠 Hardware Specifications

| Component | Purpose | Datasheet/Reference |
| :--- | :--- | :--- |
| **Arduino Nano** | Main Controller | [Official Manual](https://docs.arduino.cc/resources/datasheets/A000005-datasheet.pdf) |
| **TB6612FNG** | Motor Driver | [Toshiba Datasheet](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf) |
| **N20 Motors** | 6V 200RPM w/ Encoders | [Technical Specs](https://www.handsontec.com/dataspecs/motor/N20-Motor.pdf) |
| **QTR-8RC** | IR Sensor Array | [Pololu Documentation](https://www.pololu.com/docs/0J12) |
| **SSD1306 OLED** | Debugging Display | [Adafruit Datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf) |
| **HC-05** | Bluetooth Module | [HC-05 Datasheet](https://components101.com/sites/default/files/component_datasheet/HC-05-Datasheet.pdf) |
| **LM2596 Buck** | 5V Regulation | [TI Datasheet](https://www.ti.com/lit/ds/symlink/lm2596.pdf) |

## 🔌 Proposed Pin Mapping (Nano)
*This table serves as the "contract" for the schematic design.*

| Standard Pin | KiCad Symbol Label | Component | Function | Status vs. Old |
| :--- | :--- | :--- | :--- | :--- |
| **D2** | D2 (Right Pin 11) | Encoder Left | Interrupt A (Phase A) | UNCHANGED |
| **D11** | D11 (Right Pin 2) | Encoder Left | Phase B (Dir Tracking) | UNCHANGED |
| **D3** | D3 (Right Pin 10) | Encoder Right | Interrupt B (Phase A) | UNCHANGED |
| **D12** | D12 (Right Pin 1) | Encoder Right | Phase B (Dir Tracking) | UNCHANGED |
| **D4** | D4 (Right Pin 9) | TB6612 (BIN1) | Right Motor Dir | UNCHANGED |
| **D5** | D5 (Right Pin 8) | TB6612 (BIN2) | Right Motor Dir | UNCHANGED |
| **D7** | D7 (Right Pin 6) | TB6612 (AIN1) | Left Motor Dir | UNCHANGED |
| **D8** | D8 (Right Pin 5) | TB6612 (AIN2) | Left Motor Dir | UNCHANGED |
| **D9** | D9 (Right Pin 4) | TB6612 (PWMA) | Left Motor Speed (PWM) | UNCHANGED |
| **D10** | D10 (Right Pin 3) | TB6612 (PWMB) | Right Motor Speed (PWM) | UNCHANGED |
| **A0** | D14 (Left Pin 4) | QTR-8RC Pin 1 | IR Reflectance | UNCHANGED |
| **A1** | D15 (Left Pin 5) | QTR-8RC Pin 2 | IR Reflectance | UNCHANGED |
| **A2** | D16 (Left Pin 6) | QTR-8RC Pin 3 | IR Reflectance | UNCHANGED |
| **A3** | D17 (Left Pin 7) | QTR-8RC Pin 4 | IR Reflectance | UNCHANGED |
| **D6** | D6 (Right Pin 7) | QTR-8RC Pin 5 | IR Reflectance | UNCHANGED |
| **A4** | D18 (Left Pin 8) | QTR-8RC Pin 6 | IR Reflectance | **MOVED** (From D13) |
| **A5** | D19 (Left Pin 9) | QTR-8RC Pin 7 | IR Reflectance | **MOVED** (From A6) |
| **D13** | D13 (Left Pin 1) | QTR-8RC Pin 8 | IR Reflectance | **MOVED** (From A7) |
| **D0** | D0 (RX) | NOT USED | Leave Empty for Uploads | **REMOVED** (Finish LED) |
| **A6 / A7** | A6 / A7 | NOT USED | Hardware Input Only | **VOID** |

### ⚠️ Critical Hardware Notes
* **A6/A7 Pins:** These pins on the Nano are **Analog Input Only**. They cannot be used for the QTR-8RC or Motor Standby because they cannot function as Digital Outputs.
* **QTR-8RC Version:** This project uses the **RC (Digital)** version of the sensor. Pins are toggled as outputs to charge the onboard capacitor, then read as inputs to measure discharge time.
* **USB Uploading:** Digital Pin **D0 (RX)** is left disconnected to prevent serial communication conflicts during code uploading.

## 🛠 Hardware Design

![Robot Schematic](hardware/schematic/Schematic_jpg/Schematic_v1.3_photo.jpg)
[Download PDF Version](hardware/schematic/Schematic_pdf/Schematic_v1.3.pdf)

## 🧠 Software Logic & Path Optimization

The robot's intelligence is divided into three layers: **Perception**, **Control**, and **Strategy**.

### 1. Perception & Control (PID)
* **The Error:** Using the QTR-8RC, we calculate the robot's position relative to the center (3500). 
    * $Error = 3500 - \text{Current Reading}$
* **PID Math:** We use Proportional (Muscle) and Derivative (Brakes) logic to calculate correction.
    * `Correction = (Kp * error) + (Kd * (error - lastError))`
    * `LeftSpeed = Base + Correction` | `RightSpeed = Base - Correction`

### 2. The Discovery Phase (Dry Run)
The robot uses a **Preferential Wall-Following Rule** (Straight > Left > Right). 
* **The Log:** Every move is recorded in a memory array.
* **Encoder Mapping:** Encoders track distance in millimeters to ensure precise turns and junction detection.

### 3. Path Optimization (The "Aha!" Moment)
The robot simplifies its recorded path by removing dead ends (represented as 'B' for Back).
* **Logic:** `Left -> Back -> Left` is simplified to `Straight`.
* **Optimization Example:** `L -> B -> L` becomes `S`. This "shrinks" the journey for the final run.

### 4. Advanced Mapping & Exploration
To cover the entire map, the robot utilizes a coordinate-based Node system:
```cpp
struct Node {
  long x;           // X coordinate from encoders
  long y;           // Y coordinate from encoders
  bool visited[3];  // [Left, Straight, Right]
  int parentNode;   // Back-tracking reference
};
```

## 📸 Component Gallery
<p align="center">
  <img src="media/microcontroller.jpeg" width="90%" />
</p>
<p align="center">
  <img src="media/wheels.jpeg" width="30%" />
  <img src="media/motors.jpeg" width="30%" />
  <img src="media/lipo_batteries.jpeg" width="30%" />
</p>
<p align="center">
  <img src="media/sensor_array(1).jpeg" width="45%" />
  <img src="media/sensor_array(2).jpeg" width="45%" />
</p>

## 📂 Project Structure
* `/src`: Final Arduino (.ino) and configuration (.h) files.
* `/hardware`: Schematic diagrams and PCB layouts (In Progress).
* `/media`: Component photos and project progress shots.

---
*Created by [Kavy Ondhia](https://github.com/Kavy-Ondhia)*
