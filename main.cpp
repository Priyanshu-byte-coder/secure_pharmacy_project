#include <bits/stdc++.h>
using namespace std;



//for storing the userinfo 
struct userinfo{
    string password;
    string role;
};
class User{
    private:
    string username;
    string password;
    string role;
    //file where all the users are stored
    static const string filename;
    protected:
    string userID;
    string email;
    string phone;
    string name;
    bool isLoggedIn;
    public:
    //default constructor
    User():isLoggedIn(false){}
    //parameterized constructor
    User(string uname,string pass,string r,string n="",string e="",string p=""){
        username=uname;
        password=pass;
        role=r;
        name=n;
        email=e;
        phone=p;
        isLoggedIn=false;
        userID=generateUserID();
    }

    //it is a virutal fuction which will work differently for different users.
    virtual void displayMenu()=0;
    virtual bool performOperation(int choice)=0;

    virtual ~User(){}

    // getter fuctions
    string getUsername()const{return username;}
    string getPassword()const{return password;}
    string getRole()const{return role;}
    string getName()const{return name;}
    bool getLoginStatus()const{return isLoggedIn;}

    //for the userid generation
    //static variable to count the number of users of 3 types
    static int patientCounter;
    static int doctorCounter;
    static int chemistCounter;
    //static fuctions for ID generation 
    static string generateUserID(const string& role){
        if(role=="patient")return "P"+to_string(patientCounter++);
        else if(role=="doctor")return "D"+to_string(doctorCounter++);
        else return "C"+to_string(chemistCounter++);
    }
    //if the user is new then register them
    bool registerUser(){
        unordered_map<string,userinfo>users=loadUsers();
        if(users.find(username)!=users.end()){
            cout<<"User already exists"<<endl;
            return false;
        }
        ofstream fout(filename,ios::app);
        if(!fout){
            cout<<"ERROR: could not open the file for writing"<<endl;
            return false;
        }
        fout<<username<<','<<password<<','<<role<<','<<userID<<name<<email<<phone<<endl;
        fout.close();
        cout<<"Registration successful! your ID is: "<<userID<<endl;
        return true;
    }

    //for loging in the user
    bool loginUser(){
        unordered_map<string,userinfo>users=loadUsers();
        auto it=users.find(username);
        if(it==users.end()){
            cout<<"No such user found."<<endl;
            return false;
        }
        if(password==it->second.password&&role==it->second.role){
            cout<<"login successfull !!"<<endl;
            cout<<"Welcome, "<<username<<"(ID: "<<userID<<")"<<endl;
            isLoggedIn=true;
            return true;
        }else{
            cout<<"INCORECT password OR role"<<endl;
            return false;
        }
    }


    //to load the users into the map
    static unordered_map<string,userinfo>loadUsers(){
        unordered_map<string,userinfo>mpp;
        ifstream fin(filename);
        if(!fin)return mpp;
        string line;
        while(getline(fin,line)){
            if(line.empty())continue;
            stringstream ss(line);
            string uname,pass,role;
            if(getline(ss,uname,',')&&getline(ss,pass,',')&&getline(ss,role)){
                mpp[uname]={pass,role};
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
            string uname, pass,role;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);
            cout << "Enter role: ";
            getline(cin, role);

            User newUser(uname,pass,role);
            newUser.registerUser();

        } else if (choice == "2") {
            string uname, pass,role;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);
            cout << "Enter role: ";
            getline(cin, role);

            User loginAttempt(uname, pass,role);
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