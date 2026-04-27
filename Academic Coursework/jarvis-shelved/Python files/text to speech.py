import pyttsx3

speak = pyttsx3.init()

# RATE: is for speed at which the speaker will speak(keep rate 100)
# VOLUME: is the volume, it lies between 0 to 1 decimal
# VOICE: 1 - Ravi; 3 - Heera



''' Getting and Setting "RATE" 
    keep rate 100 in general
    120 for female(zira -- voices[1].id)
    
    
rate = speak.getProperty('rate')
print(rate)
speak.setProperty("rate",100)
speak.say("Akash Sagar and Satya")
speak.runAndWait()

'''


''' Gettin and setting "VOLUME"

volume = speak.getProperty('volume')
print(volume)

speak.setProperty("volume",0.4)

'''



''' 
voices = speak.getProperty('voices')
#print(voices[1].id)

#by the next step you can get all the voices and their list no.
for i in range(0,5):
    
    print(voices[i].id)

speak.setProperty('voice',voices[0].id)


'''


speak.setProperty("rate",150)

voices = speak.getProperty('voices')
speak.setProperty('voice',voices[1].id)


while True:
    
    
    
    
    text = input("Write the text for input: ")

    speak.say(text)
    speak.runAndWait()
