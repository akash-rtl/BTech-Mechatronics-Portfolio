import speech_recognition as sr
import pyttsx3

listener = sr.Recognizer()

while True:
    
    try:

        with sr.Microphone() as source:
            print("Speak Anything: ")
            audio  = listener.listen(source)
            
            
            text = listener.recognize_google(audio)
            print("YOU SAID: ",text)
        
    except:
        print("TRY AGAIN...........")

    
        
        
               
    
        