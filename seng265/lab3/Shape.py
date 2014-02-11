#!/usr/bin/python
class Shape:
	def Area(self):
		print "Not initialized"
	def Parameter(self):
		print "not initialized"
	def Scale(self,factor):
		print "Not intiailized"

class Rectangle(Shape):
	width,height = 0,0
	area = 0
	param = 0
	def __init__(self,w,h):
		self.width=w
		self.height=h
		self.Area()
		self.Parameter()
	def Area(self):
		self.area = self.width*self.height
	def Parameter(self):
		self.param = 2*self.width+2*self.height
	def Scale(self,factor):
		self.width = self.width*factor
		self.height = self.height*factor
	def __str__(self):
		string = "Width: %d Height: %d "%(self.width,self.height)
		string += "Area: %d Perimeter: %d"%(self.area,self.param)
		return string
class triangle(Shape):
	base = 0
	height = 0
	area = 0
	param = 0
	def __init__(self,b,h):
		self.base = b
		self.height = h
		self.Area()
		self.Parameter()
	def Area(self):
		self.area = self.base*self.height
		self.area = self.area/2
	def Parameter(self):
		self.param = self.base*3
	def Scale(self,factor):
		self.base = self.base*factor
		self.height = self.height*factor
	def __str__(self):
		string =  "Base: %d Height : %d "%(self.base,self.height)
		string +="Area: %d Perimeter: %d" %(self.area,self.param)
		return string
def main():
	shapes = [triangle(1,2),Rectangle(3,4)]
	for elem in shapes:
		print str(elem)
main()
