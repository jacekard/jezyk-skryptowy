#pragma once

class variable {
public:
	char* key;
	int value;
	bool isNul;
	bool toDisplay;
	variable() {
		key = '\0';
		value = NULL;
		isNul = true;
		toDisplay = false;
	}
	int compareTo(variable &b) {
		
	}
	friend std::ostream& operator<<(std::ostream& os, const variable& var);

};


std::ostream& operator<<(std::ostream &os, const variable& var) {
	if (var.isNul)
		os << "Nul";
	else
		os << var.value;
	
	return os;
}