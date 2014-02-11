#!/usr/bin/python
"""
	Author: Muhammad Zubair
	Student Id: V00757068
	Prompt module that handles the commands passed by the user and takes the appropriate actions
	
	Exported Classes:
	Promptclass : Handles user commands
"""
import file.read
import file.write
from essentials import constants
import sys
import re
class Promptclass:
	"""Promptclass handles the user commands and takes appropriate actions

	Public functions:
	prompt	--	Prompts the user to input a command and passes it to a process method
	process --	Takes a command as parameter and checks to see if its valid. Valid commands are than used to call methods
	function_o --	Opens a file for editing, loading the content into buffer
	function_p --	prints the content of the file read into buffer
	function_s --	Saves the content of buffer into file
	fuction_d --	Deletes lines from the buffer
	function_a --	adds lines or words to the buffer
	function_r --	replaces lines or words in the buffer
	function_q --	Quits the program, if a file is open, it asks the user if they want to save
	function handleparam --	Splits and checks to see if the parameters are passed with correct syntax 
	function yes_no --	Handles the yes or no questions
	"""
	
	ask='sedit:'		#Initial token that is printed before user types anything
	file_open = False	#variable that determines if a file is open
	filename = ''		#Stores the filename of open files
	file_changed = False 	#Stores True if file has been changed, false if it hasn't
	fcontent = ''		#Stores multidimensional array containing the content of open file
	#a list of allowed commmands
	functions = ("open","o","print","p","add","a","delete","d","replace","r","search","c","searep","b","save","s","quit","q")
	
	def prompt(self):
		"""Prompts the user to input a command and passes it to the process method, if the user process method returns false, 
			it stops prompting for input
			
		Arguments:
		None
		"""
		command = raw_input(self.ask+">>")
		while (self.process(command)):
			command = raw_input(self.ask+">>")
			
			
	def process(self,command):
		"""Takes a command as parameter and checks to see if its valid. Valid commands are than used to call methods
		Arguments:
		command - A string representing the entire command that user typed
		Returns:
		True - if the called method returns True
		False- if the called method returns False
		"""
		param = None	#Initializes param to None 
		
		"""Checks if there are more than 1 arguements in user typed command"""
		if " " in command.strip():
			"""splits where the first space occurs, the first part is command and second part is assigned to param"""
			command,param = command.strip().split(None, 1)
		else:
			"""If there was no space, it still splits it to convert the string into a list"""
			command = command.strip()

			
		if command in self.functions:
			"""Checks to see if user typed a correct command and then uses the first character of the command to determine the 
			appropriate method call"""
			result = True
			if (command == "open" or command == "o"):
				result = self.function_o(param)
			elif (command == "save" or command == "s"):
				result = self.function_s(param)
			elif (command == "print" or command == "p"):
				result = self.function_p(param)
			elif (command == "add" or command == "a"):
				result = self.function_a(param)
			elif (command == "print" or command == "p"):
				result = self.function_p(param)
			elif (command == "delete" or command == "d"):
				result = self.function_d(param)
			elif (command == "replace" or command == "r"):
				result = self.function_r(param)
			elif (command == "quit" or command == "q"):
				result = self.function_q(param)
			elif (command == "search" or command == "c"):
				result = self.function_c(param)
			elif (command == "searep" or command == "b"):
				result = self.function_b(param)
			if result is False:
				return False
		else:
			"""If command was not found the program spits out an error"""
			print "Invalid command."
		return True
	def function_o(self,param):
		"""Opens a file for editing, loading the content into buffer
		Arguments:
		param - string representing the paramater user typed after the command
		Returns:
		returns True after operations have been performed"""
		
		if param is None: #Prints errors if used passed no arguement with open command - e.g a file name
			print constants.WRONG
			print constants.OPEN_1
			return True
			
		"""Calls handleparam function to separate the parameters into proper segments for further processing"""
		result = self.handleparam("o",param)
		 
		if result[0] is False: #If handleparam found an error it stops processing and returns to prompt
			return True
		if self.file_changed == True:
			"""Checks to see if a file had been changed..only happens if file was open."""
			answer = self.yes_no("Warning: Would you like to save the changes to '"+self.filename+"' ?")
			if answer is True:
				"""If user wanted to save the changes, it writes the buffer to file"""
				file.write.fwrite(self.filename,self.fcontent)
			self.file_changed = False
		if self.file_open == True:
			self.file_open = False
			"""Modify the initial string that shows open files to remove the old file name"""
			self.ask = self.ask[:self.ask.find(":")+1]
		"""Used the fopen method from file.read module to read the file content into a buffer"""
		self.fcontent = file.read.fopen(param)
		if self.fcontent is None:
			"""If after reading the file the array contains None it prints out a NO FILE error"""
			print constants.NO_FILE
		else:
			"""Otherwise it stores the filename and file_open variables and appends the ask with filename"""
			self.filename = param
			self.ask+=str(param)
			self.file_open = True
	#FUNCTION FOR SEAREP
	def function_b(self,param):
		"""Search for pattern and replace with the user paramater
		parameters: param 
		returns: True/False"""
		pattern = ""
		param2 = None
		param3 = None
		if " " in param:
			param,param2 = param.split(None,1)		#Break the parameter into maximum two pieces
			if " " in param2:
				param2,param3 = param2.split(None,1)
			if (param3 is not None):			#if three parameters were passed 
				if ((param2[len(param2)-1] != '"' or param2[0]!='"') or (param3[len(param3)-1] != '"' or param3[0] !='"')):
					print constants.SEAREP
					return True
				else:
					pattern = param2[1:-1]
					replace = param3[1:-1]
			elif (param3 is None and param2 is not None):	#Print the error if wrong forma
				if (param2[len(param2)-1] != '"'or param2[0]!='"' or param[len(param)-1]!='"' or param[0]!='"'):
					print constants.SEAREP
					return True
			
				else:
					pattern = param[1:-1]
					replace = param2[1:-1]
		else:
			print constants.SEAREP
			return True	
		if (param == "-i" and param2 is not None):	#check for ignore case parameter and pass that flag
			m = re.compile(pattern,re.IGNORECASE)
		else:
			m = re.compile(pattern)
		quit = False						#flag for loop
		found = False				#flag for match
		while (quit is False):
			i =0						#reset i to start from 0
			while i < len(self.fcontent):
				match = False
				content = " ".join(self.fcontent[i])	#join the line with spaces in between
				content = content.replace("&^&%+"," ")	#replace the special character for extra space
				i = i + 1;
				starting = 0
				f = m.search(content)
				if f is not None or (f is None and pr == 'e'):		#print the line number and tab
					print i,
					print "\t",
					match = True
					found = True
				for find in m.finditer(content):	#print the matches with | around the word
					print content[starting:find.start()]+"|"+content[find.start():find.end()]+"|",
					starting = find.end()+1

				if match is True:			#if there was a match, print the end of it			
					print content[starting:]
					#ask for instruction on what to do next
	 				pr = raw_input( "(n)ext, (p)revious, r(e)place, (q)uit or (r)estart? ") 
	 				if (pr == 'q'):						#if user wants to quit
	 					quit = True
	 					break
	 				elif (pr == 'p'):					#if user wants the previous
	 					if (i==1):
	 						i = 0
	 					elif (i == len(self.fcontent)):
	 						i = 0
	 					else:
	 						i = i -  2
	 				elif (pr == 'r'):					#if user wants to restart
	 					i = 0
	 				elif (pr == 'n'):
	 					if (i == len(self.fcontent)):			#if user wants to go next
	 						i = 0
	 				elif (pr == 'e'):					#if user wants to replace
	 					i = i - 1
	 					newstring = m.sub(replace,content,count=1)	#Produce the new string
	 					self.fcontent[i] = newstring.split()		#replace the old one with new one
	 					self.file_changed = True			#set File_changed flag to true
			if found is False:
				print "No matches in the file!"				#if no match was found
				break

	def function_c(self,param):
		"""Search for pattern"""
		pattern = ""
		if " " in param:
			param,param2 = param.split(None,1)		#Break the parameter into maximum two pieces
			if (param2[len(param2)-1] != '"'):		#Make sure last element is a quote
				print constants.SEARCH
				return True
			else:
				pattern = param2[1:-1]
		elif (param[len(param)-1] != '"'):
			print constants.SEARCH
			return True
		else:
			pattern = param[1:-1]
		if (param == "-i" and param2 is not None):
			m = re.compile(pattern,re.IGNORECASE)
		else:
			m = re.compile(pattern)
		quit = False						#flag for loop
		found = False				#flag for match
		while (quit is False):
			i =0						#reset i to 0
			while i < len(self.fcontent):
				match = False				#set match flag to false
				content = " ".join(self.fcontent[i])
				content = content.replace("&^&%+"," ")
				i = i + 1;
				starting = 0
				f = m.search(content)			#Search for an occurance
				if f is not None:			#if search came out with a result print the line number
					print i,
					print "\t",
					match = True
					found = True
				for find in m.finditer(content):	#print the result with | around the word
					print content[starting:find.start()]+"|"+content[find.start():find.end()]+"|",
					starting = find.end()+1

				if match is True:			#if there was a match, print the end of it			
					print content[starting:]
	 				pr = raw_input( "(n)ext, (p)revious, (q)uit or (r)estart? ") #ask for instruction on what to do next
	 				if (pr == 'q'):
	 					quit = True
	 					break
	 				elif (pr == 'p'):
	 					if (i==1):
	 						i = 0
	 					elif (i == len(self.fcontent)):
	 						i = 0
	 					else:
	 						i = i -  2
	 				elif (pr == 'r'):
	 					i = 0
	 	
			if found is False:
				print "No matches in the file!"				#if no match was found
				break

	def function_p(self,param):
		"""prints the content of the file read into buffer
		Arguments:
		param - string representing the paramater user typed after the command
		Returns:
		True if everything went fine """
		if param is None:
			file.read.print_file(self.fcontent)
			return True
		result = self.handleparam("p",param)
		if result[0] is True:
			#print (result[1])
			file.read.print_file(self.fcontent,result[1][0],result[1][1])
		
	def function_s(self,param):
		"""Saves the content of buffer into file
		Arguments:
		param - string representing the paramater user typed after the command
		"""
		if param is None:
			"""If no file name was entered, just save it as the old filename"""
			file.write.fwrite(self.filename,self.fcontent)
			self.file_changed=False
			return
		if " " in param:
			print constants.WRONG
			print constants.SAVE_1
			print constants.SAVE_2
			return
		else:
			"""If a file name was entered, save the file as that"""
			file.write.fwrite(param.strip(),self.fcontent)
			self.file_changed=False
			return
		print constants.WRONG
		print constants.SAVE_1
		print constants.SAVE_2
		
	def function_d(self,param):
		"""Deletes lines from the buffer
		Arguments: 
		param - string representing the paramater user typed after the command
		"""
		result = self.handleparam("d",param)
		if result[0] is True:
			self.fcontent,self.file_changed=file.write.delete(self.fcontent,result[1][0],result[1][1])

	def function_a(self,param):
		"""Adds a line to the buffer
		Arguments: 
		param - string representing the paramater user typed after the command
		"""
		if param is None or  " "  not in param:
			print constants.WRONG
			print constants.ADD_1
			print constants.ADD_2
			return True
		result = self.handleparam("ADD",param)
		if result[0] is True:

			self.fcontent,changed = file.write.append(self.fcontent,result[1][0],result[1][1],result[1][2])
			if self.file_changed is False and changed is True:
				self.file_changed = True
		
	def function_r(self,param):
		"""Replaces word in the buffer with another
		Arguments: 
		param - string representing the paramater user typed after the command
		"""
		if param is None or  " "  not in param:
			print constants.WRONG
			print constants.REPLACE_1
			print constants.REPLACE_2
			return True
		result = self.handleparam("REPLACE",param)
		if result[0] is True:
			self.fcontent,changed = file.write.replace(self.fcontent,result[1][0],result[1][1],result[1][2])
			if self.file_changed is False and changed is True:
				self.file_changed = True
		
	def function_q(self,param):
		"""Quits the program, if a file is open and change has been made, it asks the user if they want to save it
		Arguments: 
		param - string representing the paramater user typed after the command
		"""
		if param is not None:
			print constants.WRONG
			print constants.QUIT_1
			return True
		if self.file_changed is True:
			answer = self.yes_no("Warning: Would you like to save the changes to '"+self.filename+"' ?")
			if answer is True:
				"""If user wanted to save the changes, it writes the buffer to file"""
				file.write.fwrite(self.filename,self.fcontent)
			self.file_changed = False
		return False


	def handleparam(self,condition,param):
		"""Splits and checks to see if the parameters are passed with correct syntax 
		Arguments:
		condition -- A string that represents the action
		param -- A string containing the rest of the user typed parameters
		Returns:
		listToReturn - A list that has the elements separated. The first value of the list is True if everything was ok, otherwise False
		"""
		params = []
		listToReturn = [True,params]
		if (condition == "o"):
			"""If the open condition is called"""
			if " " in param:
				listToReturn[0] = False
				print constants.WRONG
				print constants.OPEN_1
			return listToReturn
		if (condition == "p"):
			"""if the print condition is called it splits the parameters to get the numbers"""
			listToReturn[1] = params = param.split()
			if len(params) is 2 and params[0]>params[1]: #If the first number is bigger than second give error
				listToReturn[0] = False
				print constants.WRONG
				print constants.PRINT_3.replace("3","1")
				return listToReturn
			if len(params)==2: #If two parameters are passed
				if params[0].isdigit() and params[1].isdigit(): #If both of them are digits than just return list
					return listToReturn
			if len(params)>2:
				listToReturn[0] = False
				print constants.WRONG
				print constants.PRINT_1
				print constants.PRINT_2
				return listToReturn		
			if params[0].isdigit(): #If only one parameter is passed and its a digit
				params.append(None) #Add none to the params list so the second number is set to none
				return listToReturn
			"""If no return has been called so far, there was an error so print the error and return list with first element False"""
			listToReturn[0] = False
			print constants.WRONG
			print constants.PRINT_1
			print constants.PRINT_2
			return listToReturn

		if (condition == "ADD" or condition=="REPLACE"):
			"""Add and replace use the same conditions"""
			startq = param.find("\"")	#Get the start of the quote
			endq = param.rfind("\"")	#Get the end of the quote
			if (startq!=-1 and endq !=-1 and startq!=endq and endq+1==len(param)):
				"""The if statement checks if a start and end quote was found, and they were not both found at the same location
					and the ending quote was found at the end of the program"""
				#Get the word that needs to be added/replaced
				words = param[startq+1:endq]
				#Separate the line number and word number
				params = param[0:startq-1]
				#Split the line and word number
				params = params.strip().split()
				if len(params)==1:	#If only 1 number is given in the parameter add None as second number
					params = [params[0],None]
				if len(params)<=2:
					params.append(words)				
					listToReturn[1] = params
				if len(params)>1:
					if params[0].isdigit():	#Make sure only a number is passed
						return listToReturn
				if len(params)==2:
					if params[0].isdigit() and params[1].isdigit():
						return listToReturn
			"""If list hasn't been returned yet, there was an error so print the error messages and return the list with false"""
			listToReturn[0] = False
			print constants.WRONG
			error1 = getattr(constants,condition+"_1")
			error2 = getattr(constants,condition+"_2")
			print error1
			print error2
			return listToReturn
		#Delete line functionality
		if (condition == "d"):
			"""If the user wants to delete a line"""
			if " " in param:
				small,big = param.strip().split(None,1)	#separate the numbers
				if small.isdigit() and big.isdigit():	#check if they are both digits
					small = int(small)
					big = int(big)
					if small>0 and big>0 and small<big:	#check if they are bigger than zero and small is < big
						params = [small,big]
						listToReturn[1]=params
						return listToReturn
			elif param.isdigit():
				num = int(param)
				if num>0:
					params = [num,None]
					listToReturn[1]=params
					return listToReturn
			if small >= big:
				listToReturn[0] = False
				print constants.WRONG
				print constants.DELETE_2.replace("2","")
				return listToReturn			
			listToReturn[0] = False
			print constants.WRONG
			print constants.DELETE_1
			print constants.DELETE_2
			return listToReturn
		#Save file functionalities

			
	def yes_no(self,q):
		"""Asks a question and checks if the user typed y or n
		Arguments: 
		q -- String containing the question to ask
		Returns:
		True if user answers yes, False if user answers no"""
		valid = {"y":True, "n": False}
		while True:
			sys.stdout.write(q+"[y|n]")
			choice = raw_input()
			if choice in valid:
				return valid[choice]
			else:
				sys.stdout.write("Please respond with 'y' for yes or 'n' for no\n")

