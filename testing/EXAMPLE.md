# 🚀 Quick Start Guide

## Compilation & Execution

### Compile
```bash
g++ secure_pharmacy.cpp -o secure_pharmacy
```

### Run
```bash
./secure_pharmacy
```

---

## 📝 Sample Test Scenario

### Step 1: Register a Patient
```
Main Menu → 1 (Register)
Role: patient
Username: john_patient
Password: pass123
Full name: John Doe
Email: john@email.com
Phone: 1234567890
Address: 123 Main Street
Emergency contact: 9876543210
```
**Result:** Patient registered with ID **P1000**

---

### Step 2: Register a Doctor
```
Main Menu → 1 (Register)
Role: doctor
Username: dr_smith
Password: doc456
Full name: Dr. Sarah Smith
Email: sarah@hospital.com
Phone: 5551234567
Specialization: General Physician
License number: MED12345
```
**Result:** Doctor registered with ID **D2000**

---

### Step 3: Register a Chemist
```
Main Menu → 1 (Register)
Role: chemist
Username: pharmacy_main
Password: chem789
Full name: Mike Johnson
Email: mike@pharmacy.com
Phone: 5559876543
Pharmacy license: PHARM567
Pharmacy name: Main Street Pharmacy
```
**Result:** Chemist registered with ID **C3000**

---

### Step 4: Doctor Writes Prescription

```
Main Menu → 2 (Login)
Username: dr_smith
Password: doc456
Role: doctor

Doctor Menu → 2 (Write Prescription)
Patient ID: P1000

Medicine 1:
- Name: Amoxicillin
- OTC: 0 (Non-OTC)
- Quantity: 21
- Dosage: 500mg three times daily for 7 days

Add another? y

Medicine 2:
- Name: Paracetamol
- OTC: 1 (OTC)
- Quantity: 10
- Dosage: 500mg as needed for pain

Add another? n
```
**Result:** Prescription **RX1000** created

---

### Step 5: Patient Views Prescription

```
Main Menu → 2 (Login)
Username: john_patient
Password: pass123
Role: patient

Patient Menu → 2 (View My Prescriptions)
```
**Shows:** All prescriptions with medicines and dosages

```
Patient Menu → 3 (View Prescription Status)
```
**Shows:** 
```
Prescription ID    Medicine              Quantity    Status
RX1000            Amoxicillin           21          PENDING
RX1000            Paracetamol           10          PENDING
```

---

### Step 6: Chemist Dispenses Medicine

```
Main Menu → 2 (Login)
Username: pharmacy_main
Password: chem789
Role: chemist

Chemist Menu → 1 (View Prescription)
Prescription ID: RX1000
```
**Shows:** Medicine data ONLY (no patient personal info)

```
Chemist Menu → 2 (Dispense Medicine)
Prescription ID: RX1000
```
**Result:** Status changed to DISPENSED

---

### Step 7: Patient Checks Status Again

```
Patient Menu → 3 (View Prescription Status)
```
**Shows:**
```
Prescription ID    Medicine              Quantity    Status
RX1000            Amoxicillin           21          DISPENSED
RX1000            Paracetamol           10          DISPENSED
```

---

## 🎯 Key Features to Test

### 1. Security Features
- ✅ Try to dispense same prescription twice (should fail)
- ✅ Chemist cannot see patient personal information
- ✅ Only doctors can write prescriptions

### 2. OTC vs Non-OTC
- ✅ Doctor can prescribe both OTC and Non-OTC
- ✅ System tracks medicine type
- ✅ Prevents fake prescriptions

### 3. Data Privacy
- ✅ Patient sees only their own data
- ✅ Doctor sees all patient data (friend class)
- ✅ Chemist sees only medicine data

### 4. File Management
- ✅ Check `users.csv` (only login info)
- ✅ Check `patient_data/P1000_data.csv` (complete patient info)
- ✅ Check `prescriptions/RX1000.csv` (prescription details)
- ✅ Check `prescriptions/P1000_status.csv` (status tracking)

---

## 📂 Expected File Structure After Testing

```
secure_pharmacy_project/
│
├── secure_pharmacy.cpp
├── secure_pharmacy.exe
├── users.csv
│
├── patient_data/
│   └── P1000_data.csv
│
├── prescriptions/
│   ├── RX1000.csv
│   └── P1000_status.csv
│
└── chemist_data/
    └── C3000_dispensing_history.csv
```

---

## 🔍 What to Check in Each File

### users.csv
```csv
john_patient,pass123,patient,P1000
dr_smith,doc456,doctor,D2000
pharmacy_main,chem789,chemist,C3000
```
**Contains:** Only username, password, role, userID

---

### patient_data/P1000_data.csv
```
=== PATIENT PERSONAL INFORMATION ===
Name,John Doe
UserID,P1000
Email,john@email.com
Phone,1234567890
Address,123 Main Street
EmergencyContact,9876543210

=== MEDICAL HISTORY ===

=== PRESCRIPTIONS ===

--- Prescription ID: RX1000 ---
Date: 2025-10-25 10:50:00
Doctor ID: D2000
Medicines Prescribed:
  - Amoxicillin (Non-OTC), Qty: 21, Dosage: 500mg three times daily
  - Paracetamol (OTC), Qty: 10, Dosage: 500mg as needed
Status: PENDING DISPENSING
--- End of Prescription ---
```
**Contains:** Complete patient information

---

### prescriptions/RX1000.csv
```csv
PrescriptionID,RX1000
PatientID,P1000
DoctorID,D2000
Date,2025-10-25 10:50:00
Status,DISPENSED

Medicines:
MedicineID,Name,Type,Quantity,Dosage
MED1234,Amoxicillin,Non-OTC,21,500mg three times daily
MED5678,Paracetamol,OTC,10,500mg as needed
```
**Contains:** Prescription details for chemist

---

## 🎓 OOP Concepts in Action

### When You Register
- **Constructor Overloading:** Different constructors for different user types
- **Encapsulation:** Password stored privately
- **Static Members:** Counter increments for unique ID

### When You Login
- **Polymorphism:** Different menus for different roles
- **Abstraction:** User is abstract, cannot instantiate directly
- **Inheritance:** Patient/Doctor/Chemist inherit from User

### When Doctor Writes Prescription
- **Friend Class:** Doctor accesses Patient's private data
- **File Handling:** Data saved to multiple files
- **Operator Overloading:** Medicine objects easily output

### When Chemist Dispenses
- **Encapsulation:** Chemist cannot see patient personal info
- **File Handling:** Updates multiple files atomically
- **Access Control:** Role-based permissions enforced

---

## ⚠️ Common Issues & Solutions

### Issue 1: "File not found"
**Solution:** Program creates directories automatically, but ensure you have write permissions

### Issue 2: "User already exists"
**Solution:** Choose a different username or delete users.csv to start fresh

### Issue 3: "Patient not found"
**Solution:** Ensure patient is registered before doctor writes prescription

### Issue 4: "Prescription already dispensed"
**Solution:** This is a security feature - cannot dispense twice

---

## 🎯 Testing Checklist

- [ ] Register patient, doctor, chemist
- [ ] Login as each user type
- [ ] Doctor writes prescription with OTC and Non-OTC medicines
- [ ] Patient views complete data
- [ ] Patient views prescription status
- [ ] Chemist views prescription (verify no personal info shown)
- [ ] Chemist dispenses medicine
- [ ] Try to dispense same prescription again (should fail)
- [ ] Patient checks updated status
- [ ] Doctor updates medical history
- [ ] Doctor views all their prescriptions
- [ ] Chemist views dispensing history

---

## 📞 Support

If you encounter any issues:
1. Check file permissions
2. Verify g++ compiler is installed
3. Ensure all files are in the same directory
4. Check README.md for detailed documentation

---

## 🎉 Success Indicators

✅ All users can register and login  
✅ Doctors can write prescriptions  
✅ Patients can view their data  
✅ Chemists can dispense medicines  
✅ Files are created in correct folders  
✅ Status updates correctly  
✅ Privacy is maintained (chemist cannot see patient info)  
✅ Cannot dispense same prescription twice  

---

**Congratulations!** You now have a fully functional secure pharmacy prescription management system demonstrating all major OOP concepts! 🎊
