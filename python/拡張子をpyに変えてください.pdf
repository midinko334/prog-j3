data = "Mirai-20,Tokyo,Computer; Ureshii - 22 , Osaka , Electronics ; Tanoshii-19,Kyoto,Control"

# Split the entries by semicolon
entries = data.split(';')

for entry in entries:
    # Remove spaces and split by comma
    parts = [p.strip() for p in entry.replace('-', ',').split(',')]
    
    name = parts[0]
    age = parts[1]
    city = parts[2]
    field = parts[3]
    
    print(f"{name} is {age} years old, lives in {city}, and studies {field} Engineering.")

