#include <iostream>

std::string tm(char a, std::string b) {
	switch(a) {
		case 'a': b = ".- "; break;
		case 'b': b = "-... "; break;
		case 'c': b = "-.-. "; break;
		case 'd': b = "-.. "; break;
		case 'e': b = ". "; break;
		case 'f': b = "..-. "; break;
		case 'g': b = "--. "; break;
		case 'h': b = ".... "; break;
		case 'i': b = ".. "; break;
		case 'j': b = ".--- "; break;
		case 'k': b = "-.- "; break;
		case 'l': b = ".-.. "; break;
		case 'm': b = "-- "; break;
		case 'n': b = "-. "; break;
		case 'o': b = "--- "; break;
		case 'p': b = ".--. "; break;
		case 'q': b = "--.- "; break;
		case 'r': b = ".-. "; break;
		case 's': b = "... "; break;
		case 't': b = "- "; break;
		case 'u': b = "..- "; break;
		case 'v': b = "...- "; break;
		case 'w': b = ".-- "; break;
		case 'x': b = "-..- "; break;
		case 'y': b = "-.-- "; break;
		case 'z': b = "--.. "; break;
		case 'A': b = ".- "; break;
		case 'B': b = "-... "; break;
		case 'C': b = "-.-. "; break;
		case 'D': b = "-.. "; break;
		case 'E': b = ". "; break;
		case 'F': b = "..-. "; break;
		case 'G': b = "--. "; break;
		case 'H': b = ".... "; break;
		case 'I': b = ".. "; break;
		case 'J': b = ".--- "; break;
		case 'K': b = "-.- "; break;
		case 'L': b = ".-.. "; break;
		case 'M': b = "-- "; break;
		case 'N': b = "-. "; break;
		case 'O': b = "--- "; break;
		case 'P': b = ".--. "; break;
		case 'Q': b = "--.- "; break;
		case 'R': b = ".-. "; break;
		case 'S': b = "... "; break;
		case 'T': b = "- "; break;
		case 'U': b = "..- "; break;
		case 'V': b = "...- "; break;
		case 'W': b = ".-- "; break;
		case 'X': b = "-..- "; break;
		case 'Y': b = "-.-- "; break;
		case 'Z': b = "--.. "; break;
		case '(': b = "-.--. "; break;
		case '-': b = "-....- "; break;
		case '&': b = ".-... "; break;
		case ',': b = "--..-- "; break;
		case '?': b = "..--.. "; break;
		case ')': b = "-.--.- "; break;
		case ':': b = "---... "; break;
		case '!': b = "-.-.-- "; break;
		case '$': b = "...-..- "; break;
		case ';': b = "-.-.-. "; break;
		case '/': b = "-..-. "; break;
		case '=': b = "-...- "; break;
		case '@': b = ".--.-. "; break;
		case '"': b = ".-..-. "; break;
		case '.': b = ".-.-.- "; break;
		case '+': b = ".-.-. "; break;
		case '_': b = "..--.- "; break;
		case '\'': b = ".----. "; break;
		case ' ': b = "/ "; break;
		case '0': b = "----- "; break;
		case '1': b = ".---- "; break;
		case '2': b = "..--- "; break;
		case '3': b = "...-- "; break;
		case '4': b = "....- "; break;
		case '5': b = "..... "; break;
		case '6': b = "-.... "; break;
		case '7': b = "--... "; break;
		case '8': b = "---.. "; break;
		case '9': b = "----. "; break;
		case '%': b = "----- -..-. ----- "; break;
		default: b = "# "; break;
	}
	return b;
}

void check(std::string a, std::string b, std::string c, std::string d) {
	if (a == c) {
		b = d;
	}
}

std::string mt(std::string a, std::string b) {
	if (a == ".-") {
		b = "A";
	}
	else if (a == "-...") {
		b = "B";
	}
	else if (a == "-.-.") {
		b = "C";
	}
	else if (a == "-..") {
		b = "D";
	}
	else if (a == ".") {
		b = "E";
	}
	else if (a == "..-.") {
		b = "F";
	}
	else if (a == "--.") {
		b = "G";
	}
	else if (a == "....") {
		b = "H";
	}
	else if (a == "..") {
		b = "I";
	}
	else if (a == ".---") {
		b = "J";
	}
	else if (a == "-.-") {
		b = "K";
	}
	else if (a == ".-..") {
		b = "L";
	}
	else if (a == "--") {
		b = "M";
	}
	else if (a == "-.") {
		b = "N";
	}
	else if (a == "---") {
		b = "O";
	}
	else if (a == ".--.") {
		b = "P";
	}
	else if (a == "--.-") {
		b = "Q";
	}
	else if (a == ".-.") {
		b = "R";
	}
	else if (a == "...") {
		b = "S";
	}
	else if (a == "-") {
		b = "T";
	}
	else if (a == "..-") {
		b = "U";
	}
	else if (a == "...-") {
		b = "V";
	}
	else if (a == ".--") {
		b = "W";
	}
	else if (a == "-..-") {
		b = "X";
	}
	else if (a == "-.--") {
		b = "Y";
	}
	else if (a == "--..") {
		b = "Z";
	}
	else if (a == "-----") {
		b = "0";
	}
	else if (a == ".----") {
		b = "1";
	}
	else if (a == "..---") {
		b = "2";
	}
	else if (a == "...--") {
		b = "3";
	}
	else if (a == "....-") {
		b = "4";
	}
	else if (a == ".....") {
		b = "5";
	}	
	else if (a == "-....") {
		b = "6";
	}
	else if (a == "--...") {
		b = "7";
	}
	else if (a == "---..") {
		b = "8";
	}
	else if (a == "----.") {
		b = "9";
	}
	else if (a == ".-...") {
		b = "&";
	}
	else if (a == ".--.-.") {
		b = "@";
	}
	else if (a == "-.--.-") {
		b = "(";
	}
	else if (a == "-.--.") {
		b = ")";
	}
	else if (a == "---...") {
		b = ":";
	}
	else if (a == "--..--") {
		b = ",";
	}
	else if (a == "-...-") {
		b = "=";
	}
	else if (a == "-.-.--") {
		b = "!";
	}
	else if (a == ".-.-.-") {
		b = ".";
	}
	else if (a == ".-..-.") {
		b = "\"";
	}
	else if (a == "-....-") {
		b = "-";
	}
	else if (a == "..--.-") {
		b = "_";
	}
	else if (a == ".-.-.") {
		b = "+";
	}
	else if (a == ".----.") {
		b = "'";
	}
	else if (a == "..--..") {
		b = "?";
	}
	else if (a == "-..-.") {
		b = "/"; 
	}
	else if (a == "/") {
		b = " ";
	}
	else if (a == "-.-.-.") {
		b = ";"; 
	}
	else {
		b = "#";
	}
	return b;
}
	

int main() {
	int choice;  
	int size;
	bool s;
	std::string bin;
	std::string data, sub;
	
	std::cout << "This program only support translation for standard Morse code.\n";
	std::cout << "Abbreviations or shortened letters aren't supported.\n";
	std::cout << "# represents undefined or invalid letter.\n";
	do {
		std::cout << "Do you want to convert a text to Morse code (1) or vice versa (2)? ";
		std::cin >> choice;
		if (choice == 1) {
			std::cout << "Proceed to run text-Morse converter.\n";
			std::cout << "Enter your data: ";
			std::cin.ignore();
			std::getline(std::cin, data);
			size = data.size();
			for (int i = 0; i < size; i++) {
				data.append(tm(data[0], bin));
				data.erase(0, 1);
			}
		}
		else if (choice == 2) {
			std::cout << "Proceed to run Morse code translator.\n";
			std::cout << "How many characters/symbols are there in total? ";
			std::cin >> size;
			std::cout << "Enter your data down below (whitespace excluded please): \n";
			for (int i = 0; i < size; i++) {
				do {
					std::cin >> bin;
					s = true;
					for (int j = 0; j < bin.size(); j++) {
						if (!(bin[j] == '.'||bin[j]=='-'||bin[j]=='/')) {
							s = false;
							std::cout << "Invalid input. Please enter in Morse code.\n";
							break;
						}
					}
					if (s) {
						data.append(mt(bin, sub));
					}
				} while (!s);
            }
		}
		else {
			std::cout << "Please choose between 1 or 2 only.";  
		}
		std::cout << data;
	} while (!(choice == 1 || choice == 2));
			
	return 0;
}