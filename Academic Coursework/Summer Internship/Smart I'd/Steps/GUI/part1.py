import tkinter as tk
import serial

# Initialize serial port
ser = serial.Serial('COM12', 115200)  # Adjust COM port and baud rate as necessary

# Create tkinter window
root = tk.Tk()
root.title("Pointer Display")
root.configure(bg="black")

# Define canvas size and padding
canvas_size = 1000
drawable_size = 800  # Size of the drawable area
padding = (canvas_size - drawable_size) // 2

# Create frame to act as the box or rectangle
box_frame = tk.Frame(root, width=canvas_size, height=canvas_size, bg='black')
box_frame.pack()

# Create header frame
header_frame = tk.Frame(root, bg="black")
header_frame.pack(fill="x")

# Create header label
header_label = tk.Label(header_frame, text="Room - 1", font=("Helvetica", 24), bg="black", fg="white")
header_label.pack(pady=10)

# Create dropdown menu
options = ["Room - 1", "Room - 2", "Room - 3", "Room - 4", "Room - 5", "HOME"]
dropdown_var = tk.StringVar(root)
dropdown_var.set(options[0])  # Set default value
dropdown_menu = tk.OptionMenu(header_frame, dropdown_var, *options)
dropdown_menu.config(font=("Helvetica", 14), bg="black", fg="white", width=10)
dropdown_menu.pack(side="left", padx=20, pady=10)

# Create canvas as the drawing area
canvas = tk.Canvas(box_frame, width=drawable_size, height=drawable_size, bg='gray')
canvas.pack(padx=padding, pady=padding)

# Create rectangle to represent the drawable area
canvas.create_rectangle(0, 0, drawable_size, drawable_size, outline='gray')

# Create pointer on canvas with increased size
pointer_radius = 10
pointer = canvas.create_oval(0, 0, pointer_radius * 2, pointer_radius * 2, fill='red')

# Variable to keep track of previous pointer position for tracing
prev_x = None
prev_y = None
trace_line = None

# Function to update pointer position based on received data
def update_pointer():
    global prev_x, prev_y, trace_line
    
    # Read data from serial port
    data = ser.readline().decode().strip()  # Read data from the serial port
    
    # Check if the received data contains valid position information
    if "Device Position: (" in data:
        try:
            # Extract x, y coordinates from the data
            start_index = data.find("(") + 1
            end_index = data.find(")")
            coordinates = data[start_index:end_index].split(',')
            x, y = float(coordinates[0]), float(coordinates[1])
            
            # Ensure coordinates are within valid range (0-100)
            if 0 <= x <= 450 and 0 <= y <= 315:
                # Map x, y coordinates to fit within the canvas dimensions
                mapped_x = (x / 100) * drawable_size
                mapped_y = (y / 100) * drawable_size

                # Update pointer position on canvas
                canvas.coords(pointer, mapped_x - pointer_radius, mapped_y - pointer_radius, mapped_x + pointer_radius, mapped_y + pointer_radius)
                
                # Draw trace line from previous position to current position
                if prev_x is not None and prev_y is not None:
                    if trace_line is not None:
                        canvas.delete(trace_line)
                    trace_line = canvas.create_line(prev_x, prev_y, mapped_x, mapped_y, fill='blue')
                    
                # Update previous pointer position
                prev_x, prev_y = mapped_x, mapped_y
        except (ValueError, IndexError):
            pass  # Ignore invalid or unexpected data

    # Schedule the next update
    root.after(100, update_pointer)

# Start updating the pointer position
update_pointer()

# Run the tkinter event loop
root.mainloop()
