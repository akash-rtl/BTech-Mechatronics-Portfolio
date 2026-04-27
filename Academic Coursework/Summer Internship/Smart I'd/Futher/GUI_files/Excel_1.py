import pandas as pd

def append_data_to_csv(file_path, new_data):
    # Create a DataFrame for the new data
    new_row = pd.DataFrame(new_data)
    
    # Append the new row to the CSV file without reading it first
    new_row.to_csv(file_path, mode='a', header=False, index=False)
    print(f"Data appended to {file_path}")

# Path to your CSV file
file_path = 'csv_file.csv'

# New data to add
new_data = {'Room 1': ['new_value1'], 'Room 2': ['new_value2']}

# Call the function to append data
append_data_to_csv(file_path, new_data)
