#!/usr/bin/python
"""
	Author: Muhammad Zubair
	Student ID: V00757068
	
	Read module handles all the file reading aspect of the editor
	Public functions:
	check -- Accepts a string representing the location of the file and checks if that file exists
	fopen -- Accepts a string representing the location of the file and reads its content into a buffer
	print_file -- Prints the content of the file to the screen
"""
#Import constants from the essential folder
from essentials import constants
def check(loc):
	"""Accepts a string representing the location of the file and checks if that file exists
	Arguments:
	loc - String representing the location of the file
	Returns:
	1 if it was able to open the file, 0 if it IOERROR was found
	"""
	try:
		open (loc)
		return 1
	except IOError as e:
		return 0

def fopen(loc):
	"""Accepts a string representing the location of the file and reads its content into a buffer
	Arguments:
	loc - String representing the location of the file
	Returns:
	multidimensional array containing the data it read from file or None if file could't be opened 
	"""
	try:
		f = open(loc,'r')
		lines = f.readlines()	#Read line by line
		"""split line into a multidimensional array of lines and words"""
		lines = [elem.split() for elem in [item.replace("  "," &^&%+").strip() for item in lines]]
		f.close()
		return lines
	except IOError as e:
		"""return None if there was an error IOERROR"""
		return None

#PrintFile method - Prints the file in lines
def print_file(fopen,first=None,second=None):
	"""Prints the content of the file buffer to the screen, There are two different ways of printing
	Arguments:
	fopen - The file content, a multidimensional array
	first - the starting number to print the lines from  - Optional parameter
	second- the ending number to stop printing lines at - Optional parameter
	Returns:
	None
	"""
	total = len(fopen)	#Calculate the total number of lines
	if ((first is not None) and (second is not None)):
		"""If all three parameters were passed in it prints the lines from start to end"""
		first = int(first)
		second = int(second)
		if first > total or second > total:
			print "No such line range."
		elif(first>=second):
			print constants.WRONG
			print constants.PRINT_1
			print constants.PRINT_2
		else:
			"""If there are no errors, it prints the data to screen"""
			for i, line in enumerate(fopen):
				if i+1 >=first and  i+1 <=second:
					print "%d==%s"%(i+1," ".join(line).replace("&^&%+"," "))
	elif first is not None:
		"""If first is not none"""
		first = int(first)
		if first > total or first < 1:
			print "No such line."
		else:
			for i, line in enumerate(fopen):
				if i+1 == first:
					print "%d==%s"%(i+1," ".join(line).replace("&^&%+"," "))
	else:
		"""If first and second is none then print the entire content of the file"""
		for i, line in enumerate(fopen):
			print "%d===%s" %(i+1," ".join(line).replace("&^&%+"," "))
