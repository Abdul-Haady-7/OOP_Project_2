#include <iostream>
#include <fstream>
#include <string>
#include "SocialNetworkApp.h"
using namespace std;

// --- Private Helper Methods ---
// For linking IDs to Objects

User* SocialNetworkApp::findUser(string id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getID() == id) return users[i];
    }
    return nullptr;
}

Page* SocialNetworkApp::findPage(string id) {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i]->getID() == id) return pages[i];
    }
    return nullptr;
}

Post* SocialNetworkApp::findPost(string id) {
    for (int i = 0; i < postCount; i++) {
        if (posts[i]->getID() == id) return posts[i];
    }
    return nullptr;
}

// --- Load Data Method ---
void SocialNetworkApp::loadData() {
   
}


void SocialNetworkApp::setUser() {
    string id;
    cout << "Enter User ID: ";
    cin >> id;
    
    User* user = findUser(id);
    if (user != nullptr) {
        currentUser = user;
        cout << user->getName() << " successfully set as Current User" << endl;
    } else {
        cout << "Error: User '" << id << "' not found." << endl;
    }
}

void SocialNetworkApp::viewFriendList() {
    if (currentUser == nullptr) {
        cout << "Please set a current user first (Option 1)." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << currentUser->getName() << " - Friend List\n" << endl;

    User** friends = currentUser->getFriends();
    int count = currentUser->getFriendsCount();

    if (friends != nullptr && count > 0) {
        for (int i = 0; i < count; i++) {
            cout << friends[i]->getID() << " - " << friends[i]->getName() << endl;
        }
    } else {
        cout << "This user has no friends." << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

// ------ Run Method ----------
void SocialNetworkApp :: run(){
    
    loadData();
    currentUser = nullptr;

    int choice;

    do {
        cout << "\n============================================" << endl;
        cout << "Social Network Application" << endl;
        cout << "============================================" << endl;

        if (currentUser != nullptr) {
            cout << "Current User: " << currentUser->getName() << endl;
            cout << "============================================" << endl;
        }
        
        cout << "1. Set User" << endl;
        cout << "2. View Home Page" << endl;
        cout << "3. Like a post" << endl;
        cout << "4. View the list of people who liked a post" << endl;
        cout << "5. Comment on a Post" << endl;
        cout << "6. View a Post" << endl;
        cout << "7. Share a Memory" << endl;
        cout << "8. View User's Profile" << endl;
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

        switch (choice) {
            case 1:
                setUser();
                break;
            case 2:
                // viewHome(); 
                
                break;
            case 3:
                // likePost();
                
                break;
            case 4:
                // viewLikedList();
               
                break;
            case 5:
                // commentOnPost();
                
                break;
            case 6:
                // viewPost();
                
                break;
            case 7:
                // shareMemory();
                
                break;
            case 8:
                // viewProfile();
                
                break;
            case 9:
                viewFriendList();
                break;
            case 10:
                // viewPage(); 
                
                break;
            case 11:
                cout << "Exiting application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a number between 1 and 11." << endl;
        }

    } while (choice != 11);    
}





// --- Destructor ---
SocialNetworkApp::~SocialNetworkApp() {
    // Memory Deallocation (we will write this at the end)
}