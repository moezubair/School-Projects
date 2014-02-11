#!/usr/bin/python
"""
	Author: Muhammad Zubair
	Student ID: V00757068
	A simple text editor that runs in the terminal with the following options:
	open <path-to-input-file> or o <path-to-input-file>
	save
	print
	quit
	replace
	add
	delete
	"""
import sys
import os
import file.read
"""Import the prompt class from the essentials folder"""
from essentials import prompt
def main():
	"""The main function handles the parameter passed through the command line and starts the main program by calling the prompt
		function from essentials
	"""
	pr = prompt.Promptclass()	#Create an instance of promptclass
	message = "WELCOME TO SIMPLE TEXT EDITOR"
	exitmessage = "Error: Wrong invocation format.\n"
	exitmessage += "Usage 1: ./sedit.py\n"
	exitmessage += "Usage 2: ./sedit.py <path-to-input-file>\n"
	exitmessage += "Bye!"
	
	#The program exits with an error if the user runs it with more than 2 arguments
	if len(sys.argv) > 2:
		sys.exit(exitmessage)
	#If user passes exactly two arguements the program checks the parameters passed
	if (sys.argv[1:2]):
		location = sys.argv[1]
		if (file.read.check(location) == 1):
			pr.function_o(location)
		else:
			print "Error: No Such file."
			print "Starting without an input file"
	else:
		print "Starting without an input file."

	print message
	pr.prompt()
if __name__=="__main__":
	main()
