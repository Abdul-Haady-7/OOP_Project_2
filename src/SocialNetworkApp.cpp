#include <iostream>
#include <fstream>
#include <string>
#include "SocialNetworkApp.h"

using namespace std;

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

void SocialNetworkApp::loadData() {
    ifstream file;
    
    cout << "\n--- THE TRUTH TEST ---" << endl;
    file.open("Pages.txt");
    string firstWord;
    file >> firstWord;
    cout << "The exact first thing C++ sees is: ->" << firstWord << "<-" << endl;
    file.close();
    file.clear();
    
    file.open("Pages.txt");
    if (file.is_open()) {
        file >> pageCount;
        pages = new Page*[pageCount];
        for (int i = 0; i < pageCount; i++) {
            string id, name;
            file >> id;
            getline(file >> ws, name); 
            pages[i] = new Page(id, name);
        }
        file.close();
        file.clear(); 
    } else cout << "Error: Pages.txt not found." << endl;

    
    file.open("Users.txt");
    if (file.is_open()) {
        file >> userCount;
        users = new User*[userCount];
        for (int i = 0; i < userCount; i++) {
            string id, fName, lName, temp;
            file >> id >> fName >> lName;
            string fullName = fName + " " + lName;
            users[i] = new User(id, fullName);
            
            while (file >> temp && temp != "-1") {}
            while (file >> temp && temp != "-1") {}
        }
        file.close();
        file.clear(); 
    } else cout << "Error: Users.txt not found." << endl;

    
    file.open("Users.txt");
    if (file.is_open()) {
        int dummyCount;
        file >> dummyCount; 
        for (int i = 0; i < userCount; i++) {
            string id, dummy, friendId, pageId;
            file >> id >> dummy >> dummy; 
            
            User* currentUserObj = findUser(id);
            
            while (file >> friendId && friendId != "-1") {
                currentUserObj->addFriends(findUser(friendId));
            }
            while (file >> pageId && pageId != "-1") {
                currentUserObj->addLikedPages(findPage(pageId));
            }
        }
        file.close();
        file.clear(); 
    }

    
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
            if (type == 2) {
                file >> activityType;
                getline(file >> ws, activityValue);
            }
            
            file >> authorId;
            Object* authorObj = findUser(authorId);
            if (authorObj == nullptr) authorObj = findPage(authorId);
            
            if (type == 1) {
                posts[i] = new Post(id, desc, postDate, authorObj);
            } else if (type == 2) {
                posts[i] = new Activity(id, desc, postDate, authorObj, activityType, activityValue);
            }
            
            User* u = findUser(authorId);
            if (u != nullptr) u->addPosts(posts[i]);
            else {
                Page* p = findPage(authorId);
                if (p != nullptr) p->addPost(posts[i]);
            }
            
            while (file >> likerId && likerId != "-1") {
                Object* likerObj = findUser(likerId);
                if (likerObj == nullptr) likerObj = findPage(likerId);
                posts[i]->addLike(likerObj);
            }
        }
        file.close();
        file.clear(); 
    } else cout << "Error: Posts.txt not found." << endl;

    
    file.open("Comments.txt");
    if (file.is_open()) {
        file >> commentCount;
        comments = new Comment*[commentCount];
        for (int i = 0; i < commentCount; i++) {
            string id, postId, authorId, text;
            
            file >> id >> postId >> authorId;
            getline(file >> ws, text);
            
            Object* authorObj = findUser(authorId);
            if (authorObj == nullptr) authorObj = findPage(authorId);
            
            comments[i] = new Comment(id, authorObj, text);
            
            Post* p = findPost(postId);
            if (p != nullptr) {
                p->addComment(comments[i]);
            }
        }
        file.close();
        file.clear(); 
    } else cout << "Error: Comments.txt not found." << endl;
    
    cout << "System Data Successfully Loaded." << endl;
    cout << "--- DIAGNOSTICS ---" << endl;
    cout << "Users loaded: " << userCount << endl;
    cout << "Pages loaded: " << pageCount << endl;
    cout << "Posts loaded: " << postCount << endl;
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

void SocialNetworkApp::viewHome() {
    if (currentUser == nullptr) {
        cout << "Error: Please set a current user first (Option 1) before performing this action." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << currentUser->getName() << " - Home Page" << endl;
    cout << "--------------------------------------------------\n" << endl;

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
                for (int j = 0; j < fPostCount; j++) 
                {
                    Date* postDate = friendPosts[j]->getDate();
                    if (postDate != nullptr && postDate->isIn24(theDate)) {
                        friendPosts[j]->display();
                        cout << endl << endl;
                    }
                }
            }
        }
    }

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
                likedBy[i]->display(); 
                cout << endl;
            }
        } else {
            cout << "No one has liked this post yet." << endl;
        }
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

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
        cin.ignore(); 
        getline(cin, text); 

        string newCommentId = "c" + to_string(commentCount + 1);
        Comment* newComment = new Comment(newCommentId, currentUser, text);
        post->addComment(newComment);
        
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
    bool foundMemory = false;

    if (userPosts != nullptr && count > 0) {
        for (int i = 0; i < count; i++) {
            Date* postDate = userPosts[i]->getDate();
            if (postDate != nullptr) {
                int yearsAgo = postDate->yearDiff(theDate); 
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
        Memory* newMemory = new Memory(newPostId, text, theDate, currentUser, originalPost);
        
        if (posts == nullptr) {
            posts = new Post*[500]; 
        }
        if (postCount < 500) {
            posts[postCount++] = newMemory;
        }

        currentUser->addPosts(newMemory);

        cout << "Memory successfully shared on your timeline!" << endl;
    } else {
        cout << "Error: Post '" << postId << "' not found." << endl;
    }
}

void SocialNetworkApp::run() {
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
        cout << "7. See Memories" << endl;
        cout << "8. View User's Profile" << endl;
        cout << "9. View Friend List" << endl;
        cout << "10. View Page" << endl;
        cout << "11. Share a Memory" << endl;
        cout << "12. Exit Program" << endl;
        cout << "Enter choice: ";

        while (true) {
            if (cin >> choice) {
                if (cin.peek() == '\n') break;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter ONE integer between 1-12: ";
        }
        
        if (choice < 1 || choice > 12) {
            cout << "Invalid Choice. Choice must be between 1 and 12." << endl;
        } else {
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

SocialNetworkApp::~SocialNetworkApp() {
    cout << "Cleaning up memory..." << endl;

    if (users != nullptr) {
        for (int i = 0; i < userCount; i++) {
            if (users[i] != nullptr) delete users[i]; 
        }
        delete[] users; 
    }

    if (pages != nullptr) {
        for (int i = 0; i < pageCount; i++) {
            if (pages[i] != nullptr) delete pages[i];
        }
        delete[] pages;
    }

    if (posts != nullptr) {
        for (int i = 0; i < postCount; i++) {
            if (posts[i] != nullptr) delete posts[i];
        }
        delete[] posts;
    }

    if (comments != nullptr) {
        delete[] comments;
    }

    cout << "Memory successfully deallocated. System shutdown complete." << endl;
}