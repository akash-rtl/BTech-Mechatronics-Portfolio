import csv

with open("d:\IOT\Projects\Smart I'd\Futher\GUI_files\csv_file.csv", mode = "w") as csvfile:
    fieldnames = ["Room_1", "Room_2"]
    writer = csv.DictWriter(csvfile, fieldnames = fieldnames)
    writer.writeheader()
    writer.writerow({"Room_1":"Jai Jai", "Room_2": "Har"})
    writer.writerow({"Room_1":"Shri", "Room_2": "Har"})
    writer.writerow({"Room_1":"Ram", "Room_2": "Mahadev"})
    writer.writerow({"Room_1":"Bhai", "Room_2": "Jai ho"})