import sys
from difflib import SequenceMatcher

def compareAdd(dicAdd):
	i = 0
	j = 0
	print("\tAddress\tAddress\tScore")
	for i in range(len(dicAdd["NUMBER"])):
		j = i + 1
		for j in range(len(dicAdd["NUMBER"])):
			score = 0
			if j == i: #don't compare same addresses
				continue
			elif j < i: #don't compare addresses twice
				continue
			elif dicAdd["error"][i] != " ":
				continue
			elif dicAdd["error"][j] != " ":
				continue
			else: 
			#compare
			#compare street number
				#if both are empty
				if dicAdd["strNr"][i] == " " and dicAdd["strNr"][j] == " ":
					score = score + 0
				#if i is empty
				elif dicAdd["strNr"][i] == " " and dicAdd["strNr"][j] != " ":
					score = score - 20
				#if j is empty	
				elif dicAdd["strNr"][j] == " " and dicAdd["strNr"][i] != " ":
					score = score - 20
				elif dicAdd["strNr"][i] != " " and dicAdd["strNr"][j] != " ":
					if dicAdd["strNr"][i] == dicAdd["strNr"][j]:
						score = score + 20
					else:
						score = score - 20
				else:
					score = score
				#print(score)		
				#print(dicAdd["strNr"][i]) 
				#print(dicAdd["strNr"][j])
			#compare street type
				#if both are empty
				if dicAdd["strTyp"][i] == " " and dicAdd["strTyp"][j] == " ":
					score = score + 10
				#if i is empty
				elif dicAdd["strTyp"][i] == " " and dicAdd["strTyp"][j] != " ":
					score = score + 5
				elif dicAdd["strTyp"][j] == " " and dicAdd["strTyp"][i] != " ":
					score = score + 5
				elif dicAdd["strTyp"][i] != " " and dicAdd["strTyp"][j] != " ":
					if dicAdd["strTyp"][i] == dicAdd["strTyp"][j]:
						score = score + 10
					else:
						score = score - 10
				else:
					score = score
				#print(score)
				#print(dicAdd["strTyp"][i])
				#print(dicAdd["strTyp"][j])
			#compare direction
				#if both are empty
				if dicAdd["strDir"][i] == " " and dicAdd["strDir"][j] == " ":
					score = score + 5
				elif dicAdd["strDir"][i] == " " and dicAdd["strDir"][j] != " ":
					score = score - 5
				elif dicAdd["strDir"][j] == " "  and dicAdd["strDir"][i] != " ":
					score = score - 5
				elif dicAdd["strDir"][i] != " " and dicAdd["strDir"][j] != " ":
					if dicAdd["strDir"][i] == dicAdd["strDir"][j]:
						score = score + 5
					else:
						score = score - 10
				else:
					score = score
				#print(score)
				#print(dicAdd["strDir"][i]) 
				#print(dicAdd["strDir"][j])
			#compare apt number
				if dicAdd["aptNum"][i] == "" and dicAdd["aptNum"][j] == "":
					score = score + 10
				elif dicAdd["aptNum"][i] == "" and dicAdd["aptNum"][j] != "":
					score = score - 10
				elif dicAdd["aptNum"][j] == "" and dicAdd["aptNum"][i] != "":
					score = score - 10
				elif dicAdd["aptNum"][i] != "" and dicAdd["aptNum"][j] != "":
					match = SequenceMatcher(None, dicAdd["aptNum"][i], dicAdd["aptNum"][j]).ratio()
					if dicAdd["aptNum"][i] == dicAdd["aptNum"][j]:
						score = score + 20
					elif match > 0.6:
						add = match * 5
						score = score + add
					else:
						score = score - 20
				else:
					print("Error, something went wrong\n")
				#print(score)
				#print(dicAdd["aptNum"][i]) 
				#print(dicAdd["aptNum"][j])
			#compare city
				if dicAdd["city"][i] == " " and dicAdd["city"][j] == " ":
					score = score + 10
				elif dicAdd["city"][i] == " " and dicAdd["city"][j] != " ":
					score = score - 10
				elif dicAdd["city"][j] == " " and dicAdd["city"][i] != " ":
					score = score - 10
				elif dicAdd["city"][i] != " " and dicAdd["city"][j] != " ":
					match = SequenceMatcher(None, dicAdd["city"][i], dicAdd["city"][j]).ratio()	
					if dicAdd["city"][i] == dicAdd["city"][j]:
						score = score + 20
					elif match > 0.6:
						add = match * 15
						score = score + add
					else:
						score = score - 20
				else:
					score = score
				#print(score)
				#print(dicAdd["city"][i]) 
				#print(dicAdd["city"][j])
			#compare state
				if dicAdd["state"][i] != " " and dicAdd["state"][j] != " ":
					if dicAdd["state"][i] == dicAdd["state"][j]:
						score = score + 10
					else:
						score = score - 20
			#compare street name
				if dicAdd["strName"][i] == " " and dicAdd["strName"][j] == " ":
					score = score - 20 
				elif dicAdd["strName"][i] == " " and dicAdd["strName"][j] != " ":
					score = score - 20
				elif dicAdd["strName"][j] == " " and dicAdd["strName"][i] != " ":
					score = score - 20
				elif dicAdd["strName"][i] != " " and dicAdd["strName"][j] != " ":
					match = SequenceMatcher(None, dicAdd["strName"][i], dicAdd["strName"][j]).ratio()
					if dicAdd["strName"][i] == dicAdd["strName"][j]:
						score = score + 20
					elif match > 0.6:
						add = match * 10
						score = score + add
					else:
						score = score - 5
				else:
					score = score
				#print(score)
				#print(dicAdd["strName"][i])
				#print(dicAdd["strName"][j])
			#compare zipcode
				if len(dicAdd["zip"][i]) == len(dicAdd["zip"][j]) and len(dicAdd["zip"][i]) == 10:
					if dicAdd["zip"][i] == dicAdd["zip"][j]:
						score = score + 80
					else:
						score = score
				elif len(dicAdd["zip"][i]) == len(dicAdd["zip"][j]) and len(dicAdd["zip"][i]) == 5:
					if dicAdd["zip"][i] == dicAdd["zip"][j]:
						score = score + 5
					else:
						score = score
				elif len(dicAdd["zip"][i]) != len(dicAdd["zip"][j]):
					firstC = dicAdd["zip"][i]
					secondC = dicAdd["zip"][j]
					if firstC[:5] == secondC[:5]:
						score = score + 5
					else:
						score = score
				else:
					print("Something is not right")
			#round the numbers
				if score > 100:
					score = 100
				if score < 0:
					score = 0
					
			#print results last
				print("\t%s\t%s\t%d" %(dicAdd["NUMBER"][i], dicAdd["NUMBER"][j], score))
def parseAddress(line, city, state, zipc,strtNm):
	if line == "" or line == " " or line is None:
		errorStr = "error"
		print("\t\t\t\t\t\t\t*** Missing Address Line ***")
	elif city == "" or city == " " or city is None:
		errorStr = "error"
		print("\t\t\t\t\t\t\t*** Missing City ***")
	elif state == "" or state == " " or state is None:
		errorStr = "error"
		print("\t\t\t\t\t\t\t*** Missing State ***")
	elif strtNm == "" or strtNm == " " or strtNm is None:
		errorStr = "error"
		print("\t\t\t\t\t\t\t*** Missing Street Number ***")
	elif len(zipc) < 5 or len(zipc) > 10:
		errorStr = "error"
		print("\t\t\t\t\t\t\t*** Zip is invalid ***")
	elif len(zipc) == 10:
		if zipc[5] != '-':
			errorStr = "error"
			print("\t\t\t\t\t\t\t*** Zip is invalid ***")
		elif not zipc[:4].isdigit():
			errorStr = "error"
			print("\t\t\t\t\t\t\t*** Zip is invalid ***")
		elif not zipc[6:9].isdigit():
			errorStr = "error"
			print("\t\t\t\t\t\t\t*** Zip is invalid ***")
		else:
			errorStr = " "
	else:
		errorStr = " "
	return errorStr
