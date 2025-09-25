#include <iostream>
#include <Windows.h>
#include "File.h"
#include "Folder.h"

using namespace std;


void Folder::thisComputer() {
	DWORD drives = GetLogicalDrives();
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
	cout << fs::absolute(path).string() << endl;
	cout << "-------------------------------------------------- " << endl;
	//if (files) {
	//	for (int i = 0; i < fileSize; i++) {
	//		cout << "- " << files[i].getName() << "." << files[i].getExtension() << endl;
	//	}
	//}
	//if (subFolders) {
	//	for (int i = 0; i < folderSize; i++) {
	//		cout << "[Folder] " << subFolders[i].getName() << endl;
	//	}
	//}
	for (auto entry : fs::directory_iterator(path)) {
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

void Folder::changeDirectory(const string& newPath) {
	setPath(newPath);
}

// Method to add a file to the folder
void Folder::addFile() {
	string fileNameExt;
	cin.ignore();
	getline(cin, fileNameExt);

	string newFile = path + fileNameExt;
	if (!fs::exists(newFile)) {
		ofstream file(newFile);
		file.close();
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

	string newFolder = path + folderName;
	if (!fs::exists(newFolder)) {
		fs::create_directory(newFolder);
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

	string del = path + file_folderName;
	if (fs::exists(del)) {
		if (fs::is_directory(del)) {
			fs::remove_all(del);
			cout << "Directory deleted: " << del << endl;
		}
		else {
			fs::remove(del);
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

// Method to rename a file
void Folder::renameFile_Folder() {
	string oldName, newName;

	cout << "Enter the old name: ";
	cin.ignore();
	getline(cin, oldName);

	cout << "Enter a new name: ";
	cin.ignore();
	getline(cin, newName);

	string oldPath = path + oldName;
	string newPath = path + newName;

	if (fs::exists(oldPath)) {
		fs::rename(oldPath, newPath);
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

//// Method to copy a file or folder
//void Folder::copyFileFolder(int index) {
//	if (index - 1 < 0 || index - 1 >= fileSize + folderSize) {
//		cout << "Index out of bounds!" << endl;
//	}
//	else {
//		if (index - 1 < fileSize) {
//			if (fileSize < 100) {
//				files[fileSize] = files[index - 1];
//				fileSize++;
//			}
//			else {
//				cout << "File array is full!" << endl;
//			}
//		}
//		else {
//			int folderIndex = index - 1 - fileSize;
//			if (folderSize < 100) {
//				subFolders[folderSize] = subFolders[folderIndex];
//				folderSize++;
//			}
//			else {
//				cout << "Folder array is full!" << endl;
//			}
//		}
//	}
//}
//
//// Method to transfer a file or folder to another folder
//void Folder::transferFileFolder(int index, Folder& folder) {
//	if (index - 1 < 0 || index - 1 >= fileSize + folderSize) {
//		cout << "Index out of bounds!" << endl;
//	}
//	else {
//		if (index - 1 < fileSize) {
//			if (folder.fileSize < 100) {
//				folder.addFile(files[index - 1]);
//				removeFile(index);
//			}
//			else {
//				cout << "File array is full!" << endl;
//			}
//		}
//		else {
//			int folderIndex = index - 1 - fileSize;
//			if (folder.folderSize < 100) {
//				folder.addSubFolder(subFolders[folderIndex]);
//				removeSubFolder(index);
//			}
//			else {
//				cout << "Folder array is full!" << endl;
//			}
//		}
//	}
//}
//
//// Method to search for a file or folder by name
//void Folder::searchFileFolder(const string& fileName) const {
//    bool found = false;
//    if (files) {
//        for (int i = 0; i < fileSize; i++) {
//            if (files[i].getName() == fileName) {
//                cout << "\n" << files[i].getName() << "." << files[i].getExtension() << " found in Folder: " << name << endl;
//                found = true;
//            }
//        }
//    }
//    if (subFolders) {
//        for (int i = 0; i < folderSize; i++) {
//            if (subFolders[i].getName() == fileName) {
//                cout << "\n" << subFolders[i].getName() << " found in Folder: " << name << endl;
//                found = true;
//            }
//        }
//
//		if (!found) {
//			for (int i = 0; i < folderSize; i++) {
//				subFolders[i].searchFileFolder(fileName);
//			}
//		}
//    }
//
//	if (!found) {
//		cout << "\n" << fileName << " not found in Folder: " << name << endl;
//	}
//}

