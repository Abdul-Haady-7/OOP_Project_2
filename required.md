#Required#

Follows the format of 

[Class]
    - Scope
        - [Members] 
    - Scope
        - [Methods]


#Data Layer#


- Object (Abstract Base Class)
    - PROTECTED
        - id, string
    - PUBLIC
        - constructor
        - getID, string, const
        - display, void, const, virtual (pure virtual)
        - destructor (virtual)


- Date
    - PRIVATE
        - day, int
        - month, int
        - year, int
    - PUBLIC
        - constructor
        - isIn24, bool, const
        - yearDiff, int, const
        - display, void, const

- Comment
    - PRIVATE
        - id, string
        - text, string
        - author, Object*
    - PUBLIC
        - constructor
        - display, void, const


- Post (child of Object)
    - PROTECTED
        - description, string
        - date, Date
        - author, Object*
        - likeBY, Object**
        - likescount, int
        - comments, Comment**
        - commentscount, int
    - PUBLIC
        - constructor
        - plusDaLike, void
        - plusDaComment, void
        - getComment, Comment^*, const
        - getCommentCount, int, const
        - getLikeBy, Object**, const
        - getLikeCount, int, const
        - getDate, Date*
        - getAuthor, Object*, const
        - display, void, const, virtual
        - destructor (virtual)


- Activity (child of Post)
    - PRIVATE
        - type, int
        - value, string
    - PUBLIC
        - constructor
        - display, void, const


- Memory (child of Post)
    - PRIVATE
        - ogPost, Post*
    - PUBLIC
        - constructor
        - getOgPost, Post*, const
        - display, void, const


- Page (child of object)
    - PRIVATE
        - name, string
        - postss, post**
        - postCount, int
    - PUBLIC
        - constructor
        - addPost, void
        - getPosts, Post**
        - getPostCount, int
        - getName, string
        - display, void, const
        - destructor


- User (child of Obejct)
    - PRIVATE
        - name, string
        - friends user**
        - friendscount, int
        - likedPages, Page**
        - likedPagesCount, int
    - PUBLIC
        - constructor
        - addFriend, void
        - addLikedPage, void
        - getFriends, User**, const
        - getFriendsCount, int, const
        - getLikedPages, Page**, const
        - getLikedPagesCount, int, const
        - getName, string, const
        - display, void, const
        - destructor 

#Interface Layer#


- SocialNetworkApp
    - PRIVATE
        - users, User**
        - userCount, int
        - pages, Page**
        - pagevount, int
        - posts, Post**
        - postCount, int
        - comments, comment**
        - commentCount, int
        - currentUser, User*
        - thaDate, Date
    - PRIVATE METHODS
        - findUser, User*
        - findPage, Page*
        - findPost, Post*
    - PUBLIC
        - loadData, void
        - run, void
        - setUser, void
        - viewHome, void
        - likePost, void
        - viewLikesList, void
        - commentonPost, void
        - viewPost, void
        - seeMemories, void
        - shareMemoru, void
        - viewProfile, void
        - viewFrndList, void
        - viewPage, void
        - destructor


#MAIN#

- socialNetworkApp app;
- app.Run;