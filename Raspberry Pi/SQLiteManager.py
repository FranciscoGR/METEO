import sqlite3
from sqlite3 import Error
from datetime import datetime

MAX_TABLE_SIZE = 2880

# Queries to create tables
sql_create_invalues_table_ = """CREATE TABLE IF NOT EXISTS invalues (
                                    date text,
                                    temperature float,
                                    humidity float,
                                    pressure float,
                                    altitude float,
                                    aq float,
                                    hi float
                                );"""

sql_create_outvalues_table_ = """CREATE TABLE IF NOT EXISTS outvalues (
                                    date text,
                                    temperature float,
                                    humidity float,
                                    wind float
                                );"""

# Queries to manage data
sql_insert_invalues_        = """INSERT INTO invalues values(?,?,?,?,?,?,?)"""
sql_get_rowcount_invalues_  = """SELECT COUNT(*) FROM invalues"""
sql_delete_oldest_invalues_ = """DELETE FROM invalues WHERE id = (SELECT id FROM invalues ORDER BY id ASC LIMIT 1)"""

sql_insert_outvalues_       = """INSERT INTO outvalues values(?,?,?,?)"""
sql_get_rowcount_outvalues_ = """SELECT COUNT(*) FROM outvalues"""
sql_delete_oldest_outvalues_ = """DELETE FROM outvalues WHERE id = (SELECT id FROM outvalues ORDER BY id ASC LIMIT 1)"""

# SQLite handle class
class SQLiteManager():
    def __init__(self):
        # Init connection 
        self._connection = None
    
    # Create connection function
    def create_connection(self, dbname):
        try:
            self._connection = sqlite3.connect(dbname)
            return True
        except Error as e:
            print(e)
            return False 
        
    # Table creation function
    def create_default_tables(self):
        try:
            # If connection exists, create tables
            if self._connection is not None:
                cursor = self._connection.cursor()
                cursor.execute(sql_create_invalues_table_)
                cursor.execute(sql_create_outvalues_table_)

            return True
        except Error as e:
            print(e)
            return False

    # Inside values insertion function
    def insert_invalues(self, temp, hum, press, alt, aq, hi):
        # Check connection
        if self._connection is not None:
            try:
                # Get cursor
                cursor = self._connection.cursor()

                # Check rowcount
                cursor.execute(sql_get_rowcount_invalues_)
                rowCount = cursor.fetchone()[0]

                # Delete oldest if row count equals max size
                if rowCount >= MAX_TABLE_SIZE:
                    cursor.execute(sql_delete_oldest_invalues_)

                # Insert data
                cursor.execute(sql_insert_invalues_, \
                               (str(datetime.now()),float(temp),float(hum),float(press),float(alt),float(aq),float(hi)))
                self._connection.commit()
                return True
            except Error as e:
                print(e)
                return False
    
    # Outside values insertion function
    def insert_outvalues(self, temp, hum, wind):
        # Check connection
        if self._connection is not None:
            try:
                # Get cursor
                cursor = self._connection.cursor()

                # Check rowcount
                cursor.execute(sql_get_rowcount_outvalues_)
                rowCount = cursor.fetchone()[0]

                # Delete oldest if row count equals max size
                if rowCount >= MAX_TABLE_SIZE:
                    cursor.execute(sql_delete_oldest_outvalues_)

                # Insert data
                cursor.execute(sql_insert_outvalues_, \
                               (str(datetime.now()),float(temp),float(hum),float(wind)))
                self._connection.commit()
                return True
            except Error as e:
                print(e)
                return False

    # Closing connection function 
    def close_connection(self):
        if self._connection is not None: 
            self._connection.close()
            self._connection = None

