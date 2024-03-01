#include <iostream>
#include "kmp.h"
#include <vector>
#include <fstream>

charArray::charArray()
{
	chars = new char[1];
	length = 0;

	chars[length] = '\0';
}

charArray::charArray(unsigned long long size)
{
	chars = new char[size + 1];
	length = size;

	chars[length] = '\0';
}

charArray::charArray(const char* intext)
{
	length = findLength(intext);
	chars = new char[length + 1];

	unsigned long long i = 0;
	while (intext[i] != '\0')
	{
		chars[i] = intext[i];
		++i;
	}
	chars[length] = '\0';
}

charArray::charArray(const charArray& inarray)
{
	unsigned long long len = inarray.length;
	chars = new char[len + 1];
	length = len;

	for (unsigned long long i = 0; i < len; ++i)
	{
		chars[i] = inarray.chars[i];
	}

	chars[len] = '\0';
}

void charArray::readFromFile(const char* filename)
{
	std::ifstream fis(filename);
	if (fis.is_open())
	{
		fis.seekg(0, std::ios::end);
		int size = fis.tellg();
		fis.seekg(0, std::ios::beg);
		chars = new char[size];
		length = size;
		fis.read(chars, size);
		unsigned long long newlength = length;
		for (unsigned long long i = 0; i < length; ++i)
		{
			if (chars[i] == '\n')
			{
				--newlength;
			}
		}
		length = newlength;
		chars[length] = '\0';
		return;
	}
	std::cerr << "ERROR WHILE OPENING THE FILE" << std::endl;
	exit(-1);
}

unsigned long long charArray::findLength(const char* intext)
{
	unsigned long long i = 0;
	while (intext[i] != '\0')
	{
		++length;
		++i;
	}

	return i;
}

unsigned long long charArray::getLength()
{
	return length;
}

void charArray::appendArray(charArray newarray)
{
	unsigned long long i = 0;
	while (i < newarray.length)
	{
		chars[length + i] = newarray.chars[i];
		++i;
	}

	length += newarray.length;
	chars[length] = '\0';
}

void charArray::toLower()
{
	unsigned long long i = 0;
	while (i < length)
	{
		if (chars[i] >= 'A' && chars[i] <= 'Z')
		{
			chars[i] += 32;
		}
		++i;
	}
}

void charArray::toUpper()
{
	unsigned long long i = 0;
	while (i < length)
	{
		if (chars[i] >= 'a' && chars[i] <= 'z')
		{
			chars[i] -= 32;
		}
		++i;
	}
}

bool charArray::isEmpty()
{
	return length == 0;
}

void charArray::reverseArray()
{
	char* tempChars = new char[length + 1];
	unsigned long long i = 0;

	while (i < length)
	{
		tempChars[length - i - 1] = chars[i];
		++i;
	}

	i = 0;
	while (i < length)
	{
		chars[i] = tempChars[i];
		++i;
	}
	chars[length] = '\0';

	delete[] tempChars;
}

void charArray::printArray()
{
	unsigned long long i = 0;
	while (i < length)
	{
		std::cout << chars[i];
		++i;
	}
	std::cout << std::endl;
}

void charArray::insertArray(const char* intext, unsigned long long index)
{
	charArray inarray(intext);
	insertArray(inarray, index);
}

void charArray::insertArray(charArray inarray, unsigned long long index)
{
	char* newchars = new char[length + inarray.length];

	for (unsigned long long i = 0; i < index; i++)
	{
		newchars[i] = chars[i];
	}

	unsigned long long inarrayind = 0;
	for (unsigned long long i = index; i < index + inarray.getLength(); ++i)
	{
		newchars[i] = inarray[inarrayind];
		++inarrayind;
	}

	unsigned long long newi = index;
	for (unsigned long long i = index + inarray.getLength(); i < length + inarray.getLength(); i++)
	{
		newchars[i] = chars[newi];
		++newi;
	}

	delete[] chars;

	chars = newchars;

	length += inarray.getLength();
	chars[length] = '\0';
}

void charArray::lpsArray(charArray pattern, unsigned long long* lps)
{
	unsigned long long m = pattern.length;
	lps[0] = 0;

	unsigned long long len = 0;
	unsigned long long i = 1;

	while (i < m)
	{
		if (pattern.chars[i] == pattern.chars[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0)
			{
				len = lps[len - 1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

bool charArray::containsKMP(const char* intext)
{
	std::vector<unsigned long long> indexes;
	charArray temparray(intext);

	searchKMP(temparray, indexes);

	if (indexes.size() > 0)
	{
		return true;
	}
	return false;
}

bool charArray::containsKMP(charArray inarray)
{
	std::vector<unsigned long long> indexes;

	searchKMP(inarray, indexes);

	if (indexes.size() > 0)
	{
		return true;
	}

	return false;
}

void charArray::searchKMP(const char* pattern, std::vector<unsigned long long>& indexes)
{
	charArray temparray(pattern);
	searchKMP(temparray, indexes);
}

void charArray::searchKMP(charArray pattern, std::vector<unsigned long long>& indexes)
{
	unsigned long long m = pattern.length;
	unsigned long long* lps = new unsigned long long[m];
	lpsArray(pattern, lps);

	unsigned long long i = 0;
	unsigned long long j = 0;

	while (i < length)
	{
		if (chars[i] == pattern.chars[j])
		{
			++i;
			++j;
		}

		if (j == m)
		{
			indexes.push_back(i - j);
			j = lps[j - 1];
		}
		else if (i < length && chars[i] != pattern.chars[j])
		{
			if (j != 0)
			{
				j = lps[j - 1];
			}
			else
			{
				i++;
			}
		}
	}

	delete[] lps;
}

charArray charArray::operator+(const charArray& inarray)
{
	charArray newarray;
	newarray.length = length + inarray.length;

	newarray.chars = new char[newarray.length + 1];

	unsigned long long i = 0;
	while (chars[i] != '\0')
	{
		newarray.chars[i] = chars[i];
		++i;
	}

	unsigned long long j = 0;
	while (inarray.chars[j] != '\0')
	{
		newarray.chars[i] = inarray.chars[j];
		++i;
		++j;
	}

	newarray.chars[i] = '\0';

	return newarray;
}

charArray& charArray::operator=(const charArray& inarray)
{
	if (this == &inarray)
		return *this;

	delete[] chars;

	unsigned long long len = inarray.length;
	chars = new char[len + 1];
	length = len;

	for (unsigned long long i = 0; i < len; ++i)
		chars[i] = inarray.chars[i];

	chars[len] = '\0';

	return *this;
}

charArray& charArray::operator+=(const charArray& inarray)
{
	charArray newarray(length + inarray.length);

	unsigned long long i = 0;
	while (i < length)
	{
		newarray.chars[i] = chars[i];
		++i;
	}
	unsigned long long tilnow = i;
	i = 0;
	while (i < inarray.length)
	{
		newarray.chars[tilnow + i] = inarray.chars[i];
		++i;
	}

	length += inarray.length;
	newarray.chars[length] = '\0';
	chars = newarray.chars;

	return *this;
}

bool charArray::operator==(const charArray& inarray)
{
	if (length != inarray.length)
	{
		return false;
	}
	unsigned long long i = 0;
	while (chars[i] != '\0')
	{
		if (chars[i] != inarray.chars[i])
		{
			return false;
		}
		++i;
	}
	return true;
}

char& charArray::operator[](const unsigned long long i)
{
	if (i < length && i >= 0)
	{
		return chars[i];
	}
}

std::ostream& operator<<(std::ostream& os, const charArray& inarray)
{
	unsigned long long i = 0;
	unsigned long long length = inarray.length;
	while (i < length)
	{
		os << inarray.chars[i];
		++i;
	}
	return os;
}

charArray::~charArray()
{
	
}
