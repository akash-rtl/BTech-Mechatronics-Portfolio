import tkinter as tk
import serial

# Create tkinter window
root = tk.Tk()
root.title("Live Location Tracker")
root.configure(bg="black")

# Define canvas size and padding
canvas_width = (450*2)
canvas_height = (315*2)
padding_x = (canvas_width - canvas_height) // 2
padding_y = 10  # Adjust as necessary

# Create frame to act as the box or rectangle
box_frame = tk.Frame(root, width=canvas_width, height=canvas_height + 2 * padding_y, bg='black')
box_frame.pack()

# Create canvas as the drawing area
canvas = tk.Canvas(box_frame, width=canvas_width, height=canvas_height, bg='gray')
canvas.pack(padx=padding_x, pady=padding_y)

# Variable to store pointers and their labels
pointers = {}

# Initialize serial port
ser = serial.Serial('COM12', 115200, timeout=1)  # Adjust COM port and baud rate as necessary

# Variable to accumulate received data within a cycle
cycle_data = ""

# Function to update pointers based on received data
def update_pointers():
    global pointers, cycle_data
    
    # Read data from serial port
    try:
        line = ser.readline().decode(errors='ignore').strip()
        print("Received data:", line)
        
        # Accumulate data within a cycle
        if not line.startswith("---"):
            cycle_data += line + "\n"
        else:
            # Cycle ended, clear previous pointers and labels
            for pointer, label in pointers.values():
                canvas.delete(pointer)
                canvas.delete(label)
            pointers = {}
            
            # Display the most recent coordinates
            print("Cycle ended, displaying recent coordinates:")
            print(cycle_data)
            display_recent_coordinates(cycle_data)
            
            # Reset cycle data
            cycle_data = ""
                
    except Exception as e:
        print("Error:", e)
    
    # Schedule the next update
    root.after(100, update_pointers)

# Function to display the most recent coordinates
def display_recent_coordinates(data):
    # Process the data to extract the most recent coordinates
    lines = data.strip().split("\n")
    for line in reversed(lines):
        if line.startswith("(R1,"):
            # Extract x, y coordinates and address from the data
            data = line.split(":")[0]  # Split line by colon to get data before colon
            data = data.replace("(R1,", "").replace(")", "").split(",")  # Extract x and y coordinates
            x, y = float(data[0].strip()), float(data[1].strip())
            address = line.split(":")[1].strip()
            print("Parsed coordinates and address:", x, y, address)
            
            # Map x and y coordinates
            mapped_x = (x / 4.5) * canvas_width
            mapped_y = (y / 3.15) * canvas_height
            
            # Ensure mapped coordinates are within valid range (0-canvas_width/height)
            if 0 <= mapped_x <= canvas_width and 0 <= mapped_y <= canvas_height:
                # Create new pointer and label
                pointer = canvas.create_oval(mapped_x - 5, mapped_y - 5, mapped_x + 5, mapped_y + 5, fill='red')
                label = canvas.create_text(mapped_x + 10, mapped_y, text=address, anchor='w', fill='white')
                pointers[(x, y)] = (pointer, label)

# Start updating the pointers
update_pointers()

# Run the tkinter event loop
root.mainloop()
