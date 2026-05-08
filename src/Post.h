#pragma once
#include <iostream>
#include <string>
#include "Object.h"
#include "Date.h"
#include "Comment.h"

using namespace std;

class Post : public Object{

protected:
    string description;
    Date date;
    Object** author;
    Object** likeBy;
    int likesCount;
    Comment** comments;
    int commentsCount; 

public:
    Post(string id, string desc, Date d, Object* auth);
    void addLike(Object* liker); 
    void addComment(Comment* c); 
    Comment** getComments() const;
    int getCommentCount() const; 
    Object** getLikedBy() const; 
    int getLikeCount() const;
    Date* getDate(); 
    Object* getAuthor() const;
    virtual void display() const override;
    virtual ~Post();

};