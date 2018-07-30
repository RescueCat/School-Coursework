import sys

filename = sys.argv[1]

def mainLoop(filename):
	#open the file
	f = open(filename, 'r')

	line = f.readline()

	while line:
		lines = line.split(" ")
		if lines[0] == "CUSTOMER":
			lineName = ' '.join(lines[1:])
			print(lineName)
		line = f.readline()
	f.close()

mainLoop(filename)
