#include <iostream>
#include <Windows.h>
#include "File.h"
#include "Folder.h"

using namespace std;

// Method for selecting a drive
void Folder::thisComputer() {
	DWORD drives = GetLogicalDrives(); // Get bitmask of drives
	vector<char> drivesVector;
	cout << "This Computer: " << endl;
	cout << "-------------------------------------------------- " << endl;
	for (char i = 'A'; i <= 'Z'; i++) { 
		if (drives & (1 << (i - 'A'))) {
			string drive = string(1, i) + ":\\";
			cout << drive << endl;
			drivesVector.push_back(i);
		}
	}
	cout << "-------------------------------------------------- " << endl;

	bool value = true;
	char choice;
	cout << "Change drive: ";
	cin >> choice;
	
	
	for (char i : drivesVector) {
		if (i == choice) {
			value = false;
			break;
		}
	}
	
	string strchoice(1, choice);

	if (value == true) {
		throw runtime_error("Invalid drive selected. Defaulting to C:");
	}
	else {
		setPath(strchoice + ":\\");
	}
}

// Method to print folder contents
void Folder::print() const {
	cout << fs::absolute(path).string() << endl; // Print the path of the current directory
	cout << "-------------------------------------------------- " << endl;
	for (auto entry : fs::directory_iterator(path)) { // Outputting directories and subfolders
		if (entry.is_directory()) {
			cout << "[Folder] " << entry.path().filename().string() << endl;
		}
		else {
			cout << "- " << entry.path().filename().string() << endl;
		}
		index + 1;
	}

	cout << "-------------------------------------------------- " << endl;
}

// Method to set the path of the folder
void Folder::changeDirectory(const string& newPath) {
	setPath(newPath); 
}

// Method to open a file
void Folder::openFile() {
	string fileName;
	cin.ignore();
	getline(cin, fileName);

	string filePath = path + "\\" + fileName;
	
	if (fs::exists(filePath) && !fs::is_directory(filePath)) { // Check if the file exist and is not a directory
		cout << "Opening file: " << filePath << endl;

		string command = "start \"\" \"" + filePath + "\""; // Command to open the file
		system(command.c_str()); // Execute command
	}
	else if (fs::is_directory(filePath)) {
		cerr << "This is a directory, not a file!" << endl;
	}
	else {
		cerr << "This file does not exist!" << endl;
	}

}

// Method to add a file to the folder
void Folder::addFile() {
	string fileNameExt;
	cin.ignore();
	getline(cin, fileNameExt);

	string newFile = path + "\\" + fileNameExt;

	if (!fs::exists(newFile)) { // Check if the file exist
		ofstream file(newFile); // Create the file
		file.close(); // Close the file
		cout << "Directory created: " << newFile << endl;
	}
	else {
		cerr << "Such a file already exists!" << endl;
	}
}

// Method to add a subfolder to the folder
void Folder::addSubFolder() {
	string folderName;
	cin.ignore();
	getline(cin, folderName);

	string newFolder = path + "\\" + folderName;

	if (!fs::exists(newFolder)) { // Check if the folder exist
		fs::create_directory(newFolder); // Create the folder
		cout << "Directory created: " << newFolder << endl;
	}
	else {
		cerr << "Such a directory already exists!" << endl;
	}
}

// Method to remove a file from the folder
void Folder::removeFile_Folder() {
	string file_folderName;
	cin.ignore();
	getline(cin, file_folderName);

	try { 
	string del = path + "\\" + file_folderName;
	if (fs::exists(del)) {// Check if the file or folder exist
		if (fs::is_directory(del)) { // Check if it's a directory
			fs::remove_all(del); // Remove the directory
			cout << "Directory deleted: " << del << endl;
		}
		else {
			fs::remove(del); // Remove the file
			cout << "File deleted: " << del << endl;
		}
	}
	else {
		if (fs::is_directory(del)) {
			cerr << "This directory does not exist!" << endl;
		}
		else {
			cerr << "This file does not exist!" << endl;
		}
	}
	}
	catch (const fs::filesystem_error& e) { 
		cout << "Remove error: " << e.what() << endl;
	}
}

// Method to rename a file
void Folder::renameFile_Folder() {
	string oldName, newName;

	cin.ignore();
	getline(cin, oldName);

	cout << "Enter a new name: ";
	getline(cin, newName);

	string oldPath = path + "\\" + oldName;
	string newPath = path + "\\" + newName;

	try {
		if (fs::exists(oldPath)) { // Check if the file or folder exist
			fs::rename(oldPath, newPath); // Rename the file or folder
			cout << "Rename: " << oldName << " -> " << newName << endl;
		}
		else {
			if (fs::is_directory(oldPath)) {
				cerr << "This directory does not exist!" << endl;
			}
			else {
				cerr << "This file does not exist!" << endl;
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Rename error: " << e.what() << endl;
	}
}

//// Method to copy a file or folder
void Folder::copyFile_Folder() {
	string copyFileFolder;
	
	cin.ignore();
	getline(cin, copyFileFolder);

	string copyPath = path + "\\" + copyFileFolder;

	string filename = fs::path(copyPath).filename().string(); 
	string copyPath2 = path + "\\" + filename + "_copy";

	if (!fs::exists(copyPath)) {
		if (fs::is_directory(copyFileFolder)) { 
			cerr << "This directory does not exist!" << endl;
		}
		else {
			cerr << "This file does not exist!" << endl;
		}
	}

	try {
		if (fs::is_directory(copyPath)) { // Check if it's a directory
			fs::copy(copyPath, copyPath2, fs::copy_options::recursive | fs::copy_options::overwrite_existing); // Copy the directory
		}
		else {
			fs::copy_file(copyPath, copyPath2, fs::copy_options::overwrite_existing); // Copy the file
		}
		cout << "Copying " << filename << " successful!" << endl;
	}
	catch (const fs::filesystem_error& e) {
		cout << "Directory copy error: " << e.path1() << " -> " << e.path2() << endl;
	}
}

//// Method to transfer a file or folder to another folder
void Folder::moveFileFolder() {
	string name, toDir;

	cin.ignore();
	getline(cin, name);

	cout << "Enter the directory to transfer(.. - to return to the parent directory): ";
	getline(cin, toDir);


	string namePath = path + "\\" + name;
	string toDirPath;

	if (!fs::exists(namePath)) {
		if (fs::is_directory(name)) {
			cerr << "This directory does not exist!" << endl;
		}
		else {
			cerr << "This file does not exist!" << endl;
		}
	}

	try {
		if (toDir == "..") {
			string parentPath = fs::path(path).parent_path().string(); // Get the parent directory
			toDirPath = parentPath + "\\" + name;
		}
		else {
			string toDirFolder = path + "\\" + toDir;
			if (!fs::is_directory(toDirFolder)) {
				cerr << "There is no such folder for transfer!" << endl;
			}
			toDirPath = toDirFolder + "\\" + name; 
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Invalid path!" << endl;
		return;
	}

	try {
		fs::rename(namePath, toDirPath); // Move the file or folder
		cout << "Transfer " << namePath << " to -> " << toDirPath << " successful!" << endl;
	}
	catch (const fs::filesystem_error& e) {
		cout << "Directory transfer error: " << fs::path(namePath).string() << " -> " << fs::path(toDirPath).string() << endl;
	}

}

void Folder::sizeOfFileFolder() const {
	string name;

	cin.ignore();
	getline(cin, name);

	string namePath = path + "\\" + name;

	try {
		if (fs::exists(namePath)) { // Check if the file or folder exist
			int size = 0;

			if (!fs::is_directory(namePath)) { // Check if it's a file
				size += fs::file_size(namePath); // Add size
			}
			else {
				for (auto& entry : fs::recursive_directory_iterator(namePath, fs::directory_options::skip_permission_denied)) { // Iterate through the directory
					if (!fs::is_directory(entry)) { // Check if it's a file
						size += fs::file_size(entry); // Add size
					}
				}
			}

			cout << "Size: " << name << " = " << size << " byte" << endl;
		}
		else {
			if (fs::is_directory(namePath)) {
				cerr << "This directory does not exist!" << endl;
			}
			else {
				cerr << "This file does not exist!" << endl;
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Size error: " << e.what() << endl;
	}
	catch (const exception& e) {
		cout << "Invalid path!" << endl;
	}
}

//// Method to search for a file or folder by name
void Folder::maskSearch() const {
	string searchName;
	string mask;

	cin.ignore();
	getline(cin, searchName);


	for (char i : searchName) { // Convert mask to regex
		if (i == '*') {
			mask += ".*";
		}
		else if (i == '?') {
			mask += ".";
		}
		else {
			mask += i;
		}
	}	

	regex r; // Regular expression
	try {
		try {
			r = regex(mask, regex_constants::icase); // Initialize regex with case insensitive flag
		}
		catch (const regex_error& e) {
			cout << "Regex error: " << e.what() << endl;
			return;
		}
		
		for (auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) { // Iterate through the directory
			try {
				string filename = entry.path().filename().string();
				if (regex_match(filename, r)) { // Checking a given regular expression
					cout << entry.path().string() << endl;
				}
			}
			catch (const exception& e) {
				cout << "Invalid path!" << endl;
				continue;
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Search error: Access denied!" << endl;
	}
}

