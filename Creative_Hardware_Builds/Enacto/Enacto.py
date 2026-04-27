import tkinter
import pyttsx3
import serial

ser = serial.Serial(port="COM14", baudrate = 9600, bytesize = 8, timeout=2,stopbits = serial.STOPBITS_ONE)

#from PIL import ImageTk, Image 


window =  tkinter.Tk()

window.title("Enactus Sales")

window.geometry('750x600')

window.configure(bg = 'black')





# Load the image using the PhotoImage class
image = tkinter.PhotoImage(file=r"C:\Users\omaka\Downloads\Enactus logo 2.png")
    # Create a label to display the image
label = tkinter.Label(window, image=image)
    # Pack the label to display it in the window
label.pack(pady = 100)












# pack is used to show the object in the window

l1 = tkinter.Label(window,text = "Enter Your Name: ", font = ("Times New Roman", 50), fg = 'white', bg = 'black').pack()



#image1 = Image.open(r"C:\Users\omaka\Downloads\Enactus logo 2.jpg")
#image1 = img.resize((50, 50), Image.ANTIALIAS)

#logo = PhotoImage(file = r"C:\Users\omaka\Downloads\Enactus logo 2.png").pack()

#label = tkinter.Label(window, text = "Hello World!").pack()

names = tkinter.StringVar()


def entry(event):
    
    speak = pyttsx3.init()
    user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
    speak.setProperty("rate",125)

    voices = speak.getProperty('voices')
    speak.setProperty('voice',voices[2].id)

    ser.write("1".encode('Ascii'))
    speak.say("Hello I am enacto."+"  "+"Welcome "+user+", to the ENACTUS Sales")
     #
    speak.runAndWait()
    
def chalo(event):
     
     speak = pyttsx3.init()
    #user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
     speak.setProperty("rate",125)

     voices = speak.getProperty('voices')
     speak.setProperty('voice',voices[1].id)

    #ser.write("1".encode('Ascii'))
     speak.say("Jaldi Yaha se hato")
     #
     speak.runAndWait()
 
def paani(event):
     
     speak = pyttsx3.init()
    #user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
     speak.setProperty("rate",125)

     voices = speak.getProperty('voices')
     speak.setProperty('voice',voices[1].id)

    #ser.write("1".encode('Ascii'))
     speak.say("Uncle Ji, Paani Peela dijiye")
    
     speak.runAndWait()
     
def samjha(event):
     
     speak = pyttsx3.init()
    #user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
     speak.setProperty("rate",125)

     voices = speak.getProperty('voices')
     speak.setProperty('voice',voices[1].id)

    #ser.write("1".encode('Ascii'))
     speak.say("Tu samjha, nhi tu nhi Samjha")
    
     speak.runAndWait()
     
def paisa(event):
     
     speak = pyttsx3.init()
    #user = textbox1.get()
    #label = tkinter.Label(window, text = user).pack()
     speak.setProperty("rate",125)

     voices = speak.getProperty('voices')
     speak.setProperty('voice',voices[1].id)

    #ser.write("1".encode('Ascii'))
     speak.say("Is Baar, Paisa he Paisa")
    
     speak.runAndWait()
     




textbox1 = tkinter.Entry(window, font = ("Times New Roman", 50) ,fg = 'blue', textvariable = names)
textbox1.place(x = 425, y = 500)

window.bind("<Return>",entry)
window.bind("<[>",chalo)
window.bind("<]>",paani)
window.bind("<'>",samjha)
window.bind("<;>",paisa)
#window.bind("<caps lock>")


#textbox1.tkinter.grid(row = 0, column = 1)
#height = 1, width =10,



#print(names)

























window.mainloop()