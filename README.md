# Rathalos Gambling

![image](https://github.com/user-attachments/assets/3bd21988-59e8-46bc-943a-58308a45042d)


**Hunt Tool** is a simple desktop application that simulates a monster hunting experience. The goal is to hunt the legendary Rathalos and try to obtain its rare drop, the **Rathalos Mantle**. Every time you click the "Hunt!" button, you have a **3% chance** to get the Mantle. If you fail, you get nothing! The tool also plays sound effects to enhance the hunting experience.

---

## Features

- **Hunt Rathalos**: Click the "Hunt!" button to start the hunt.
- **Random Drop Chance**: 3% chance to get the Rathalos Mantle.
- **Sound Effects**: Unique sounds for success and failure.
- **Image Display**: Shows an image of Rathalos during the hunt.

---

## Requirements

- **Windows OS**: The tool is built for Windows using the WinAPI.
- **Visual Studio Build Tools**: Required to compile the project.
- **GDI+**: Used for loading and displaying the PNG image.

---

## How to Use

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/hunt-tool.git
   cd hunt-tool
   ```

2. **Compile the Project**:
   - Open the project in Visual Studio Code.
   - Compile the code using the following command:
     ```bash
     cl main.cpp /EHsc /Fe:HuntTool.exe user32.lib gdi32.lib winmm.lib gdiplus.lib
     ```

3. **Run the Tool**:
   - Execute the generated `HuntTool.exe`.
   - Click the "Hunt!" button to start hunting Rathalos.

4. **Sounds and Images**:
   - Place your `monster.png` in the `images` folder.
   - Place your `success.wav` and `failure.wav` in the `sounds` folder.

---

## Folder Structure

```
hunt-tool/
├── main.cpp               # Main source code
├── images/
│   └── monster.png        # Rathalos image
├── sounds/
│   ├── success.wav        # Sound for successful hunt
│   └── failure.wav        # Sound for failed hunt
└── README.md              # This file
```

---

## How It Works

- **Hunt Mechanics**:
  - Each click on the "Hunt!" button generates a random number between 0 and 99.
  - If the number is less than 3, you get the Rathalos Mantle.
  - Otherwise, you get nothing.

- **Sound Effects**:
  - A unique sound plays depending on the result of the hunt.
  - The sound is played asynchronously, so it doesn't block the application.

- **Image Display**:
  - The Rathalos image is loaded using GDI+ and displayed in the center of the window.
