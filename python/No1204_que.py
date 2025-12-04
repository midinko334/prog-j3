import sqlite3
DatabaseConnection = sqlite3.connect("clubmember.db")
Database = DatabaseConnection.cursor()

Database.execute("SELECT * FROM tel")

print(Database.fetchall())
DatabaseConnection.close()
