#include <iostream>
#include <cmath>
#include <string>

int main() {
	int choice;  
	int size;
	int sub = 0;
	int s;
	std::string c;
	std::string bin;
	std::string data;
	std::string rep = "00000000 ";
	
	do {
		std::cout << "Do you want to convert a text to binary type (1) or vice versa (2)? ";
		std::cin >> choice;
		if (choice == 1) {
			std::cout << "Proceed to run text-binary converter.\n";
			std::cout << "Enter your data: ";
			std::cin.ignore();
			std::getline(std::cin, data);
			size = data.size();
			for (int i = size; i > 0; i--) {
				sub = (int) data[0];
				data.erase(0,1);
				for (int j =7; j>=0; j--) {
					if (sub >= pow(2, j)) {
						rep.erase(7 - j, 1);
						rep.insert(7 - j, "1");
						sub = sub - pow(2, j);
					}
				}
				data.append(rep);
				rep = "00000000 ";
			}
		}
		else if (choice == 2) {
			std::cout << "Proceed to run binary-text converter.\n";
			std::cout << "How many characters/symbols represented are there in total? ";
			std::cin >> size;
			std::cout << "Enter your data down below: \n";
			for (int i = 0; i < size; i++) {				
				std::cin >> bin;
				while (bin.size() > 8) {
					std::cout << "Only 8 bit binary is supported!\n";
					std::cout << "Try again:\n";
						std::cin >> bin;
				}
				for (int j = 0; j < bin.size(); j++) {
					while (!(bin[j] == '1' || bin[j] == '0')) {
						std::cout << "Only binary-type date is allowed!\n";
						std::cout << "Try again:\n";
						std::cin >> bin;
					}
				}
				s = bin.size();
				for (int j = 1; j < s + 1; j++) {
					if (bin[s-j] == '1') {
						rep.erase(8-j,1);
						rep.insert(8-j, "1");
					}
				}
				for (int j = 0; j < 8; j++) {
					if (rep[j] == '1') {
						sub = sub + pow(2, 7-j);
					}
				}
				c = (char) sub;
				data.append(c);
				sub = 0;
				rep = "00000000 ";
		}
	}
		
		std::cout << data;
	} while (!(choice == 1 || choice == 2));
			
	return 0;
}