#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include "Folder.h"
#include "File.h"

using namespace std;

int main()  
{ 
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	Folder ThisComputer("This Computer");  
	Folder* currentFolder = &ThisComputer; 
	
	try {
		ThisComputer.thisComputer();
	}
	catch (const runtime_error& e) {
		cout << e.what() << endl;
		ThisComputer.setPath("C:\\");
		cout << "Press Enter to continue..." << endl;
		cin.ignore();
		cin.get();
	}
	


	system("cls");
	ThisComputer.print();

	while (true) {
		string choice;
		cout << "\n\nTerminal> \n";
		cout << "Select an action:\nexit - Closing the program.\ncd - Change Directory.\nmkfile - Make file.\nmkdir - Make directory.\ndel - Delete file/directory.\nren - Rename file/directory.\ncopy - Copy file/directory.\nmove - Transfer file/directory.\nsearch - Search file/directory.\n. - current directory\n.. - Back." << endl;
		cout << ">>> ";
		cin >> choice;

		if (choice == "Exit") {
			break;
		}
		else if (choice == "cd") {
			string subChoice;
			cout << "Select a directory to open: ";
			cin.ignore();
			getline(cin, subChoice);

			ThisComputer.changeDirectory(ThisComputer.getPath() + subChoice + "\\");

			cout << endl; 
			system("cls");

			ThisComputer.print();
			/*Folder* selected = currentFolder->getSubFolder(subChoice);
			if (selected != nullptr) {
				currentFolder = selected;
				currentFolder->print();
			}
			else {
				system("cls");
				currentFolder->print();

				cout << "Invalid folder index." << endl;
			}*/
		}
		else if (choice == "..") {
			ThisComputer.setPath(fs::path(ThisComputer.getPath()).parent_path().string());

			cout << endl;
			system("cls");

			ThisComputer.print();
		}
		//else if (choice == 2) {
  //          string fileName, fileType;
  //          cout << "Enter file name: ";
  //          cin.ignore();
  //          getline(cin, fileName);
  //          cout << "Enter file type (extension): ";
  //          getline(cin, fileType);
  //          currentFolder->addFile(File(fileName, fileType));
  //          system("cls");
  //          currentFolder->print();
		//}
  //      else if (choice == 3) {
		//	string folderName;
		//	cout << "Enter subfolder name: ";
		//	cin.ignore();
		//	getline(cin, folderName);
		//	Folder NewFolder(folderName);
		//	currentFolder->addSubFolder(NewFolder);
		//	system("cls");
		//	currentFolder->print();
  //      }
		//else if (choice == 4) {
		//	int fileIndex;
		//	cout << "Enter file index to remove: ";
		//	cin >> fileIndex;
		//	currentFolder->removeFile(fileIndex);
		//	system("cls");
		//	currentFolder->print();
		//}
		//else if (choice == 5) {
		//	int folderIndex;
		//	cout << "Enter subfolder index to remove: ";
		//	cin >> folderIndex;
		//	currentFolder->removeSubFolder(folderIndex);
		//	system("cls");
		//	currentFolder->print();
		//}
		//else if (choice == 6) {
		//	int fileIndex;
		//	string newName;
		//	cout << "Enter file index to rename: ";
		//	cin >> fileIndex;
		//	cout << "Enter new file name: ";
		//	cin.ignore();
		//	getline(cin, newName);
		//	currentFolder->renameFile(fileIndex, newName);
		//	system("cls");
		//	currentFolder->print();
		//}
		//else if (choice == 7) {
		//	string newName;
		//	cout << "Enter new folder name: ";
		//	cin.ignore();
		//	getline(cin, newName);
		//	currentFolder->setName(newName);
		//	system("cls");
		//	currentFolder->print();
		//}
		//else if (choice == 8) {
		//	int index;
		//	cout << "Enter file/folder index to copy: ";
		//	cin >> index;
		//	currentFolder->copyFileFolder(index);
		//	system("cls");
		//	currentFolder->print();
		//}
		//else if (choice == 9) {
		//	int index;
		//	int subChoice;
		//	cout << "Enter file/folder index to transfer: ";
		//	cin >> index;
		//	cout << "\nSelect a folder to transfer to: ";
		//	cin >> subChoice;
		//	if (currentFolder->getSubFolder(subChoice) != nullptr) {
		//		currentFolder->transferFileFolder(index, *(currentFolder->getSubFolder(subChoice)));
		//		system("cls");
		//		currentFolder->print();
		//	}
		//	else {
		//		system("cls");
		//		currentFolder->print();

		//		cout << "Invalid folder index." << endl;
		//	}
		//}
		//else if (choice == 10) {
		//	string searchName;
		//	cout << "Enter file or folder name to search: ";
		//	cin.ignore();
		//	getline(cin, searchName);

		//	system("cls");
		//	currentFolder->print();

		//	cout << "\n\nSearch results for \"" << searchName << "\":" << endl;
		//	currentFolder->searchFileFolder(searchName);
		//}
		//else if (choice == 11) {
		//	system("cls");

		//	currentFolder = &ThisComputer;
		//	currentFolder->print();
		//	continue;
		//}
		//else {
		//	system("cls");
		//	currentFolder->print();

		//	cout << "Invalid choice. Please try again." << endl;

		//	continue;
		//}
	}
}

