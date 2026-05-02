#include <iostream>
#include <fstream>
#include <string>
#include "SocialNetworkApp.h"
using namespace std;

void SocialNetworkApp :: run(){
    
    loadData();
    int choice;

    do {
        cout << "\n============================================" << endl;
        cout << "Social Network Application" << endl;
        cout << "============================================" << endl;
        cout << "1. Set User" << endl;
        cout << "2. View Home Page" << endl;
        cout << "3. Like a post" << endl;
        cout << "4. View the list of people who liked a post" << endl;
        cout << "5. Comment on a Post" << endl;
        cout << "6. View a Post" << endl;
        cout << "7. Share a Memory" << endl;
        cout << "8. View User’s Profile" << endl;
        cout << "9. View Friend List" << endl;
        cout << "10. View Page" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter choice: ";

		while (true)
		{
			if (cin >> choice) {
				if (cin.peek() == '\n') break;
			}

			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Enter ONE integer: ";
		}

        
    } while (choice != 11);

    
}

void SocialNetworkApp :: loadData() {

    ifStream inFile("Users.txt");
    int userCount;
    string line;

    if (!inFile.is_open()) 
    {
        cout << "Error: Could not open the file!" << endl;
        return;
    }
     inFile >> userCount;

    while (getline(inFile, line))
    {
        
        
        for (int i = 0; i < line.length(); i++)
        {

            if (line[i] == '\r') 
            { 
                line.erase(i);
            }
            char ch = line[i];
            if (ch == ',') 
            {
                if (c < 7)
                    arr[r][c] = word;
                c++;
                word = "";
            }
            else
            {
                word += ch;
            }
        }
        if (c < 7)
            arr[r][c] = word;
        r++;
    }

    inFile.close();

}