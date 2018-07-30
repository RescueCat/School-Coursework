import sys

#Define the filename from command line arguements
filename = sys.argv[1]

def getAddress(f):
	#get the NEXT current file line
	line = f.readline()
	
	count = 1

	#create a new dictionary
	dic = {"LINE": [], "CITY": [], "STATE": [], "ZIP": [], "ADNR": []}

	#while there are lines to read in filename
	while 'ADDREND' not in line:
		#split the line for insertion
		lines = line.split()

		#if "LINE" add to dic
		if 'LINE' in line:
			dic["LINE"].append(lines[1:])

		#if "CITY" add to dic
		if 'CITY' in line:
			dic["CITY"] = lines[1:]

		#if "STATE" add dic
		if 'STATE' in line:
			dic["STATE"] = lines[1:]
		
		#if "ZIP" add dic
		if 'ZIP' in line:
			dic["ZIP"] = lines[1:]
			dic["ADNR"] = count
			count = count + 1
			

		line = f.readline()

	#print (dic["LINE"])
	#print (dic["CITY"])
	#print (dic["STATE"])
	#print (dic["ZIP"])
	return dic

def printAddress(addressD, addressNr):
	test = str(addressD["LINE"])
	test = test.replace("[", "")
	test = test.replace("]", "")
	test = test.replace("'", "")
	test = test.replace(",", "")
	print("%d\t%s" % (addressNr, test))

	city = str(addressD["CITY"])
	city = city.replace("[", "")
	city = city.replace("]", "")
	city = city.replace("'", "")
	city = city.replace(",", "")
	
	state = str(addressD["STATE"])
	state = state.replace("[", "")
	state = state.replace("]", "")
	state = state.replace("'", "")
	state = state.replace(",", "")

	zipc = str(addressD["ZIP"])
	zipc = zipc.replace("[", "")
	zipc = zipc.replace("]", "")
	zipc = zipc.replace("'", "")
	zipc = zipc.replace(",", "")
	
	print("\t%s, %s %s \n" % (city, state, zipc))
	#print (addressNr)
	#print (addressD["LINE"])
	#print (addressD["CITY"])
	#print (addressD["STATE"])
	#print (addressD["ZIP"])
	addressNr += 1
	return addressNr
	

	
	
