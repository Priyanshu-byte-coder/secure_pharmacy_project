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


    void bookAppointment() { //half chatgpt
        string doctorID, date, reason;
        
        cout << "\n--- Book New Appointment ---\n";
        cout << "Enter Doctor ID (e.g., D2000): ";
        getline(cin, doctorID);
        cout << "Enter Desired Date (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter Reason for Appointment: ";
        getline(cin, reason);

        if (doctorID.length() < 5 || doctorID[0] != 'D') {
             cout << "Invalid Doctor ID format. Must start with 'D' (e.g., D2000).\n";
             return;
        }
        
        // patient history (chatgpt idea)
        ofstream fout(appointmentFilename, ios::app); 
        if (!fout.is_open()) {
            cout << "ERROR: Could not open patient appointment file: " << appointmentFilename << endl;
            return;
        }
        fout << userID << "," << doctorID << "," << date << "," << reason << ",PENDING" << endl;
        fout.close();
        
        // doctor ke inbox mai jayega (chatgpt)
        string doctorInboxFilename = doctorID + "_inbox.csv";
        ofstream docFout(doctorInboxFilename, ios::app);
        
        if (docFout.is_open()) {
            docFout << userID << "," << doctorID << "," << date << "," << reason << ",PENDING" << endl;
            docFout.close();
            cout << "\nAppointment request successfully submitted!\n";
            cout << "Status: PENDING confirmation from Doctor " << doctorID << ".\n";
        } else {
             cout << "WARNING: Could not open Doctor's inbox file: " << doctorInboxFilename << endl;
             cout << "Appointment submitted to your history, but may not show up in doctor's inbox.\n";
        }
    }
};

class Doctor : public User {
    private:
        string inboxFilename;
    public:
        // Constructor for NEW registration
        Doctor(string uname, string pass, string n="", string e="", string p="")
            : User(uname, pass, "doctor", n, e, p){
            inboxFilename = userID + "_inbox.csv";
        }
        
        // Constructor for EXISTING user login
        Doctor(const vector<string>& details) 
            : User(details[0], details[1], details[2], details[3], details[4], details[5], details[6], true) {
            inboxFilename = userID + "_inbox.csv";
        }

        void displayMenu() override {
            cout << "\n--- Doctor Menu (ID: " << userID << ") ---\n";
            cout << "1: View Appointment Requests\n";
            cout << "2: Write Prescription\n";
            cout << "0: Logout\n";
            cout << "Choice: ";
        }
        
        bool performOperation(int choice) override {
            switch (choice) {
                case 1:
                    viewAppointmentRequests();
                    return true;
                case 2:
                    writePrescription();
                    return true;
                case 0:
                    cout << "Logging out...\n";
                    return false;
                default:
                    cout << "Invalid choice for Doctor. Try again.\n";
                    return true;
            }
        }
        
        void viewAppointmentRequests() {  //half chatgpt
            cout << "\n--- Appointment Requests (Inbox: " << userID << ") ---\n";
            ifstream fin(inboxFilename);
            
            if (!fin.is_open()) {
                cout << "No pending appointment requests in your inbox. File: " << inboxFilename << endl;
                return;
            }
            
            string line;
            int count = 0;
            
            // simple table
            cout << "------------------------------------------------------------------------\n";
            cout << "Patient ID | Date       | Reason (First 20 Chars) | Status\n";
            cout << "------------------------------------------------------------------------\n";
            
            while (getline(fin, line)) {
                stringstream ss(line);
                string patientID, doctorID, date, reason, status;
                
                if (getline(ss, patientID, ',') && 
                    getline(ss, doctorID, ',') && 
                    getline(ss, date, ',') && 
                    getline(ss, reason, ',') && 
                    getline(ss, status)) 
                {
                    //truncate reason
                    string displayReason = reason.length() > 20 ? reason.substr(0, 17) + "..." : reason;

                    cout << patientID << " | " 
                         << date << " | " 
                         << displayReason << " | "
                         << status << endl;
                    count++;
                }
            }
            cout << "------------------------------------------------------------------------\n";
            fin.close();
            
            if (count == 0) {
                cout << "You have no PENDING appointment requests.\n";
            } else {
                cout << count << " PENDING requests found. (Note: Confirmation/management logic not implemented).\n";
            }
        }

        void writePrescription() {
            string patientID;
            cout << "\n--- Write New Prescription ---\n";
            cout << "Enter Patient ID (e.g., P1000): ";
            getline(cin, patientID);
            
            string prescriptionFilename = patientID + "_prescriptions.txt";
            
            if (patientID.length() < 5 || patientID[0] != 'P') {
                cout << "Invalid Patient ID format. Must start with 'P' (e.g., P1000).\n";
                return;
            }

            string medicine, dosage, notes;
            cout << "Enter Medicine Name: ";
            getline(cin, medicine);
            cout << "Enter Dosage Instructions: ";
            getline(cin, dosage);
            cout << "Enter Notes/Duration: ";
            getline(cin, notes);
            
            //date (chatgpt)
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char dateBuffer[11];
            strftime(dateBuffer, 11, "%Y-%m-%d", ltm);
            string currentDate(dateBuffer);

            ofstream fout(prescriptionFilename, ios::app);
            if (!fout.is_open()) {
                cout << "ERROR: Could not open prescription file for Patient ID: " << patientID << endl;
                return;
            }

            fout << "Date: " << currentDate << endl;
            fout << "Doctor ID: " << userID << endl;
            fout << "Medicine: " << medicine << endl;
            fout << "Dosage: " << dosage << endl;
            fout << "Notes: " << notes << endl;
            fout << "--- End of Prescription ---\n";
            fout.close();

            cout << "\nPrescription successfully written to file: " << prescriptionFilename << endl;
        }
};

class Chemist : public User {
    public:
        Chemist(string uname, string pass, string n="", string e="", string p="")
            : User(uname, pass, "chemist", n, e, p){}
        
        Chemist(const vector<string>& details) 
            : User(details[0], details[1], details[2], details[3], details[4], details[5], details[6], true) {}

        void displayMenu() override {
            cout << "\n--- Chemist Menu (ID: " << userID << ") ---\n";
            cout << "1: Process Prescription (Simulated)\n";
            cout << "0: Logout\n";
            cout << "Choice: ";
        }
        
        bool performOperation(int choice) override {
            switch (choice) {
                case 1:
                    processPrescription();
                    return true;
                case 0:
                    cout << "Logging out...\n";
                    return false;
                default:
                    cout << "Invalid choice for Chemist. Try again.\n";
                    return true;
            }
        }

        void processPrescription() {
            string patientID;
            cout << "\n--- Process Prescription ---\n";
            cout << "Enter Patient ID to check for prescription (e.g., P1000): ";
            getline(cin, patientID);

            
            string prescriptionFilename = patientID + "_prescriptions.txt";
            ifstream fin(prescriptionFilename);
            
            if (fin.is_open()) {
                cout << "Prescription found for Patient " << patientID << ". Dispensing medication...\n";
                cout << "Process completed. (File content not displayed for simplicity).\n";
                fin.close();
            } else {
                cout << "No prescription found for Patient " << patientID << " in file: " << prescriptionFilename << endl;
            }
        }
};

//helper func, keep user in loop(chatgpt)
void runUserSession(User* user) {
    bool keepRunning = true;
    while (keepRunning) {
        user->displayMenu();
        string choiceStr;
        getline(cin, choiceStr);
        try {
            int choice = stoi(choiceStr);
            keepRunning = user->performOperation(choice);
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

int main() {


    ofstream usersFile("users.csv", ios::app);
    if (usersFile.is_open() && usersFile.tellp() == 0) {
        usersFile << "docuser,docpass,doctor,D2000,Dr. Smith,doc@hospital.com,5551234\n"; 
        usersFile << "patuser,patpass,patient,P1000,Jane Doe,jane@home.com,5555678\n";
        // update counters, from last uid
        User::doctorCounter = 2001; 
        User::patientCounter = 1001;
        usersFile.close();
    }


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

            User* newUser = nullptr;
            if(role=="patient"){
                newUser = new Patient(uname,pass);
            }
            else if(role=="doctor"){
                newUser = new Doctor(uname, pass);
            }
            else{
                newUser = new Chemist(uname,pass,role);
            }

          

            } else if (choice == "2") {
            string uname, pass,role;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);
            cout << "Enter role: ";
            getline(cin, role);

            unordered_map<string, userinfo> users = User::loadUsers();
            auto it = users.find(uname);

            // authenticate
            if (it == users.end() || it->second.role != role || it->second.password != pass) {
                cout << "Login failed. Check username, password, and role.\n";
                continue;
            }

            vector<string> details = User::loadFullUserDetails(uname);
            User* currentUser = nullptr;

            if (details.empty()) {
                cout << "Error: User details corrupted or not found in data file.\n";
                continue;
            }

            // polymorphism based on role
            if (role == "patient") {
                currentUser = new Patient(details);
            } else if (role == "doctor") {
                currentUser = new Doctor(details);
            } else (role == "chemist") {
                currentUser = new Chemist(details);
            }
            
            cout << "Login successful! Welcome, " << currentUser->getUsername() << ".\n";
            
            runUserSession(currentUser);

            delete currentUser; 
            
        } else if (choice == "0") {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
