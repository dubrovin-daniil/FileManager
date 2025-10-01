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
		ThisComputer.thisComputer(); // Select a drive
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

	while (true) { // Main loop
		string choice;
		cout << "\n\nTerminal> \n";
		cout << "Select an action:\nexit - Closing the program.\ncdrive - Change Drive.\ncd <directory_name>/(.. - to return to the parent directory) - Change Directory.\nopen <name.*> - Open file.\nmkdir <name> - Make directory.\ntouch <name.*> - Make file.\ndel <name>/<name.*> - Delete directory/file.\nren <old_name>  - Rename file/directory.\ncopy <name>/<name.*> - Copy file/directory.\nmove <name>/<name.*> - Transfer file/directory.\nsize <name>/<name.*> - Output size in bytes.\nsearch <name>/<*.*> - Search file/directory." << endl;
		cout << ">>> ";
		cin >> choice;

		if (choice == "exit") { // Exit the program
			break;
		}
		else if (choice == "cdrive") { // Change drive
			system("cls");
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

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "cd") { // Change directory
			string subChoice;
			cin.ignore();
			getline(cin, subChoice);

			try {
				if (subChoice == "..") {
					ThisComputer.setPath(fs::path(ThisComputer.getPath()).parent_path().string()); // Go to parent directory
				}
				else {
					ThisComputer.changeDirectory(ThisComputer.getPath() + "\\" + subChoice); // Change directory
				}

				cout << endl;
				system("cls"); // Clear the console
				ThisComputer.print();
			}
			catch (const runtime_error& e) {
				cout << "The system cannot find the specified path: " << fs::absolute(ThisComputer.getPath()).string() << endl;
				cout << "Press Enter to continue..." << endl;
				cin.get();

				ThisComputer.setPath(fs::path(ThisComputer.getPath()).parent_path().string());
				ThisComputer.setPath(fs::path(ThisComputer.getPath()).parent_path().string());
				system("cls");
				ThisComputer.print();
			}
		}
		else if (choice == "open") { // Open file
			ThisComputer.openFile();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "mkdir") { // Make directory
			ThisComputer.addSubFolder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "touch") { // Make file
			ThisComputer.addFile();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "del") { // Delete file/folder
			ThisComputer.removeFile_Folder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "ren") { // Rename file/folder
			ThisComputer.renameFile_Folder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "copy") { // Copy file/folder
			ThisComputer.copyFile_Folder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "move") { // Move file/folder
			ThisComputer.moveFileFolder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "size") { // Get size of file/folder
			ThisComputer.sizeOfFileFolder();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else if (choice == "search") { //Search by mask
			ThisComputer.maskSearch();

			cout << "Press Enter to continue..." << endl;
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
		else {
			cerr << "Unknown command!";

			cout << "Press Enter to continue..." << endl;
			cin.ignore();
			cin.get();

			system("cls"); // Clear the console
			ThisComputer.print();
		}
	}
}
