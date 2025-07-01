import json

# Open and read the JSON file
with open('inputExample.json', 'r') as file:
    data = json.load(file)

# Print the data
print(data['max30100']['heartrate'])