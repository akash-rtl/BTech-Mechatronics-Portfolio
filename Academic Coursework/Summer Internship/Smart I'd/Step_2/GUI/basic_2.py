import tkinter as tk
import serial
import threading

# Serial port configuration
serial_port = 'COM12'  # Update with your serial port
baud_rate = 115200

# Coordinates of Room 1 and Room 2
room_coordinates = {
    "Room 1": [],
    "Room 2": []
}

# Create Tkinter window
window = tk.Tk()
window.title("Live Location Presentation")

# Create canvas for layout
canvas_width = 400
canvas_height = 300
canvas = tk.Canvas(window, width=canvas_width, height=canvas_height, bg='white')
canvas.pack()

# Dropdown menu for room selection
selected_room = tk.StringVar()
selected_room.set("Select Room")

# Function to update pins on canvas based on selected room
def update_pins(*args):  # Add *args to accept the extra argument from OptionMenu
    canvas.delete("pin")  # Clear existing pins on canvas
    room = selected_room.get()
    coordinates = room_coordinates.get(room)
    if coordinates:
        for coord in coordinates:
            x, y = coord
            canvas.create_oval(x, y, x + 5, y + 5, fill="red", tags="pin")

# Dropdown menu
room_menu = tk.OptionMenu(window, selected_room, "Room 1", "Room 2", command=update_pins)
room_menu.pack()

# Function to read data from serial port and update pins
def read_serial():
    try:
        ser = serial.Serial(serial_port, baud_rate, timeout=1)
        while True:
            data = ser.readline().decode().strip()  # Read serial data
            if data.startswith("(") and data.endswith(")"):
                try:
                    room, x_str, y_str, address = data.strip("()").split(",")
                    x, y = float(x_str), float(y_str)
                    if x != 0 or y != 0:
                        room_coordinates[room].append((x, y))
                        if room == selected_room.get():
                            update_pins()  # Update pins for the selected room
                except ValueError:
                    print("Invalid data format:", data)
    except serial.SerialException as e:
        print("Error reading from serial port:", e)


# Function to start reading serial data in a separate thread
def start_serial_thread():
    serial_thread = threading.Thread(target=read_serial)
    serial_thread.daemon = True  # Set the thread as daemon so it terminates when the main program exits
    serial_thread.start()

# Start reading serial data in a separate thread
start_serial_thread()

# Run Tkinter event loop
window.mainloop()
