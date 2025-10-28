# SECURE PHARMACY PRESCRIPTION MANAGEMENT SYSTEM
## Object-Oriented Programming - Innovative Project Report

---

**Student Name:** Priyanshu Doshi  
**Project Title:** Secure Pharmacy Prescription Management System  
**Programming Language:** C++  
**Date:** October 2025  

---

## TABLE OF CONTENTS

1. Executive Summary
2. Problem Statement
3. Objectives
4. System Architecture
5. OOP Concepts Implementation
6. System Design and Features
7. Implementation Details
8. Security Mechanisms
9. Testing and Results
10. Challenges and Solutions
11. Conclusion and Future Work

---

## 1. EXECUTIVE SUMMARY

This project presents a comprehensive **Secure Pharmacy Prescription Management System** developed in C++ to address the critical issue of fake prescriptions for non-OTC (Over-The-Counter) medicines, which has led to widespread prescription drug abuse and addiction.

### Key Achievements

✅ **Implemented all major OOP concepts:** Inheritance, Polymorphism, Abstraction, Encapsulation, Friend Classes, Operator Overloading, Static Members, Constructor Overloading, Virtual Destructors, and Protected Members

✅ **Created secure role-based access control** with three distinct user types: Patients, Doctors, and Chemists

✅ **Developed streamlined dispensing workflow** for efficient medicine distribution

✅ **Established complete audit trail** for all transactions with timestamps and user IDs

✅ **Maintained patient privacy** with restricted data access for chemists

✅ **Implemented file-based persistent storage** with organized directory structure

### System Overview

The application implements a robust, role-based access control mechanism ensuring:
- Only licensed doctors can prescribe non-OTC medicines
- Chemists can only dispense medicines with valid prescriptions
- Patient privacy is maintained throughout the process
- Complete traceability of all prescriptions and dispensing activities

---

## 2. PROBLEM STATEMENT

### 2.1 Background

Prescription drug abuse has become a significant public health crisis globally. The ease of obtaining fake prescriptions for non-OTC medicines, particularly controlled substances, has led to:

- **Addiction epidemic:** Increasing cases of prescription drug dependency
- **Health risks:** Improper medication usage without medical supervision
- **Legal issues:** Illegal distribution of controlled substances
- **Economic burden:** Healthcare costs associated with drug abuse treatment

### 2.2 Current Challenges

**1. Lack of Verification**
- No systematic way to verify prescription authenticity
- Paper prescriptions can be easily forged or altered

**2. No Audit Trail**
- Difficulty tracking who prescribed and dispensed medicines
- No accountability for prescription abuse

**3. Privacy Concerns**
- Patient information often exposed unnecessarily
- No role-based access control

**4. Inventory Management**
- No tracking of individual medicine dispensing
- Cannot handle partial fulfillment of prescriptions

### 2.3 Proposed Solution

A digital system that:
- Ensures only authorized doctors can write prescriptions
- Maintains complete records of all prescriptions
- Allows chemists to verify and dispense medicines securely
- Protects patient privacy while enabling necessary access
- Provides comprehensive audit trails for accountability
- Enables individual medicine tracking and dispensing

---

## 3. OBJECTIVES

### 3.1 Primary Objectives

**1. Prevent Fake Prescriptions**
- Implement a system where only registered doctors can create prescriptions
- Digital verification of prescription authenticity

**2. OTC/Non-OTC Classification**
- Clearly distinguish between medicines requiring prescriptions
- Prevent unauthorized access to controlled substances

**3. Role-Based Access Control**
- Ensure each user type has appropriate access levels
- Enforce security at code level

**4. Patient Privacy**
- Protect sensitive patient information from unauthorized access
- Chemists see only medicine data, not personal information

**5. Audit Trail**
- Maintain complete records of all prescriptions and dispensing activities
- Timestamp and user ID for all transactions

### 3.2 Technical Objectives

**1. Demonstrate OOP Mastery**
- Implement all major OOP concepts comprehensively
- Show practical application of theoretical concepts

**2. File Management**
- Create organized, persistent data storage system
- Separate files for different data types

**3. User Authentication**
- Secure login system with role verification
- Session management

**4. Data Integrity**
- Ensure consistency across multiple data files
- Prevent data corruption

**5. Scalability**
- Design system to handle multiple users and transactions
- Modular architecture for easy extension

---

## 4. SYSTEM ARCHITECTURE

### 4.1 High-Level Architecture

```
┌─────────────────────────────────────────────┐
│         USER INTERFACE LAYER                │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │ Patient  │  │  Doctor  │  │ Chemist  │  │
│  │  Menu    │  │   Menu   │  │   Menu   │  │
│  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────┐
│        BUSINESS LOGIC LAYER                 │
│  ┌──────────────────────────────────────┐   │
│  │    User (Abstract Base Class)        │   │
│  └──────────────────────────────────────┘   │
│       │            │            │            │
│       ▼            ▼            ▼            │
│  ┌────────┐  ┌────────┐  ┌─────────┐       │
│  │Patient │  │ Doctor │  │ Chemist │       │
│  └────────┘  └────────┘  └─────────┘       │
│  ┌──────────────────────────────────────┐   │
│  │         Medicine Class               │   │
│  └──────────────────────────────────────┘   │
└─────────────────────────────────────────────┘
                    │
                    ▼
┌─────────────────────────────────────────────┐
│      DATA PERSISTENCE LAYER                 │
│  ┌──────────┐  ┌──────────────┐            │
│  │users.csv │  │patient_data/ │            │
│  └──────────┘  └──────────────┘            │
│  ┌──────────────┐  ┌──────────────┐        │
│  │prescriptions/│  │chemist_data/ │        │
│  └──────────────┘  └──────────────┘        │
└─────────────────────────────────────────────┘
```

### 4.2 Class Hierarchy

```
              ┌─────────────┐
              │    User     │
              │ (Abstract)  │
              └─────────────┘
                     △
                     │
      ┏━━━━━━━━━━━━━┻━━━━━━━━━━━━━┓
      ┃                            ┃
┌──────────┐  ┌──────────┐  ┌──────────┐
│ Patient  │  │  Doctor  │  │ Chemist  │
└──────────┘  └──────────┘  └──────────┘
                    │
              (Friend of Patient)

┌──────────────┐
│   Medicine   │
└──────────────┘
```

### 4.3 File Structure

```
secure_pharmacy_project/
│
├── secure_pharmacy.cpp          # Main source code
├── secure_pharmacy.exe          # Compiled executable
├── users.csv                    # Authentication data
│
├── patient_data/                # Patient information
│   ├── P1000_data.csv
│   ├── P1001_data.csv
│   └── ...
│
├── prescriptions/               # Prescription records
│   ├── RX1000.csv
│   ├── RX1001.csv
│   ├── P1000_status.csv
│   └── ...
│
└── chemist_data/                # Chemist records
    ├── C3000_dispensing_history.csv
    └── ...
```

### 4.4 Data Flow

```
1. Doctor writes prescription
        ↓
2. Saves to patient_data/P1000_data.csv (complete info)
        ↓
3. Creates prescriptions/RX1000.csv (for chemist)
        ↓
4. Creates prescriptions/P1000_status.csv (tracking)
        ↓
5. Chemist views prescription (medicine data only)
        ↓
6. Chemist selects medicines to dispense
        ↓
7. Updates status: PENDING → DISPENSED
        ↓
8. Logs to chemist_data/C3000_dispensing_history.csv
        ↓
9. Patient views updated status
```

---

## 5. OOP CONCEPTS IMPLEMENTATION

### 5.1 Inheritance (IS-A Relationship)

**Definition:** A mechanism where a derived class inherits properties and methods from a base class.

**Implementation:**
```cpp
class User {  // Base class
    private:
        string username;
        string password;
        string role;
    protected:
        string userID;
        string name;
    public:
        virtual void displayMenu() = 0;
};

class Patient : public User {  // Derived class
    private:
        string address;
        string emergencyContact;
    public:
        void displayMenu() override;
};
```

**Benefits:**
- Code reusability (common attributes in base class)
- Establishes logical relationships (Patient IS-A User)
- Reduces redundancy and easier maintenance

---

### 5.2 Polymorphism (Many Forms)

**Runtime Polymorphism (Virtual Functions):**
```cpp
// Base class
virtual void displayMenu() = 0;

// Patient class
void displayMenu() override {
    cout << "1. View Medical Records\n";
}

// Doctor class
void displayMenu() override {
    cout << "1. View Patient Data\n";
}

// Usage - Dynamic binding
User* currentUser = new Patient(details);
currentUser->displayMenu();  // Calls Patient's version
```

**Compile-time Polymorphism (Constructor Overloading):**
```cpp
User();  // Default
User(string uname, string pass, string r, ...);  // New user
User(string uname, string pass, string r, string id, ...);  // Existing
```

**Benefits:**
- Single interface, multiple implementations
- Dynamic binding at runtime
- Extensible and cleaner code

---

### 5.3 Abstraction (Hiding Complexity)

**Implementation:**
```cpp
class User {
public:
    virtual void displayMenu() = 0;  // Pure virtual
    virtual bool performOperation(int choice) = 0;
    virtual ~User() {}
};
```

**Characteristics:**
- Cannot instantiate User class directly
- Forces derived classes to implement methods
- Provides common interface

---

### 5.4 Encapsulation (Data Hiding)

**Implementation:**
```cpp
class User {
private:
    string username;  // Hidden
    string password;  // Protected
public:
    string getUsername() const { return username; }
    void setLoginStatus(bool status) { isLoggedIn = status; }
};

class Medicine {
private:
    string medicineID;
    int quantity;
public:
    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { 
        if (qty >= 0) quantity = qty; 
    }
};
```

**Benefits:**
- Protects sensitive data
- Controlled access with validation
- Easier to modify internal implementation

---

### 5.5 Friend Class

**Implementation:**
```cpp
class Patient : public User {
private:
    string address;
    string patientDataFile;
public:
    friend class Doctor;  // Doctor can access private members
};

class Doctor : public User {
public:
    void viewPatientData() {
        // Can access Patient's private members
    }
};
```

**Justification:**
- Doctors need full access to patient data for medical care
- Real-world scenario: Doctor-patient relationship
- Controlled violation of encapsulation

---

### 5.6 Operator Overloading

**Implementation:**
```cpp
class Medicine {
    friend ostream& operator<<(ostream& os, const Medicine& med) {
        os << "ID: " << med.medicineID 
           << ", Name: " << med.name 
           << ", Type: " << (med.isOTC ? "OTC" : "Non-OTC");
        return os;
    }
};

// Usage
Medicine med;
cout << med;  // Natural syntax
```

---

### 5.7 Static Members

**Implementation:**
```cpp
class User {
public:
    static int patientCounter;  // Shared by all objects
    static int doctorCounter;
    static int chemistCounter;
    
    static unordered_map<string, userinfo> loadUsers();
};

// Initialization
int User::patientCounter = 1000;
int User::doctorCounter = 2000;
int User::chemistCounter = 3000;
```

**Benefits:**
- Unique ID generation across all instances
- Shared data among all users
- Utility functions without object state

---

### 5.8 Constructor Overloading

**Implementation:**
```cpp
User();  // Default
User(string uname, string pass, string r, ...);  // New user
User(string uname, string pass, string r, string id, ...);  // Existing
```

**Benefits:**
- Different initialization scenarios
- Flexibility in object creation

---

### 5.9 Virtual Destructor

```cpp
class User {
public:
    virtual ~User() {}
};
```

**Purpose:** Ensures proper cleanup when deleting derived class objects through base class pointer

---

### 5.10 Protected Members

```cpp
class User {
protected:
    string userID;  // Accessible in derived classes
    string email;
    string name;
};
```

**Benefits:** Balance between private and public access

---

## 6. SYSTEM DESIGN AND FEATURES

### 6.1 User Types and Access Control

#### Patient Access Rights
✅ View complete personal medical records  
✅ View all prescriptions  
✅ Check prescription status (Pending/Dispensed)  
❌ Cannot modify prescriptions  
❌ Cannot access other patients' data  

#### Doctor Access Rights
✅ View any patient's complete data (Friend class)  
✅ Write prescriptions (OTC and Non-OTC)  
✅ Update patient medical history  
✅ View all their prescriptions  
✅ Full access to patient medical records  

#### Chemist Access Rights
✅ View prescription medicine data ONLY  
✅ Dispense medicines (mark as dispensed)  
✅ View their dispensing history  
❌ Cannot see patient personal information  
❌ Cannot modify prescriptions  

### 6.2 Medicine Classification

**OTC (Over-The-Counter)**
- Can be sold without prescription
- Examples: Paracetamol, Aspirin, Vitamin C
- Lower risk of abuse

**Non-OTC (Prescription Required)**
- Requires valid doctor prescription
- Examples: Antibiotics, Controlled substances
- Higher risk of abuse
- Requires medical supervision

### 6.3 Key Features

#### 1. User Management
- Unique ID generation (P1000, D2000, C3000)
- Role-based registration
- Secure authentication
- Session management

#### 2. Patient Features
- **View Complete Medical Records:** Personal info, medical history, prescriptions
- **View Prescription Status:** Track dispensing status of each medicine

#### 3. Doctor Features
- **View Patient Data:** Full access to any patient's records
- **Write Prescription:** Add multiple medicines with OTC/Non-OTC classification
- **Update Medical History:** Add timestamped medical entries

#### 4. Chemist Features
- **View Prescription:** See medicine data only (no patient personal info)
- **Dispense Medicine:** Dispense all medicines in prescription
- **View Dispensing History:** Complete audit trail

### 6.4 Simplified Medicine Dispensing

**Process:**
1. Chemist enters prescription ID
2. System displays all medicines in prescription
3. Chemist confirms to dispense all medicines
4. System updates status for all medicines to DISPENSED
5. Logs dispensing activity with timestamp

**Benefits:**
- Simple and efficient workflow
- Clear audit trail
- Easy to use interface
- Reduces errors in dispensing

---

## 7. IMPLEMENTATION DETAILS

### 7.1 Data Storage Strategy

#### users.csv (Authentication Only)
```csv
username,password,role,userID
john_patient,pass123,patient,P1000
dr_smith,doc456,doctor,D2000
```
**Contains:** Only login credentials

#### patient_data/P1000_data.csv
```
=== PATIENT PERSONAL INFORMATION ===
Name,John Doe
UserID,P1000
Email,john@email.com
Phone,1234567890
Address,123 Main St
EmergencyContact,9876543210

=== MEDICAL HISTORY ===
2025-10-25 10:30:00: Diabetes Type 2 (Dr. D2000)

=== PRESCRIPTIONS ===
--- Prescription ID: RX1000 ---
Date: 2025-10-25 10:35:00
Doctor ID: D2000
Medicines Prescribed:
  - Metformin (Non-OTC), Qty: 30, Dosage: 500mg twice daily
Status: PENDING DISPENSING
```
**Contains:** Complete patient information

#### prescriptions/RX1000.csv
```csv
PrescriptionID,RX1000
PatientID,P1000
DoctorID,D2000
Date,2025-10-25 10:35:00
Status,PENDING

Medicines:
MedicineID,Name,Type,Quantity,Dosage
MED1234,Metformin,Non-OTC,30,500mg twice daily
```
**Contains:** Prescription for chemist (no patient personal info)

### 7.2 Core Algorithms

#### User Registration
```
1. Check if username already exists
2. Generate unique user ID based on role
3. Write to users.csv (username, password, role, userID)
4. Create role-specific data files
5. Return success/failure
```

#### Prescription Writing
```
1. Verify patient exists
2. Generate unique prescription ID
3. Collect medicine details (name, type, quantity, dosage)
4. Save to patient file (complete info)
5. Create prescription file for chemist (medicine data only)
6. Create status file for patient tracking
7. Return prescription ID
```

#### Medicine Dispensing
```
1. Load prescription by ID
2. Parse and display all medicines
3. Get chemist selection (individual or all)
4. Update status for selected medicines only
5. Log to dispensing history
6. Display confirmation
```

---

## 8. SECURITY MECHANISMS

### 8.1 Authentication
- Username, password, AND role must match
- Cannot login as different role with same credentials
- Session management with login status

### 8.2 Authorization (Role-Based Access)

| Feature | Patient | Doctor | Chemist |
|---------|---------|--------|---------|
| View own data | ✅ | ✅ | ✅ |
| View patient personal info | ✅ (own) | ✅ (all) | ❌ |
| View patient medical history | ✅ (own) | ✅ (all) | ❌ |
| Write prescription | ❌ | ✅ | ❌ |
| View prescription medicines | ✅ (own) | ✅ (all) | ✅ (data only) |
| Dispense medicine | ❌ | ❌ | ✅ |
| Update medical history | ❌ | ✅ | ❌ |

### 8.3 Data Segregation
- Separate files for different purposes
- Chemist prescription files exclude patient personal info
- Access controlled at function level
- Principle of least privilege

### 8.4 Privacy Protection
- Chemists see only medicine data
- Patient personal information hidden
- Minimal data exposure

### 8.5 Audit Trail
- All prescriptions logged with timestamp and doctor ID
- All dispensing activities logged with timestamp and chemist ID
- Individual medicine tracking
- Complete traceability

---

## 9. TESTING AND RESULTS

### 9.1 Test Scenarios

#### Test Case 1: User Registration
**Input:** Register patient with username "john_patient"  
**Expected:** User ID P1000 generated, saved to users.csv  
**Result:** ✅ PASS - User registered successfully  

#### Test Case 2: User Authentication
**Input:** Login with correct username, password, role  
**Expected:** Login successful, appropriate menu displayed  
**Result:** ✅ PASS - Authentication working correctly  

#### Test Case 3: Doctor Writes Prescription
**Input:** Doctor writes prescription with 3 medicines (2 Non-OTC, 1 OTC)  
**Expected:** Prescription saved to multiple files, status set to PENDING  
**Result:** ✅ PASS - Prescription created successfully  

#### Test Case 4: Patient Views Status
**Input:** Patient views prescription status  
**Expected:** All medicines shown with PENDING status  
**Result:** ✅ PASS - Status displayed correctly  

#### Test Case 5: Chemist Views Prescription
**Input:** Chemist enters prescription ID  
**Expected:** Medicine data shown, patient personal info hidden  
**Result:** ✅ PASS - Privacy maintained  

#### Test Case 6: Medicine Dispensing
**Input:** Chemist dispenses prescription  
**Expected:** All medicines marked as DISPENSED  
**Result:** ✅ PASS - Dispensing working correctly  

#### Test Case 7: Patient Checks Updated Status
**Input:** Patient views status after dispensing  
**Expected:** All medicines show DISPENSED  
**Result:** ✅ PASS - Status updated correctly  

### 9.2 Performance Results

- **Compilation:** Successful with no errors
- **Execution:** Smooth operation with all features functional
- **File Operations:** Fast read/write operations
- **Memory Management:** No memory leaks detected
- **User Experience:** Intuitive menus and clear feedback

### 9.3 Security Testing

✅ Cannot login with wrong password  
✅ Cannot login with wrong role  
✅ Chemist cannot access patient personal info  
✅ Patient cannot access other patients' data  
✅ Cannot dispense without valid prescription  
✅ Streamlined dispensing reduces complexity  

---

## 10. CHALLENGES AND SOLUTIONS

### Challenge 1: File Management Complexity
**Problem:** Managing multiple CSV files with different formats  
**Solution:** Created separate directories for different data types, standardized CSV format, implemented helper functions for file operations

### Challenge 2: Privacy Protection
**Problem:** Ensuring chemists cannot see patient personal information  
**Solution:** Created separate prescription files for chemists containing only medicine data, implemented filtered view functions

### Challenge 3: Simplified Dispensing Workflow
**Problem:** Complex medicine selection could lead to errors  
**Solution:** Streamlined to dispense all medicines at once, simplified status tracking, cleaner dispensing history

### Challenge 4: Data Consistency
**Problem:** Keeping data consistent across multiple files  
**Solution:** Implemented atomic updates, transaction-like operations, validation checks

### Challenge 5: User ID Generation
**Problem:** Ensuring unique IDs across program restarts  
**Solution:** Used static counters with proper initialization, starting values (P1000, D2000, C3000)

---

## 11. CONCLUSION AND FUTURE WORK

### 11.1 Achievements

This project successfully demonstrates:

✅ **Complete OOP Implementation:** All major concepts applied practically  
✅ **Real-World Problem Solving:** Addresses prescription drug abuse  
✅ **Secure System Design:** Role-based access control and privacy protection  
✅ **Scalable Architecture:** Modular design for easy extension  
✅ **User-Friendly Interface:** Intuitive menus for all user types  
✅ **Complete Audit Trail:** Full traceability of all actions  
✅ **Streamlined Dispensing:** Simple and efficient workflow  

### 11.2 Learning Outcomes

1. **OOP Mastery:** Deep understanding of inheritance, polymorphism, abstraction, encapsulation
2. **Security Awareness:** Importance of access control and data protection
3. **File Management:** Organized data storage and retrieval
4. **Problem-Solving:** Breaking down complex problems into manageable components
5. **Code Quality:** Writing maintainable, documented, and modular code

### 11.3 Future Enhancements

**1. Database Integration**
- Replace CSV files with SQL database
- Improved query performance
- Better data integrity

**2. GUI Implementation**
- Graphical user interface using Qt or similar
- More user-friendly experience
- Better visualization

**3. Network Capabilities**
- Multi-user concurrent access
- Client-server architecture
- Real-time updates

**4. Advanced Security**
- Password encryption
- Two-factor authentication
- Digital signatures for prescriptions

**5. Reporting and Analytics**
- Prescription trends analysis
- Inventory management
- Usage statistics

**6. Mobile Application**
- Patient mobile app for viewing prescriptions
- Doctor app for writing prescriptions on-the-go
- Push notifications for status updates

**7. Integration with Pharmacy Systems**
- Real-time inventory checking
- Automatic reordering
- Insurance verification

**8. Barcode/QR Code Support**
- Scan prescription codes
- Quick verification
- Reduced manual entry errors

### 11.4 Conclusion

The Secure Pharmacy Prescription Management System successfully addresses the critical issue of fake prescriptions through a comprehensive, secure, and user-friendly application. By implementing all major OOP concepts and focusing on security and privacy, the system provides a robust solution that can be extended and deployed in real-world scenarios.

The project demonstrates that theoretical OOP concepts, when applied correctly, can solve practical problems while maintaining code quality, security, and scalability. The simplified dispensing workflow ensures ease of use while maintaining security and audit capabilities.

This project serves as a strong foundation for understanding how software engineering principles can be applied to healthcare technology, addressing both technical requirements and ethical considerations such as patient privacy and drug abuse prevention.

---

## APPENDIX

### A. Compilation and Execution

**Compile:**
```bash
g++ secure_pharmacy.cpp -o secure_pharmacy
```

**Run:**
```bash
./secure_pharmacy
```

### B. Sample Test Data

**Users:**
- Patient: username=`priyanshu`, password=`1234`, ID=`P1000`
- Doctor: username=`doctor`, password=`1234`, ID=`D2000`
- Chemist: username=`chemist`, password=`1234`, ID=`C3000`

### C. File Formats

**users.csv:**
```
username,password,role,userID
```

**patient_data/P1000_data.csv:**
```
=== PATIENT PERSONAL INFORMATION ===
Name,<name>
UserID,<userID>
...
=== MEDICAL HISTORY ===
...
=== PRESCRIPTIONS ===
...
```

**prescriptions/RX1000.csv:**
```
PrescriptionID,<id>
PatientID,<patientID>
DoctorID,<doctorID>
Date,<datetime>
Status,<PENDING/DISPENSED>

Medicines:
MedicineID,Name,Type,Quantity,Dosage
<data>
```

### D. Code Statistics

- **Total Lines of Code:** ~700 lines
- **Number of Classes:** 5 (User, Patient, Doctor, Chemist, Medicine)
- **Number of Methods:** 30+
- **OOP Concepts Used:** 10+
- **File Types:** CSV-based storage

---

**END OF REPORT**

---
