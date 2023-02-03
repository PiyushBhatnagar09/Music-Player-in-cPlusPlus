// Linker file: -lwinmm (used in codeBlocks)
#include <stdio.h>
#include <iostream>
#include <cstdlib>   
#include <windows.h> 
#include <ctime>   
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// node of circular doubly linked list
class node
{
public:
    string song_name;
    string songFileLocation;
    string lyricsFileLocation;
    int n;               // no. of singers
    string *singerNames; // array to store names of all singers of a song.

    node *next;
    node *prev;
    node(string sn, string sl, string ll, string singer[], int n) // parameterized constructor
    {
        song_name = sn;
        songFileLocation = sl;
        lyricsFileLocation = ll;
        next = NULL;
        prev = NULL;

        singerNames = new string[n];
        for (int i = 0; i < n; i++)
        {
            singerNames[i] = singer[i];
        }
        this->n = n;
    }
};
node *tail = NULL; // tail of our CDLL

class sortedNode // node of our sorted songs list (CDLL)
{
public:
    string song_name;
    sortedNode *prev;
    sortedNode *next;
    sortedNode(string sn)
    {
        song_name = sn;
        prev = next = NULL;
    }
};

class nNode // node of a basic linked list
{
public:
    string name;
    nNode *next;
    nNode(string n)
    {
        name = n;
        next = NULL;
    }
};

class nodeP // simple linked list for playlists
{
public:
    string name;
    string location; // location of .txt file of playlist
    nodeP *next;
    nodeP(string n, string l)
    {
        name = n;
        location = l;
        next = NULL;
    }
};
nodeP *playlists = NULL;

// declaring all functions
void addNode(node *&tail, string sn, string sl, string ll, string singer[], int num);
void deleteNode(node *toDel);
void addSortedNode(sortedNode *&tail, string name);
int lengthOfCDLL();
int lenghtOfITH();
int lenghtOfGH();
int lengthOfnNode(nNode *head);
int lenghtOfnodeP(nodeP *head);
int lengthOfSortedNode(sortedNode *curr);
void WelcomeScreenFront(); // function for welcome screen
void welcomeScreen();
void musicSystemHeader();
void askAdminOrUser();
void adminLogin();
void userLogin();
void exitMusicSystem();
void adminMainMenu();
void userMainMenu();
void viewAllSongs();
void chooseMusicToPlay();
void playPrevOrNextSong(node *curr);
string getLocation(sortedNode *curr);
void playPrevOrNextSongSorted(sortedNode *curr);
void playMusic(string songLoc);
void makeLowercase(string &s);
void addNewSong(); // adding song to database
void deleteSong();
bool checkEmptyITH();
bool checkEmptyGH();
void editIndiaTopHits();
void viewSongsITH();
void chooseMusicToPlayITH();
void addSongITH();
void deleteSongITH();
void editGloballyHit();
void viewSongsGH();
void chooseMusicToPlayGH();
void addSongGH();
void deleteSongGH();
void playMusicHelp(string name);
void askToPlaySearchedSong(nNode *list1, nNode *list2); // called after searching is done for a song.
void displayList(nNode *list1, nNode *list2);
void displaynNode(nNode *head); // just for verfication purposes
void searchSong();
nNode *searchInSongName(string s);
nNode *searchInSongLyrics(string s);
void askToPlaySearchedSong2(nNode *list); // called after searching is done for a song.
void displayList2(nNode *list);
void searchSongUsingSinger();
void editPlaylists();
void newPlaylist();
void addNewPlaylist(string playlist_name);
void deletenodeP(nodeP *curr);
void addSongToPlaylist(nodeP *&playlist);
int viewAllPlaylists();
void selectPlaylist();
void viewSongsFromPlaylist(nodeP *playlist);
void editParticularPlaylist(nodeP *playlist, int flag);
void playSongFromPlaylist(nodeP *playlist);
void deleteSongFromPlaylist(nodeP *&playlist);
void deletePlaylist();
void display(node *tail);
void addExistingPlaylistToLL(string name);
void retreivePlaylistsFromDatabase();
void retreiveFromDatabase();
void deleteSongFromPlaylist();
string replaceSpaceByUnderscore(string s);
bool isAlphabeticallySmaller(string str1, string str2);
void selectionSort(string arr[], int n, sortedNode *&sortedLL);
void sortCDLL();

/*Insert and delete node in CDLL*/
void addNode(node *&tail, string sn, string sl, string ll, string singer[], int num)
{
    node *n = new node(sn, sl, ll, singer, num);
    if (tail == NULL)
    {
        tail = n;
        n->next = n;
        n->prev = n;
        return;
    }

    n->next = tail->next;
    tail->next->prev = n;
    tail->next = n;
    n->prev = tail;

    tail = n;
}

void deleteNode(node *toDel)
{
    if (tail == toDel)
    {
        tail->prev->next = tail->next;
        tail->next->prev = tail->prev;

        node *temp = tail;
        tail = tail->prev;
        free(temp);
        return;
    }

    node *temp = tail;
    do
    {
        temp = temp->next;
    } while (temp != toDel);

    toDel->prev->next = toDel->next;
    toDel->next->prev = toDel->prev;

    delete toDel;
}

void addSortedNode(sortedNode *&tail, string name)
{
    if (tail == NULL)
    {
        tail = new sortedNode(name);
        tail->prev = tail;
        tail->next = tail;
        return;
    }

    sortedNode *newNode = new sortedNode(name);

    newNode->next = tail->next;
    tail->next->prev = newNode;
    tail->next = newNode;
    newNode->prev = tail;

    tail = newNode;
}

int lengthOfCDLL()
{
    node *temp = tail;
    int count = 1;
    do
    {
        temp = temp->next;
        count++;
    } while (temp != tail);

    return count - 1;
}

int lengthOfSortedNode(sortedNode *curr)
{
    int count = 0;
    sortedNode *temp = curr;
    do
    {
        count++;
        temp = temp->next;
    } while (temp != curr);

    return count;
}

int lengthOfnNode(nNode *head)
{
    nNode *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

int lenghtOfnodeP(nodeP *head)
{
    string loc = head->location;
    fstream ptr;
    ptr.open(loc, ios::in);

    string line;
    int count = 0;
    while (getline(ptr, line))
    {
        count++;
    }

    return count;
}

int lenghtOfITH()
{
    int count = 0;
    fstream ptr;
    ptr.open("Database\\ITH.txt", ios::in);

    string line;
    while (getline(ptr, line))
    {
        count++;
    }

    return count;
}

int lenghtOfGH()
{
    int count = 0;
    fstream ptr;
    ptr.open("Database\\GH.txt", ios::in);

    string line;
    while (getline(ptr, line))
    {
        count++;
    }

    return count;
}

string replaceSpaceByUnderscore(string s)
{
    string newStr = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            newStr += "_";
        }
        else
        {
            newStr += s[i];
        }
    }

    return newStr;
}

void WelcomeScreenFront() // function for welcome screen
{
    cout << "\n\n\n\n\n\n\n\t\t\t\t*****************************************" << endl;
    cout << "\n\t\t\t\t*\t\tWELCOME TO\t\t*" << endl;
    cout << "\n\t\t\t\t\t*      MUSIC SYSTEM  *" << endl;
    cout << "\n\t\t\t\t*****************************************" << endl;
    cout << "\n\n\n\n\n Press any key to continue......\n"
         << endl;
    fflush(stdin);
    getchar(); // Use to holds screen for some seconds
}

void welcomeScreen()
{
    cout << "WELCOME TO MUSIC SYSTEM" << endl;
    cout << "\n";
}

void musicSystemHeader()
{
    cout << "MUSIC SYSTEM" << endl;
    cout << "\n\n";
}

void askAdminOrUser()
{
    system("cls");
    welcomeScreen();
    char ch;
    cout << "LOGIN: " << endl;
    cout << "1. Enter 'a' for admin\n2. Enter 'u' for user\n3. 'e' for exit" << endl;
    cout << "Enter here: ";
    cin >> ch;

    if (ch == 'a' || ch == 'A')
    {
        adminLogin();
    }
    else if (ch == 'u' || ch == 'U')
    {
        userLogin();
    }
    else if (ch == 'e' || ch == 'E')
    {
        cout << "Thanks for Visiting...." << endl;
        fflush(stdin);
        getchar();
        exit(0);
    }
    else
    {
        cout << "Invalid character entered !! Please enter again." << endl;
        getchar();
        askAdminOrUser();
    }
}

void adminLogin()
{
    system("cls");
    welcomeScreen();

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (username == "admin" && password == "1")
    {
        cout << "LOGIN SUCCESSFULL !!!" << endl;
        cout << "\nPress any key to continue......\n";
        fflush(stdin);
        getchar(); // Use to holds screen for some seconds
        adminMainMenu();
    }
    else
    {
        cout << "Invalid username / password" << endl;
        fflush(stdin);
        getchar();
        adminLogin();
    }
}

void userLogin()
{
    system("cls");
    welcomeScreen();

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (username == "user" && password == "1")
    {
        cout << "LOGIN SUCCESSFULL !!!" << endl;
        cout << "\nPress any key to continue......\n";
        fflush(stdin);
        getchar(); // Use to holds screen for some seconds
        userMainMenu();
    }
    else
    {
        cout << "Invalid username / password" << endl;
        fflush(stdin);
        getchar();
        userLogin();
    }
}

void exitMusicSystem() // runs when we exit from any mainmenu either admin or user
{
    system("cls");
    musicSystemHeader();
    cout << "Changes are saved. Logged out Successfully !!." << endl;
    fflush(stdin);
    getchar();
}

/*********************** MAINMENU****************************/
void adminMainMenu()
{
    system("cls");
    musicSystemHeader();

    cout << "1. View all songs\n2. Add song to Database\n3. Delete song from Database\n4. Edit India Top Hits\n5. Edit Globally Hits\n6. Exit" << endl;
    int option;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        viewAllSongs();
        break;

    case 2:
        addNewSong();
        break;

    case 3:
        deleteSong();
        break;

    case 4:
        editIndiaTopHits();
        break;

    case 5:
        editGloballyHit();
        break;

    case 6:
        exitMusicSystem();
        askAdminOrUser();
        return;
    }
    adminMainMenu();
}

void userMainMenu()
{
    system("cls");
    musicSystemHeader();

    cout << "1. View all songs\n2. View songs in Sorted order\n3. Search song\n4. Edit playlists\n5. View India Top hits\n6. View globally Hits\n7. Exit" << endl;
    int option;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        viewAllSongs();
        userMainMenu();
        break;

    case 2:
        sortCDLL();
        userMainMenu();
        break;

    case 3:
        cout << endl;
        cout << "1. search using keyword/line\n2. search using singer name" << endl;
        cout << "Enter option: ";
        cin >> option;
        if (option == 1)
        {
            searchSong();
        }
        else if (option == 2)
        {
            searchSongUsingSinger();
        }
        else
        {
            userMainMenu();
        }
        userMainMenu();
        break;

    case 4:
        editPlaylists();
        userMainMenu();
        break;

    case 5:
        viewSongsITH();
        userMainMenu();
        break;

    case 6:
        viewSongsGH();
        userMainMenu();
        break;

    case 7:
        exitMusicSystem();
        askAdminOrUser();
        break;
    }
}

/**************** SELECT & PLAY MUSIC*****************/
void viewAllSongs()
{
    system("cls");

    if (tail == NULL) // tail, here is tail of CDLL
    {
        cout << "No songs are added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    node *temp = tail;
    int idx = 1;
    cout << endl;
    cout << "SONGS :" << endl;
    do
    {
        cout << idx << ". " << temp->next->song_name << endl;
        temp = temp->next;
        idx++;
    } while (temp != tail);

A:
    cout << endl;
    char ch;
    cout << "Want to play a song, [y/n]: ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        chooseMusicToPlay();
    }
    else if (ch == 'n' || ch == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid choice !!" << endl;
        getchar();
        goto A;
    }
}

void chooseMusicToPlay()
{
    int song_no;
    cout << "Enter song no. :";
    cin >> song_no;
    if (song_no < 1 || song_no > lengthOfCDLL())
    {
        cout << "Invalid choice !!" << endl;
        getchar();
        return;
    }

    node *temp = tail;
    while (song_no--)
    {
        temp = temp->next;
    }

    playMusic(temp->songFileLocation);
    playPrevOrNextSong(temp);
}

void playPrevOrNextSong(node *curr)
{
    int option;
    cout << "1. Play prev song\n2. Play next song\n3. Play current song again\n4. Exit" << endl;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        playMusic(curr->prev->songFileLocation);
        playPrevOrNextSong(curr->prev);
        break;

    case 2:
        playMusic(curr->next->songFileLocation);
        playPrevOrNextSong(curr->next);
        break;

    case 3:
        playMusic(curr->songFileLocation);
        playPrevOrNextSong(curr);
        break;

    case 4:
        cout << endl;
        cout << "Returning..." << endl;
        fflush(stdin);
        getchar();
        return;

    default:
        cout << "Invalid choice..." << endl;
        playPrevOrNextSong(curr);
        return;
    }
}

string getLocation(sortedNode *curr)
{
    node *temp = tail;
    do
    {
        if (temp->song_name == curr->song_name)
        {
            return temp->songFileLocation;
        }
        temp = temp->next;
    } while (temp != tail);

    return "";
}

void playPrevOrNextSongSorted(sortedNode *curr)
{
    int option;
    cout << "1. Play prev song\n2. Play next song\n3. Play current song again\n4. Exit" << endl;
    cout << "Enter option: ";
    cin >> option;

    string loc;
    switch (option)
    {
    case 1:
        loc = getLocation(curr->prev);
        playMusic(loc);
        playPrevOrNextSongSorted(curr->prev);
        break;

    case 2:
        loc = getLocation(curr->next);
        playMusic(loc);
        playPrevOrNextSongSorted(curr->next);
        break;

    case 3:
        loc = getLocation(curr);
        playMusic(loc);
        playPrevOrNextSongSorted(curr);
        break;

    case 4:
        cout << endl;
        cout << "Returning..." << endl;
        fflush(stdin);
        getchar();
        return;

    default:
        cout << "Invalid choice..." << endl;
        playPrevOrNextSongSorted(curr);
        return;
    }
}

void playMusic(string songLoc)
{
    int n;
    time_t t1, t2, previous_pause_time = 0;
    string name = "song";
    string playCommand = "Open \"" + songLoc + "\" type mpegvideo alias song";
    LPCSTR s = playCommand.c_str();

    MCIERROR err = mciSendString(s, NULL, 0, NULL);
    if (err != 0)
    {
        cout << "Error in playing song..." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    while (1)
    {
        cout << endl;
        cout << "Press 1 to play the file and press 2 to exit the file: ";
        cin >> n;

        if (n == 1)
        {
            // play the audio file
            t1 = time(0);
            mciSendString("play song", NULL, 0, NULL);
            cout << "Audio file playing..." << endl;
        }
        else if (n == 2)
        {
            // close the file and get out of the loop
            mciSendString("close song", NULL, 0, NULL);
            break;
        }

        cout << endl;
        cout << "Press 0 to pause the file and press 2 to exit the file: ";
        cin >> n;

        if (n == 0)
        {
            // pause the audio file
            mciSendString("pause song", NULL, 0, NULL);
            t2 = time(0);
            cout << "Audio file paused after " << t2 - t1 + previous_pause_time << " seconds..." << endl;
            previous_pause_time += t2 - t1;
        }
        else if (n == 2)
        {
            // close the audio file
            mciSendString("close song", NULL, 0, NULL);
            cout << "Song closed..." << endl;
            fflush(stdin);
            getchar();
            break;
        }
    }
}

void makeLowercase(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

/****************** add new song*********************/
void addNewSong() // adding song to database
{
    system("cls");
    musicSystemHeader();
    cout << "ADDING NEW SONG: " << endl;
    cout << endl;

    string sn, sl, ll;
    int n;

    cout << "Enter song name: ";
    fflush(stdin);
    getline(cin, sn);
    makeLowercase(sn);

    cout << "Enter song location: ";
    fflush(stdin);
    getline(cin, sl);

    cout << "Enter lyrics location: ";
    fflush(stdin);
    getline(cin, ll);

    cout << "How many singers for this song?" << endl;
    cin >> n;

    string singer[n];
    cout << "Enter singers name: " << endl;

    for (int i = 0; i < n; i++)
    {
        fflush(stdin);
        getline(cin, singer[i]);
        makeLowercase(singer[i]);
        singer[i] = replaceSpaceByUnderscore(singer[i]);
    }

    fstream ptr1, ptr2, ptr3, ptr4;

    ptr1.open("Database\\songsName.txt", ios::app);
    ptr2.open("Database\\songsLocation.txt", ios::app);
    ptr3.open("Database\\songsLyricsLocation.txt", ios::app);
    ptr4.open("Database\\singersName.txt", ios::app);
    if (!ptr1 && !ptr2 && !ptr3 && !ptr4)
    {
        cout << "Can't open files" << endl;
        getchar();
        return;
    }

    ptr1 << sn;
    ptr1 << "\n";
    ptr2 << sl;
    ptr2 << "\n";
    ptr3 << ll;
    ptr3 << "\n";
    for (int i = 0; i < n; i++)
    {
        ptr4 << singer[i] << " ";
    }
    ptr4 << "\n";

    ptr1.close();
    ptr2.close();
    ptr3.close();
    ptr4.close();

    addNode(tail, sn, sl, ll, singer, n); // adds new song info as node in the CDLL.
    cout << "SONG ADDED SUCCESSFULLY !!" << endl;
    fflush(stdin);
    getchar();
}

void deleteSong()
{
    system("cls");
    musicSystemHeader();
    if (tail == NULL)
    {
        cout << "No songs added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    viewAllSongs();

    int song_no;
    cout << "Enter song no. to delete it :";
    cin >> song_no;

    if (song_no < 1 || song_no > lengthOfCDLL())
    {
        cout << "Invalid song number !!" << endl;
        fflush(stdin);
        getchar();
        deleteSong();
    }

    node *temp = tail;
    while (song_no--)
    {
        temp = temp->next;
    }

    fstream ptr1, ptr2, ptr3, ptr4;
    ptr1.open("Database\\songsName.txt", ios::in);
    ptr2.open("Database\\songsLocation.txt", ios::in);
    ptr3.open("Database\\songsLyricsLocation.txt", ios::in);
    ptr4.open("Database\\singersName.txt", ios::in);
    if (!ptr1 && !ptr2 && !ptr3 && !ptr4)
    {
        cout << "Can't open files 1, 2, 3, 4" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    fstream ptr5, ptr6, ptr7, ptr8;
    ptr5.open("Database\\tempsongsName.txt", ios::out);
    ptr6.open("Database\\tempsongsLocation.txt", ios::out);
    ptr7.open("Database\\tempsongsLyricsLocation.txt", ios::out);
    ptr8.open("Database\\tempsingersName.txt", ios::out);
    if (!ptr5 && !ptr6 && !ptr7 && !ptr8)
    {
        cout << "Can't open files 5,6,7,8" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string deleteline1 = temp->song_name;
    string line1;

    while (getline(ptr1, line1))
    {
        if (line1 != deleteline1)
        {
            ptr5 << line1;
            ptr5 << "\n";
        }
    }

    ptr1.close();
    ptr5.close();

    if (remove("Database\\songsName.txt") != 0)
    {
        cout << ("Error deleting songsName.txt") << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempsongsName.txt", "Database\\songsName.txt");

    string deleteline2 = temp->songFileLocation;
    string line2;

    while (getline(ptr2, line2))
    {
        if (line2 != deleteline2)
        {
            ptr6 << line2;
            ptr6 << "\n";
        }
    }

    ptr2.close();
    ptr6.close();

    if (remove("Database\\songsLocation.txt") != 0)
    {
        cout << "Error deleting songsLocation.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempsongsLocation.txt", "Database\\songsLocation.txt");

    string deleteline3 = temp->lyricsFileLocation;
    string line3;

    while (getline(ptr3, line3))
    {
        if (line3 != deleteline3)
        {
            ptr7 << line3;
            ptr7 << "\n";
        }
    }

    ptr3.close();
    ptr7.close();

    if (remove("Database\\songsLyricsLocation.txt") != 0)
    {
        cout << "Error deleting songsLyricsLocation.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempsongsLyricsLocation.txt", "Database\\songsLyricsLocation.txt");

    string deleteline4 = "";
    for (int i = 0; i < temp->n; i++)
    {
        deleteline4 += temp->singerNames[i];
        deleteline4 += " ";
    }
    string line4;

    while (getline(ptr4, line4))
    {
        if (line4 != deleteline4)
        {
            ptr8 << line4;
            ptr8 << "\n";
        }
    }

    ptr4.close();
    ptr8.close();

    if (remove("Database\\singersName.txt") != 0)
    {
        cout << "Error deleting singersName.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempsingersName.txt", "Database\\singersName.txt");

    deleteNode(temp);
    cout << "Song deleted Successfully !!" << endl;
    fflush(stdin);
    getchar();
}

bool checkEmptyITH() // returns 0 in both cases, either file is present but empty or file is not present
{
    fstream ptr;
    ptr.open("Database\\ITH.txt");

    string line = "";
    if (!getline(ptr, line))
    {
        ptr.close();
        return 0;
    }

    ptr.close();
    return 1;
}

bool checkEmptyGH()
{
    fstream ptr;
    ptr.open("Database\\GH.txt");

    string line = "";
    if (!getline(ptr, line))
    {
        ptr.close();
        return 0;
    }

    ptr.close();
    return 1;
}

void editIndiaTopHits()
{
    cout << endl;
    cout << "Options: " << endl;
    cout << "1. View India Top Hits songs\n2. Add song\n3. Delete song\n4. Exit" << endl;
    int option;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        viewSongsITH();
        break;

    case 2:
        addSongITH();
        break;

    case 3:
        deleteSongITH();
        break;

    case 4:
        adminMainMenu();
        break;

    default:
        cout << "Invalid option choosen !!" << endl;
        fflush(stdin);
        getchar();
        adminMainMenu();
    }
}

void viewSongsITH()
{
    system("cls");
    if (!checkEmptyITH())
    {
        cout << "No songs added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    int idx = 1;
    string line;

    fstream ptr;
    ptr.open("Database\\ITH.txt", ios::in);
    if (!ptr.is_open())
    {
        cout << "Error opening ITH.txt" << endl;
        getchar();
        return;
    }

    musicSystemHeader();
    cout << "India Top hit Songs:-" << endl;
    while (getline(ptr, line))
    {
        cout << idx << ". " << line << endl;
        idx++;
    }

    ptr.close();

B:
    cout << endl;
    char ch;
    cout << "Want to play a song, [y/n]: ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        chooseMusicToPlayITH();
    }
    else if (ch == 'n' || ch == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid choice !!" << endl;
        getchar();
        goto B;
    }
}

void chooseMusicToPlayITH()
{
    int song_no;
    cout << "Enter song no. :";
    cin >> song_no;

    if (song_no < 1 || song_no > lenghtOfITH())
    {
        cout << "Invalid song_no !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    fstream ptr;
    ptr.open("Database\\ITH.txt", ios::in);
    if (!ptr.is_open())
    {
        cout << "Error opening ITH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string Sname;
    while (song_no--)
    {
        getline(ptr, Sname);
    }

    int count = 1;
    node *temp = tail;
    do
    {
        if (temp->next->song_name == Sname)
        {
            break;
        }
        count++;
        temp = temp->next;
    } while (temp != tail);

    playMusic(temp->next->songFileLocation);
    viewSongsITH();
}

void addSongITH()
{
    // songs will be added to ITH using songs which are already in our CDLL.
    viewAllSongs();
    int option;
    cout << "Enter song no. :";
    cin >> option;

    if (option < 1 || option > lengthOfCDLL())
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    node *temp = tail;
    while (option--)
    {
        temp = temp->next;
    }

    fstream ptr;
    ptr.open("Database\\ITH.txt", ios::app);
    ptr << temp->song_name;
    ptr << "\n";

    ptr.close();
    cout << "Song added successfully !!" << endl;
    fflush(stdin);
    getchar();
}

void deleteSongITH()
{
    if (!checkEmptyITH())
    {
        cout << "No songs added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    viewSongsITH();
    int option;
    cout << "Enter song no. :";
    cin >> option;

    if (option < 1 || option > lenghtOfITH())
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string line; // line i.e. song name which we want to delete.
    fstream ptr;
    ptr.open("Database\\ITH.txt", ios::in);

    while (option--)
    {
        getline(ptr, line);
    }
    ptr.close();

    fstream ptr1, ptr2;
    ptr1.open("Database\\ITH.txt", ios::in);
    if (!ptr1)
    {
        cout << "Can't open files ITH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr2.open("Database\\tempITH.txt", ios::out);
    if (!ptr2)
    {
        cout << "Can't open tempITH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string line1;
    while (getline(ptr1, line1))
    {
        if (line1 != line)
        {
            ptr2 << line1;
            ptr2 << "\n";
        }
    }
    ptr1.close();
    ptr2.close();

    if (remove("Database\\ITH.txt") != 0)
    {
        cout << "Error deleting ITH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempITH.txt", "Database\\ITH.txt");

    cout << "Song deleted successfully !!" << endl;
    fflush(stdin);
    getchar();
}

void editGloballyHit()
{
    cout << endl;
    cout << "Options: " << endl;
    cout << "1. View Globally Hit songs\n2. Add song\n3. Delete song\n4. Exit" << endl;
    int option;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        viewSongsGH();
        break;

    case 2:
        addSongGH();
        break;

    case 3:
        deleteSongGH();
        break;

    case 4:
        adminMainMenu();
        break;

    default:
        cout << "Invalid option choosen !!" << endl;
        fflush(stdin);
        getchar();
        adminMainMenu();
    }
}

void viewSongsGH()
{
    system("cls");
    if (!checkEmptyGH())
    {
        cout << "No songs added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    int idx = 1;
    string line;

    fstream ptr;
    ptr.open("Database\\GH.txt", ios::in);
    if (!ptr.is_open())
    {
        cout << "Error opening GH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    musicSystemHeader();
    cout << "Globally hit Songs:-" << endl;
    while (getline(ptr, line))
    {
        cout << idx << ". " << line << endl;
        idx++;
    }

    ptr.close();

B:
    cout << endl;
    char ch;
    cout << "Want to play a song, [y/n]: ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        chooseMusicToPlayGH();
    }
    else if (ch == 'n' || ch == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        goto B;
    }
}

void chooseMusicToPlayGH()
{
    int song_no;
    cout << "Enter song no. :";
    cin >> song_no;

    if (song_no < 1 || song_no > lenghtOfGH())
    {
        cout << "Invalid song_no !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    fstream ptr;
    ptr.open("Database\\GH.txt", ios::in);
    if (!ptr.is_open())
    {
        cout << "Error opening GH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string Sname;
    while (song_no--)
    {
        getline(ptr, Sname);
    }

    ptr.close();

    int count = 1;
    node *temp = tail;
    do
    {
        if (temp->next->song_name == Sname)
        {
            break;
        }
        count++;
        temp = temp->next;
    } while (temp != tail);

    playMusic(temp->next->songFileLocation);
    viewSongsGH();
}

void addSongGH()
{
    // songs will be added to GH using songs which are already in our CDLL.
    viewAllSongs();
    int option;
    cout << "Enter song no. :";
    cin >> option;

    if (option < 1 || option > lengthOfCDLL())
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    node *temp = tail;
    while (option--)
    {
        temp = temp->next;
    }

    fstream ptr;
    ptr.open("Database\\GH.txt", ios::app);
    ptr << temp->song_name;
    ptr << "\n";

    ptr.close();

    cout << "Song added successfully !!" << endl;
    fflush(stdin);
    getchar();
}

void deleteSongGH()
{
    if (!checkEmptyGH())
    {
        cout << "No songs added yet !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    viewSongsGH();
    int option;
    cout << "Enter song no. :";
    cin >> option;

    if (option < 1 || option > lenghtOfGH())
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string line; // line i.e. song name which we want to delete.
    fstream ptr;
    ptr.open("Database\\GH.txt", ios::in);

    while (option--)
    {
        getline(ptr, line);
    }
    ptr.close();

    fstream ptr1, ptr2;
    ptr1.open("Database\\GH.txt", ios::in);
    if (!ptr1)
    {
        cout << "Can't open files GH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr2.open("Database\\tempGH.txt", ios::out);
    if (!ptr2)
    {
        cout << "Can't open tempGH.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string line1;
    while (getline(ptr1, line1))
    {
        if (line1 != line)
        {
            ptr2 << line1;
            ptr2 << "\n";
        }
    }

    ptr1.close();
    ptr2.close();

    if (remove("Database\\GH.txt") != 0)
    {
        cout << ("Error deleting GH.txt") << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\tempGH.txt", "Database\\GH.txt");
    cout << "Song deleted successfully !!" << endl;
    fflush(stdin);
    getchar();
}

/**************************** SORTING CDLL*****************************/
void sortCDLL()
{
    sortedNode *sortedLL = NULL;    // tail of our sorted CDLL songs
    string songArr[lengthOfCDLL()]; // to store names of all songs of CDLL

    int idx = 0;
    node *temp = tail;
    do
    {
        songArr[idx] = temp->song_name;
        temp = temp->next;
        idx++;
    } while (temp != tail);

    selectionSort(songArr, lengthOfCDLL(), sortedLL);

    int option;
    cout << "Enter song no. to play: ";
    cin >> option;

    if (option < 1 || option > lengthOfSortedNode(sortedLL))
    {
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    sortedNode *temp1 = sortedLL;
    while (option--)
    {
        temp1 = temp1->next;
    }

    node *temp2 = tail;
    do
    {
        if (temp2->song_name == temp1->song_name)
        {
            playMusic(temp2->songFileLocation);
            playPrevOrNextSongSorted(temp1);
            return;
        }
        temp2 = temp2->next;
    } while (temp2 != tail);
}

void selectionSort(string arr[], int n, sortedNode *&sortedLL)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (isAlphabeticallySmaller(arr[j], arr[min_idx])) // if second string is greater then 1 is returned otherwise 0
            {
                min_idx = j;
            }
        }
        string temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }

    int idx = 1;
    sortedNode *temp = sortedLL;
    cout << endl;
    cout << "Sorted songs List:-" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << idx << ". " << arr[i] << endl;
        addSortedNode(sortedLL, arr[i]);
        idx++;
    }
}

bool isAlphabeticallySmaller(string str1, string str2)
{
    // Converting both str1 and str2 to uppercase
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

    if (str1 < str2)
    {
        return true;
    }
    return false;
}

/************************ SEARCH SONG USING KEYWORD*************************/
void searchSong()
{
    string userSongname;
    cout << "Enter keyword or a line of the song: ";
    fflush(stdin);
    getline(cin, userSongname);
    makeLowercase(userSongname); // because our whole lyrics is in lowercase

    nNode *list1 = searchInSongName(userSongname);
    nNode *list2 = searchInSongLyrics(userSongname);
    if (list1 == NULL && list2 == NULL)
    {
        cout << "No such song is in Database !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    displayList(list1, list2);
}

nNode *s1 = NULL; // linked list to store songs node after searching in songs name
nNode *searchInSongName(string s)
{
    node *temp = tail;
    nNode *temp_s1 = s1;

    cout << endl;
    cout << "Processing..." << endl;
    do
    {
        if ((temp->song_name).find(s) != string::npos) // checking if s is a substring of the song_name or not.
        {
            nNode *n = new nNode(temp->song_name);
            if (s1 == NULL)
            {
                temp_s1 = s1 = n;
            }
            else
            {
                temp_s1->next = n;
                temp_s1 = temp_s1->next;
            }
        }
        temp = temp->next;
    } while (temp != tail);

    cout << "Searching in songs name is done." << endl;
    return s1;
}

nNode *s2 = NULL; // linked list to store songs node after searching in songs lyrics
nNode *searchInSongLyrics(string s)
{
    fstream ptr;
    node *temp = tail;
    nNode *temp_s2 = s1;
    string line;

    cout << endl;
    cout << "Processing..." << endl;
    do
    {
        ptr.open(temp->lyricsFileLocation, ios::in);
        if (!ptr.is_open())
        {
            cout << "Can't open File" << endl;
            fflush(stdin);
            getchar();
            return NULL;
        }

        while (getline(ptr, line))
        {
            if (line.find(s) != string::npos)
            {
                cout << "Line of match: " << line << endl;
                nNode *n = new nNode(temp->song_name);
                if (s2 == NULL)
                {
                    temp_s2 = s2 = n;
                }
                else
                {
                    temp_s2->next = n;
                    temp_s2 = temp_s2->next;
                }
                break;
            }
        }
        temp = temp->next;
        ptr.close();
    } while (temp != tail);

    cout << "Searching in songs lyrics is done." << endl;
    return s2;
}

void displayList(nNode *list1, nNode *list2)
{
    cout << endl;
    cout << "Matched songs :-" << endl;
    nNode *temp1 = list1;
    nNode *temp2 = list2;
    int idx = 1;

    while (temp1 != NULL)
    {
        cout << idx << ". " << temp1->name << endl;
        idx++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        cout << idx << ". " << temp2->name << endl;
        idx++;
        temp2 = temp2->next;
    }

    askToPlaySearchedSong(list1, list2);
}

void askToPlaySearchedSong(nNode *list1, nNode *list2) // called after searching is done for a song.
{
    cout << "Do you want to play song? [y/n]: ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        int option;
        cout << "Enter song no. :";
        cin >> option;
        if (option < 1 || option > (lengthOfnNode(list1) + lengthOfnNode(list2)))
        {
            cout << "Invalid option !!" << endl;
            fflush(stdin);
            getchar();
            askToPlaySearchedSong(list1, list2);
        }

        if (list1 != NULL)
        {
            option--;
        }
        while (list1 != NULL && option--)
        {
            list1 = list1->next;
        }
        if (option == -1)
        {
            playMusicHelp(list1->name);
            return;
        }
        option--;
        while (list2 != NULL && option--)
        {
            list2 = list2->next;
        }
        playMusicHelp(list2->name);
    }
    else if (ch == 'n' || ch == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid character !! please enter either y or n." << endl;
        askToPlaySearchedSong(list1, list2);
    }
}

void playMusicHelp(string name)
{
    node *temp = tail;
    do
    {
        if (temp->song_name == name)
        {
            playMusic(temp->songFileLocation);
            return;
        }
        temp = temp->next;
    } while (temp != tail);
}

void displaynNode(nNode *head) // just for verfication purposes
{
    nNode *temp = head;
    while (temp != NULL)
    {
        cout << temp->name << endl;
        temp = temp->next;
    }
    cout << endl;
}

/***************************** SEARCHING USING SINGER NAME***********************************/
nNode *s3 = NULL;
void searchSongUsingSinger()
{
    string singerName;
    cout << "Enter 1 singer name: ";
    fflush(stdin);
    getline(cin, singerName);
    makeLowercase(singerName);
    singerName = replaceSpaceByUnderscore(singerName);

    node *temp = tail;
    nNode *temp_s3 = s3;
    do
    {
        for (int i = 0; i < temp->n; i++)
        {
            if (temp->singerNames[i] == singerName)
            {
                nNode *newNode = new nNode(temp->song_name);
                if (s3 == NULL)
                {
                    temp_s3 = s3 = newNode;
                }
                else
                {
                    temp_s3->next = newNode;
                }
                break;
            }
        }
        temp = temp->next;
    } while (temp != tail);

    if (s3 == NULL)
    {
        cout << "No such song is in Database !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    displayList2(s3);
}

void displayList2(nNode *list)
{
    cout << endl;
    cout << "Matched songs :-" << endl;
    nNode *temp = list;
    int idx = 1;

    while (temp != NULL)
    {
        cout << idx << ". " << temp->name << endl;
        idx++;
        temp = temp->next;
    }

    askToPlaySearchedSong2(list);
}

void askToPlaySearchedSong2(nNode *list) // called after searching is done for a song.
{
    cout << "Do you want to play song? [y/n]" << endl;
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        int option;
        cout << "Enter song no. :";
        cin >> option;

        if (option < 1 || option > lengthOfnNode(list))
        {
            cout << "Invalid option !!" << endl;
            fflush(stdin);
            getchar();
            askToPlaySearchedSong2(list);
        }

        option--;
        while (option--)
        {
            list = list->next;
        }
        if (option == -1)
        {
            playMusicHelp(list->name);
            return;
        }
    }
    else if (ch == 'n' || ch == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid character !! please enter either y or n." << endl;
        askToPlaySearchedSong2(list);
    }
}

/*********************** PLAYLIST****************************/
void editPlaylists()
{
    system("cls");
    cout << "Action to perform on Playlists:-" << endl;
    int option, temp;
    cout << "1. View all playlists\n2. Create new playlist\n3. Delete playlist\n4. Exit" << endl;
    cout << "Enter option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        temp = viewAllPlaylists();
        if (temp != 0)
        {
            selectPlaylist();
        }
        editPlaylists();
        break;

    case 2:
        newPlaylist();
        editPlaylists();
        break;

    case 3:
        deletePlaylist();
        editPlaylists();
        break;

    case 4:
        userMainMenu();
        break;

    default:
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
    }
}

int viewAllPlaylists()
{
    system("cls");
    cout << "Playlists:- " << endl;

    if (playlists == NULL)
    {
        cout << "No playlists made yet..." << endl;
        fflush(stdin);
        getchar();
        return 0;
    }

    nodeP *temp = playlists;
    int index = 1;
    while (temp != NULL)
    {
        cout << index << ". " << temp->name << endl;
        temp = temp->next;
        index++;
    }
    return 1;
}

void selectPlaylist()
{
    int ch;
    cout << "Enter playlist no. to view: ";
    cin >> ch;

    nodeP *temp = playlists;
    ch--;
    while (temp != NULL && ch--)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
        return;
    }

    viewSongsFromPlaylist(temp);
}

void viewSongsFromPlaylist(nodeP *playlist)
{
    fstream ptr;
    ptr.open(playlist->location, ios::in);

    string s;
    int flag = 1;
    int index = 1;

    getline(ptr, s);
    if (s != "")
    {
        cout << endl;
        cout << "Songs:-" << endl;

        cout << index << ". " << s << endl;
        index++;
        while (getline(ptr, s))
        {
            cout << index << ". " << s << endl;
            index++;
        }
    }
    else
    {
        cout << "No songs in playlist" << endl;
        fflush(stdin);
        getchar();
        flag = 0;
    }

    ptr.close();
    editParticularPlaylist(playlist, flag); // flag is used when user is trying to play song in empty playlist
}

void editParticularPlaylist(nodeP *playlist, int flag)
{
    int ch;
    cout << endl;
    cout << "Functions:-" << endl;
    cout << "1. Add song\n2. Play song\n3. Delete song\n4. exit" << endl;
    cout << "Enter option: ";
    cin >> ch;
    if (ch == 1)
    {
        addSongToPlaylist(playlist);
    }
    else if (ch == 2 && flag == 1)
    {
        playSongFromPlaylist(playlist);
    }
    else if (ch == 2 && flag == 0)
    {
        cout << "There are no songs in playlist to play..." << endl;
        fflush(stdin);
        getchar();
    }
    else if (ch == 3)
    {
        deleteSongFromPlaylist(playlist);
    }
    else if (ch == 4)
    {
        editPlaylists();
    }
    else
    {
        cout << "Invalid choice" << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
    }
}

void addSongToPlaylist(nodeP *&playlist)
{
    viewAllSongs();

    int choice;
    cout << "Enter song number to add song or type '0' to exit: ";
    cin >> choice;

    if (choice == 0)
    {
        cout << "Your Playlist is saved..." << endl;
        fflush(stdin);
        getchar();
        return;
    }
    if (choice < 1 || choice > lengthOfCDLL())
    {
        cout << "Invalid choice !!" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    node *temp = tail;
    while (choice--)
    {
        temp = temp->next;
    }

    fstream ptr1;
    ptr1.open(playlist->location, ios::app);
    if (!ptr1.is_open())
    {
        cout << "Error opening playlist file." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr1 << temp->song_name;
    ptr1 << "\n";
    ptr1.close();

    cout << "Song added successfully...";
    fflush(stdin);
    getchar();
}

void playSongFromPlaylist(nodeP *playlist)
{
    int ch;
    cout << "Enter song no. to play: ";
    cin >> ch;
    if (ch < 1 || ch > lenghtOfnodeP(playlist))
    {
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
    }

    fstream ptr;
    ptr.open(playlist->location, ios::in);

    string s;
    while (ch--)
    {
        getline(ptr, s);
    }

    node *temp = tail;
    do
    {
        if (temp->song_name == s)
        {
            break;
        }
        temp = temp->next;
    } while (temp != tail);

    ptr.close();

    playMusic(temp->songFileLocation);
}

void deleteSongFromPlaylist(nodeP *&playlist)
{
    string checkLine;
    fstream temp;
    temp.open(playlist->location, ios::in);
    getline(temp, checkLine);
    if (checkLine == "")
    {
        cout << "No songs added yet..." << endl;
        fflush(stdin);
        getchar();
        return;
    }
    temp.close();

    int ch;
    cout << "Enter song no. to delete: ";
    cin >> ch;
    if (ch < 1 || ch > lenghtOfnodeP(playlist))
    {
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
    }

    fstream ptr, ptr1;
    ptr.open(playlist->location, ios::in);
    ptr1.open("Database\\playlists\\temp.txt", ios::out);

    string line;
    int count = 1; // when count becomes equal to ch, we will not copy that particular line in temp.txt
    while (getline(ptr, line))
    {
        if (count != ch)
        {
            ptr1 << line;
            ptr1 << "\n";
        }
        count++;
    }

    ptr.close();
    ptr1.close();

    char charArr[(playlist->location).length()+ 1];
    strcpy(charArr, (playlist->location).c_str());

    if (remove(charArr) != 0) // remove function take char array as argument, not string
    {
        cout << "Error deleting playlist file..." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\playlists\\temp.txt", charArr);

    cout << "Song deleted successfully..." << endl;
    fflush(stdin);
    getchar();
}

void newPlaylist() /*********************** ADDING NEW PLAYLIST************************/
{
    string name;
    cout << "Enter name of playlist: ";
    fflush(stdin);
    getline(cin, name);
    makeLowercase(name);

    addNewPlaylist(name);
}

void addNewPlaylist(string playlist_name)
{
    if (playlists == NULL)
    {
        playlists = new nodeP(playlist_name, "Database\\playlists\\" + playlist_name + ".txt");

        fstream ptr;
        ptr.open("Database\\playlists\\playlistNames.txt", ios::app); // new file will be created if no existing playlistNames.txt is there.

        ptr << playlist_name;
        ptr << "\n";
        ptr.close();
        ptr.open("Database\\playlists\\" + playlist_name + ".txt", ios::out); // new playlist txt file will be created
        ptr.close();
        cout << "Playlist made successfully..." << endl;
        fflush(stdin);
        getchar();

        addSongToPlaylist(playlists);
    }
    else
    {
        fstream ptr;
        ptr.open("Database\\playlists\\playlistNames.txt", ios::in);

        string line;
        while (getline(ptr, line)) // checking if playlist with same name already exists or not !!
        {
            if (line == playlist_name)
            {
                cout << "Playlist already exists with this name..." << endl;
                fflush(stdin);
                getchar();
                return;
            }
        }
        ptr.close();

        nodeP *temp = playlists; // to traverse till last node in playlists Linked List to add new node
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        nodeP *newPlaylist = new nodeP(playlist_name, "Database\\playlists\\" + playlist_name + ".txt");
        temp->next = newPlaylist;

        ptr.open("Database\\playlists\\playlistNames.txt", ios::app);

        ptr << playlist_name;
        ptr << "\n";
        ptr.close();
        ptr.open("Database\\playlists\\" + playlist_name + ".txt", ios::out); // new playlist file will be created
        ptr.close();
        cout << "Playlist made successfully..." << endl;
        fflush(stdin);
        getchar();

        addSongToPlaylist(newPlaylist); // already used this function while adding songs to existing playlists
    }
}

void deletePlaylist()
{
    int n = viewAllPlaylists(); // to check whether there are any playlists or not
    if (n == 0)
    {
        return;
    }

    int ch;
    cout << "Enter playlist no. to delete: ";
    cin >> ch;

    nodeP *temp = playlists;
    ch--;
    while (temp != NULL && ch--)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Invalid choice..." << endl;
        fflush(stdin);
        getchar();
        editPlaylists();
        return;
    }

    fstream ptr, ptr1;
    ptr.open("Database\\playlists\\playlistNames.txt", ios::in);
    ptr1.open("Database\\playlists\\tempplaylistNames.txt", ios::out);

    string line;
    while (getline(ptr, line))
    {
        if (line != temp->name)
        {
            ptr1 << line;
            ptr1 << "\n";
        }
    }
    ptr.close();
    ptr1.close();

    if (remove("Database\\playlists\\playlistNames.txt") != 0)
    {
        cout << "Error deleting playlistNames.txt" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    rename("Database\\playlists\\tempplaylistNames.txt", "Database\\playlists\\playlistNames.txt");

    char charArr[(temp->location).length() + 1];
    strcpy(charArr, (temp->location).c_str());

    if (remove(charArr) != 0)
    {
        cout << "Error deleting playlist file..." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    deletenodeP(temp);
    cout << "Playlist deleted successfully..." << endl;
    fflush(stdin);
    getchar();
}

void deletenodeP(nodeP *curr) // deletes a node from playlists Linked List
{
    if (playlists->name == curr->name)
    {
        nodeP *temp = playlists;
        playlists = playlists->next;
        free(temp);
    }
    else
    {
        nodeP *temp = playlists;
        while (temp != NULL)
        {
            if (temp->next->name == curr->name)
            {
                break;
            }
            temp = temp->next;
        }

        temp = temp->next;
        temp->next = temp->next->next;
        free(temp);
    }
}

/*void display(node *tail)
{
    if (tail == NULL)
    {
        cout << "no songs in CDLL" << endl;
        return;
    }
    node *temp = tail;
    do
    {
        cout << temp->next->song_name << " ";
        temp = temp->next;
    } while (temp != tail);
}*/

void retreivePlaylistsFromDatabase() // will run at the beginning of program.
{
    fstream ptr;
    ptr.open("Database\\playlists\\playlistNames.txt", ios::in);
    if (!ptr)
    {
        cout << "Error opening playlistNames.txt..." << endl;
        fflush(stdin);
        getchar();
        return;
    }

    while (1)
    {
        string name;
        fflush(stdin);
        getline(ptr, name);

        if (name != "")
        {
            addExistingPlaylistToLL(name);
        }
        else
        {
            break;
        }
    }
    ptr.close();
}

void addExistingPlaylistToLL(string name)
{
    if (playlists == NULL)
    {
        playlists = new nodeP(name, "Database\\playlists\\" + name + ".txt");
        return;
    }

    nodeP *temp = playlists;
    nodeP *newPlaylist = new nodeP(name, "Database\\playlists\\" + name + ".txt");
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newPlaylist;
}

void retreiveFromDatabase() // will run at the beginning of program.
{
    fstream ptr1, ptr2, ptr3, ptr4;

    ptr1.open("Database\\songsName.txt", ios::in);
    if (!ptr1.is_open())
    {
        cout << "Can't open songs name file" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr2.open("Database\\songsLocation.txt", ios::in);
    if (!ptr2.is_open())
    {
        cout << "Can't open songs Location file" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr3.open("Database\\songsLyricsLocation.txt", ios::in);
    if (!ptr3.is_open())
    {
        cout << "Can't open songs lyrics Location file" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    ptr4.open("Database\\singersName.txt", ios::in);
    if (!ptr4.is_open())
    {
        cout << "Can't open singers Name file" << endl;
        fflush(stdin);
        getchar();
        return;
    }

    string line1, line2, line3, line4;

    getline(ptr1, line1);
    getline(ptr2, line2);
    getline(ptr3, line3);
    getline(ptr4, line4); // line4 contains the names of the singers separated by space

    string str = "";
    string singerArray[10]; // assuming maximum singers for 1 song will be less than 10
    int idx = 0;            // to count number of singers using line4
    if (line1 != "" && line2 != "" && line3 != "" && line4 != "")
    {
        for (int i = 0; i < line4.length(); i++)
        {
            if (line4[i] == ' ')
            {
                singerArray[idx] = str;
                idx++;
                str = "";
            }
            else
            {
                str += line4[i];
            }
        }
        singerArray[idx] = str;

        addNode(tail, line1, line2, line3, singerArray, idx + 1);
        while (getline(ptr1, line1) && getline(ptr2, line2) && getline(ptr3, line3) && getline(ptr4, line4))
        {
            idx = 0;
            for (int i = 0; i < line4.length(); i++)
            {
                if (line4[i] == ' ')
                {
                    singerArray[idx] = str;
                    idx++;
                    str = "";
                }
                else
                {
                    str += line4[i];
                }
            }
            singerArray[idx] = str;
            addNode(tail, line1, line2, line3, singerArray, idx + 1);
        }
    }
}

int main(void)
{
    WelcomeScreenFront();
    retreiveFromDatabase();
    cout << "Songs retrieved from database successfully !!" << endl;
    retreivePlaylistsFromDatabase();
    cout << "Playlists retrieved from database successfully !!" << endl;

    fflush(stdin);
    getchar();
    askAdminOrUser();
    return 0;
}
