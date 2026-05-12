/* ==========================================================================
 * Class: Post
 * Type: Derived Class (Inherits from Object)
 * Purpose: Acts as the main unit of content in the application. It stores
 * the text description, the upload date, a pointer to the author 
 * (User or Page), an array of people who liked it, and an array 
 * of comments attached to it.
 * ========================================================================== */

#include <iostream>
#include <string>
#include "Post.h"
#include "Date.h"
#include "Object.h"
#include "Comment.h"

using namespace std;

// Constructor: Initializes Post, Date, base Object, and allocates dynamic arrays for authors, likes, and comments
Post::Post(string id, string desc, Date d, Object* auth) : Object(id), date(d) {
    description = desc;
    author = new Object*[1];   // Always an array of 1 since a post has only 1 author
    author[0] = auth;
    likeBy = new Object*[10];  // Max 10 likers allowed per project spec
    likesCount = 0;
    comments = new Comment*[10]; // Max 10 comments allowed per project spec
    commentsCount = 0;
}

// Adds a pointer of the User/Page who liked the post to the likeBy array
void Post::addLike(Object* liker) {
    if (likesCount < 10) {
        likeBy[likesCount++] = liker;
    }
}

// Adds a Comment pointer to the post's comment array
void Post::addComment(Comment* c) {
    if (commentsCount < 10) {
        comments[commentsCount++] = c;
    }
}

// Basic Getters for Post attributes
Comment** Post::getComments() const { return comments; }
int Post::getCommentCount() const { return commentsCount; }
Object** Post::getLikedBy() const { return likeBy; }
int Post::getLikeCount() const { return likesCount; }
Date* Post::getDate() { return &date; }
Object* Post::getAuthor() const { return author[0]; }

// Prints the generic post data and cascades the display call down to its comments
void Post::display() const {
    cout << "--- ";
    author[0]->display(); // Polymorphic display of the User or Page name
    cout << " shared \"" << description << "\"" << endl;
    
    // Loops through and triggers display() for every comment attached to this post
    for (int i = 0; i < commentsCount; i++) {
        comments[i]->display();
    }
}

// Destructor: Cleans up the dynamic arrays, AND deletes the actual comment objects
Post::~Post() {
    delete[] author;
    delete[] likeBy;
    
    // Post is the "owner" of the comments, so it deletes the heap memory to prevent leaks
    for (int i = 0; i < commentsCount; i++) {
        delete comments[i];
    }
    delete[] comments;
}