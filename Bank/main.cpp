#include <iostream>  /// Basic input and output library.
#include <conio.h>   /// Found online. Used in getch() function to store chars without displaying them "Passwords".
#include <sstream>   /// Found online. Used to convert for int to string.
#include <string>    /// Used to handle string methods.
#include <fstream>   /// Used to handle text files to store data in them.

/**
*   This Program will handle a simple BANK system
*   Will Handle 2 basic users (admin,employee)
*   Will allow to store accounts data in DOC file ---> only admin is allowed to view them
*   store clients data 1-ID 2-name 3-age 4-city 5-password 6-balance 7-creation date
*/

using namespace std;

void mainframe();       ///Show the mainframe of the BANK.
string password(bool x); /// enter or create password.
void History_Accounts(string [][7], int); ///
int Create_Account(string [][7]);
void view_Data();  ///View Accounts Data.
void Employee(); ///Return to Employee Privileges.

string accounts[100][7] = {{"10001","client 1","age 1","city 1","pass 1","balance 1","date 1"},  ///Initialize to show data
                               {"10002","client 2","age 2","city 2","pass 2","balance 2","date 2"},  ///in DOC file
                               {"10003","client 3","age 3","city 3","pass 3","balance 3","date 3"}}; /// and pick new ID
///Put out of main to be PUPLIC " Seen by all Functions ".

int main()
{
    History_Accounts(accounts,0);
    History_Accounts(accounts,1); ///store in .DOC file
    History_Accounts(accounts,2);
    char check;
    do
    {
        mainframe();
        cout << endl << endl;
        cout << "WOULD YOU LIKE TO GO BACK TO THE MAINFRAME ?! ( Y / N ) \nChoice ---> ";
        cin >> check;
    } while (check == 'Y' || check == 'y');
    cout << endl << endl;
    cout << "THANKS FOR USING THE PROGRAME \nMADE BY MUHAMMAD KASSAB (SECTION 3)" << endl;
    return 0;
}

void mainframe()
{
    int choice;
    char check;
    string x = "admin" , emp[3] = {"emp1","emp2","emp3"};
    cout << "\t\tWelcome to X Bank Mainframe : " << endl;
    cout << "\nPICK AN OPTION! \n( 1 ) for Administrator Privileges. \n( 2 ) for Employee Privileges.\nChoice ---> ";
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "ENTER A VALID CHOICE!";
        cin >> choice;
    }
    if (choice == 1)
    {
        string admin = password(1);
        while (admin != x)
        {
            cout << "\nINCORRECT PASSWORD!!!" << endl;
            admin = password(1);
        }
        cout << "\n\t\tWELCOME ADMIN" << endl;
        cout << "TO VIEW FULL ACCOUNTS DATA PRESS 'Y' \nEntry = ";
        cin >> check;
        if (check =='Y' || check == 'y')
            view_Data();
        else
        {
            cout << "\t\t<ERROR>GOING BACK TO MAINFRAME\n\n" << endl;
            mainframe();  ///Recursive call due to error in entry
        }
    }
    else
    {
        string employee = password(1);
        while (employee != emp[0] && employee != emp[1] && employee != emp[2])
        {
            cout << "\nINCORRECT PASSWORD!!!" << endl;
            employee = password(1);
        }
        Employee();
    }
}

void Employee()
{
    int check;
    string x;
    cout << "\n\t\tWELCOME EMPLOYEE" << endl;
    cout << "PICK AN OPTION. \n( 1 ) Create New Account \n( 2 ) View Account's balance \nChoice ---> ";
    cin >> check;
    while (check != 1 && check != 2)
    {
        cout << "ENTER A VALID CHOICE!" << endl; cin >> check;
    }
    if (check == 1)
        {
            int y = Create_Account(accounts); ///y refers to the index which this new account is stored at
            History_Accounts(accounts,y);
        }
    else
    {
        cout << "ENTER ID : ";
        cin >> x;
        for (int i = 0; i < 100; i++)
        {
            if (accounts[i][0] == x)
            {
                cout << "BALANCE = " << accounts[i][5] << endl;
            }
        }
    }
    cout << "CONTINUE ?! ( Y / N )";
    cin >> x;
    if (x == "Y" || x == "y")
        Employee();
}

string password(bool x)
{
    if (x == 0) cout << "Enter a password : 'min. 6 chars & max. 15 chars" << endl;  ///x=0 means creating new pass
    else cout << "Enter The Password : ";
    char temp;
    string pass = "";
    for (int i = 0; i < 25; )
    {
        temp = getch();
        if ( (temp>='a' && temp<='z') || (temp>='A' && temp<='Z') || (temp>='0' && temp<='9'))
        {
            if (pass.length() == i) pass += temp;
            else pass.at(i) = temp;
            ++i;
            cout << "*";
        }
        if (temp == '\b')
        {
            cout << "\b \b";
            if (i > 0) --i;
        }
        if (temp == '\r') break;
    }
    if (x == 0) if (pass.length() < 6 || pass.length() > 25)
    {
        cout << endl;
        cout << "Enter a password within the conditions!!" << endl;
        password(0); /// Recursive Call
    }
    return pass;
}


void History_Accounts(string arr[][7], int x)
{
    fstream account;
    account.open("Accounts.doc", ios::out | ios::app); ///opens or create .doc file to store data in
    account << "Account ( " << x+1 << " )  \n";
    account << "ID            : " << arr[x][0] << "\n";
    account << "Name          : " << arr[x][1] << "\n";
    account << "Age           : " << arr[x][2] << "\n";
    account << "City          : " << arr[x][3] << "\n";
    account << "Password      : " << arr[x][4] << "\n";
    account << "Balance       : " << arr[x][5] << "\n";
    account << "Creation Date : " << arr[x][6] << "\n";
    account.close();
}


int Create_Account(string arr[][7])
{
    long int id = 10001, account , balance;
    char check;
    string name;
    stringstream x;
    if ( arr[0][0] == "" ) {account = 1; arr[0][0] = "10001";}
    else
        for (int i = 1; i < 100; i++)
        {
            id++;
            if (arr[i][0] == "")
            {
                x << id;
                account = i+1;
                arr[i][0] = x.str();
                break;
            }
        }
    ///1-ID 2-name 3-age 4-city 5-password 6-balance 7-creation date
    cout << "<IMPORTANT> CLIENT'S ID IS      : " << arr[account-1][0] << endl;
    cout << "Enter the client's Name (FULL)  : "; getline(cin,name);
    getline(cin,name);
    arr[account-1][1] = name;
    cout << "Enter the client's Age          : "; cin >> arr[account-1][2];
    cout << "Enter the client's City         : "; cin >> arr[account-1][3];
    cout << "Enter the Creation date (YEAR)  : "; cin >> arr[account-1][6];
    cout << "Allow client to enter a Password for the Account : " << endl;
    arr[account-1][4] = password(0);
    cout << "\nCreation Fee = 15$. \nWould you like to deposit ?! (YES / NO) \nChoice ---> ";
    cin >> check;
    if (check == 'Y' || check == 'y')
    {
        cout << "How much would you like to deposit ? ";
        cin >> arr[account-1][5];
    }
    else arr[account-1][5] = "0";
    return account-1;
}

void view_Data()
{
    fstream show;
    string line;
    show.open("Accounts.doc", ios::in);
    while (!show.eof())  ///as long it's not the end of file it keeps printing what's in it
    {
        getline(show,line);
        cout << line << endl;
    }
}


