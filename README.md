# MazeSolver-Nano-2026 🏎️💨

A high-performance line-following and maze-solving robot built on the Arduino Nano platform. This project utilizes PID control and magnetic encoders for precision navigation.

## 🛠 Hardware Design Phase
I have received the core mechanical components (N20 motors, wheels) and the sensor array. 
The project is currently in the **Schematic Design** phase, focusing on:
- **Power regulation:** Implementing a Buck Converter to step down battery voltage for the Arduino Nano and sensors.
- **H-Bridge logic:** Integrating the TB6612FNG driver for efficient motor control.
- **Encoder routing:** Mapping magnetic encoder signals to interrupt pins for precise PID feedback.

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

| Nano Pin | Component | Function |
| :--- | :--- | :--- |
| **D2** | Encoder Left | Interrupt A |
| **D3** | Encoder Right | Interrupt B |
| **D4 / D5** | TB6612 (BIN1/2) | Right Motor Direction |
| **D6** | TB6612 (STBY) | Driver Standby (Active High) |
| **D7 / D8** | TB6612 (AIN1/2) | Left Motor Direction |
| **D9** | TB6612 (PWMA) | Left Motor Speed (PWM) |
| **D10** | TB6612 (PWMB) | Right Motor Speed (PWM) |
| **A0 - A7** | QTR-8RC | IR Reflectance Data |
| **A4 (SDA)** | SSD1306 | OLED Data |
| **A5 (SCL)** | SSD1306 | OLED Clock |

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

## 📸 Component Gallery
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
