import speech_recognition as sr
import pyttsx3

#########################################

speak = pyttsx3.init()
speak.setProperty("rate",80)

voices = speak.getProperty('voices')
speak.setProperty('voice',voices[1].id)

#text = input("Write the text for input: ")

#speak.say(text)
#speak.runAndWait()


########################################

listener = sr.Recognizer()


while True:
    
    try:

        with sr.Microphone() as source:
            print("Speak Anything: ")
            audio  = listener.listen(source)
            
            
            text = listener.recognize_google(audio)
            text = text.lower()
            
            l = text.split()
            
            print(l)
            
            # .split() is used to convert a string sentence to a list of words 
            
            
            for i in l:
                if i == "tom":
                    text = "Yes Boss"
            
            print("YOU SAID: ",text)
            speak.say(text)
            speak.runAndWait()
        
    except:
        print("TRY AGAIN...........")
        speak.say("TRY AGAIN")
        speak.runAndWait()
    