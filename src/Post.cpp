#include <iostream>
#include <string>
#include "Post.h"
#include "Date.h"
#include "Object.h"
#include "Comment.h"

using namespace std;

Post::Post(string id, string desc, Date d, Object* auth) : Object(id), date(d) {
    description = desc;
    author = new Object*[1];
    author[0] = auth;
    likeBy = new Object*[10];
    likesCount = 0;
    comments = new Comment*[10];
    commentsCount = 0;
}

void Post::addLike(Object* liker) {
    if (likesCount < 10) {
        likeBy[likesCount++] = liker;
    }
}

void Post::addComment(Comment* c) {
    if (commentsCount < 10) {
        comments[commentsCount++] = c;
    }
}

Comment** Post::getComments() const {
    return comments;
}

int Post::getCommentCount() const {
    return commentsCount;
}

Object** Post::getLikedBy() const {
    return likeBy;
}

int Post::getLikeCount() const {
    return likesCount;
}

Date* Post::getDate() {
    return &date;
}

Object* Post::getAuthor() const {
    return author[0];
}

void Post::display() const {
}

Post::~Post() {
    delete[] author;
    delete[] likeBy;
    for (int i = 0; i < commentsCount; i++) {
        delete comments[i];
    }
    delete[] comments;
}