import sys
from address import getAddress, printAddress
from checkAddress import compareAdd


#Get the file name from command line
filename = sys.argv[1]

def mainLoop(filename):
	#Open the file
	f = open(filename, 'r')
	
	#Read first line in
	line = f.readline()	

	#dictionary for comparison
	dicAdd = {"NUMBER": [], "strNr": [], "strTyp": [], "strDir": [], "aptNum": [], "city": [], "state": [], "strName": [], "zip": [], "error": []}

	#While there are lines to be read from the file
	while line:
		#Split line for inspection
		lines = line.split(" ")
		
		#If the first element of lines is CUSTOMER it's a customer name
		if lines[0] == "CUSTOMER":
			count = 1
			#Join the line to print
			lineName = ' '.join(lines[1:])
			lineName = lineName.replace("\n","")
			#if len(lineName) < 8:
				#print("%s\t\t\t\t\t\t\tStNum\tDirection\tAptNum\tStType\tStName" % lineName)
			print('{:30s}\t\t\t\t{:10s} {:15s} {:15s} {:10s} {:20s}\n'.format(lineName,'stNum','Direction','AptNum','StType','StName'))
			#else:
			#	print("%s\t\t\t\t\t\tStNum\tDirection\tAptNum\tStType\tStName" % lineName)

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
			count = printAddress(dic, count, dicAdd)
		
		line = f.readline()
		if 'CUSTOMEREND' in line:
			#print("Dictionary entries: %d" % (len(dicAdd)))
			#print(dicAdd["strName"][1])
			#if len(dicAdd["strName"]) > 3:
			#	print(dicAdd["strName"][3])
			#print(dicAdd["aptNum"])
			compareAdd(dicAdd)
			#print("Compare Here! \n")

			#lastly clear the dictionary for another customer
			dicAdd.clear()
	f.close()

mainLoop(filename)
