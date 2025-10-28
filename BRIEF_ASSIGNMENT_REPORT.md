# Secure Pharmacy Prescription Management System
## Object-Oriented Programming Assignment Report

---

## 1. Executive Summary

This project implements a comprehensive **Secure Pharmacy Prescription Management System** in C++ to address the critical issue of fake prescriptions for non-OTC (Over-The-Counter) medicines. The system employs robust Object-Oriented Programming principles to create a role-based access control system with three distinct user types: Patients, Doctors, and Chemists.

**Key Achievements:**
- Implemented all 10 core OOP concepts (Inheritance, Polymorphism, Abstraction, Encapsulation, Friend Class, Operator Overloading, Static Members, Constructor Overloading, Virtual Functions, Access Specifiers)
- Developed a privacy-preserving architecture where chemists can only access medicine data, not patient personal information
- Created an audit trail system for tracking prescription dispensing
- Established OTC/Non-OTC medicine classification to prevent unauthorized dispensing
- Built a file-based persistent storage system using CSV format

**Technical Specifications:**
- Language: C++ (Standard C++11)
- Storage: CSV-based file system
- Architecture: Object-oriented with inheritance hierarchy
- Lines of Code: ~850 lines
- Compilation: `g++ secure_pharmacy.cpp -o secure_pharmacy`

---

## 2. Problem Statement

### 2.1 Background
The pharmaceutical industry faces a significant challenge with **fake prescriptions** for non-OTC medicines, leading to:
- Unauthorized access to controlled substances
- Potential drug abuse and addiction
- Lack of proper medical oversight
- Privacy breaches in patient data handling

### 2.2 Core Issues
1. **Security Gap:** No verification system to prevent fake prescriptions
2. **Privacy Concerns:** Patient personal information exposed to unauthorized personnel
3. **Accountability:** No audit trail for medicine dispensing
4. **Access Control:** Lack of role-based permissions for different user types

### 2.3 Requirements
- Distinguish between OTC and Non-OTC medicines
- Implement role-based access control
- Maintain patient privacy (chemists should not see personal data)
- Create audit trails for all prescription activities
- Prevent duplicate or fake prescriptions

---

## 3. Objectives

### 3.1 Primary Objectives
1. **Develop a secure prescription management system** using OOP principles
2. **Implement role-based access control** for three user types
3. **Ensure patient privacy** through controlled data access
4. **Create an audit trail** for all prescription and dispensing activities

### 3.2 Technical Objectives
1. Demonstrate all 10 core OOP concepts in a practical application
2. Implement inheritance hierarchy with abstract base class
3. Use polymorphism for role-specific behavior
4. Apply friend class concept for controlled access
5. Create persistent storage using file I/O

### 3.3 Functional Objectives
1. **Patient Management:** Registration, medical history tracking, prescription viewing
2. **Doctor Capabilities:** Full patient access, prescription writing, medical history updates
3. **Chemist Operations:** Medicine dispensing, prescription verification, history logging
4. **Security:** Authentication, authorization, data privacy

---

## 4. System Architecture

### 4.1 High-Level Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    Main Application                     │
│                  (secure_pharmacy.cpp)                  │
└─────────────────────────────────────────────────────────┘
                            │
                ┌───────────┴───────────┐
                │                       │
        ┌───────▼────────┐      ┌──────▼──────┐
        │  User Classes  │      │   Storage   │
        │   Hierarchy    │      │   System    │
        └───────┬────────┘      └──────┬──────┘
                │                      │
    ┌───────────┼───────────┐          │
    │           │           │          │
┌───▼───┐  ┌───▼────┐  ┌───▼────┐      │
│Patient│  │ Doctor │  │Chemist │      │
└───────┘  └────────┘  └────────┘      │
                                       │
                      ┌────────────────┼────────────────┐
                      │                │                │
              ┌───────▼──────┐  ┌──────▼──────┐    ┌────▼────┐
              │ users.csv    │  │patient_data/│    │prescriptions/│
              │              │  │             │    │chemist_data/ │
              └──────────────┘  └─────────────┘    └─────────────┘
```

### 4.2 Class Hierarchy

```
                    ┌──────────┐
                    │   User   │ (Abstract Base Class)
                    └────┬─────┘
                         │
         ┌───────────────┼───────────────┐
         │               │               │
    ┌────▼────┐    ┌─────▼─────┐   ┌────▼────┐
    │ Patient │    │  Doctor   │   │ Chemist │
    └─────────┘    └───────────┘   └─────────┘
         │              │ Friend         │
         └──────────────┘                │
                                         │
                    ┌──────────┐         │
                    │ Medicine │◄────────┘
                    └──────────┘
```

### 4.3 Data Flow

**Prescription Workflow:**
```
Doctor → Write Prescription → Patient Data File
                           → Prescription File (prescriptions/)
                           → Status File (prescriptions/)
                                    ↓
Chemist → View Prescription → Dispense Medicine
                           → Update Status (PENDING → DISPENSED)
                           → Log History (chemist_data/)
                                    ↓
Patient → View Status → See DISPENSED status
```

### 4.4 File Structure

```
secure_pharmacy_project/
├── secure_pharmacy.cpp          # Main source code
├── users.csv                    # User authentication data
├── patient_data/                # Patient-specific files
│   ├── P1000_data.csv          # Individual patient records
│   ├── P1001_data.csv
│   └── ...
├── prescriptions/               # Prescription tracking
│   ├── RX1000.csv              # Individual prescriptions
│   ├── RX1001.csv
│   ├── P1000_status.csv        # Patient prescription status
│   └── ...
└── chemist_data/               # Dispensing audit trail
    ├── C3000_dispensing_history.csv
    └── ...
```

---

## 5. OOP Concepts Implementation

### 5.1 Inheritance
**Implementation:** Patient, Doctor, and Chemist classes inherit from User base class
**Purpose:** Code reuse and establishing IS-A relationships
**Benefit:** Common functionality (login, logout, user management) shared across all user types

### 5.2 Polymorphism
**Implementation:** Virtual functions `displayMenu()` and `performOperation()` overridden in each derived class
**Purpose:** Different behavior for each user type using same interface
**Benefit:** Single `runUserSession()` function works for all user types through runtime polymorphism

### 5.3 Abstraction
**Implementation:** User class with pure virtual functions (`= 0`)
**Purpose:** Define interface without implementation, making User an abstract class
**Benefit:** Cannot instantiate User directly; forces derived classes to implement required methods

### 5.4 Encapsulation
**Implementation:** Private data members with public getter/setter methods
**Purpose:** Data hiding and controlled access
**Benefit:** Internal implementation can change without affecting external code

### 5.5 Friend Class
**Implementation:** Doctor declared as friend of Patient class
**Purpose:** Allow doctors full access to patient private data for medical care
**Benefit:** Controlled violation of encapsulation for legitimate medical access while maintaining privacy from chemists

### 5.6 Operator Overloading
**Implementation:** Overloaded `<<` operator for Medicine class
**Purpose:** Custom output formatting for Medicine objects
**Benefit:** Clean syntax: `cout << medicineObject;`

### 5.7 Static Members
**Implementation:** Static counters (patientCounter, doctorCounter, chemistCounter, prescriptionCounter)
**Purpose:** Generate unique IDs shared across all instances
**Benefit:** Ensures no duplicate user IDs or prescription IDs

### 5.8 Constructor Overloading
**Implementation:** Multiple constructors in each class (default, parameterized, for existing users)
**Purpose:** Flexible object creation for different scenarios
**Benefit:** Same class can be instantiated for new registration or existing user login

### 5.9 Virtual Functions & Virtual Destructor
**Implementation:** Virtual `displayMenu()`, `performOperation()`, and virtual destructor
**Purpose:** Enable runtime polymorphism and proper cleanup
**Benefit:** Correct destructor called when deleting derived class objects through base pointer

### 5.10 Access Specifiers
**Implementation:** Private, protected, and public sections in all classes
**Purpose:** Control visibility and access to class members
**Benefit:** Protected members accessible to derived classes, private members hidden from all

---

## 6. System Design

### 6.1 User Class (Abstract Base)
**Responsibilities:**
- User authentication (registration, login)
- User ID generation with static counters
- File I/O for user data (users.csv)
- Pure virtual functions for derived class implementation

**Key Methods:**
- `registerUser()` - Save new user to CSV
- `loadUsers()` - Read all users for authentication
- `generateUserID()` - Create unique IDs (P1000, D2000, C3000)

### 6.2 Patient Class
**Responsibilities:**
- Personal data file management (patient_data/)
- View complete medical records
- View prescriptions and status
- Privacy-protected data storage

**Key Methods:**
- `createPatientDataFile()` - Initialize patient record
- `viewCompleteData()` - Display all patient information
- `viewPrescriptions()` - Show only prescription section
- `viewPrescriptionStatus()` - Check PENDING/DISPENSED status

### 6.3 Doctor Class
**Responsibilities:**
- Full patient data access (friend class privilege)
- Prescription writing with multiple medicines
- Medical history updates with timestamps
- Prescription file generation

**Key Methods:**
- `viewPatientData()` - Access any patient's complete records
- `writePrescription()` - Create prescription with OTC/Non-OTC classification
- `updateMedicalHistory()` - Add timestamped medical entries
- `initializePrescriptionCounter()` - Prevent duplicate prescription IDs

**Prescription Creation Process:**
1. Verify patient exists
2. Generate unique prescription ID
3. Collect medicine details (name, OTC status, quantity, dosage)
4. Save to patient data file
5. Create separate prescription file for chemist
6. Create status tracking file

### 6.4 Chemist Class
**Responsibilities:**
- View prescription medicine data only (no patient personal info)
- Dispense medicines and update status
- Maintain dispensing audit trail
- Privacy-preserving prescription access

**Key Methods:**
- `viewPrescription()` - Show only medicine data, hide patient info
- `dispenseMedicine()` - Update status to DISPENSED, log activity
- `viewDispensingHistory()` - Display audit trail

**Dispensing Process:**
1. Load prescription file
2. Parse medicine data
3. Display medicines to dispense
4. Update status file (PENDING → DISPENSED)
5. Log to chemist's history file with timestamp

### 6.5 Medicine Class
**Responsibilities:**
- Store medicine information
- OTC/Non-OTC classification
- Dosage and quantity management

**Attributes:**
- medicineID, name, isOTC, quantity, dosage

---

## 7. Challenges and Solutions

### 7.1 Challenge: Duplicate Prescription IDs
**Problem:** Prescription counter reset to 1000 on each program restart, causing ID collisions and file overwrites.

**Root Cause:** Static counter initialized to fixed value, not persisted between runs.

**Solution:** 
- Implemented `initializePrescriptionCounter()` method
- Scans prescriptions folder on startup
- Finds highest existing prescription ID
- Sets counter to highest + 1
- Ensures unique IDs across program restarts

### 7.2 Challenge: Patient Privacy vs Doctor Access
**Problem:** Doctors need full patient access for medical care, but chemists should only see medicine data.

**Solution:**
- Used **friend class** concept: Doctor is friend of Patient
- Doctors can access Patient's private members
- Chemists access separate prescription files without patient personal info
- Demonstrates controlled access in OOP

### 7.3 Challenge: Role-Based Menu Systems
**Problem:** Different user types need completely different interfaces and operations.

**Solution:**
- Pure virtual functions in User base class
- Each derived class implements custom `displayMenu()` and `performOperation()`
- Single `runUserSession()` function uses polymorphism
- Runtime binding determines correct menu for each user type

### 7.4 Challenge: Prescription Status Tracking
**Problem:** Need to track individual medicine dispensing status (PENDING/DISPENSED) for patient visibility.

**Solution:**
- Created separate status files (prescriptions/P1000_status.csv)
- Each medicine in prescription gets status entry
- Chemist updates status during dispensing
- Patient can view real-time status

### 7.5 Challenge: File-Based Data Persistence
**Problem:** No database available, need persistent storage across program runs.

**Solution:**
- CSV-based file system with structured format
- Separate files for different data types
- Directory structure for organization (patient_data/, prescriptions/, chemist_data/)
- String parsing with `stringstream` for CSV reading

### 7.6 Challenge: Audit Trail for Accountability
**Problem:** Need to track who dispensed what and when for security and compliance.

**Solution:**
- Chemist dispensing history files (chemist_data/)
- Log prescription ID, timestamp, and chemist ID
- Immutable append-only log
- Provides complete audit trail

### 7.7 Challenge: Multiple Medicines per Prescription
**Problem:** Real prescriptions often contain multiple medicines with different properties.

**Solution:**
- Vector of Medicine objects in prescription
- Loop to collect multiple medicines during prescription writing
- Store all medicines in single prescription file
- Dispense all medicines together

### 7.8 Challenge: Input Validation and Error Handling
**Problem:** User input can be invalid (non-numeric, empty, wrong format).

**Solution:**
- Try-catch blocks for string-to-integer conversion
- File existence checks before reading
- Empty string checks for CSV parsing
- User-friendly error messages

---

## 8. Conclusion

This Secure Pharmacy Prescription Management System successfully demonstrates all core Object-Oriented Programming concepts in a practical, real-world application. The system addresses critical security and privacy concerns in pharmaceutical prescription management while maintaining a clean, extensible architecture.

**Key Accomplishments:**
- ✅ All 10 OOP concepts implemented and demonstrated
- ✅ Role-based access control with three distinct user types
- ✅ Privacy-preserving architecture (chemists cannot access patient personal data)
- ✅ Audit trail for accountability and compliance
- ✅ OTC/Non-OTC classification to prevent fake prescriptions
- ✅ Persistent file-based storage system
- ✅ Unique ID generation preventing duplicates
- ✅ Comprehensive error handling

**Technical Achievements:**
- Clean inheritance hierarchy with abstract base class
- Polymorphic behavior through virtual functions
- Friend class for controlled access
- Static members for shared state
- Operator overloading for clean syntax
- Multiple constructors for flexibility

The system is production-ready for educational purposes and demonstrates a solid understanding of Object-Oriented Programming principles applied to solve real-world problems.

---

**END OF BRIEF REPORT**
