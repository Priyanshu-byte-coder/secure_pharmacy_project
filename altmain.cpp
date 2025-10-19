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

    string generateUID(){
        if(role=="patient")return "P" + to_string(patientCounter++);
        else if(role=="doctor")return "D" + to_string(doctorCounter);
        else return "C" + to_string(chemistCounter);
    }
    public:

    static int patientCounter;
    static int doctorCounter;
    static int chemistCounter;

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
        userID=generateUID();
    }
    //loading existing users
    User(string uname,string pass,string r,string id,string n,string e,string p, bool loggedIn = false)
    : username(uname),password(pass),role(r),name(n),email(e),phone(p),isLoggedIn(loggedIn){}

    //it is a virutal fuction which will work differently for different users.
    virtual void displayMenu()=0;
    virtual bool performOperation(int choice)=0;

    virtual ~User(){}

    // getter fuctions
    string getUsername()const{return username;}
    string getRole()const{return role;}
    string getUserID() const {return userID;}

    
    //Register new user
    bool registerUser(){
        unordered_map<string,userinfo>users=loadUsers();
        if(users.find(username)!=users.end()){
            cout<<"User already exists."<<endl;
            return false;
        }
        ofstream fout(filename,ios::app);
        if(!fout.is_open()){
            cout<<"ERROR: could not open the file for writing"<<endl;
            return false;
        }
        fout<<username<<','<<password<<','<<role<<','<<userID<<','<<name<<','<<email<<','<<phone<<endl;
        fout.close();
        cout<<"Registration successful! Your ID is: "<<userID<<endl;
        return true;
    }

    //load uname/pass/role for login validation
    static unordered_map<string, userinfo> loadUsers() {
        unordered_map<string, userinfo> mpp;
        ifstream fin(filename);
        if (!fin.is_open()) return mpp;
        
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string uname, pass, role, junk;
            // Only need username, password, and role for validation
            if (getline(ss, uname, ',') && getline(ss, pass, ',') && getline(ss, role, ',')) {
                mpp[uname] = {pass, role};
            }
        }
        fin.close();
        return mpp;
    }


    //load full deets after successufull login
    static vector<string> loadFullUserDetails(const string& uname) {
        ifstream fin(filename);
        if (!fin.is_open()) return {};
        
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string part;
            vector<string> parts;
            while (getline(ss, part, ',')) {
                parts.push_back(part);
            }
            if (parts.size() >= 7 && parts[0] == uname) {
                fin.close();
                return parts; // {uname, pass, role, userID, name, email, phone}
            }
        }
        fin.close();
        return {};
    }
    
    
};


const string User::filename="users.csv";
// stat counter for uid gen, patient-1000,doc-2000,chem-3000
int User::patientCounter = 1000;
int User::doctorCounter = 2000;
int User::chemistCounter = 3000;

class Patient : public User {
    private:
        string prescriptionFilename;
        string appointmentFilename;
    public:
        Patient(string uname, string pass, string n="",string e="",string p="") : User(uname,pass,"patient",n,e,p){
            prescriptionFilename = userID + "_prescriptions.txt";
            appointmentFilename = userID + "_appointments.csv";
        }

        //existing user
        Patient(const vector<string>& details) 
        : User(details[0], details[1], details[2], details[3], details[4], details[5], details[6], true) {
        prescriptionFilename = userID + "_prescriptions.txt";
        appointmentFilename = userID + "_appointments.csv";
    }

        void displayMenu() override {
        cout << "\n--- Patient Menu ---\n";
        cout << "1: View Medical Records\n";
        cout << "2: View Prescriptions\n";
        cout << "3: Book Appointment\n"; 
        cout << "0: Logout\n";
        cout << "Choice: ";
    }
    bool performOperation(int choice) override {
        switch (choice) {
            case 1:
                cout << "Displaying medical records (Not Implemented)...\n";
                return true;
            case 2:
                viewPrescription();
                return true;
            case 3:
                bookAppointment();
                return true;
            case 0:
                cout << "Logging out...\n";
                return false;
            default:
                cout << "Invalid choice for Patient. Try again.\n";
                return true; 
        }
    }

    void viewPrescription() {
        cout << "\n--- Viewing Prescriptions (" << userID << ") ---\n";
        ifstream fin(prescriptionFilename);
        
        if (!fin.is_open()) {
            cout << "No prescriptions found. File: " << prescriptionFilename << endl;
            return;
        }

        string line;
        cout << "------------------------------------------\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        cout << "------------------------------------------\n";
        fin.close();
    }

    void bookAppointment() {
        string doctorID, date, reason;
        
        cout << "\n--- Book New Appointment ---\n";
        cout << "Enter Doctor ID (e.g., D2001): ";
        getline(cin, doctorID);
        cout << "Enter Desired Date (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter Reason for Appointment: ";
        getline(cin, reason);

        //open appmn file for appending
        ofstream fout(appointmentFilename, ios::app); 
        
        if (!fout.is_open()) {
            cout << "ERROR: Could not open the appointment file.\n";
            return;
        }

        //write request
        fout << userID << "," << doctorID << "," << date << "," << reason << ",PENDING" << endl;
        fout.close();
        
        cout << "\nAppointment request successfully submitted!\n";
        cout << "Status: PENDING confirmation from Doctor " << doctorID << ".\n";
    }
};

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