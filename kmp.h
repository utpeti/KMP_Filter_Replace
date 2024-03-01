#ifndef KMP_H
#define KMP_H
#include <vector>

class charArray
{
	char* chars;
	unsigned long long length;
	void lpsArray(charArray, unsigned long long*);

public:
	charArray();
	charArray(unsigned long long);
	charArray(const char*);
	charArray(const charArray&);
	void readFromFile(const char*);
	unsigned long long findLength(const char*);
	unsigned long long getLength();
	void appendArray(charArray);
	void toLower();
	void toUpper();
	bool isEmpty();
	void reverseArray();
	void printArray();
	void insertArray(const char*, unsigned long long);
	void insertArray(charArray, unsigned long long);
	bool containsKMP(const char*);
	bool containsKMP(charArray);
	void searchKMP(const char*, std::vector<unsigned long long>&);
	void searchKMP(charArray, std::vector<unsigned long long>&);
	
	charArray operator+(const charArray&);
	charArray& operator=(const charArray&);
	charArray& operator+=(const charArray&);
	bool operator==(const charArray&);
	char& operator[](const unsigned long long);
	friend std::ostream& operator<<(std::ostream&, const charArray&);
	
	~charArray();

};

#endif
