#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>
#include <direct.h>
using namespace std;

// ==================== STRUCTURES ====================

struct userinfo {
    string password;
    string role;
};

// ==================== UTILITY FUNCTIONS ====================

string getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void createDirectory(const string& path) {
    _mkdir(path.c_str());
}

// ==================== MEDICINE CLASS ====================

class Medicine {
private:
    string medicineID;
    string name;
    bool isOTC;
    int quantity;
    string dosage;

public:
    Medicine() : isOTC(false), quantity(0) {}
    Medicine(string id, string n, bool otc, int qty, string dose)
        : medicineID(id), name(n), isOTC(otc), quantity(qty), dosage(dose) {}
    
    string getMedicineID() const { return medicineID; }
    string getName() const { return name; }
    bool getIsOTC() const { return isOTC; }
    int getQuantity() const { return quantity; }
    string getDosage() const { return dosage; }
    
    void setMedicineID(string id) { medicineID = id; }
    void setName(string n) { name = n; }
    void setIsOTC(bool otc) { isOTC = otc; }
    void setQuantity(int qty) { quantity = qty; }
    void setDosage(string dose) { dosage = dose; }
    
    friend ostream& operator<<(ostream& os, const Medicine& med) {
        os << "ID: " << med.medicineID << ", Name: " << med.name 
           << ", Type: " << (med.isOTC ? "OTC" : "Non-OTC") 
           << ", Qty: " << med.quantity << ", Dosage: " << med.dosage;
        return os;
    }
};

// ==================== BASE USER CLASS ====================

class User {
private:
    string username;
    string password;
    string role;
    static const string filename;

protected:
    string userID;
    string email;
    string phone;
    string name;
    bool isLoggedIn;
    
    string generateUserID() {
        if (role == "patient") return "P" + to_string(patientCounter++);
        else if (role == "doctor") return "D" + to_string(doctorCounter++);
        else return "C" + to_string(chemistCounter++);
    }

public:
    static int patientCounter;
    static int doctorCounter;
    static int chemistCounter;
    
    User() : isLoggedIn(false) {}
    User(string uname, string pass, string r, string n = "", string e = "", string p = "")
        : username(uname), password(pass), role(r), name(n), email(e), phone(p), isLoggedIn(false) {
        userID = generateUserID();
    }
    User(string uname, string pass, string r, string id, string n, string e, string p)
        : username(uname), password(pass), role(r), userID(id), name(n), email(e), phone(p), isLoggedIn(false) {}
    
    virtual void displayMenu() = 0;
    virtual bool performOperation(int choice) = 0;
    virtual ~User() {}
    
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getName() const { return name; }
    string getUserID() const { return userID; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    bool getLoginStatus() const { return isLoggedIn; }
    void setLoginStatus(bool status) { isLoggedIn = status; }
    
    bool registerUser() {
        unordered_map<string, userinfo> users = loadUsers();
        if (users.find(username) != users.end()) {
            cout << "User already exists." << endl;
            return false;
        }
        ofstream fout(filename, ios::app);
        if (!fout) {
            cout << "ERROR: Could not open file for writing." << endl;
            return false;
        }
        fout << username << "," << password << "," << role << "," << userID << endl;
        fout.close();
        cout << "\n=== Registration Successful! ===" << endl;
        cout << "Your User ID: " << userID << endl;
        return true;
    }
    
    static unordered_map<string, userinfo> loadUsers() {
        unordered_map<string, userinfo> mpp;
        ifstream fin(filename);
        if (!fin) return mpp;
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string uname, pass, role, id;
            if (getline(ss, uname, ',') && getline(ss, pass, ',') && 
                getline(ss, role, ',') && getline(ss, id, ',')) {
                mpp[uname] = {pass, role};
            }
        }
        fin.close();
        return mpp;
    }
    
    static vector<string> loadFullUserDetails(const string& uname) {
        ifstream fin(filename);
        if (!fin) return {};
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string part;
            vector<string> parts;
            while (getline(ss, part, ',')) {
                parts.push_back(part);
            }
            if (parts.size() >= 4 && parts[0] == uname) {
                fin.close();
                return parts;
            }
        }
        fin.close();
        return {};
    }
    
    void logout() {
        isLoggedIn = false;
        cout << "Logged out successfully." << endl;
    }
};

const string User::filename = "users.csv";
int User::patientCounter = 1000;
int User::doctorCounter = 2000;
int User::chemistCounter = 3000;
// PART 2: Patient, Doctor, Chemist Classes

// ==================== PATIENT CLASS ====================

class Patient : public User {
private:
    string address;
    string emergencyContact;
    string patientDataFile;
    
    void createPatientDataFile() {
        createDirectory("patient_data");
        patientDataFile = "patient_data/" + userID + "_data.csv";
        ifstream checkFile(patientDataFile);
        if (!checkFile.good()) {
            ofstream fout(patientDataFile);
            if (fout) {
                fout << "=== PATIENT PERSONAL INFORMATION ===" << endl;
                fout << "Name," << name << endl;
                fout << "UserID," << userID << endl;
                fout << "Email," << email << endl;
                fout << "Phone," << phone << endl;
                fout << "Address," << address << endl;
                fout << "EmergencyContact," << emergencyContact << endl;
                fout << "\n=== MEDICAL HISTORY ===" << endl;
                fout << "\n=== PRESCRIPTIONS ===" << endl;
                fout.close();
            }
        }
        checkFile.close();
    }

public:
    Patient(string uname, string pass, string n, string e, string p, string addr, string emergency)
        : User(uname, pass, "patient", n, e, p), address(addr), emergencyContact(emergency) {
        createPatientDataFile();
    }
    
    Patient(const vector<string>& details, string addr = "", string emergency = "")
        : User(details[0], details[1], details[2], details[3], "", "", ""), 
          address(addr), emergencyContact(emergency) {
        patientDataFile = "patient_data/" + userID + "_data.csv";
    }
    
    void displayMenu() override {
        cout << "\n========================================"<< endl;
        cout << "   PATIENT MENU (" << getUserID() << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. View My Complete Medical Records" << endl;
        cout << "2. View My Prescriptions Only" << endl;
        cout << "3. View Prescription Status" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Choice: ";
    }
    
    bool performOperation(int choice) override {
        switch (choice) {
            case 1: viewCompleteData(); return true;
            case 2: viewPrescriptions(); return true;
            case 3: viewPrescriptionStatus(); return true;
            case 0: cout << "Logging out..." << endl; return false;
            default: cout << "Invalid choice." << endl; return true;
        }
    }
    
    void viewCompleteData() {
        cout << "\n========================================"<< endl;
        cout << "   MY COMPLETE MEDICAL RECORDS" << endl;
        cout << "========================================" << endl;
        ifstream fin(patientDataFile);
        if (!fin) { cout << "No data found." << endl; return; }
        string line;
        while (getline(fin, line)) cout << line << endl;
        fin.close();
        cout << "========================================" << endl;
    }
    
    void viewPrescriptions() {
        cout << "\n========================================"<< endl;
        cout << "        MY PRESCRIPTIONS" << endl;
        cout << "========================================" << endl;
        ifstream fin(patientDataFile);
        if (!fin) { cout << "No prescriptions." << endl; return; }
        string line;
        bool inPrescriptionSection = false;
        while (getline(fin, line)) {
            if (line.find("=== PRESCRIPTIONS ===") != string::npos) {
                inPrescriptionSection = true;
                continue;
            }
            if (inPrescriptionSection) cout << line << endl;
        }
        fin.close();
        cout << "========================================" << endl;
    }
    
    void viewPrescriptionStatus() {
        cout << "\n========================================"<< endl;
        cout << "      PRESCRIPTION STATUS" << endl;
        cout << "========================================" << endl;
        string statusFile = "prescriptions/" + userID + "_status.csv";
        ifstream fin(statusFile);
        if (!fin) { cout << "No status records." << endl; return; }
        cout << left << setw(18) << "Prescription ID" << setw(25) << "Medicine" 
             << setw(12) << "Quantity" << setw(15) << "Status" << endl;
        cout << string(70, '-') << endl;
        string line;
        while (getline(fin, line)) cout << line << endl;
        fin.close();
        cout << "========================================" << endl;
    }
    
    friend class Doctor;
};

// ==================== DOCTOR CLASS ====================

class Doctor : public User {
private:
    string specialization;
    string licenseNumber;
    static int prescriptionCounter;
    
    string generatePrescriptionID() {
        return "RX" + to_string(prescriptionCounter++);
    }

public:
    Doctor(string uname, string pass, string n, string e, string p, string spec, string license)
        : User(uname, pass, "doctor", n, e, p), specialization(spec), licenseNumber(license) {}
    
    Doctor(const vector<string>& details, string spec = "", string license = "")
        : User(details[0], details[1], details[2], details[3], "", "", ""),
          specialization(spec), licenseNumber(license) {}
    
    void displayMenu() override {
        cout << "\n========================================"<< endl;
        cout << "   DOCTOR MENU (" << getUserID() << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. View Patient Data (Full Access)" << endl;
        cout << "2. Write Prescription" << endl;
        cout << "3. Update Patient Medical History" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Choice: ";
    }
    
    bool performOperation(int choice) override {
        switch (choice) {
            case 1: viewPatientData(); return true;
            case 2: writePrescription(); return true;
            case 3: updateMedicalHistory(); return true;
            case 0: cout << "Logging out..." << endl; return false;
            default: cout << "Invalid choice." << endl; return true;
        }
    }
    
    void viewPatientData() {
        string patientID;
        cout << "\nEnter Patient ID (e.g., P1000): ";
        getline(cin, patientID);
        string patientFile = "patient_data/" + patientID + "_data.csv";
        ifstream fin(patientFile);
        if (!fin) { cout << "Patient not found!" << endl; return; }
        cout << "\n========================================"<< endl;
        cout << "   PATIENT DATA: " << patientID << endl;
        cout << "========================================" << endl;
        string line;
        while (getline(fin, line)) cout << line << endl;
        fin.close();
        cout << "========================================" << endl;
    }
    
    void writePrescription() {
        string patientID;
        cout << "\n=== WRITE NEW PRESCRIPTION ===" << endl;
        cout << "Enter Patient ID: ";
        getline(cin, patientID);
        string patientFile = "patient_data/" + patientID + "_data.csv";
        ifstream checkFile(patientFile);
        if (!checkFile.good()) {
            cout << "ERROR: Patient not found!" << endl;
            checkFile.close();
            return;
        }
        checkFile.close();
        
        string prescriptionID = generatePrescriptionID();
        cout << "\nPrescription ID: " << prescriptionID << endl;
        cout << "Date: " << getCurrentDateTime() << endl;
        
        vector<Medicine> medicines;
        char addMore = 'y';
        
        while (addMore == 'y' || addMore == 'Y') {
            Medicine med;
            cout << "\n--- Adding Medicine ---" << endl;
            cout << "Enter Medicine Name: ";
            string medName;
            getline(cin, medName);
            med.setName(medName);
            
            cout << "Is this OTC medicine? (1=Yes, 0=No): ";
            string otcInput;
            getline(cin, otcInput);
            med.setIsOTC(otcInput == "1");
            
            cout << "Enter Quantity: ";
            string qtyStr;
            getline(cin, qtyStr);
            med.setQuantity(stoi(qtyStr));
            
            cout << "Enter Dosage Instructions: ";
            string doseInst;
            getline(cin, doseInst);
            med.setDosage(doseInst);
            
            med.setMedicineID("MED" + to_string(rand() % 10000));
            medicines.push_back(med);
            
            cout << "\nAdd another medicine? (y/n): ";
            cin >> addMore;
            cin.ignore();
        }
        
        ofstream fout(patientFile, ios::app);
        if (fout) {
            fout << "\n--- Prescription ID: " << prescriptionID << " ---" << endl;
            fout << "Date: " << getCurrentDateTime() << endl;
            fout << "Doctor ID: " << getUserID() << endl;
            fout << "Medicines Prescribed:" << endl;
            for (const auto& med : medicines) {
                fout << "  - " << med.getName() << " (" << (med.getIsOTC() ? "OTC" : "Non-OTC") 
                     << "), Qty: " << med.getQuantity() << ", Dosage: " << med.getDosage() << endl;
            }
            fout << "Status: PENDING DISPENSING" << endl;
            fout << "--- End of Prescription ---" << endl;
            fout.close();
        }
        
        createDirectory("prescriptions");
        string prescriptionFile = "prescriptions/" + prescriptionID + ".csv";
        ofstream prescFout(prescriptionFile);
        if (prescFout) {
            prescFout << "PrescriptionID," << prescriptionID << endl;
            prescFout << "PatientID," << patientID << endl;
            prescFout << "DoctorID," << getUserID() << endl;
            prescFout << "Date," << getCurrentDateTime() << endl;
            prescFout << "Status,PENDING" << endl;
            prescFout << "\nMedicines:" << endl;
            prescFout << "MedicineID,Name,Type,Quantity,Dosage" << endl;
            for (const auto& med : medicines) {
                prescFout << med.getMedicineID() << "," << med.getName() << "," 
                         << (med.getIsOTC() ? "OTC" : "Non-OTC") << "," 
                         << med.getQuantity() << "," << med.getDosage() << endl;
            }
            prescFout.close();
        }
        
        string statusFile = "prescriptions/" + patientID + "_status.csv";
        ofstream statusFout(statusFile, ios::app);
        if (statusFout) {
            for (const auto& med : medicines) {
                statusFout << left << setw(18) << prescriptionID << setw(25) << med.getName() 
                          << setw(12) << med.getQuantity() << setw(15) << "PENDING" << endl;
            }
            statusFout.close();
        }
        
        cout << "\n*** Prescription written successfully! ***" << endl;
    }
    
    void updateMedicalHistory() {
        string patientID;
        cout << "\n=== UPDATE MEDICAL HISTORY ===" << endl;
        cout << "Enter Patient ID: ";
        getline(cin, patientID);
        string patientFile = "patient_data/" + patientID + "_data.csv";
        ifstream checkFile(patientFile);
        if (!checkFile.good()) {
            cout << "ERROR: Patient not found!" << endl;
            checkFile.close();
            return;
        }
        checkFile.close();
        
        cout << "Enter Medical History Entry: ";
        string historyEntry;
        getline(cin, historyEntry);
        
        ifstream fin(patientFile);
        vector<string> lines;
        string line;
        while (getline(fin, line)) {
            lines.push_back(line);
            if (line.find("=== MEDICAL HISTORY ===") != string::npos) {
                lines.push_back(getCurrentDateTime() + ": " + historyEntry + " (Dr. " + getUserID() + ")");
            }
        }
        fin.close();
        
        ofstream fout(patientFile);
        for (const auto& l : lines) fout << l << endl;
        fout.close();
        cout << "\n*** Medical history updated! ***" << endl;
    }
    
    void viewMyPrescriptions() {
        cout << "\n========================================"<< endl;
        cout << "      MY PRESCRIPTIONS" << endl;
        cout << "========================================" << endl;
        cout << "Feature: View all prescriptions written by this doctor" << endl;
        cout << "Check prescriptions/ folder for details" << endl;
        cout << "========================================" << endl;
    }
};

int Doctor::prescriptionCounter = 1000;

// ==================== CHEMIST CLASS ====================

class Chemist : public User {
private:
    string pharmacyLicense;
    string pharmacyName;

public:
    Chemist(string uname, string pass, string n, string e, string p, string license, string pharmName)
        : User(uname, pass, "chemist", n, e, p), pharmacyLicense(license), pharmacyName(pharmName) {}
    
    Chemist(const vector<string>& details, string license = "", string pharmName = "")
        : User(details[0], details[1], details[2], details[3], "", "", ""),
          pharmacyLicense(license), pharmacyName(pharmName) {}
    
    void displayMenu() override {
        cout << "\n========================================"<< endl;
        cout << "   CHEMIST MENU (" << getUserID() << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. View Prescription (Medicine Data Only)" << endl;
        cout << "2. Dispense Medicine" << endl;
        cout << "3. View Dispensing History" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Choice: ";
    }
    
    bool performOperation(int choice) override {
        switch (choice) {
            case 1: viewPrescription(); return true;
            case 2: dispenseMedicine(); return true;
            case 3: viewDispensingHistory(); return true;
            case 0: cout << "Logging out..." << endl; return false;
            default: cout << "Invalid choice." << endl; return true;
        }
    }
    
    void viewPrescription() {
        string prescriptionID;
        cout << "\n=== VIEW PRESCRIPTION ===" << endl;
        cout << "Enter Prescription ID (e.g., RX1000): ";
        getline(cin, prescriptionID);
        string prescFile = "prescriptions/" + prescriptionID + ".csv";
        ifstream fin(prescFile);
        if (!fin) {
            cout << "ERROR: Prescription not found!" << endl;
            return;
        }
        cout << "\n========================================"<< endl;
        cout << "   PRESCRIPTION: " << prescriptionID << endl;
        cout << "========================================" << endl;
        string line;
        bool showLine = false;
        while (getline(fin, line)) {
            if (line.find("PrescriptionID,") != string::npos || 
                line.find("Date,") != string::npos || 
                line.find("Status,") != string::npos) {
                cout << line << endl;
            }
            if (line.find("Medicines:") != string::npos) showLine = true;
            if (showLine) cout << line << endl;
        }
        fin.close();
        cout << "========================================" << endl;
        cout << "NOTE: Patient personal info is hidden." << endl;
    }
    
    void dispenseMedicine() {
        string prescriptionID;
        cout << "\n=== DISPENSE MEDICINE ===" << endl;
        cout << "Enter Prescription ID: ";
        getline(cin, prescriptionID);
        string prescFile = "prescriptions/" + prescriptionID + ".csv";
        ifstream fin(prescFile);
        if (!fin) {
            cout << "ERROR: Prescription not found!" << endl;
            return;
        }
        
        vector<Medicine> medicines;
        string line, patientID;
        bool inMedicineSection = false;
        
        while (getline(fin, line)) {
            if (line.find("PatientID,") != string::npos) {
                patientID = line.substr(line.find(",") + 1);
            }
            if (line.find("Medicines:") != string::npos) {
                inMedicineSection = true;
                continue;
            }
            if (inMedicineSection && line.find("MedicineID,Name,Type") == string::npos && !line.empty()) {
                stringstream ss(line);
                string medID, name, type, qtyStr, dosage;
                if (getline(ss, medID, ',') && getline(ss, name, ',') && 
                    getline(ss, type, ',') && getline(ss, qtyStr, ',') && getline(ss, dosage, ',')) {
                    Medicine med;
                    med.setMedicineID(medID);
                    med.setName(name);
                    med.setIsOTC(type == "OTC");
                    med.setQuantity(stoi(qtyStr));
                    med.setDosage(dosage);
                    medicines.push_back(med);
                }
            }
        }
        fin.close();
        
        if (medicines.empty()) {
            cout << "No medicines found!" << endl;
            return;
        }
        
        cout << "\n========================================" << endl;
        cout << "   MEDICINES TO DISPENSE" << endl;
        cout << "========================================" << endl;
        for (size_t i = 0; i < medicines.size(); i++) {
            cout << (i + 1) << ". " << medicines[i].getName() 
                 << " (" << (medicines[i].getIsOTC() ? "OTC" : "Non-OTC") << ")" 
                 << " - Qty: " << medicines[i].getQuantity() << endl;
        }
        
        // Update status file
        if (!patientID.empty()) {
            string statusFile = "prescriptions/" + patientID + "_status.csv";
            ifstream statusIn(statusFile);
            vector<string> statusLines;
            if (statusIn) {
                while (getline(statusIn, line)) {
                    if (line.find(prescriptionID) != string::npos && line.find("PENDING") != string::npos) {
                        size_t pos = line.find("PENDING");
                        if (pos != string::npos) line.replace(pos, 7, "DISPENSED");
                    }
                    statusLines.push_back(line);
                }
                statusIn.close();
                ofstream statusOut(statusFile);
                for (const auto& sl : statusLines) statusOut << sl << endl;
                statusOut.close();
            }
        }
        
        // Log dispensing
        string historyFile = "chemist_data/" + getUserID() + "_dispensing_history.csv";
        createDirectory("chemist_data");
        ofstream histFout(historyFile, ios::app);
        if (histFout) {
            histFout << prescriptionID << "," << getCurrentDateTime() << "," << getUserID() << endl;
            histFout.close();
        }
        
        cout << "\n*** All medicines dispensed successfully! ***" << endl;
    }
    
    void viewDispensingHistory() {
        cout << "\n========================================"<< endl;
        cout << "      DISPENSING HISTORY" << endl;
        cout << "========================================" << endl;
        string historyFile = "chemist_data/" + getUserID() + "_dispensing_history.csv";
        ifstream fin(historyFile);
        if (!fin) {
            cout << "No dispensing history found." << endl;
            return;
        }
        cout << left << setw(20) << "Prescription ID" << setw(25) << "Date & Time" << setw(15) << "Chemist ID" << endl;
        cout << string(60, '-') << endl;
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string prescID, dateTime, chemistID;
            if (getline(ss, prescID, ',') && getline(ss, dateTime, ',') && getline(ss, chemistID, ',')) {
                cout << left << setw(20) << prescID << setw(25) << dateTime << setw(15) << chemistID << endl;
            }
        }
        fin.close();
        cout << "========================================" << endl;
    }
};
// PART 3: Helper Functions and Main Function

// ==================== HELPER FUNCTIONS ====================

// Function to run user session (keeps user in their menu loop)
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
            cout << "Invalid input. Please enter a number." << endl;
        }
    }
}

// ==================== MAIN FUNCTION ====================

int main() {
    srand(time(0));  // Seed for random medicine IDs
    
    cout << "\n============================================" << endl;
    cout << "   SECURE PHARMACY PRESCRIPTION SYSTEM" << endl;
    cout << "============================================" << endl;
    cout << "Preventing Fake Prescriptions for Non-OTC Medicines" << endl;
    cout << "============================================\n" << endl;
    
    while (true) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Register New User" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit System" << endl;
        cout << "===============================" << endl;
        cout << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            // REGISTRATION
            string uname, pass, role;
            cout << "\n=== USER REGISTRATION ===" << endl;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);
            cout << "Enter role (patient/doctor/chemist): ";
            getline(cin, role);

            User* newUser = nullptr;
            
            if (role == "patient") {
                string name, email, phone, address, emergency;
                cout << "Enter full name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter address: ";
                getline(cin, address);
                cout << "Enter emergency contact: ";
                getline(cin, emergency);
                
                newUser = new Patient(uname, pass, name, email, phone, address, emergency);
                
            } else if (role == "doctor") {
                string name, email, phone, specialization, license;
                cout << "Enter full name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter specialization: ";
                getline(cin, specialization);
                cout << "Enter license number: ";
                getline(cin, license);
                
                newUser = new Doctor(uname, pass, name, email, phone, specialization, license);
                
            } else if (role == "chemist") {
                string name, email, phone, license, pharmName;
                cout << "Enter full name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter pharmacy license: ";
                getline(cin, license);
                cout << "Enter pharmacy name: ";
                getline(cin, pharmName);
                
                newUser = new Chemist(uname, pass, name, email, phone, license, pharmName);
                
            } else {
                cout << "Invalid role! Please enter patient, doctor, or chemist." << endl;
                continue;
            }

            if (newUser) {
                newUser->registerUser();
                delete newUser;
            }

        } else if (choice == "2") {
            // LOGIN
            string uname, pass, role;
            cout << "\n=== USER LOGIN ===" << endl;
            cout << "Enter username: ";
            getline(cin, uname);
            cout << "Enter password: ";
            getline(cin, pass);
            cout << "Enter role (patient/doctor/chemist): ";
            getline(cin, role);

            // Authenticate user
            unordered_map<string, userinfo> users = User::loadUsers();
            auto it = users.find(uname);

            if (it == users.end() || it->second.role != role || it->second.password != pass) {
                cout << "\nLOGIN FAILED! Check username, password, and role." << endl;
                continue;
            }

            // Load full user details
            vector<string> details = User::loadFullUserDetails(uname);
            User* currentUser = nullptr;

            if (details.empty()) {
                cout << "ERROR: User details corrupted or not found." << endl;
                continue;
            }

            // Polymorphism: Create appropriate user object based on role
            if (role == "patient") {
                currentUser = new Patient(details);
            } else if (role == "doctor") {
                currentUser = new Doctor(details);
            } else if (role == "chemist") {
                currentUser = new Chemist(details);
            }

            if (currentUser) {
                cout << "\n*** LOGIN SUCCESSFUL! ***" << endl;
                cout << "Welcome, " << currentUser->getUsername() << " (" << currentUser->getUserID() << ")" << endl;
                
                // Run user session with polymorphic menu
                runUserSession(currentUser);
                
                // Cleanup
                delete currentUser;
            }

        } else if (choice == "0") {
            cout << "\n============================================" << endl;
            cout << "   Thank you for using our system!" << endl;
            cout << "   Stay safe and healthy!" << endl;
            cout << "============================================" << endl;
            break;
            
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
