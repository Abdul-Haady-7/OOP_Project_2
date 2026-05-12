/* ==========================================================================
 * Class: SocialNetworkApp
 * Type: Core Controller / Manager Class
 * Purpose: This is the brain of the entire application. It is responsible for 
 * reading the text files to dynamically allocate all users, pages, 
 * posts, and comments. It wires all the pointers together to form 
 * the network graph. It also runs the main console loop, processes 
 * user inputs, and manages the master cleanup upon exit.
 * ========================================================================== */

#include <iostream>
#include <fstream>
#include <string>
#include "SocialNetworkApp.h"

using namespace std;

// Constructor: Sets the system date and initializes all master arrays to null
SocialNetworkApp::SocialNetworkApp() : theDate(15, 11, 2017) 
{
    users = nullptr;
    userCount = 0;
    pages = nullptr;
    pageCount = 0;
    posts = nullptr;
    postCount = 0;
    comments = nullptr;
    commentCount = 0;
    currentUser = nullptr;
}

// Helper: Searches the master users array and returns a pointer if ID matches
User* SocialNetworkApp::findUser(string id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getID() == id) return users[i];
    }
    return nullptr; // Returns null if user doesn't exist
}

// Helper: Searches the master pages array and returns a pointer if ID matches
Page* SocialNetworkApp::findPage(string id) {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i]->getID() == id) return pages[i];
    }
    return nullptr;
}

// Helper: Searches the master posts array and returns a pointer if ID matches
Post* SocialNetworkApp::findPost(string id) {
    for (int i = 0; i < postCount; i++) {
        if (posts[i]->getID() == id) return posts[i];
    }
    return nullptr;
}

// Master parsing function: Reads all txt files and builds the object graph
void SocialNetworkApp::loadData() {
    ifstream file; // File stream object used to read the text files
    
    // --- 1. LOAD PAGES ---
    file.open("Pages.txt");
    if (file.is_open()) {
        file >> pageCount;
        pages = new Page*[pageCount]; // Allocates the master Pages array
        for (int i = 0; i < pageCount; i++) {
            string id, name;
            file >> id;
            getline(file >> ws, name); // Reads the rest of the line (clearing hidden whitespace)
            pages[i] = new Page(id, name);
        }
        file.close();
        file.clear(); // Resets the stream state to prevent EOF bugs on the next file
    } else cout << "Error: Pages.txt not found." << endl;

    // --- 2. LOAD USERS (Creation Pass) ---
    file.open("Users.txt");
    if (file.is_open()) {
        file >> userCount;
        users = new User*[userCount];
        for (int i = 0; i < userCount; i++) {
            string id, fName, lName, temp;
            file >> id >> fName >> lName;
            string fullName = fName + " " + lName; // Combines first and last name
            users[i] = new User(id, fullName);
            
            // Fast-forwards through the friend/page IDs (we will read them in Pass 2)
            while (file >> temp && temp != "-1") {}
            while (file >> temp && temp != "-1") {}
        }
        file.close();
        file.clear();
    } else cout << "Error: Users.txt not found." << endl;

    // --- 3. WIRE USER POINTERS (Linking Pass) ---
    // Re-reads Users.txt now that all User and Page objects actually exist in memory
    file.open("Users.txt");
    if (file.is_open()) {
        int dummyCount;
        file >> dummyCount; 
        for (int i = 0; i < userCount; i++) {
            string id, dummy, friendId, pageId;
            file >> id >> dummy >> dummy; // Skips the names since they are already loaded
            
            User* currentUserObj = findUser(id);
            
            // Reads friend IDs until "-1" is hit, and links the pointers
            while (file >> friendId && friendId != "-1") {
                currentUserObj->addFriends(findUser(friendId));
            }
            // Reads page IDs until "-1" is hit, and links the pointers
            while (file >> pageId && pageId != "-1") {
                currentUserObj->addLikedPages(findPage(pageId));
            }
        }
        file.close();
        file.clear();
    }

    // --- 4. LOAD POSTS ---
    file.open("Posts.txt");
    if (file.is_open()) {
        file >> postCount;
        posts = new Post*[postCount];
        for (int i = 0; i < postCount; i++) {
            int type, d, m, y;
            string id, desc, authorId, likerId;
            
            file >> type >> id;
            file >> d >> m >> y;
            Date postDate(d, m, y);
            
            getline(file >> ws, desc);
            
            int activityType = 0;
            string activityValue = "";
            // If type is 2, it's an Activity, meaning we have to read the extra data line
            if (type == 2) {
                file >> activityType;
                getline(file >> ws, activityValue);
            }
            
            file >> authorId;
            
            // Polymorphic resolution: Checks if author is a User. If not, assumes it's a Page.
            Object* authorObj = findUser(authorId);
            if (authorObj == nullptr) authorObj = findPage(authorId);
            
            // Instantiates the correct derived class based on the type flag
            if (type == 1) {
                posts[i] = new Post(id, desc, postDate, authorObj);
            } else if (type == 2) {
                posts[i] = new Activity(id, desc, postDate, authorObj, activityType, activityValue);
            }
            
            // Adds the created post to the specific timeline of the author (User or Page)
            User* u = findUser(authorId);
            if (u != nullptr) u->addPosts(posts[i]);
            else {
                Page* p = findPage(authorId);
                if (p != nullptr) p->addPost(posts[i]);
            }
            
            // Reads liker IDs until "-1", finds them, and adds them to the post's like array
            while (file >> likerId && likerId != "-1") {
                Object* likerObj = findUser(likerId);
                if (likerObj == nullptr) likerObj = findPage(likerId);
                posts[i]->addLike(likerObj);
            }
        }
        file.close();
        file.clear();
    } else cout << "Error: Posts.txt not found." << endl;

    // --- 5. LOAD COMMENTS ---
    file.open("Comments.txt");
    if (file.is_open()) {
        file >> commentCount;
        comments = new Comment*[commentCount];
        for (int i = 0; i < commentCount; i++) {
            string id, postId, authorId, text;
            
            file >> id >> postId >> authorId;
            getline(file >> ws, text);
            
            // Resolves author as User or Page
            Object* authorObj = findUser(authorId);
            if (authorObj == nullptr) authorObj = findPage(authorId);
            
            comments[i] = new Comment(id, authorObj, text);
            
            // Finds the associated post and links the comment inside it
            Post* p = findPost(postId);
            if (p != nullptr) {
                p->addComment(comments[i]);
            }
        }
        file.close();
        file.clear();
    } else cout << "Error: Comments.txt not found." << endl;
    
    cout << "System Data Successfully Loaded." << endl;
}

// Changes the 'currentUser' pointer to simulate a user logging in
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

// Displays a list of all friends for the currently logged-in user
void SocialNetworkApp::viewFriendList() {
    if (currentUser == nullptr) {
        cout << "Please set a current user first (Option 1)." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << currentUser->getName() << " - Friend List\n" << endl;

    User** friends = currentUser->getFriends();
    int count = currentUser->getFriendsCount();

    // Loops through the friends array and prints IDs and Names
    if (friends != nullptr && count > 0) {
        for (int i = 0; i < count; i++) {
            cout << friends[i]->getID() << " - " << friends[i]->getName() << endl;
        }
    } else {
        cout << "This user has no friends." << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

// Displays all posts created by the currently logged-in user
void SocialNetworkApp::viewProfile() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1) before performing this action." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << currentUser->getName() << " - Time Line" << endl;
    cout << "--------------------------------------------------\n" << endl;

    Post** userPosts = currentUser->getPosts();
    int count = currentUser->getPostCount();

    // Loops through and triggers display() for every post on the user's timeline
    if (userPosts != nullptr && count > 0) {
        for (int i = 0; i < count; i++) {
            userPosts[i]->display(); 
            cout << endl << endl; 
        }
    } 
    else {
        cout << "No posts on the timeline." << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

// Generates a news feed consisting of recent posts from friends and liked pages
void SocialNetworkApp::viewHome() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1) before performing this action." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << currentUser->getName() << " - Home Page" << endl;
    cout << "--------------------------------------------------\n" << endl;

    // --- 1. Get Friend Posts ---
    User** friends = currentUser->getFriends();
    int friendCount = currentUser->getFriendsCount();

    if (friends != nullptr) 
    {
        for (int i = 0; i < friendCount; i++) 
        {
            Post** friendPosts = friends[i]->getPosts();
            int fPostCount = friends[i]->getPostCount();
            
            if (friendPosts != nullptr) 
            {
                // Nested loop checks every post of every friend
                for (int j = 0; j < fPostCount; j++) 
                {
                    Date* postDate = friendPosts[j]->getDate();
                    // Filters out posts that are older than 24 hours
                    if (postDate != nullptr && postDate->isIn24(theDate)) {
                        friendPosts[j]->display();
                        cout << endl << endl;
                    }
                }
            }
        }
    }

    // --- 2. Get Page Posts ---
    Page** pages = currentUser->getLikedPages();
    int pageCount = currentUser->getLikedPagesCount();

    if (pages != nullptr) 
    {
        for (int i = 0; i < pageCount; i++) 
        {
            Post** pagePosts = pages[i]->getPosts();
            int pPostCount = pages[i]->getPostCount();
            
            if (pagePosts != nullptr) 
            {
                for (int j = 0; j < pPostCount; j++)
                 {
                    Date* postDate = pagePosts[j]->getDate();
                    // Filters out posts that are older than 24 hours
                    if (postDate != nullptr && postDate->isIn24(theDate)) 
                    {
                        pagePosts[j]->display();
                        cout << endl << endl;
                    }
                }
            }
        }
    }
    cout << "--------------------------------------------------" << endl;
}

// Prompts for a post ID and prints everyone who liked it
void SocialNetworkApp::viewLikedList() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string postId;
    cout << "Enter Post ID: ";
    cin >> postId;

    Post* post = findPost(postId);
    if (post != nullptr) {
        cout << "\nPost Liked By:" << endl;
        Object** likedBy = post->getLikedBy();
        int likeCount = post->getLikeCount();

        if (likedBy != nullptr && likeCount > 0) {
            for (int i = 0; i < likeCount; i++) {
                cout << likedBy[i]->getID() << " - ";
                likedBy[i]->display(); // Polymorphic display prints name
                cout << endl;
            }
        } else {
            cout << "No one has liked this post yet." << endl;
        }
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

// Prompts for a post ID and displays that specific post and its comments
void SocialNetworkApp::viewPost() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string postId;
    cout << "Enter Post ID: ";
    cin >> postId;

    Post* post = findPost(postId);
    if (post != nullptr) {
        cout << "\n--------------------------------------------------" << endl;
        post->display(); 
        cout << "\n--------------------------------------------------" << endl;
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

// Prompts for a page ID and prints all posts uploaded by that page
void SocialNetworkApp::viewPage() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string pageId;
    cout << "Enter Page ID: ";
    cin >> pageId;

    Page* page = findPage(pageId);
    if (page != nullptr) {
        cout << "--------------------------------------------------" << endl;
        page->display();
        cout << "\n--------------------------------------------------\n" << endl;

        Post** pagePosts = page->getPosts();
        int count = page->getPostCount();

        if (pagePosts != nullptr && count > 0) {
            for (int i = 0; i < count; i++) {
                pagePosts[i]->display();
                cout << endl << endl;
            }
        } else {
            cout << "No posts on this page." << endl;
        }
        cout << "--------------------------------------------------" << endl;
    } else {
        cout << "Error: Page '" << pageId << "' not found." << endl;
    }
}

// Adds the current logged-in user to the "likedBy" array of a specific post
void SocialNetworkApp::likePost() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string postId;
    cout << "Enter Post ID to like: ";
    cin >> postId;

    Post* post = findPost(postId);
    if (post != nullptr) {
        post->addLike(currentUser);
        cout << "You have successfully liked post '" << postId << "'." << endl;
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

// Allows the current user to write text and append a new comment to a post
void SocialNetworkApp::commentOnPost() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string postId;
    cout << "Enter Post ID to comment on: ";
    cin >> postId;

    Post* post = findPost(postId);
    if (post != nullptr) {
        string text;
        cout << "Enter your comment: ";
        cin.ignore(); // Clears the newline character left by cin so getline works
        getline(cin, text); 

        // Generates a new ID (e.g., "c14")
        string newCommentId = "c" + to_string(commentCount + 1);
        
        // Dynamically allocates the new comment and passes it to the post
        Comment* newComment = new Comment(newCommentId, currentUser, text);
        post->addComment(newComment);
        
        // Adds the comment to the App's master tracking array
        if (comments == nullptr) {
            comments = new Comment*[500]; 
        }
        if (commentCount < 500) {
            comments[commentCount++] = newComment;
        }

        cout << "Comment successfully added to post '" << postId << "'." << endl;
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

// Scans the user's timeline to find and display posts made on the exact same day in previous years
void SocialNetworkApp::seeMemory() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n" << endl;
    cout << "On this Day" << endl;
    cout << "--------------------------------------------------" << endl;

    Post** userPosts = currentUser->getPosts();
    int count = currentUser->getPostCount();
    bool foundMemory = false; // Flag to track if any memories were actually found

    if (userPosts != nullptr && count > 0) {
        for (int i = 0; i < count; i++) {
            Date* postDate = userPosts[i]->getDate();
            if (postDate != nullptr) {
                int yearsAgo = postDate->yearDiff(theDate); 
                // Only prints the memory if the difference is greater than 0 (not today)
                if (yearsAgo > 0) {
                    cout << yearsAgo << " Years Ago" << endl;
                    userPosts[i]->display();
                    cout << endl << endl;
                    foundMemory = true;
                }
            }
        }
    }

    if (!foundMemory) {
        cout << "You have no memories to look back on today!" << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

// Creates a new 'Memory' object wrapping an old post, and adds it to the user's timeline
void SocialNetworkApp::shareMemory() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1)." << endl;
        return;
    }

    string postId;
    cout << "Enter Post ID to share as a memory: ";
    cin >> postId;

    Post* originalPost = findPost(postId);
    if (originalPost != nullptr) {
        string text;
        cout << "Enter your thoughts for this memory: ";
        cin.ignore(); 
        getline(cin, text);

        string newPostId = "post" + to_string(postCount + 1);
        
        // Dynamically allocates the Memory (which acts as a Post via Polymorphism)
        Memory* newMemory = new Memory(newPostId, text, theDate, currentUser, originalPost);
        
        // Adds the memory to the Master Posts array
        if (posts == nullptr) {
            posts = new Post*[500]; 
        }
        if (postCount < 500) {
            posts[postCount++] = newMemory;
        }

        // Adds the memory to the User's specific timeline
        currentUser->addPosts(newMemory);

        cout << "Memory successfully shared on your timeline!" << endl;
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

// The core application loop that presents the menu and handles user input
void SocialNetworkApp::run() {
    loadData(); // Automatically loads files on startup
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
        cout << "7. See Memories" << endl;
        cout << "8. View User's Profile" << endl;
        cout << "9. View Friend List" << endl;
        cout << "10. View Page" << endl;
        cout << "11. Share a Memory" << endl;
        cout << "12. Exit Program" << endl;
        cout << "Enter choice: ";

        // Input validation loop to prevent infinite loops if the user types a string instead of an int
        while (true) {
            if (cin >> choice) {
                if (cin.peek() == '\n') break; // Ensures no trailing garbage characters
            }

            cin.clear(); // Clears the error flag
            cin.ignore(10000, '\n'); // Empties the buffer
            cout << "Invalid input. Enter ONE integer between 1-12: ";
        }
        
        if (choice < 1 || choice > 12) {
            cout << "Invalid Choice. Choice must be between 1 and 12." << endl;
        } else {
            // Triggers the appropriate method based on input
            switch (choice) {
                case 1: setUser(); break;
                case 2: viewHome(); break;
                case 3: likePost(); break;
                case 4: viewLikedList(); break;
                case 5: commentOnPost(); break;
                case 6: viewPost(); break;
                case 7: seeMemory(); break;
                case 8: viewProfile(); break;
                case 9: viewFriendList(); break;
                case 10: viewPage(); break;
                case 11: shareMemory(); break;
                case 12: cout << "Exiting application." << endl; break;
                default: cout << "Invalid choice. Please select a number between 1 and 12." << endl;
            }
        }
    } while (choice != 12);    
}

// Application Destructor: Deallocates all dynamic heap memory to prevent memory leaks upon exit
SocialNetworkApp::~SocialNetworkApp() {
    cout << "Cleaning up memory..." << endl;

    // 1. Loop and delete every allocated User object
    if (users != nullptr) {
        for (int i = 0; i < userCount; i++) {
            if (users[i] != nullptr) delete users[i]; 
        }
        delete[] users; // Delete the array pointer itself
    }

    // 2. Loop and delete every allocated Page object
    if (pages != nullptr) {
        for (int i = 0; i < pageCount; i++) {
            if (pages[i] != nullptr) delete pages[i];
        }
        delete[] pages;
    }

    // 3. Loop and delete every allocated Post object
    if (posts != nullptr) {
        for (int i = 0; i < postCount; i++) {
            if (posts[i] != nullptr) delete posts[i];
        }
        delete[] posts;
    }

    // 4. Delete the comments tracker array ONLY (Comments themselves are deleted by Post::~Post to avoid Double Free crash)
    if (comments != nullptr) {
        delete[] comments;
    }

    cout << "Memory successfully deallocated. System shutdown complete." << endl;
}