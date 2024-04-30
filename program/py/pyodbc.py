import pyodbc

cnxn = pyodbc.connect( "Driver={goldilocks};SERVER=192.168.0.120;port=30009;user=sys;pwd=gliese;database=test")
cursor = cnxn.cursor()

sql =  '''select * from TEST'''
res =  cursor.execute(con, sql)
for r in res:
    print(r)
