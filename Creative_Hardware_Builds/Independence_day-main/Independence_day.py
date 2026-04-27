import tkinter
import pyttsx3
import serial

ser = serial.Serial(port="COM14", baudrate = 9600, bytesize = 8, timeout=2,stopbits = serial.STOPBITS_ONE)

window =  tkinter.Tk()

window.title("Enactus Sales")

window.geometry('1080x1920')

window.configure(bg = 'black')





# Load the image using the PhotoImage class
image = tkinter.PhotoImage(file=r"E:\Projects\Independence Day\Codes\flag.gif")
    # Create a label to display the image
label = tkinter.Label(window, image=image)
    # Pack the label to display it in the window
label.pack()







def entry(event):
    
    speak = pyttsx3.init()
    #user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
    speak.setProperty("rate",125)

    voices = speak.getProperty('voices')
    speak.setProperty('voice',voices[2].id)


    ser.write("1".encode('Ascii'))
    speak.say("Hello I am enacto. Happy Independence Day")

    speak.runAndWait()

    
    speak.setProperty('voice',voices[1].id)

    speak.say("Swatantrata Diwas, ki hardik shubhkaamnaye, Jai Hind, Vande Matram ")

    speak.runAndWait()
    

window.bind("<Return>",entry)



window.mainloop()