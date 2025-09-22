#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "File.h"

using namespace std;
namespace fs = filesystem;

class Folder
{
private:
	// Fields
	string name;
	File* files;
	Folder* subFolders;
	string path = "H\\";
	vector<string> dirs;
	int index = 0;
	int fileSize;
	int folderSize;
public:
	// Constructors
	Folder() : Folder("New Folder") {}
	Folder(string n) : name(n), fileSize(0), folderSize(0){}
	
	// Copy Constructor
	Folder(const Folder& other) : name(other.name), fileSize(other.fileSize), folderSize(other.folderSize) {
		files = new File[fileSize];
		for (int i = 0; i < fileSize; i++) {
			files[i] = other.files[i];
		}
		subFolders = new Folder[folderSize];
		for (int i = 0; i < folderSize; i++) {
			subFolders[i] = other.subFolders[i];
		}
	}

	// Destructor
	~Folder() {
		delete[] files;
		delete[] subFolders;
	}

	// Getters and Setters
	string getName() const {
		return name;
	}
	int getFileSize() const {
		return fileSize;
	}
	int getFolderSize() const {
		return folderSize;
	}
	Folder* getSubFolder(int index) {
		if (index < 0 || index > folderSize) {
			return nullptr;
		}
		return &subFolders[index - 1];
	}
	void setName(string folderName) {
		name = folderName;
	}
	void setPath(const string& p) {
		path = p;
	}
	string getPath() const {
		return path;
	}


	// Methods
	void thisComputer();
	void print() const;
	void changeDirectory(const string& dir);
	void addFile(const File& file);
	void addSubFolder(const Folder& folder);
	void removeFile(int index);
	void removeSubFolder(int index);
	void renameFile(int index, const string& newName);
	void copyFileFolder(int index);
	void transferFileFolder(int index, Folder& folder);
	void searchFileFolder(const string& fileName) const;
};

