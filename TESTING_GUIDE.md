# 🧪 Complete Testing Guide - Step by Step

## Prerequisites

### Step 1: Compile the Program
Open your terminal/command prompt in the project directory and run:

```bash
g++ secure_pharmacy.cpp -o secure_pharmacy
```

**Expected Output:** No errors, `secure_pharmacy.exe` file created

---

## 🎯 Test Suite 1: Patient Functionality

### Test 1.1: Patient Login & View Complete Records

**Steps:**
1. Run the program:
   ```bash
   ./secure_pharmacy
   ```
   Or on Windows:
   ```bash
   secure_pharmacy.exe
   ```

2. At Main Menu, enter: `2` (Login)

3. Enter credentials:
   ```
   Username: john_doe
   Password: pass123
   Role: patient
   ```

4. **Expected:** Login successful, Patient Menu appears with User ID P1001

5. Select: `1` (View My Complete Medical Records)

6. **Expected Output:**
   - Personal information (Name, Email, Phone, Address)
   - Medical history entries with timestamps
   - All prescriptions (RX1001 and RX1003)
   - Both DISPENSED and PENDING prescriptions visible

7. Press Enter to continue

---

### Test 1.2: Patient View Prescriptions Only

**Steps:**
1. From Patient Menu, select: `2` (View My Prescriptions Only)

2. **Expected Output:**
   - Only prescription section displayed
   - No personal info shown
   - Both prescriptions visible with medicine details

---

### Test 1.3: Patient Check Prescription Status

**Steps:**
1. From Patient Menu, select: `3` (View Prescription Status)

2. **Expected Output:**
   ```
   Prescription ID    Medicine                 Quantity    Status
   ------------------------------------------------------------------
   RX1001            Metformin                60          DISPENSED
   RX1001            Glimepiride              30          DISPENSED
   RX1003            Metformin                60          PENDING
   RX1003            Aspirin                  30          PENDING
   ```

3. Verify:
   - ✅ RX1001 medicines show DISPENSED
   - ✅ RX1003 medicines show PENDING

4. Select: `0` (Logout)

---

## 👨‍⚕️ Test Suite 2: Doctor Functionality

### Test 2.1: Doctor Login & View Patient Data

**Steps:**
1. At Main Menu, enter: `2` (Login)

2. Enter credentials:
   ```
   Username: dr_wilson
   Password: doc789
   Role: doctor
   ```

3. **Expected:** Login successful, Doctor Menu appears with User ID D2001

4. Select: `1` (View Patient Data - Full Access)

5. Enter Patient ID: `P1001`

6. **Expected Output:**
   - Complete patient information visible
   - Personal details (Name, Email, Phone, Address, Emergency Contact)
   - Full medical history
   - All prescriptions
   - **This demonstrates Friend Class access!**

7. Press Enter to continue

---

### Test 2.2: Doctor Write New Prescription

**Steps:**
1. From Doctor Menu, select: `2` (Write Prescription)

2. Enter Patient ID: `P1002`

3. **Expected:** System confirms patient exists, generates Prescription ID (e.g., RX1005)

4. Add Medicine #1:
   ```
   Medicine Name: Azithromycin
   Is this OTC? (1=Yes, 0=No): 0
   Quantity: 6
   Dosage Instructions: 500mg once daily for 3 days
   Add another medicine? (y/n): y
   ```

5. Add Medicine #2:
   ```
   Medicine Name: Cough Syrup
   Is this OTC? (1=Yes, 0=No): 1
   Quantity: 1
   Dosage Instructions: 10ml three times daily
   Add another medicine? (y/n): n
   ```

6. **Expected Output:**
   - "Prescription written successfully!"
   - Prescription ID displayed
   - Files created automatically

7. **Verify Files Created:**
   - Check `patient_data/P1002_data.csv` - prescription added
   - Check `prescriptions/RX1005.csv` - new file created
   - Check `prescriptions/P1002_status.csv` - status entries added

---

### Test 2.3: Doctor Update Medical History

**Steps:**
1. From Doctor Menu, select: `3` (Update Patient Medical History)

2. Enter Patient ID: `P1001`

3. Enter Medical History Entry:
   ```
   Blood sugar levels stable, continue current medication
   ```

4. **Expected:** "Medical history updated!" message

5. **Verify:** 
   - Login as patient john_doe
   - View complete records
   - New history entry should appear with timestamp and doctor ID

6. Logout: `0`

---

## 💊 Test Suite 3: Chemist Functionality

### Test 3.1: Chemist View Prescription (Privacy Check)

**Steps:**
1. At Main Menu, enter: `2` (Login)

2. Enter credentials:
   ```
   Username: chemist
   Password: 1234
   Role: chemist
   ```

3. **Expected:** Login successful, Chemist Menu appears with User ID C3000

4. Select: `1` (View Prescription - Medicine Data Only)

5. Enter Prescription ID: `RX1003`

6. **Expected Output:**
   ```
   ========================================
      PRESCRIPTION: RX1003
   ========================================
   PrescriptionID,RX1003
   Date,2025-10-25 10:30:00
   Status,PENDING
   
   Medicines:
   MedicineID,Name,Type,Quantity,Dosage
   MED3001,Metformin,Non-OTC,60,500mg twice daily after meals
   MED3002,Aspirin,OTC,30,75mg once daily
   ========================================
   NOTE: Patient personal info is hidden.
   ```

7. **Verify:**
   - ✅ Medicine data visible
   - ✅ Patient name NOT visible
   - ✅ Patient address NOT visible
   - ✅ Only prescription and medicine info shown
   - **This demonstrates Privacy Protection!**

---

### Test 3.2: Chemist Dispense Medicine

**Steps:**
1. From Chemist Menu, select: `2` (Dispense Medicine)

2. Enter Prescription ID: `RX1003`

3. **Expected Output:**
   ```
   ========================================
      MEDICINES TO DISPENSE
   ========================================
   1. Metformin (Non-OTC) - Qty: 60
   2. Aspirin (OTC) - Qty: 30
   ```

4. System automatically dispenses all medicines

5. **Expected:** "All medicines dispensed successfully!" message

6. **Verify Dispensing:**
   - Status updated to DISPENSED
   - Dispensing logged with timestamp

---

### Test 3.3: Chemist View Dispensing History

**Steps:**
1. From Chemist Menu, select: `3` (View Dispensing History)

2. **Expected Output:**
   ```
   ========================================
         DISPENSING HISTORY
   ========================================
   Prescription ID      Date & Time               Chemist ID
   ------------------------------------------------------------
   RX1000              2025-10-25 11:07:27       C3000
   RX1001              2025-10-20 14:30:00       C3000
   RX1002              2025-10-18 16:45:00       C3000
   RX1003              [current timestamp]       C3000
   ```

3. **Verify:**
   - ✅ All dispensed prescriptions listed
   - ✅ Timestamps recorded
   - ✅ Chemist ID logged
   - **This demonstrates Audit Trail!**

4. Logout: `0`

---

### Test 3.4: Verify Patient Sees Updated Status

**Steps:**
1. Login as patient:
   ```
   Username: john_doe
   Password: pass123
   Role: patient
   ```

2. Select: `3` (View Prescription Status)

3. **Expected Output:**
   ```
   RX1003            Metformin                60          DISPENSED
   RX1003            Aspirin                  30          DISPENSED
   ```

4. **Verify:** Status changed from PENDING to DISPENSED

5. Logout: `0`

---

## 🔒 Test Suite 4: Security & Access Control

### Test 4.1: Wrong Password

**Steps:**
1. Try to login:
   ```
   Username: john_doe
   Password: wrongpass
   Role: patient
   ```

2. **Expected:** "LOGIN FAILED! Check username, password, and role."

---

### Test 4.2: Wrong Role

**Steps:**
1. Try to login:
   ```
   Username: john_doe
   Password: pass123
   Role: doctor
   ```

2. **Expected:** "LOGIN FAILED! Check username, password, and role."

3. **Verify:** Cannot login as different role with same credentials

---

### Test 4.3: Non-existent User

**Steps:**
1. Try to login:
   ```
   Username: hacker123
   Password: anything
   Role: patient
   ```

2. **Expected:** "LOGIN FAILED! Check username, password, and role."

---

## 🎓 Test Suite 5: OOP Concepts Verification

### Test 5.1: Polymorphism (Virtual Functions)

**Verify:**
- Login as different user types (patient, doctor, chemist)
- Each shows different menu (same function name, different behavior)
- **Concept:** Runtime polymorphism with virtual functions

---

### Test 5.2: Inheritance

**Verify:**
- All three user types (Patient, Doctor, Chemist) inherit from User base class
- Common functions like logout work for all
- **Concept:** IS-A relationship

---

### Test 5.3: Friend Class

**Verify:**
- Doctor can view complete patient data (Test 2.1)
- Chemist CANNOT view patient personal info (Test 3.1)
- **Concept:** Friend class gives Doctor special access to Patient private data

---

### Test 5.4: Encapsulation

**Verify:**
- Cannot directly access user passwords
- Data accessed through getters/setters
- **Concept:** Data hiding with private members

---

### Test 5.5: Static Members

**Verify:**
- User IDs increment: P1000, P1001, P1002 (patients)
- User IDs increment: D2000, D2001, D2002 (doctors)
- User IDs increment: C3000, C3001 (chemists)
- **Concept:** Static counters shared across all instances

---

## 📋 Complete Test Checklist

### Functional Tests
- [ ] Patient can view complete records
- [ ] Patient can view prescriptions only
- [ ] Patient can check prescription status
- [ ] Doctor can view any patient data
- [ ] Doctor can write prescriptions
- [ ] Doctor can update medical history
- [ ] Chemist can view prescription (medicine only)
- [ ] Chemist can dispense medicines
- [ ] Chemist can view dispensing history

### Security Tests
- [ ] Wrong password rejected
- [ ] Wrong role rejected
- [ ] Non-existent user rejected
- [ ] Chemist cannot see patient personal info
- [ ] Patient cannot access other patients' data

### OOP Concepts
- [ ] Polymorphism demonstrated (different menus)
- [ ] Inheritance working (all derive from User)
- [ ] Friend class working (Doctor has special access)
- [ ] Encapsulation working (private data protected)
- [ ] Static members working (unique ID generation)
- [ ] Abstraction working (User is abstract base class)
- [ ] Operator overloading (Medicine class)
- [ ] Constructor overloading (multiple constructors)

### Data Integrity
- [ ] Files created correctly
- [ ] Status updates properly (PENDING → DISPENSED)
- [ ] Timestamps recorded
- [ ] Audit trail maintained
- [ ] No data corruption

---

## 🐛 Common Issues & Solutions

### Issue 1: "Prescription not found"
**Solution:** Make sure you're entering the correct Prescription ID (e.g., RX1003, not rx1003)

### Issue 2: "Patient not found"
**Solution:** Use exact Patient ID format (e.g., P1001, not p1001)

### Issue 3: Compilation errors
**Solution:** 
```bash
g++ -std=c++11 secure_pharmacy.cpp -o secure_pharmacy
```

### Issue 4: Files not updating
**Solution:** Check file permissions, run from correct directory

---

## 🎯 Quick Test Script

For rapid testing, follow this sequence:

```
1. Compile: g++ secure_pharmacy.cpp -o secure_pharmacy
2. Run: ./secure_pharmacy
3. Login as patient (john_doe/pass123) → View status
4. Logout
5. Login as chemist (chemist/1234) → Dispense RX1003
6. Logout
7. Login as patient (john_doe/pass123) → Verify status changed
8. Logout
9. Login as doctor (dr_wilson/doc789) → View patient P1001
10. Exit
```

**Time:** ~5 minutes for complete test

---

## ✅ Success Criteria

Your system passes all tests if:
- ✅ All user types can login with correct credentials
- ✅ Each user type sees appropriate menu
- ✅ Privacy is maintained (chemist can't see patient info)
- ✅ Prescriptions can be written and dispensed
- ✅ Status updates correctly
- ✅ Audit trail is maintained
- ✅ All OOP concepts are demonstrated
- ✅ Security checks work properly

---

**Ready to test!** Start with Test Suite 1 and work your way through.
