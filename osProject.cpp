#pragma warning (disable : 4996)
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include<cstring>
#include <direct.h>
#include <string.h>
#include <vector>
#include <ctime>
using namespace std;

enum enCommands {
    pwd = 1, date = 2, ls = 3, clear = 4, cd = 5, history = 6, emkdir = 7, ermdir = 8, cat = 9,
    touch = 10, mv = 11, ecreateAndChange = 12, AddWithSave = 13, cp = 14, rmfile = 15, Exite = 16
};

string returnCommandWord(short number)
{
    string arr[16] = { "pwd","date","ls","clear","cd","history","mkdir","rmdir","cat","touch","mv",">",">>","cp","rmfile" ,"Exit" };
    return arr[number - 1];
}

string DateAndTime()
{
    string ar[12] = { "jan", "fab", "marsh", "april", "may", "jun", "julay", "augst", "seb", "oct", "nov", "des" };
    time_t t = time(0);
    tm* now = localtime(&t);
    string Date = to_string(now->tm_year + 1900) + "/" + to_string(now->tm_mon + 1) + "/" + to_string(now->tm_mday);
    Date += " " + ar[(now->tm_mon + 1) - 1];
    Date += " " + to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
    return Date;
}

int ReadNumber()
{
    int Number = 0;
    cout << "\n\t\t\t\tplease enter number from above choices between 1 and 15 :";
    cin >> Number;
    while (cin.fail())

    {

        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "\t\t\t\tInvalid Number , Enter a valid one : ";
        cin >> Number;
    }
    return Number;
}


short ValidationTheNumber(short from, short to, short number)
{

    string num = to_string(number);

    while (number < from || number > to)
    {
        number = ReadNumber();
    }

    return number;
}

vector<string> LoadDataFromFile()
{
    fstream CommandFile;
    vector<string>Commands;

    CommandFile.open("CommandsFile.txt", ios::in);

    if (CommandFile.is_open())
    {
        string Line;
        while (getline(CommandFile, Line))
        {
            if (Line != "Exit") {
                Commands.push_back(Line);
            }
        }

        CommandFile.close();
    }

    return Commands;
}

void StoreCommandsInFile(string Command)
{
    fstream CommandFile;

    CommandFile.open("CommandsFile.txt", ios::app);

    if (CommandFile.is_open())
    {
        CommandFile << Command << endl;
        CommandFile.close();
    }
}

void CdCommandWorks(string& path, char storingPath[256])
{
    string dir;
    cout << "\t\t\t\tEnter directory: ";
    getline(cin >> ws, dir);
    _chdir(dir.c_str());
    path = _getcwd(storingPath, sizeof(storingPath));
}

void HistoryCommandWorks(vector<string> commandHistory)
{
    commandHistory = LoadDataFromFile();
    short count = 1;

    for (string& Commands : commandHistory)
    {
        cout << count << " " << Commands << endl;
        count++;
    }
}

void mkdirCommandWorks()
{
    string dir;
    cout << "\t\t\t\tEnter directory name: ";
    getline(cin >> ws, dir);
    string mkdir_command = "mkdir " + dir;
    system(mkdir_command.c_str());
}

void rmdirCommandWorks()
{
    string dir;
    cout << "\t\t\t\tEnter directory name: ";
    getline(cin >> ws, dir);
    string rmdir_command = "rmdir " + dir;
    system(rmdir_command.c_str());
}

void rmfileCommandWorks()
{
    string filename;
    cout << "\t\t\t\tEnter file name: ";
    getline(cin >> ws, filename);
    string rmfile_command = "del " + filename;
    system(rmfile_command.c_str());
}

void mvCommandWorks()
{
    string source, dest;
    cout << "\t\t\t\tEnter source file/directory: ";
    getline(cin >> ws, source);
    cout << "\t\t\t\tEnter destination: ";
    getline(cin >> ws, dest);
    string mv_command = "move " + source + " " + dest;
    system(mv_command.c_str());
}

void touchCommandWorks()
{
    string filename;
    cout << "\t\t\t\tEnter file name: ";
    getline(cin >> ws, filename);
    string touch_command = "type nul > " + filename;
    system(touch_command.c_str());
}

void createAndChange()
{
    string filename, content;
    cout << "\t\t\t\tEnter file name: ";
    getline(cin >> ws, filename);
    cout << "\t\t\t\tEnter content: ";
    getline(cin >> ws, content);
    ofstream file(filename);
    file << content;
    file.close();
}

void writeInFileWithSaveInfo()
{
    string filename, content;
    cout << "\t\t\t\tEnter file name: ";
    getline(cin >> ws, filename);
    cout << "\t\t\t\tEnter content: ";
    getline(cin >> ws, content);
    ofstream file(filename, ios::app);
    file << content;
    file.close();
}

void cpCommandWorks()
{
    string source, dest;
    cout << "\t\t\t\tEnter source file: ";
    getline(cin >> ws, source);
    cout << "\t\t\t\tEnter destination: ";
    getline(cin >> ws, dest);
    string cp_command = "copy " + source + " " + dest;
    system(cp_command.c_str());
}

void catCommandWorks()
{
    string filename;
    cout << "\t\t\t\tEnter file name: ";
    getline(cin >> ws, filename);
    string cat_command = "type " + filename;
    system(cat_command.c_str());
    cout << endl;
}

void MainMenueScreen()
{
    cout << "\n\t\t\t\t\t\tMani Menue Screen :\n";
    cout << "\t\t\t\t####################################################################\n";
    cout << "\t\t\t\t|Show The Current Pathe (pwd).....................................[1]\n";
    cout << "\t\t\t\t|Show Time And History (Date).....................................[2]\n";
    cout << "\t\t\t\t|Show The Current Volumes (ls)....................................[3]\n";
    cout << "\t\t\t\t|clear The Current terminal screen (clear)........................[4]\n";
    cout << "\t\t\t\t|change The Current directory (cd)................................[5]\n";
    cout << "\t\t\t\t|Keeps track of all commands written by the user (history)........[6]\n";
    cout << "\t\t\t\t|Creates Directories with each given name if do not exite (mkdir).[7]\n";
    cout << "\t\t\t\t|removes each given Emptey directory (rmdir)......................[8]\n";
    cout << "\t\t\t\t|Show the content of the text file (cat)..........................[9]\n";
    cout << "\t\t\t\t|create emptiy files (touch)......................................[10]\n";
    cout << "\t\t\t\t|remove file or directory empty (mv)..............................[11]\n";
    cout << "\t\t\t\t|create and change (>)............................................[12]\n";
    cout << "\t\t\t\t|Add information without delete old information (>>)..............[13]\n";
    cout << "\t\t\t\t|copy and paste (cp)..............................................[14]\n";
    cout << "\t\t\t\t|delete file (rmfile).............................................[15]\n";
    cout << "\t\t\t\t|to Exite From The Programe Enter Number..........................[16]\n";
    cout << "\t\t\t\t####################################################################\n";
}

int main()
{
    string command, Data;
    bool chick = true;
    vector < string > commandHistory;
    char storingPath[256];
    string path = _getcwd(storingPath, sizeof(storingPath));
    MainMenueScreen();

    do
    {

        short choice = ReadNumber();
        choice = ValidationTheNumber(1, 16, choice);
        string dir;
        command = returnCommandWord(choice);
        StoreCommandsInFile(command);

        switch (enCommands(choice))
        {
        case enCommands::AddWithSave:
            writeInFileWithSaveInfo();
            break;

        case enCommands::cat:
            catCommandWorks();
            break;

        case enCommands::cd:
            CdCommandWorks(path, storingPath);
            break;

        case enCommands::clear:
            system("cls");
            MainMenueScreen();
            break;

        case enCommands::cp:
            cpCommandWorks();
            break;

        case enCommands::ecreateAndChange:
            createAndChange();
            break;

        case enCommands::date:
            cout << DateAndTime() << endl;
            break;

        case enCommands::history:
            HistoryCommandWorks(commandHistory);
            break;

        case enCommands::ls:
            system("dir");
            break;

        case enCommands::emkdir:
            mkdirCommandWorks();
            break;

        case enCommands::mv:
            mvCommandWorks();
            break;

        case enCommands::pwd:
            system("chdir");
            break;

        case enCommands::ermdir:
            rmdirCommandWorks();
            break;

        case enCommands::rmfile:
            rmfileCommandWorks();
            break;

        case enCommands::touch:
            touchCommandWorks();
            break;

        case enCommands::Exite:
            chick = false;
            break;
        }


    } while (chick);


    return 0;
}