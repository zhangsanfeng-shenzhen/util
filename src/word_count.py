#coding utf-8
import re
import urllib
import urllib2
import datetime
import time
import json
import sqlite3

def sql_open():
	conn = sqlite3.connect('test.db')
	conn.execute("create table if not exists words(word varchar(4) primary key,num integer)")
	return conn

def sql_write(word):
	try:
		conn.execute("insert into words(word,num) values('%s',1)"%(word))
	except:
		conn.execute("update words set num=num+1 where word=='%s'"%(word))

def sql_close(conn):
	conn.commit()
	conn.close()


conn = sql_open()
file = open("/tmp/16005.txt","r")
while True:
	line = file.readline()
	if not line:
		break
	for word in line.decode('utf-8'):
		sql_write(word)
file.close()
sql_close(conn)


conn = sql_open()
cursor = conn.execute("select * from words order by num desc limit 30")
for row in cursor:
	print row[0],row[1]
sql_close(conn)