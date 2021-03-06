import sys
import re
from checkAddress import parseAddress
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
	return dic

def printAddress(addressD, addressNr, dicAdd):
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
	zipc = zipc.replace("\n","")
	
	print("\t%s, %s %s \n" % (city, state, zipc))

	#add number before increase!
	dicAdd.setdefault("NUMBER", []).append(addressNr)

	addressNr += 1
	
	#Add city state zip to compare dictionary
	dicAdd.setdefault("city", []).append(city)
	dicAdd.setdefault("state", []).append(state)
	dicAdd.setdefault("zip", []).append(zipc)

	#here we need to split parts of line and print them accordingly
	#split the line so we can test
	stSplit = test.split()
	
	#get the different parts of line
	stNum = stSplit[0]
	if not stNum[0].isdigit():
		stNum = " " 
	
	direct = checkDir(stSplit)
	
	stType = checkStreet(stSplit)
	stName = checkStNm(stSplit)
	apNum = checkApt(stSplit)
	
	apNum = apNum.replace("\t","")
	
	errorStr = parseAddress(test, city, state, zipc, stNum)
	if errorStr == " ":
		print('{:30s}\t\t\t\t{:10s} {:15s} {:15s} {:10s} {:20s}\n'.format(' ',stNum,direct,apNum,stType,stName))

	#add street number, direction, apt num, street type, and street name to compare dic
	dicAdd.setdefault("strNr", []).append(stNum)
	dicAdd.setdefault("strDir", []).append(direct)
	dicAdd.setdefault("aptNum", []).append(apNum)
	dicAdd.setdefault("strTyp", []).append(stType)
	dicAdd.setdefault("strName", []).append(stName)
	dicAdd.setdefault("error", []).append(errorStr)

	return addressNr
	
def checkDir(x):
	for i in range(len(x)):
		dirSW = ["S.W.", "SOUTH WEST","SOUTHWEST", "SW.", "S WEST", "SOUTH W", "SW"]
		dirSE = ["S.E.", "SOUTH EAST","SOUTHEAST", "SE.", "S EAST", "SOUTH E", "SE"]
		dirNW = ["N.W." , "NORTH WEST","NORTHWEST", "NW.", "N WEST", "NORTH W", "NW"]
		dirNE = ["N.E." , "NORTH EAST","NORTHEAST", "NE.", "N EAST", "NORTH E", "NE"]
		dirNS = ["N.S." , "NORTH SOUTH", "NORTHSOUTH", "NS.", "NORTH S", "N SOUTH", "S.N.", "SOUTH NORTH", "SOUTHNORTH", "SN.", "SOUTH N", "S NORTH"]
		dirEW = ["E.W." , "EAST WEST", "EASTWEST", "EW.", "EAST W", "E WEST", "W.E.", "WEST EAST", "WESTEAST", "WE.", "WEST E", "W EAST"]
		street = ["RD", "LN","ST","AVE","STREET","ROAD","LANE","AVENUE","RD.","ST.","AVE.","BLVD.","SQAURE", "SQ.","SQ","CIRCLE","CIR.","CIR"]
		dirW = ["W", "WEST", "W."]
		dirN = ["N", "NORTH","N."]
		dirS = ["S","SOUTH","S."]
		dirE = ["E", "EAST","E."]

		#check for side by side cardinals
		if x[i] in dirE:
			try:
				gotdata = x[i + 1]
			except IndexError:
				gotdata = "no"
			if x[i - 1] in street:
				return "EAST"
			elif 'no' in gotdata:
				return " "
			elif gotdata in street:
				continue
			else:
				return "EAST"
		if x[i] in dirSW:
                        return "SOUTHWEST"
		if x[i] in dirSE:
                        return "SOUTHEAST"
		if x[i] in dirNW:
			return "NORTHWEST"
		if x[i] in dirNE:
                        return "NORTHEAST"
		if x[i] in dirNS: 			#it's not a real direction but in the problem set
                        return "NORTHSOUTH"
		if x[i] in dirEW:			#not a real direction either but covering all bases
                        return "NORTHSOUTH"
		if x[i] in dirS:
                        try:                            #check for oob south
                                gotdata = x[i + 1]
                        except IndexError:
                                gotdata = "no"
                        if 'no' in gotdata:
                                continue
                        if gotdata in street:           #try for south street
                                return " "
		if x[i] in dirW:			
			try:				#check for oob west
				gotdata = x[i + 1]
			except IndexError:
				gotdata = "no"
			if 'no' in gotdata:
				continue
			if gotdata in street:		#try for west street
				return " "
		#if x[i] in dirN:
			#return "NORTH   "
		if x[i] in dirE:
			try:				#try for oob east
				gotdata = x[i + 1]
			except IndexError:
				gotdata = "no"
			if x[i-1].isdigit():
				continue
			if 'APT' in gotdata:
				return "EAST"
			if gotdata in street:		#try for east street
				return " "
			if 'no' in gotdata:
				return "EAST"
			else:
				continue
		if x[i] in dirN:
			try:				#try for oob north
				gotdata = x[i + 1]
			except IndexError:
				gotdata = "no"
			if gotdata in dirS:
				return "NORTHSOUTH"
			if 'no' in gotdata:
				return"NORTH"
			if gotdata in street:		#try for north street
				return " "
		if x[i] in dirS and x[i + 1] in street:
			return " "
		if x[i] in dirE and x[i + 1] in street:
			continue
		if x[i] in dirS and x[i + 1] in dirW:
			return "SOUTHWEST"
		if x[i] in dirSW:
			return "SOUTHWEST"
		if x[i] in dirW:
			return "WEST"
		#check for seperated cardinals last fake cardinals like west east and north south not included
		if x[i] in dirN:
			for j in range(len(x)):         #check for northwest
                                if x[j] in dirW:
                                        return "NORTHWEST"
			for k in range(len(x)):         #check for northwest
                                if x[j] in dirE:
                                        return "NORTHEAST"
			else:
				return "NORTH"
		#check for seperated cardinals last
		if x[i] in dirS:
			for j in range(len(x)):		#check for southwest
				if x[j] in dirW:
					return "SOUTHWEST"
			for k in range(len(x)):         #check for southwest
                                if x[j] in dirE:
                                        return "SOUTHEAST"
			else:
				return "SOUTH"
		if x[i] in dirE:
			return "EAST"
	else:
		return " "

def checkStreet(x):
	for i in range(len(x)):
		strtR = ["RD","ROAD","RD."]
		strtL = ["LN", "LANE","LN."]
		strtS = ["ST", "ST.", "STREET"]
		strtA = ["A.","AVE","AVE.","AVENUE"]
		strtB = ["BLVD.", "BOULEVARD","BLVD"]
		strtC = ["CIRCLE", "CIR.", "CIR"]
		strtSq = ["SQAURE","SQUARE", "SQ.","SQ"]
		
		if x[i] in strtR:
			return "ROAD"
		if x[i] in strtL:
			return "LANE"
		if x[i] in strtS:
			return "STREET"
		if x[i] in strtA:
			return "AVENUE"
		if x[i] in strtB:
			return "BOULVARD"
		if x[i] in strtC:
			return "CIRCLE"
		if x[i] in strtSq:
			return "SQUARE"
	else:
		return " "

def checkStNm(x):
	direction = ["S.W.", "SOUTH WEST","SOUTHWEST", "SW.", "S WEST", "SOUTH W", "SW", "S.E.", "SOUTH EAST","SOUTHEAST", "SE.", "S EAST", "SOUTH E", "SE", "N.W." , "NORTH WEST","NORTHWEST", "NW.", "N WEST", "NORTH W", "NW", "N.E." , "NORTH EAST","NORTHEAST", "NE.", "N EAST", "NORTH E", "NE", "N.S." , "NORTH SOUTH", "NORTHSOUTH", "NS.", "NORTH S", "N SOUTH", "S.N.", "SOUTH NORTH", "SOUTHNORTH", "SN.", "SOUTH N", "S NORTH", "E.W." , "EAST WEST", "EASTWEST", "EW.", "EAST W", "E WEST", "W.E.", "WEST EAST", "WESTEAST", "WE.", "WEST E", "W EAST", "RD", "LN","ST","AVE","STREET","ROAD","LANE","AVENUE","RD.","ST.","AVE.","BLVD.","SQAURE", "SQ.","SQ","CIRCLE","CIR.","CIR", "W", "WEST", "W.", "N", "NORTH","N.", "S","SOUTH","S.", "E", "EAST","E."]
	street = ""
	for i in range(len(x)):
		strtR = ["RD","ROAD","RD."]
		strtL = ["LN", "LANE","LN."]
		strtS = ["ST", "ST.", "STREET"]
		strtA = ["A.","AVE","AVE.","AVENUE"]
		strtB = ["BLVD.", "BOULEVARD","BLVD"]
		strtC = ["CIRCLE", "CIR.", "CIR"]
		strtSq = ["SQAURE", "SQUARE", "SQ.","SQ"]
		strtAp = ["APT", "APT."]
		allStreets = strtR + strtL + strtS + strtA + strtB +  strtC + strtSq

		if x[i] in strtR:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtL:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtS:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtA:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtB:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtC:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtSq:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
					continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
						street = street + " " + x[j]
		elif x[i] in strtAp:
			for j in range(len(x)):
				if j == i:
					street = street.lstrip(" ")
					return street
				if x[j] in direction:
                                        continue
				elif hasNumbers(x[j]) == False:
					if x[j] not in direction:
                                                street = street + " " + x[j]
		elif x[i] in direction:
			try :
				gotdata = x[i + 1]
			except IndexError:
				gotdata = "no"
			if 'no' in gotdata:
				continue
			if gotdata in allStreets:
				return x[i]
	else:
		return x[-1]

def checkApt(x):
	aptRE = re.compile(r'#(\d+)\-*([A-Z])')
	matchApt = aptRE.search(x[-1])
	aptRE2 = re.compile(r'\d+')
	matchApt2 = aptRE2.search(x[-1])
	for i in range(len(x)):
		num = ["#"]
		num2 = ["APT"]
		if x[i] in num2:
			return  x[i+1]
		elif matchApt != None:
			return matchApt.group(1) +  matchApt.group(2)
		elif matchApt2 != None:
			return x[-1]
		else:
			return "\t"
def hasNumbers(inputString):
	return any(char.isdigit() for char in inputString)
