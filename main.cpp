#include <bits/stdc++.h>
using namespace std;

class User{
    private:
    // int userID;
    string username;
    string password;
    // char role;
    //file where all the users are stored
    static const string filename;
    protected:
    string name;
    public:
    //default constructor
    User(){}
    //parameterized constructor
    User(string uname,string pass){//,int usid,char r
        username=uname;
        password=pass;
        // userID=usid;
        // role=r;
    }
    //if the user is new then register them
    bool registerUser(){
        unordered_map<string,string>users=loadUsers();
        if(users.find(username)!=users.end()){
            cout<<"User already exists"<<endl;
            return false;
        }
        ofstream fout(filename,ios::app);
        if(!fout){
            cout<<"ERROR: could not open the file for writing"<<endl;
            return false;
        }
        fout<<username<<','<<password;
        fout.close();
        cout<<"Registration successful "<<endl;
        return true;
    }

    //for loging in the user
    bool loginUser(){
        unordered_map<string,string>users=loadUsers();
        auto it=users.find(username);
        if(it==users.end()){
            cout<<"No such user found."<<endl;
        }
        if(password==it->second){
            cout<<"login successfull !!"<<endl;
            cout<<"Welcome, "<<username<<endl;
        }else{
            cout<<"INCORECT password."<<endl;
            return false;
        }
    }


    //to load the users into the map
    static unordered_map<string,string>loadUsers(){
        unordered_map<string,string>mpp;
        ifstream fin(filename);
        if(!fin)return mpp;
        string line;
        while(getline(fin,line)){
            if(line.empty())continue;
            stringstream ss(line);
            string uname,pass;
            if(getline(ss,uname,',')&&getline(ss,pass)){
                mpp[uname]=pass;
            }
        }
        fin.close();
        return mpp;

    }
    
    
};
const string User::filename="users.csv";

int main() {
    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1: Register\n";
        cout << "2: Login\n";
        cout << "0: Exit\n";
        cout << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            string uname, pass;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);

            User newUser(uname, pass);
            newUser.registerUser();

        } else if (choice == "2") {
            string uname, pass;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);

            User loginAttempt(uname, pass);
            loginAttempt.loginUser();

        } else if (choice == "0") {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}