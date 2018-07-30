import sys
from address import getAddress, printAddress


#Get the file name from command line
filename = sys.argv[1]

def mainLoop(filename):
	#Open the file
	f = open(filename, 'r')
	
	#Read first line in
	line = f.readline()	

	#While there are lines to be read from the file
	while line:
		#Split line for inspection
		lines = line.split(" ")
		
		#If the first element of lines is CUSTOMER it's a customer name
		if lines[0] == "CUSTOMER":
			count = 1
			#Join the line to print
			lineName = ' '.join(lines[1:])
			print(lineName)

		elif 'ADDRBEG' in line:
			#Pass the file to address.py for getAddress
			#return dictionary
			dic = getAddress(f)
			#print(dic["ADNR"])
			#print(dic["LINE"])
	
			#print("%d" % count)
			#count += 1
			#print(dic["LINE"])

			#pass dictionary to printAddress for printing
			count = printAddress(dic, count)
		
		line = f.readline()
	f.close()

mainLoop(filename)
