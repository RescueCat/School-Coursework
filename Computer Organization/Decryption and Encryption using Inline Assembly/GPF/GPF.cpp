#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <io.h>

//#define TEST_CODE


// Global Variables
unsigned char gkey[65537];
unsigned char *gptrKey = gkey;			// used for inline assembly routines, need to access this way for Visual Studio
char gPassword[256] = "password";
unsigned char gPasswordHash[32];
unsigned char *gptrPasswordHash = gPasswordHash;	// used for inline assembly routines, need to access this way for Visual Studio

FILE *gfptrIn = NULL;
FILE *gfptrOut = NULL;
FILE *gfptrKey = NULL;
char gInFileName[256];
char gOutFileName[256];
char gKeyFileName[256];
int gOp = 0;			// 1 = encrypt, 2 = decrypt
int gNumRounds = 1;


// Prototypes
int sha256(char *fileName, char *dataBuffer, DWORD dataLength, unsigned char sha256sum[32]);

// assembly language to count the number of ASCII letters in a data array
//	numC = number of capital letters
//	numL = number of lowercase letters
//	numO = number of characters that are not a letter
void exCountLetters(char *data, int dataLength, int *numC, int *numL, int *numO)
{
	__asm {
		cld;					// 
		push esi;				// 
		push ecx;				// 
		push ebx;
		mov esi, data;			// 
		mov ecx, dataLength;	// 

	LOOP_X1:
		lodsb;					// 
		mov bl, al				// 
			push eax;				// 
		call isLetter;			// function returns a 1 in al if the character passed in is a letter, otherwise al = 0
		add esp, 4				// 
			test al, al;				// 
		je lbl_OTHER;			// 

		mov al, bl				// 
			and al, 0x20;			// already know it's a letter, if al == 0, then CAP
		je lbl_CAP;

		mov	ebx, numL;			// 
		add[ebx], 1;			// 
		jmp lbl_NEXT;			// 

	lbl_CAP:
		mov ebx, numC;			// 
		add[ebx], 1;			// 
		jmp lbl_NEXT;			// 

	lbl_OTHER:
		mov ebx, numO			// 
			add[ebx], 1				// 
			lbl_NEXT :
			dec ecx;				// 
		jne LOOP_X1;			// 

		pop ebx;				// 
		pop ecx;				// 
		pop esi;				// 
		jmp EXIT_C_EXAMPLE;		// let C handle whatever it did upon entering this function

	isLetter:
		push ebp;				// 
		mov ebp, esp;			// 
		mov al, [ebp + 8];			// 
		cmp al, 0x40;			// 
		ja lbl_CHK_ZU;			// check Uppercase 'Z'

	lbl_RET_FALSE:
		xor eax, eax;			// 
	lbl_RET:
		mov esp, ebp;			// 
		pop ebp;				// 
		ret;					// 

	lbl_RET_TRUE:
		mov eax, 1;				// 
		jmp lbl_RET;			// 

	lbl_CHK_ZU:
		cmp al, 0x5B;			// 
		jb lbl_RET_TRUE;		// 

		cmp al, 0x61;			// 
		jb lbl_RET_FALSE;		// check lowercase 'z'

		cmp al, 0x7A;			// 
		jbe lbl_RET_TRUE;		// 
		jmp lbl_RET_FALSE;		// 

	} // end assembly block

EXIT_C_EXAMPLE:					// 
	return;
} // exCountLetters

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // code to encrypt the data as specified by the project assignment
void encryptData(char *data, int length)
{
	//Lenghth has been introduced to the class and assigned to thisl
	int thisl = length;
	//Swap is a container that is used for making the swap half nibbles part possible
	int swap;
	//# of Rounds taken from command line
	int rounds = gNumRounds;

	//Startingpoints & Hopcounts are found with C++ using the algo. expressed in the assignment pdf.
	//These values never reset within this body of code (perfile) and are always reassessed when moving on to a next character. 
	int STARTINGPOINT1, HOPCOUNT1, STARTINGPOINT2, HOPCOUNT2;
	STARTINGPOINT1 = gPasswordHash[0 + rounds * 4] * 256 + gPasswordHash[1 + rounds * 4];
	HOPCOUNT1 = gPasswordHash[2 + rounds * 4] * 256 + gPasswordHash[3 + rounds * 4];
	STARTINGPOINT2 = gPasswordHash[4 + rounds * 4] * 256 + gPasswordHash[5 + rounds * 4];
	HOPCOUNT2 = gPasswordHash[16 + rounds * 4] * 256 + gPasswordHash[17 + rounds * 4];


	__asm
	{	

			//move "keyfile" into esi
		mov esi, gptrKey

			//setdirection
		cld

			//move "infile" into edi
		mov edi, data

			//if esi ("Keyfile") is empty exit
		cmp esi, 0
		jz EXIT

			//if edi ("infile") is empty exit
		cmp edi, 0
		jz EXIT
	}

	//repeat every step inside for every round
	for (; rounds > 0; rounds--)
	{	//repeat every step inside for every character in the infile
		for (; thisl > 0; thisl--)
		{	//make sure no points are outside of range
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}

			__asm
			{
				Rounds:
						//move length of "infile" into edx 
						//put in loop so it refresh length every round
					//mov edx, length1

				Replace:
					//Perform operations on byte from "keyfile" with byte from "infile" repeat till length(edx) is 0
					//DO NOT ALTER AL IF POSSIBLE UNLESS STORING A RESULT!!!

						//Move first byte from data into al 
					mov al, [edi]

						//xor byte of data [edi] with byte of keyfile [ESI+STARTINGPOINT1]
					//The index for the keyfile (edi) will always be incremented to the new point (in the keyfile) then decremented back to zero
					//to avoid having it ever exceede the MaximumSize[65537]. STARTINGPOINT1 is always increased outside of the asm loop by HOPCOUNT1
					//and deacresed by MaximumSize if the new point (STARTINGPOINT1+HOPCOUNT1) is out of range (>=65537), rebound (-=65536).
					//The same is true for StartingPoint2
					add esi, STARTINGPOINT1
					xor eax, [esi]
					sub esi, STARTINGPOINT1

						//Increment STARTINGPOINT1 by HOPCOUNT1
					//add STARTINGPOINT1, HOPCOUNT1

						//If STARTINGPOINT1 becomes bigger than Keyfile Size [65537] -> 
					//cmp STARTINGPOINT1, 65537
						//IF STARTINGPOINT1 < 65537 jump
					//jnae NOTTOOBIG 
						//ELSE STARTINGPOINT1 >= 65537
						//STARTINGPOINT1 = STARTINGPOINT1 - 65537
					//sub STARTINGPOINT1, 65537

				NOTTOOBIG:

						//rotate byte 1 bit to the right (ror)
					ror al, 1

						//swap nibbles aka rotate 4 bytes
					ror al, 4

						//reverse bit order
			/*Kind of confusing, use http://www.c-jump.com/CIS77/ASM/Assembly/A77_0420_rotate_with_carry.htm for better a visualization.
			Rotates lowest bit of "al" into the CF (CarryFlag), then rotates that same bit (CF) into "bl", shifting bits to the left each time.
			Repeat 8 times (for 8 bits) then we move "bl" into "al" */
					xor ecx, ecx
					xor ebx, ebx
					mov cl, 8
				XCHANGE:
					rcr al, 1
					rcl bl, 1
					loop XCHANGE
					mov al, bl

						//swap half nibbles; Detailed notes on how this was accomplished can be found in the methods PDF
				//lower 4
					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

					mov bl, al
					mov cl, al

					and bl, 0x0F
					rol bl, 2
					ror cl, 2
					and cl, 0x03
					add bl, cl
					and bl, 0x0F
					mov swap, ebx //save bottom 4 to swap

				//upper 4
					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

					mov bl, al
					mov cl, al

					ror bl, 4
					ror cl, 4

					and bl, 0x0F
					rol bl, 2
					ror cl, 2
					and cl, 0x03
					add bl, cl
					and bl, 0x0F

					ror bl, 4
					add ebx, swap //combine upper 4 and lower 4
					mov al, bl //move resulti to al 

					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

						//rotate one bit to the left 
					rol al, 1

						//xor byte of data [edi] with byte of keyfile [ESI+STARTINGPOINT2]
					add esi, STARTINGPOINT2
					xor al, [esi]
					sub esi, STARTINGPOINT2

						//Increment STARTINGPOINT2 by HOPCOUNT2
					//add STARTINGPOINT2, HOPCOUNT2

						//If STARTINGPOINT2 becomes bigger than Keyfile Size [65537] -> 
					//cmp STARTINGPOINT2, 65537

						//IF STARTINGPOINT1 < 65537 jump
					//jnae ALMOSTDONE 

						//ELSE STARTINGPOINT2 >= 65537
						//STARTINGPOINT2 = STARTINGPOINT2 - 65537
					//sub STARTINGPOINT2, 65537

				ALMOSTDONE:
						//move/store resulti byte 
					mov[edi], al

						//increment our pointer for INFILE
					inc di

						//decrement our counter, loop if not zero
					//dec edx
					//jnz Replace
					
						//decrement rounds, loop if not zero
					//dec rounds
					//jnz ROUNDS

				EXIT:

			}
			//make sure no points are outside of range
			STARTINGPOINT1 += HOPCOUNT1;
			if (STARTINGPOINT1 > 65536)
			{
				STARTINGPOINT1 -= 65536;
			}
			STARTINGPOINT2 += HOPCOUNT2;
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}
		}
	}
EXIT_C_ENCRYPT_DATA:
	return;
} // encryptData

  // code to read the file to encrypt
int encryptFile(FILE *fptrIn, FILE *fptrOut)
{
	char *buffer;
	unsigned int filesize;

	filesize = _filelength(_fileno(fptrIn));	// Linux???
	if (filesize > 0x1000000)					// 16 MB, file too large
	{
		fprintf(stderr, "Error - Input file too large.\n\n");
		return -1;
	}

	// use the password hash to encrypt
	buffer = (char *)malloc(filesize);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error - Could not allocate %d bytes of memory on the heap.\n\n", filesize);
		return -1;
	}

	fread(buffer, 1, filesize, fptrIn);	// read entire file
	encryptData(buffer, filesize);
	fwrite(buffer, 1, filesize, fptrOut);
	free(buffer);

	return 0;
} // encryptFile

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // code to decrypt the data as specified by the project assignment
void decryptData(char *data, int length)
{
	int thisl = length;
	int swap;
	int rounds = gNumRounds;

	int STARTINGPOINT1, HOPCOUNT1, STARTINGPOINT2, HOPCOUNT2;
	STARTINGPOINT1 = gPasswordHash[0 + rounds * 4] * 256 + gPasswordHash[1 + rounds * 4];
	HOPCOUNT1 = gPasswordHash[2 + rounds * 4] * 256 + gPasswordHash[3 + rounds * 4];
	STARTINGPOINT2 = gPasswordHash[4 + rounds * 4] * 256 + gPasswordHash[5 + rounds * 4];
	HOPCOUNT2 = gPasswordHash[16 + rounds * 4] * 256 + gPasswordHash[17 + rounds * 4];


	__asm
	{

		//move "keyfile" into esi
		mov esi, gptrKey

		//setdirection
		cld

		//move "infile" into edi
		mov edi, data

		//if esi ("Keyfile") is empty exit
		cmp esi, 0
		jz EXIT

		//if edi ("infile") is empty exit
		cmp edi, 0
		jz EXIT
	}

	for (; rounds > 0; rounds--)
	{
		for (; thisl > 0; thisl--)
		{
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}

			__asm
			{

				Replace:
				//Perform operations on byte from "keyfile" with byte from "infile" repeat till length(edx) is 0
				//DO NOT ALTER AL IF POSSIBLE UNLESS STORING A RESULT!!!

						//Move first byte from data into al 
					mov al, [edi]

						//xor byte of data [edi] with byte of keyfile [ESI+STARTINGPOINT2]
					add esi, STARTINGPOINT2
					xor eax, [esi]
					sub esi, STARTINGPOINT2


						//rotate byte 1 bit to the left (rol)
					rol al, 1


						//swap half nibbles
				//lower 4
					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

					mov bl, al
					mov cl, al

					and bl, 0x0F
					rol bl, 2
					ror cl, 2
					and cl, 0x03
					add bl, cl
					and bl, 0x0F
					mov swap, ebx

				//upper 4
					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

					mov bl, al
					mov cl, al

					ror bl, 4
					ror cl, 4

					and bl, 0x0F
					rol bl, 2
					ror cl, 2
					and cl, 0x03
					add bl, cl
					and bl, 0x0F

					ror bl, 4
					add ebx, swap //combine upper 4 and lower 4
					mov al, bl //move resulti to al 

					xor ebx, ebx //clear ebx
					xor ecx, ecx //clear ecx

						//reverse bit order
					/*Kind of confusing, use http://www.c-jump.com/CIS77/ASM/Assembly/A77_0420_rotate_with_carry.htm for better visualization.
					Rotates lowest bit of "al" into the CF (CarryFlag), then rotates that same bit (CF) into "bl", shifting bits to the left each time.
					Repeat 8 times (for 8 bits) then we move "bl" into "al" */
					xor ecx, ecx
					xor ebx, ebx
					mov cl, 8
					XCHANGE:
					rcr al, 1
					rcl bl, 1
					loop XCHANGE
					mov al, bl

					
						//swap nibbles aka rotate 4 bytes
					ror al, 4
								 
						//rotate one bit to the right (ror)
					ror al, 1

						//xor byte of data [edi] with byte of keyfile [ESI+STARTINGPOINT2]
					add esi, STARTINGPOINT1
					xor al, [esi]
					sub esi, STARTINGPOINT1

					ALMOSTDONE :
					//move/store resulti byte 
					mov[edi], al

					//increment our pointer for INFILE
					inc di
					

					EXIT :

			}

			STARTINGPOINT1 += HOPCOUNT1;
			if (STARTINGPOINT1 > 65536)
			{
				STARTINGPOINT1 -= 65536;
			}
			STARTINGPOINT2 += HOPCOUNT2;
			if (STARTINGPOINT2 > 65536)
			{
				STARTINGPOINT2 -= 65536;
			}
		}
	}
EXIT_C_ENCRYPT_DATA:
	return;
} // decryptData

  // code to read in file and prepare for decryption
int decryptFile(FILE *fptrIn, FILE *fptrOut)
{
	char *buffer;
	unsigned int filesize;

	filesize = _filelength(_fileno(fptrIn));	// Linux???
	if (filesize > 0x1000000)					// 16 MB, file too large
	{
		fprintf(stderr, "Error - Input file too large.\n\n");
		return -1;
	}

	// use the password hash to encrypt
	buffer = (char *)malloc(filesize);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error - Could not allocate %d bytes of memory on the heap.\n\n", filesize);
		return -1;
	}

	fread(buffer, 1, filesize, fptrIn);	// read entire file
	decryptData(buffer, filesize);
	fwrite(buffer, 1, filesize, fptrOut);
	free(buffer);

	return 0;
} // decryptFile

  //////////////////////////////////////////////////////////////////////////////////////////////////
FILE *openInputFile(char *filename)
{
	FILE *fptr;

	fptr = fopen(filename, "rb");
	if (fptr == NULL)
	{
		fprintf(stderr, "\n\nError - Could not open input file %s!\n\n", filename);
		exit(-1);
	}
	return fptr;
} // openInputFile

FILE *openOutputFile(char *filename)
{
	FILE *fptr;

	fptr = fopen(filename, "wb+");
	if (fptr == NULL)
	{
		fprintf(stderr, "\n\nError - Could not open output file %s!\n\n", filename);
		exit(-1);
	}
	return fptr;
} // openOutputFile


void usage(char *argv[])	//   cryptor.exe -e -i <input file> –k <keyfile> -p <password> [–r <#rounds>]
{
	printf("\n\nUsage:\n\n");
	printf("%s -<e=encrypt or d=decrypt> -i <message_filename> -k <keyfile> -p <password> [-r <#rounds>]\n\n", argv[0]);
	printf("-e				:encrypt the specified file\n");
	printf("-d				:decrypt the specified file\n");
	printf("-i filename		:the name of the file to encrypt or decrypt\n");
	printf("-p password		:the password to be used for encryption [default='password']\n");
	printf("-r <#rounds>	:number of encryption rounds (1 - 3)  [default = 1]\n");
	printf("-o filename		:name of the output file [default='encrypted.txt' or 'decrypted.txt'\n\n");
	exit(0);
} // usage

void parseCommandLine(int argc, char *argv[])
{
	int cnt;
	char ch;
	bool i_flag, o_flag, k_flag, p_flag, err_flag;

	i_flag = k_flag = false;				// these must be true in order to exit this function
	err_flag = p_flag = o_flag = false;		// these will generate different actions

	cnt = 1;	// skip program name
	while (cnt < argc)
	{
		ch = *argv[cnt];
		if (ch != '-')
		{
			fprintf(stderr, "All options must be preceeded by a dash '-'\n\n");
			usage(argv);
		}

		ch = *(argv[cnt] + 1);
		if (0)
		{
		}

		else if (ch == 'e' || ch == 'E')
		{
			if (gOp != 0)
			{
				fprintf(stderr, "Error! Already specified encrypt or decrypt.\n\n");
				usage(argv);
			}
			gOp = 1;	// encrypt
		}

		else if (ch == 'd' || ch == 'D')
		{
			if (gOp != 0)
			{
				fprintf(stderr, "Error! Already specified encrypt or decrypt.\n\n");
				usage(argv);
			}
			gOp = 2;	// decrypt
		}

		else if (ch == 'i' || ch == 'I')
		{
			if (i_flag == true)
			{
				fprintf(stderr, "Error! Already specifed an input file.\n\n");
				usage(argv);
			}
			i_flag = true;
			cnt++;
			if (cnt >= argc)
			{
				fprintf(stderr, "Error! Must specify a filename after '-i'\n\n");
				usage(argv);
			}
			strncpy(gInFileName, argv[cnt], 256);
		}

		else if (ch == 'o' || ch == 'O')
		{
			if (o_flag == true)
			{
				fprintf(stderr, "Error! Already specifed an output file.\n\n");
				usage(argv);
			}
			o_flag = true;
			cnt++;
			if (cnt >= argc)
			{
				fprintf(stderr, "Error! Must specify a filename after '-o'\n\n");
				usage(argv);
			}
			strncpy(gOutFileName, argv[cnt], 256);
		}

		else if (ch == 'k' || ch == 'K')
		{
			if (k_flag == true)
			{
				fprintf(stderr, "Error! Already specifed a key file.\n\n");
				usage(argv);
			}
			k_flag = true;
			cnt++;
			if (cnt >= argc)
			{
				fprintf(stderr, "Error! Must specify a filename after '-k'\n\n");
				usage(argv);
			}
			strncpy(gKeyFileName, argv[cnt], 256);
		}

		else if (ch == 'p' || ch == 'P')
		{
			if (p_flag == true)
			{
				fprintf(stderr, "Error! Already specifed a password.\n\n");
				usage(argv);
			}
			p_flag = true;
			cnt++;
			if (cnt >= argc)
			{
				fprintf(stderr, "Error! Must enter a password after '-p'\n\n");
				usage(argv);
			}
			strncpy(gPassword, argv[cnt], 256);
		}

		else if (ch == 'r' || ch == 'R')
		{
			int x;

			cnt++;
			if (cnt >= argc)
			{
				fprintf(stderr, "Error! Must enter number between 1 and 3 after '-r'\n\n");
				usage(argv);
			}
			x = atoi(argv[cnt]);
			if (x < 1 || x > 3)
			{
				fprintf(stderr, "Warning! Entered bad value for number of rounds. Setting it to one.\n\n");
				x = 1;
			}
			gNumRounds = x;
		}

		else
		{
			fprintf(stderr, "Error! Illegal option in argument. %s\n\n", argv[cnt]);
			usage(argv);
		}

		cnt++;
	} // end while

	if (gOp == 0)
	{
		fprintf(stderr, "Error! Encrypt or Decrypt must be specified.\n\n)");
		err_flag = true;
	}

	if (i_flag == false)
	{
		fprintf(stderr, "Error! No input file specified.\n\n");
		err_flag = true;
	}

	if (k_flag == false)
	{
		fprintf(stderr, "Error! No key file specified.\n\n");
		err_flag = true;
	}

	if (p_flag == false)
	{
		fprintf(stderr, "Warning! Using default 'password'.\n\n");
	}

	if (o_flag == false && err_flag == false)	// no need to do this if we have errors
	{
		strcpy(gOutFileName, gInFileName);
		if (gOp == 1)	// encrypt
		{
			strcat(gOutFileName, ".enc");
		}
		if (gOp == 2)	// decrypt
		{
			strcat(gOutFileName, ".dec");
		}
	}

	if (err_flag)
	{
		usage(argv);
	}
	return;
} // parseCommandLine


void main(int argc, char *argv[])
{
#ifdef TEST_CODE
	char testData[] = "The big lazy brown FOX jumped 123 the 987 dog. Then he 8 a CHICKEN.";
	int numCAPS, numLow, numNonLetters;
	numCAPS = numLow = numNonLetters = 0;
	exCountLetters(testData, strlen(testData), &numCAPS, &numLow, &numNonLetters);
	printf("numCAPS=%d, numLow=%d, numNonLetters=%d\n", numCAPS, numLow, numNonLetters);
	exit(0);
#endif

	int length, resulti;

	// parse command line parameters
	parseCommandLine(argc, argv);		// sets global variables, checks input options for errors

										// open the input and output files
	gfptrIn = openInputFile(gInFileName);
	gfptrKey = openInputFile(gKeyFileName);
	gfptrOut = openOutputFile(gOutFileName);

	length = (size_t)strlen(gPassword);

	resulti = sha256(NULL, gPassword, length, gPasswordHash);		// get sha-256 hash of password
	if (resulti != 0)
	{
		fprintf(stderr, "Error! Password not hashed correctly.\n\n");
		exit(-1);
	}

	length = fread(gkey, 1, 65537, gfptrKey);
	if (length != 65537)
	{
		fprintf(stderr, "Error! Length of key file is not at least 65537.\n\n");
		exit(-1);
	}
	fclose(gfptrKey);
	gfptrKey = NULL;

	if (gOp == 1)	// encrypt
	{
		encryptFile(gfptrIn, gfptrOut);
	}
	else
	{
		decryptFile(gfptrIn, gfptrOut);
	}

	fclose(gfptrIn);
	fclose(gfptrOut);
	return;
} // main