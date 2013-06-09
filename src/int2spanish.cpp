#include <vector>
#include <cstdlib>
#include <ctime>	/* only for tests */
#include <sstream>
#include <iostream>
using namespace std;

/* * * * * * *  */

#define 	ERROR(msg)		\
{ cout << "Error in function \"" << __FUNCTION__ << "\" | " << (msg) << endl; exit(-1); }

/* * * * * * *  */

string int2spanish(int n);
vector<string> splitNumber(string nStr);
string joinNumber(vector<string> pieces);
string convertMillion(string num, int place);
string joinMillion(string fstThousand, string sndThousand);
string nameMillion(string million, int place);
string convertThousand(string num);
string joinThousand(string hundreds, string tensAndUnits);
string joinTensAndUnits(string tens, string units);
string getMillionName(int place, bool plural);
string getHundredsName(int digit);
string getTensName(int digit);
string getUnitsName(int digit);
string handleSpecialCases(string num, bool negative);
string int2str(int n);
int str2int(string n);
int abs(int n);
int digit2int(char d);

/* * * * * * *  */

/*
*	Converts any integer into its
*	spanish textual representation.
*/
string int2spanish(int n)
{
	string nStr = int2str(abs(n));
	bool negative = n < 0;

	vector<string> pieces = splitNumber(nStr);

	for (int i = 0; i < pieces.size(); ++i)
		pieces[i] = convertMillion(pieces[i], pieces.size() - 1 - i);

	string num = joinNumber(pieces);

	num = handleSpecialCases(num, negative);

	return num;
}

/*
*	Splits a number into consecutive 6-digit substrings (or "millions"),
*	previously padding to the left with zeroes if necessary.
*/
vector<string> splitNumber(string nStr)
{
	nStr.insert(0, 6 - (nStr.length()%6), '0');

	vector<string> pieces;
	for (int i = 0; i < (nStr.length()/6); ++i)
		pieces.push_back(nStr.substr(6*i,6));

	return pieces;
}

/*
*	Joins the pieces of the original number after they have
*	undergone the conversion, using commas as delimiters.
*/
string joinNumber(vector<string> pieces)
{
	string num = "";
	for (int i = 0; i < pieces.size(); ++i)
	{
		if(!num.empty() && !pieces[i].empty()) num.append(", ");
		num.append(pieces[i]);
	}

	return num;
}

/*
*	Converts any number under one million into it's textual representation,
*	and adds the corresponding million marker respect to it's position in
*	the original number.
*/
string convertMillion(string num, int place)
{
	string fstThousand = convertThousand(num.substr(0,3));
	string sndThousand = convertThousand(num.substr(3,3));

	string million = joinMillion(fstThousand, sndThousand);

	string namedMillion = nameMillion(million, place);

	return namedMillion;
}

/*
*	Join's the textual representation of the most and least significant
*	thoushands composing the million.
*/
string joinMillion(string fstThousand, string sndThousand)
{
	if(fstThousand.empty())		return sndThousand;

	if(fstThousand == "un")		fstThousand = "";
	if(!fstThousand.empty()) 	fstThousand = fstThousand  + " ";
	if(!sndThousand.empty()) 	sndThousand = " " + sndThousand;

	return fstThousand + "mil" + sndThousand;
}

/*
*	Add's the million's position marker to its textual representation, handling the
*	distinction between singular/plural.
*	Example:
*		abcdef						-> (...) *empty*
*		abcdefxxxxxx				-> (...) million(millions)
*		abcdefxxxxxxxxxxxx			-> (...) billion(billions)
*		abcdefxxxxxxxxxxxxxxxxxx	-> (...) trillion(trillions)
*/
string nameMillion(string million, int place)
{
	string millionName = getMillionName(place, million != "un");

	if(million.empty())		return "";
	else					return million + (millionName.empty()?"":" ") + millionName;
}

string convertThousand(string num)
{
	int us = digit2int(num[2]), ts = digit2int(num[1]), hs = digit2int(num[0]);
	string hundreds = getHundredsName(hs), tens = getTensName(ts), units = getUnitsName(us);

	string tensAndUnits = joinTensAndUnits(tens, units);
	string thousand = joinThousand(hundreds, tensAndUnits);

	return thousand;
}

string joinThousand(string hundreds, string tensAndUnits)
{
	if(hundreds.empty())						return tensAndUnits;
	else if(tensAndUnits.empty())				return hundreds;
	else if(hundreds == "cien")					return "ciento " + tensAndUnits;
	else 										return hundreds + " " + tensAndUnits;
}

string joinTensAndUnits(string tens, string units)
{
	if(tens == "diez" && units == "un")				return "once";
	else if(tens == "diez" && units == "dos")		return "doce";
	else if(tens == "diez" && units == "tres")		return "trece";
	else if(tens == "diez" && units == "cuatro")	return "catorce";
	else if(tens == "diez" && units == "cinco")		return "quince";
	else if(tens == "diez" && units == "seis")		return "dieciséis";
	else if(tens == "diez" && units == "siete")		return "diecisiete";
	else if(tens == "diez" && units == "ocho")		return "dieciocho";
	else if(tens == "diez" && units == "nueve")		return "diecinueve";
	else if(tens == "veinte" && units == "un")		return "veintiun";
	else if(tens == "veinte" && units == "dos")		return "veintidos";
	else if(tens == "veinte" && units == "tres")	return "veintitres";
	else if(tens == "veinte" && units == "cuatro")	return "veinticuatro";
	else if(tens == "veinte" && units == "cinco")	return "veinticinco";
	else if(tens == "veinte" && units == "seis")	return "veintiséis";
	else if(tens == "veinte" && units == "siete")	return "veintisiete";
	else if(tens == "veinte" && units == "ocho")	return "veintiocho";
	else if(tens == "veinte" && units == "nueve")	return "veintinueve";
	else if(tens.empty())							return units;
	else if(units.empty())							return tens;
	else 											return tens + " y " + units;
}

string getMillionName(int place, bool plural)
{
	switch(place)
	{
		case 0: return ""; break;
		case 1: return (plural?"millones":"millón"); break;
		case 2: return (plural?"billones":"billón"); break;
		case 3: return (plural?"trillones":"trillón"); break;
		case 4: return (plural?"cuatrillones":"cuatrillón"); break;
		default: ERROR("Invalid state."); break;
	}
}

string getHundredsName(int digit)
{
	switch(digit)
	{
		case 0: return ""; break;
		case 1: return "cien"; break;
		case 2: return "doscientos"; break;
		case 3: return "trescientos"; break;
		case 4: return "cuatrocientos"; break;
		case 5: return "quinientos"; break;
		case 6: return "seiscientos"; break;
		case 7: return "setecientos"; break;
		case 8: return "ochocientos"; break;
		case 9: return "novecientos"; break;
		default: ERROR("Invalid state."); break;
	}
}

string getTensName(int digit)
{
	switch(digit)
	{
		case 0: return ""; break;
		case 1: return "diez"; break;
		case 2: return "veinte"; break;
		case 3: return "treinta"; break;
		case 4: return "cuarenta"; break;
		case 5: return "cincuenta"; break;
		case 6: return "sesenta"; break;
		case 7: return "setenta"; break;
		case 8: return "ochenta"; break;
		case 9: return "noventa"; break;
		default: ERROR("Invalid state."); break;
	}
}

string getUnitsName(int digit)
{
	switch(digit)
	{
		case 0: return ""; break;
		case 1: return "un"; break;
		case 2: return "dos"; break;
		case 3: return "tres"; break;
		case 4: return "cuatro"; break;
		case 5: return "cinco"; break;
		case 6: return "seis"; break;
		case 7: return "siete"; break;
		case 8: return "ocho"; break;
		case 9: return "nueve"; break;
		default: ERROR("Invalid state."); break;
	}

}

string handleSpecialCases(string num, bool negative)
{
	if(num.empty())								num = "cero";
	if(negative)								num = "menos " + num;
	if(num.substr(num.length()-2,2) == "un")	num = num + "o";

	return num;
}

string int2str(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

int str2int(string n)
{
	stringstream ss(n);
	int num;
	ss >> num;
	return num;
}

int abs(int n)
{
	return (n < 0 ? (-n) : n);
}

int digit2int(char d)
{
	return (d - '0');
}

/* * * * * * *  */

// /*
// * Some tests
// */

// #define		PRINT(num)			\
// { cout << (num) << " : " << (int2spanish(num)) << endl; }

// int main(int argc, char** argv)
// {
// 	if( 1 < argc )
// 	{
// 		for (int i = 1; i < argc; ++i)
// 			PRINT(str2int(argv[i]));
// 	} else {
// 		PRINT(0);
// 		PRINT(1);
// 		PRINT(2);
// 		PRINT(3);
// 		PRINT(4);
// 		PRINT(5);
// 		PRINT(6);
// 		PRINT(7);
// 		PRINT(8);
// 		PRINT(9);
// 		PRINT(10);
// 		PRINT(100);
// 		PRINT(101);
// 		PRINT(102);
// 		PRINT(103);
// 		PRINT(104);
// 		PRINT(105);
// 		PRINT(106);
// 		PRINT(107);
// 		PRINT(108);
// 		PRINT(109);
// 		PRINT(1000);
// 		PRINT(10000);
// 		PRINT(100000);
// 		PRINT(1000000);
// 		PRINT(10000000);
// 		PRINT(100000000);
// 		PRINT(1000000000);
// 		PRINT(-1000000000);
// 		srand(time(0));
// 		for (int i = 0; i < 20; ++i)
// 			{ int n = (rand()%101 - 50)*1; PRINT(n);}
// 		for (int i = 0; i < 20; ++i)
// 			{ int n = (rand()%101 - 50)*107; PRINT(n);}
// 		for (int i = 0; i < 20; ++i)
// 			{ int n = (rand()%101 - 50)*9207; PRINT(n);}
// 	}

// 	return 0;
// }

