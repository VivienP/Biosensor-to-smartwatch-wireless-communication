##################################################################
###   A python script to save the data into a local database   ###
##################################################################

import sqlite3
import os
import get_ecflex_data

# def connect_to_db():
#     conn = sqlite3.connect('database.db')     # Establish a connection to the database and create a connection object. database.db is the database file.
#     return conn

def check_db(database):
    os.path.exists(database)       # Check if the file already exists in the system.

def add_read_value_to_db(db_file, schema_file):
    if check_db(db_file):
        print('Database already exists. Exiting...')
    
    with open(schema_file, 'r') as rf:
        schema = rf.read()                           # Read the schema from the file.
        print(schema, schema_file)
    with sqlite3.connect(db_file) as conn:
        print('Connection to database established') 
        conn.executescript(schema)                   # Execute the SQL query to create the table.
        print('Database table created')
        conn.executescript(get_ecflex_data.read_callback)        # Save the list of 4 values returned by read_callback into the database.  
        print('Value inserted into the database table')
    print('Connection closed')


def main():
#    c = connect_to_db().cursor()       # Create a cursor to the Database.
    db_file = '/home/vivien/Documents/GitHub/Biosensor-to-smartwatch_wireless_communication/database.db'
    schema_file = '/home/vivien/Documents/GitHub/Biosensor-to-smartwatch_wireless_communication/schema.sql'
#    connect_to_db()
    add_read_value_to_db(db_file, schema_file)

if __name__ == "__main__":
    main()
