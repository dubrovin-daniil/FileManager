#pragma once
#include <iostream>
#include <string>

using namespace std;

class File
{
private:
	// Fields
	string name; 
	string extension;
public:
	// Constructors
	File() : File("New File", "txt") {}
	File(string fileName, string fileExtension) : name(fileName), extension(fileExtension) {}

	// Getters and Setters
	string getName() const {
		return name;
	}
	string getExtension() const {
		return extension;
	}
	void setName(string folderName) {
		name = folderName;
	}
	void setExtension(string fileExtension) {
		extension = fileExtension;
	}
};
