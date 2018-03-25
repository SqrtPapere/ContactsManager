# ContactsManager

## Overview
We are flooded with torrents of digital communication in our daily lives. Email, telephone calls, instant messaging, Skype calls, Tweets, and a myriad of other communication sources contribute to a sense of overload. Not only must we manage this communication, we must also keep track of the various contacts with whom we communicate. A Contacts Manager does just that for us: it maintains a list of known contacts with all of their important contact information (names, numbers, addresses, notes, etc).
In this programming assignment I implemented a simple contact manager using QT framework as a complete and polished Graphical User Interface. 
## Supported Operations

This GUI application supports the basic operations needed for a contact manager.

+ Visualization of all contacts: the application starts up showing all contacts by first and last names, email, phone number, free-text notes. The user is allowed to order the list of contacts by field.
+ Single-contact visualization: the user is allowed to click on a row of the mangaer to view a single contact. This visualization gives the option to delete the contact and modify it.
+ Insertion of new contact: the user can create a new contact by clicking on ```Add new``` button.
+ Contact persistence: the GUI saves the contact list persistently on a Postgres database using APIs provided in this [directory](https://github.com/SqrtPapere/ContactsManager/tree/master/postgresphpscripts) on an Apache web-server.
+ Contact tagging and tag search: the user is allowed to associate tags to contacts and can filter contact visualization by tag.
+ Contact editing: when the user views a contact, he can edit it as well.
+ Full-text search: the user can enter search terms to filter contact visualization to contacts with those terms in one or more fields.

## Implementation
The GUI was implemented using [QT](https://www1.qt.io/developers/) in C++. Trying to follow MVC pattern.

![](https://github.com/SqrtPapere/ContactsManager/blob/master/Images/mvc.png)

### Model

The model has been implemented in the `TableModel` Class and contains all the data of the contacts manager.

It provides methods to get, set, modify, sort and delete contacts using `Downloader` and `SortFilterProxyModel` classes.

### Controller/Delegate

Implemented in `MainWindow`, it handles the `ui` containing some widgets and cooperate with the model being able to receive user's input.

### View

Qt provides view widgets such as QListView, QTreeView, and QTableView. Each of them has its own special way of representing data items. For the purpose I opted for QTableView.

### Screen shots of the GUI

![](https://github.com/SqrtPapere/ContactsManager/blob/master/Images/list.png)
![](https://github.com/SqrtPapere/ContactsManager/blob/master/Images/mod.png)
![](https://github.com/SqrtPapere/ContactsManager/blob/master/Images/del.png)

## Build

Requires Qt 5.9.2 (or later, not tested in previous versions)

***IMPORTANT*** In ```tablemodel.h``` you have to change variable IP with your own server IP! 

```
#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#define IP "<insert IP>"
```
Then you also need to change:

```
$dbname      = "dbname = <insert here your db name>";
$credentials = "user = <insert here your user name> password=<insert here your psw>";
```
in all the [postgresphphscripts](https://github.com/SqrtPapere/ContactsManager/tree/master/postgresphpscripts)
### OSX

```If``` there is not any path to your installed qt in echo $PATH, set it like this:

  &nbsp; &nbsp; &nbsp; &nbsp; ```sudo nano .bash_profile```
  
  &nbsp; &nbsp; &nbsp; &nbsp; and add:

  &nbsp; &nbsp; &nbsp; &nbsp; ```PATH=“/usr/local/path-to-your-qt/bin:$PATH”```
  
  &nbsp; &nbsp; &nbsp; &nbsp;  ```export PATH```

```Else``` clone the repository and in the source code directory:

  &nbsp; &nbsp; &nbsp; &nbsp; ```qmake -makefile```

  &nbsp; &nbsp; &nbsp; &nbsp; ```make```

  &nbsp; &nbsp; &nbsp; &nbsp; ```open ContactsManager.app```


QDarkStylesheet was used for a better looking GUI (highly recommended) and can be found in [this GitHub Repo](https://github.com/ColinDuquesnoy/QDarkStyleSheet)

## Future developements
Try implement **Dynamic persistence** to allow users to asynchronously edit the contacts database indeed active GUIs should dynamically update whenever changes are made.
