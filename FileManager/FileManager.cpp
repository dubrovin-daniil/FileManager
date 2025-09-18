#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Folder.h"
#include "File.h"

using namespace std;

int main()  
{ 
	ifstream is("example.txt");
	Folder ThisComputer("This Computer");  
	Folder* currentFolder = &ThisComputer; 

	Folder diskC("Disk C");
	Folder diskD("Disk D");

	ThisComputer.addSubFolder(diskC);
	ThisComputer.addSubFolder(diskD);    
	  
	ThisComputer.print();

	while (true) {
		int choice;
		cout << "\n\nTerminal> \n";
		cout << "Select an action:\n0 - Exit\n1 - Select a folder.\n2 - Add file to Folder.\n3 - Add subfolder to Folder.\n4 - Remove file from Folder.\n5 - Remove subfolder from Folder.\n6 - Rename file.\n7 - Rename folder.\n8 - Copy file/folder.\n9 - Transfer file/folder.\n10 - Search file/folder.\n11 - Back." << endl;
		cout << ">>> ";
		cin >> choice;

		if (choice == 0) {
			break;
		}
		else if (choice == 1) {
			int subChoice;
			cout << "Select a folder to open: ";
			cin >> subChoice;
			cout << endl; 
			system("cls");

			Folder* selected = currentFolder->getSubFolder(subChoice);
			if (selected != nullptr) {
				currentFolder = selected;
				currentFolder->print();
			}
			else {
				system("cls");
				currentFolder->print();

				cout << "Invalid folder index." << endl;
			}
		}
		else if (choice == 2) {
            string fileName, fileType;
            cout << "Enter file name: ";
            cin.ignore();
            getline(cin, fileName);
            cout << "Enter file type (extension): ";
            getline(cin, fileType);
            currentFolder->addFile(File(fileName, fileType));
            system("cls");
            currentFolder->print();
		}
        else if (choice == 3) {
			string folderName;
			cout << "Enter subfolder name: ";
			cin.ignore();
			getline(cin, folderName);
			Folder NewFolder(folderName);
			currentFolder->addSubFolder(NewFolder);
			system("cls");
			currentFolder->print();
        }
		else if (choice == 4) {
			int fileIndex;
			cout << "Enter file index to remove: ";
			cin >> fileIndex;
			currentFolder->removeFile(fileIndex);
			system("cls");
			currentFolder->print();
		}
		else if (choice == 5) {
			int folderIndex;
			cout << "Enter subfolder index to remove: ";
			cin >> folderIndex;
			currentFolder->removeSubFolder(folderIndex);
			system("cls");
			currentFolder->print();
		}
		else if (choice == 6) {
			int fileIndex;
			string newName;
			cout << "Enter file index to rename: ";
			cin >> fileIndex;
			cout << "Enter new file name: ";
			cin.ignore();
			getline(cin, newName);
			currentFolder->renameFile(fileIndex, newName);
			system("cls");
			currentFolder->print();
		}
		else if (choice == 7) {
			string newName;
			cout << "Enter new folder name: ";
			cin.ignore();
			getline(cin, newName);
			currentFolder->setName(newName);
			system("cls");
			currentFolder->print();
		}
		else if (choice == 8) {
			int index;
			cout << "Enter file/folder index to copy: ";
			cin >> index;
			currentFolder->copyFileFolder(index);
			system("cls");
			currentFolder->print();
		}
		else if (choice == 9) {
			int index;
			int subChoice;
			cout << "Enter file/folder index to transfer: ";
			cin >> index;
			cout << "\nSelect a folder to transfer to: ";
			cin >> subChoice;
			if (currentFolder->getSubFolder(subChoice) != nullptr) {
				currentFolder->transferFileFolder(index, *(currentFolder->getSubFolder(subChoice)));
				system("cls");
				currentFolder->print();
			}
			else {
				system("cls");
				currentFolder->print();

				cout << "Invalid folder index." << endl;
			}
		}
		else if (choice == 10) {
			string searchName;
			cout << "Enter file or folder name to search: ";
			cin.ignore();
			getline(cin, searchName);

			system("cls");
			currentFolder->print();

			cout << "\n\nSearch results for \"" << searchName << "\":" << endl;
			currentFolder->searchFileFolder(searchName);
		}
		else if (choice == 11) {
			system("cls");

			currentFolder = &ThisComputer;
			currentFolder->print();
			continue;
		}
		else {
			system("cls");
			currentFolder->print();

			cout << "Invalid choice. Please try again." << endl;

			continue;
		}
	}
}

