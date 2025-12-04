import sqlite3
DatabaseConnection = sqlite3.connect("clubmember.db")
Database = DatabaseConnection.cursor()

Database.execute('''CREATE TABLE tel (PhoneNumber text, Name text)''')

DatabaseConnection.commit()
DatabaseConnection.close()
