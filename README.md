# Secure Pharmacy Prescription Management System

## 🎯 Project Overview
A comprehensive C++ application designed to prevent fake prescriptions for non-OTC medicines, addressing the critical issue of prescription drug abuse and addiction.

## 🚨 Problem Statement
**Fake prescriptions for non-OTC medicines leading to addiction**

This system ensures:
- Only licensed doctors can prescribe non-OTC medicines
- Chemists can only dispense medicines with valid prescriptions
- Complete audit trail of all prescriptions and dispensing
- Patient privacy with role-based access control

---

## 📚 OOP Concepts Implemented

### 1. **Inheritance** (IS-A Relationship)
- `Patient`, `Doctor`, and `Chemist` classes inherit from base `User` class
- Demonstrates hierarchical inheritance structure

### 2. **Polymorphism** (Runtime Polymorphism)
- Virtual functions: `displayMenu()` and `performOperation()`
- Each derived class provides its own implementation
- Enables dynamic binding at runtime

### 3. **Abstraction** (Data Hiding)
- `User` class is abstract with pure virtual functions
- Cannot instantiate `User` directly, only derived classes
- Hides implementation details from users

### 4. **Encapsulation** (Data Protection)
- Private data members with public getter/setter methods
- `Medicine` class encapsulates medicine data
- Controlled access to sensitive information

### 5. **Constructor Overloading**
- Multiple constructors for different initialization scenarios
- Default, parameterized, and copy constructors

### 6. **Friend Class**
- `Doctor` is a friend of `Patient` class
- Allows doctors full access to patient data
- Demonstrates controlled access violation for specific needs

### 7. **Operator Overloading**
- `<<` operator overloaded for `Medicine` class
- Enables easy output of medicine objects

### 8. **Static Members**
- Static counters for unique ID generation
- Static methods for loading user data
- Shared across all instances

### 9. **File Handling**
- CSV file storage for persistent data
- Separate files for different data types
- Directory structure for organization

---

## 👥 User Types and Access Control

### 1. **Patient** 👤
**Can Access:**
- ✅ View complete personal medical records
- ✅ View all prescriptions
- ✅ Check prescription status (Pending/Dispensed)

**Cannot Access:**
- ❌ Other patients' data
- ❌ Modify prescriptions
- ❌ Access medicine inventory

### 2. **Doctor** 👨‍⚕️
**Can Access:**
- ✅ View any patient's complete data (Friend class privilege)
- ✅ Write prescriptions (OTC and Non-OTC)
- ✅ Update patient medical history
- ✅ View all their prescriptions

**Special Powers:**
- Can prescribe both OTC and Non-OTC medicines
- Full access to patient medical records
- Can modify patient data

### 3. **Chemist** 💊
**Can Access:**
- ✅ View prescription medicine data ONLY
- ✅ Dispense medicines (mark as dispensed)
- ✅ View their dispensing history

**Cannot Access:**
- ❌ Patient personal information (name, address, phone, etc.)
- ❌ Patient medical history
- ❌ Cannot see which patient the prescription belongs to (privacy)

**Security Feature:** Chemists can ONLY see medicine-related data, ensuring patient privacy.

---

## 🏗️ System Architecture

### File Structure
```
secure_pharmacy_project/
│
├── secure_pharmacy.cpp          # Complete source code
├── users.csv                    # User authentication data (username, password, role, userID)
│
├── patient_data/                # Folder for patient files
│   ├── P1000_data.csv          # Individual patient data
│   ├── P1001_data.csv
│   └── ...
│
├── prescriptions/               # Folder for prescription files
│   ├── RX1000.csv              # Individual prescription
│   ├── RX1001.csv
│   ├── P1000_status.csv        # Patient prescription status
│   └── ...
│
└── chemist_data/                # Folder for chemist records
    ├── C3000_dispensing_history.csv
    └── ...
```

### Data Storage Strategy

#### users.csv (Only Essential Login Info)
```csv
username,password,role,userID
john_doe,pass123,patient,P1000
dr_smith,doc456,doctor,D2000
pharmacy1,chem789,chemist,C3000
```

#### patient_data/P1000_data.csv (Complete Patient Info)
```csv
=== PATIENT PERSONAL INFORMATION ===
Name,John Doe
UserID,P1000
Email,john@email.com
Phone,1234567890
Address,123 Main St
EmergencyContact,9876543210

=== MEDICAL HISTORY ===
2025-10-25 10:30:00: Diabetes Type 2 (Dr. D2000)
2025-10-25 11:00:00: High Blood Pressure (Dr. D2000)

=== PRESCRIPTIONS ===
--- Prescription ID: RX1000 ---
Date: 2025-10-25 10:35:00
Doctor ID: D2000
Medicines Prescribed:
  - Metformin (Non-OTC), Qty: 30, Dosage: 500mg twice daily
  - Aspirin (OTC), Qty: 10, Dosage: 1 tablet daily
Status: PENDING DISPENSING
--- End of Prescription ---
```

#### prescriptions/RX1000.csv (For Chemist Access)
```csv
PrescriptionID,RX1000
PatientID,P1000
DoctorID,D2000
Date,2025-10-25 10:35:00
Status,PENDING

Medicines:
MedicineID,Name,Type,Quantity,Dosage
MED1234,Metformin,Non-OTC,30,500mg twice daily
MED5678,Aspirin,OTC,10,1 tablet daily
```

---

## 🔐 Security Features

### 1. **OTC vs Non-OTC Classification**
- **OTC (Over The Counter):** Can be sold without prescription (e.g., Aspirin, Paracetamol)
- **Non-OTC:** Requires valid doctor prescription (e.g., Antibiotics, Controlled substances)

### 2. **Role-Based Access Control**
- Each user type has specific permissions
- Chemists cannot see patient personal information
- Only doctors can prescribe medicines

### 3. **Audit Trail**
- All prescriptions are logged with timestamp
- Dispensing history tracked by chemist ID
- Cannot dispense same prescription twice

### 4. **Prescription Validation**
- Prescription must exist before dispensing
- Status changes from PENDING → DISPENSED
- Prevents duplicate dispensing

---

## 🚀 How to Compile and Run

### Compilation
```bash
g++ secure_pharmacy.cpp -o secure_pharmacy
```

### Run
```bash
./secure_pharmacy
```

---

## 📖 Usage Guide

### 1. Register Users
```
Main Menu → 1 (Register)
Choose role: patient/doctor/chemist
Enter required details
```

### 2. Login
```
Main Menu → 2 (Login)
Enter username, password, and role
```

### 3. Patient Workflow
```
Login as Patient
1. View complete medical records
2. View prescriptions
3. Check prescription status
```

### 4. Doctor Workflow
```
Login as Doctor
1. View patient data (enter Patient ID)
2. Write prescription
   - Enter Patient ID
   - Add medicines (OTC/Non-OTC)
   - Specify quantity and dosage
3. Update medical history
4. View all prescriptions written
```

### 5. Chemist Workflow
```
Login as Chemist
1. View prescription (enter Prescription ID)
   - Only sees medicine data, NOT patient info
2. Dispense medicine
   - Enter Prescription ID
   - System marks as DISPENSED
   - Updates patient status
3. View dispensing history
```

---

## 🎓 OOP Concepts Summary

| Concept | Implementation |
|---------|---------------|
| **Inheritance** | Patient, Doctor, Chemist inherit from User |
| **Polymorphism** | Virtual functions displayMenu(), performOperation() |
| **Abstraction** | User is abstract base class |
| **Encapsulation** | Private members with getters/setters |
| **Constructor Overloading** | Multiple constructors for different scenarios |
| **Friend Class** | Doctor is friend of Patient |
| **Operator Overloading** | << operator for Medicine class |
| **Static Members** | Counter variables and static methods |
| **File Handling** | CSV files for persistent storage |

---

## 🔄 System Flow

```
1. User Registration
   ↓
2. User Login (Authentication)
   ↓
3. Role-Based Menu Display (Polymorphism)
   ↓
4. User Operations
   ├── Patient: View data
   ├── Doctor: Write prescription → Saves to patient file + prescription file
   └── Chemist: Dispense medicine → Updates status
   ↓
5. Logout
```

---

## 📝 Key Features

✅ **Secure Authentication:** Username, password, and role-based login  
✅ **Unique ID Generation:** Auto-generated IDs (P1000, D2000, C3000)  
✅ **OTC/Non-OTC Classification:** Prevents fake prescriptions  
✅ **Privacy Protection:** Chemists cannot see patient personal data  
✅ **Complete Audit Trail:** All actions logged with timestamps  
✅ **File-Based Storage:** Persistent data in organized folders  
✅ **Prescription Tracking:** Status monitoring (Pending/Dispensed)  
✅ **Medical History:** Doctors can update patient history  

---

## 🎯 Project Goals Achieved

1. ✅ Prevent fake prescriptions for non-OTC medicines
2. ✅ Implement all major OOP concepts
3. ✅ Role-based access control
4. ✅ Patient privacy protection
5. ✅ Complete audit trail
6. ✅ File-based persistent storage
7. ✅ User-friendly menu system

---

## 📌 Important Notes

- **users.csv** contains ONLY login credentials (username, password, role, userID)
- **patient_data/** folder contains complete patient information in separate files
- **Chemists** can ONLY see medicine data, NOT patient personal information
- **Doctors** have full access to patient data (Friend class)
- **Prescriptions** cannot be dispensed twice (security feature)
- All operations are logged with timestamps

---

## 👨‍💻 Author
**Priyanshu Doshi**  
OOP Innovative Project - Secure Pharmacy Prescription System

---

## 📄 License
Educational Project - For Academic Purposes Only

---

## 🙏 Acknowledgments
This project demonstrates comprehensive Object-Oriented Programming concepts while addressing a real-world problem of prescription drug abuse.
