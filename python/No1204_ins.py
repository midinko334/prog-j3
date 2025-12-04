import sqlite3

DatabaseConnection = sqlite3.connect("clubmember.db")
Database = DatabaseConnection.cursor()

Data=[
	('04383041311',"Manabu Honto"),
	('04383041313',"Raku Genki"),
	('04383041314',"Omoroi Tanoshii"),
	('04383041316',"Mirai Akarui"),
	('04383041317',"Sugoku Ureshii"),
	]

Database.executemany("INSERT INTO tel VALUES (?,?)",Data)

DatabaseConnection.commit()
DatabaseConnection.close()

