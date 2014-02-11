#!/usr/bin/python
"""
	Author: Muhammad Zubair
	Student ID: V00757068
	The module with methods that modify the buffer or write to the file
	public functions:
	fwrite -- Write the buffer to the file
	append -- Adds content into the buffer 
	replace -- Replaces words from the buffer
	delete -- delete lines from the buffer
"""
def fwrite(filename,content):
	"""given the file name and buffer array it overwrites the file with the content of buffer array
	Argument:
	filename - The location/name of the file
	Content - the buffer array"""
	f = open (filename,"w")
	content = [" ".join(elem) for elem in content]	#Join the words with a space in between
	content = "\n".join(content).replace("&^&%+"," ")	#Join the lines with a new line character
	f.write(content)	#Write the content to the file
	print "Saving "+filename+"...Done"
	f.close()

def append(content,line,word,string):
	"""Given the buffer array it adds string at the location provided by the user
	Arguments:
	Content - the buffer array
	line - the line number to append at
	Word - the word number to append at
	String - the string to add to the buffer array"""
	line = int(line)
	string = string.strip().replace("  "," &^&%+").split()	#Strip leading and trailing spaces and split it into a list
	if len(content)+1<int(line):	#If the length of array + 1 is less than the line user wants to add at
		print "Error: No such line."
		return (content,False)	#return the unchanged content with False representing that no change was made
	if word is not None:
		"""If the user gives the position of word """
		word = int(word)
		if len(content[line-1])+1<int(word) or line>len(content)+1:
			"""If the length of list of words + 1 is less than where the user wants to edit or the actual line number doesnt exist"""
			print "Error: No such word."
			return (content,False)
		word = word-1
		"""Modify the list at the line number given adding the string provided at the given location"""
		content[line-1] = content[line-1][:word]+string+content[line-1][word:]

	else:
		"""If only line number was provided then just adds the line"""
		line = line-1
		"""Append the string provided where the user wants to add"""
		content = content[:line]+[string]+content[line:]
	"""If everything was okay, it returns the content buffer with True for okay"""
	return (content,True)
	
def replace(content,line,word,string):
	"""Replaces the word in the buffer with the one user provides
	Arguments:
	Content - the buffer array
	line - the line number to append at
	Word - the word number to append at
	String - the string to add to the buffer array"""
	line = int(line)
	string = string.strip().replace("  "," &^&%+").split()
	if len(content)<int(line):
		print "Error: No such line."
		return (content,False)
	if word is not None:
		word = int(word)
		if len(content[line-1])<int(word) or line>len(content):
			print "Error: No such word."
			return (content,False)
		word = word-1
		content[line-1] = content[line-1][:word]+string+content[line-1][word+1:]
		
	else:
		line = line-1
		content[line] = string
	return (content,True)
def delete(content,small,big):
	"""deletes 1 or multiple lines from the buffer
	Arguments:
	content -- The buffer array containing all the content read from file
	small -- first line number to delete
	big -- the bigger line number to delete until.
	Returns:
	content -- The modified buffer array
	True, False - True if a change occured, False otherwise"""
	if big is not None:
		if len(content)>=int(big):
			content = content[0:small-1]+content[big:]
			return (content,True)
		print "Error: no such line range."
		return (content,False)
	if len(content)>=small:
		small = int(small)
		content.remove(content[small-1])
		return (content,True)
	print "Error: no such line."
	return (content,False)
