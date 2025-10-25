# OOP Concepts Detailed Explanation

## 📚 Complete OOP Concepts Implementation Guide

---

## 1. INHERITANCE (IS-A Relationship)

### Definition
A mechanism where a new class (derived/child) inherits properties and methods from an existing class (base/parent).

### Implementation in Our Project
```cpp
class User {  // Base/Parent Class
    // Common attributes and methods
};

class Patient : public User {  // Derived/Child Class
    // Patient-specific attributes and methods
};

class Doctor : public User {   // Derived/Child Class
    // Doctor-specific attributes and methods
};

class Chemist : public User {  // Derived/Child Class
    // Chemist-specific attributes and methods
};
```

### Why We Used It
- Avoids code duplication (username, password, userID common to all)
- Establishes IS-A relationship: "Patient IS-A User", "Doctor IS-A User"
- Promotes code reusability

---

## 2. POLYMORPHISM (Many Forms)

### Definition
Ability of objects to take multiple forms. Same function name behaves differently for different classes.

### Types Implemented

#### a) Runtime Polymorphism (Virtual Functions)
```cpp
// In Base Class
virtual void displayMenu() = 0;  // Pure virtual function
virtual bool performOperation(int choice) = 0;

// In Patient Class
void displayMenu() override {
    // Patient-specific menu
}

// In Doctor Class
void displayMenu() override {
    // Doctor-specific menu
}

// In Chemist Class
void displayMenu() override {
    // Chemist-specific menu
}
```

#### b) Compile-time Polymorphism (Constructor Overloading)
```cpp
User();  // Default constructor
User(string uname, string pass, string r, ...);  // Parameterized
User(string uname, string pass, string r, string id, ...);  // For existing users
```

### Why We Used It
- Single interface (`displayMenu()`) but different implementations
- Enables dynamic binding at runtime
- User pointer can point to Patient, Doctor, or Chemist objects

---

## 3. ABSTRACTION (Hiding Complexity)

### Definition
Hiding implementation details and showing only essential features.

### Implementation
```cpp
class User {
    // Pure virtual functions make this an abstract class
    virtual void displayMenu() = 0;
    virtual bool performOperation(int choice) = 0;
};
```

### Why We Used It
- Cannot create `User` object directly (abstract class)
- Forces derived classes to implement specific methods
- Provides a common interface for all user types

---

## 4. ENCAPSULATION (Data Hiding)

### Definition
Bundling data and methods together, restricting direct access to some components.

### Implementation
```cpp
class User {
private:
    string username;  // Cannot be accessed directly
    string password;  // Hidden from outside
    string role;

public:
    // Controlled access through methods
    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

class Medicine {
private:
    string medicineID;
    string name;
    bool isOTC;
    int quantity;
    string dosage;

public:
    // Getters
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    
    // Setters
    void setName(string n) { name = n; }
    void setQuantity(int qty) { quantity = qty; }
};
```

### Why We Used It
- Protects sensitive data (password, personal info)
- Provides controlled access through getters/setters
- Can add validation in setter methods

---

## 5. CONSTRUCTOR OVERLOADING

### Definition
Multiple constructors with different parameters in the same class.

### Implementation
```cpp
// Default constructor
User() : isLoggedIn(false) {}

// Parameterized constructor (for new users)
User(string uname, string pass, string r, string n = "", string e = "", string p = "")
    : username(uname), password(pass), role(r), name(n), email(e), phone(p), isLoggedIn(false) {
    userID = generateUserID();
}

// Constructor for loading existing user
User(string uname, string pass, string r, string id, string n, string e, string p)
    : username(uname), password(pass), role(r), userID(id), name(n), email(e), phone(p), isLoggedIn(false) {}
```

### Why We Used It
- Different initialization scenarios (new vs existing users)
- Flexibility in object creation
- Default values for optional parameters

---

## 6. FRIEND CLASS

### Definition
A class that can access private and protected members of another class.

### Implementation
```cpp
class Patient : public User {
private:
    string address;
    string emergencyContact;
    string patientDataFile;
    
public:
    // ... other methods ...
    
    friend class Doctor;  // Doctor can access Patient's private members
};
```

### Why We Used It
- Doctors need full access to patient data (medical necessity)
- Controlled violation of encapsulation for specific use case
- Real-world scenario: Doctors must see all patient information

---

## 7. OPERATOR OVERLOADING

### Definition
Giving special meaning to operators for user-defined types.

### Implementation
```cpp
class Medicine {
    // ... members ...
    
    // Overloading << operator for easy output
    friend ostream& operator<<(ostream& os, const Medicine& med) {
        os << "ID: " << med.medicineID << ", Name: " << med.name 
           << ", Type: " << (med.isOTC ? "OTC" : "Non-OTC") 
           << ", Qty: " << med.quantity << ", Dosage: " << med.dosage;
        return os;
    }
};

// Usage
Medicine med;
cout << med;  // Calls overloaded operator
```

### Why We Used It
- Makes code more intuitive and readable
- Enables natural syntax for custom objects
- Simplifies output operations

---

## 8. STATIC MEMBERS

### Definition
Members that belong to the class rather than individual objects.

### Implementation
```cpp
class User {
public:
    // Static variables (shared by all User objects)
    static int patientCounter;
    static int doctorCounter;
    static int chemistCounter;
    
    // Static methods (can be called without object)
    static unordered_map<string, userinfo> loadUsers() {
        // Implementation
    }
    
    static vector<string> loadFullUserDetails(const string& uname) {
        // Implementation
    }
};

// Initialization (outside class)
int User::patientCounter = 1000;
int User::doctorCounter = 2000;
int User::chemistCounter = 3000;
```

### Why We Used It
- Unique ID generation across all instances
- Shared data (counters) among all users
- Utility functions that don't need object state

---

## 9. VIRTUAL DESTRUCTOR

### Definition
Destructor declared as virtual in base class for proper cleanup in inheritance.

### Implementation
```cpp
class User {
public:
    virtual ~User() {}  // Virtual destructor
};
```

### Why We Used It
- Ensures proper cleanup when deleting derived class objects through base class pointer
- Prevents memory leaks in polymorphic scenarios
- Good practice in inheritance hierarchies

---

## 10. PROTECTED MEMBERS

### Definition
Members accessible in derived classes but not outside the class hierarchy.

### Implementation
```cpp
class User {
protected:
    string userID;       // Accessible in Patient, Doctor, Chemist
    string email;
    string phone;
    string name;
    bool isLoggedIn;
    
    string generateUserID() {  // Protected method
        // Implementation
    }
};
```

### Why We Used It
- Derived classes need access to these members
- Still hidden from outside world (encapsulation)
- Balance between private and public access

---

## 11. FILE HANDLING

### Definition
Reading from and writing to files for persistent data storage.

### Implementation
```cpp
// Writing to file
ofstream fout("users.csv", ios::app);
fout << username << "," << password << "," << role << "," << userID << endl;
fout.close();

// Reading from file
ifstream fin("users.csv");
string line;
while (getline(fin, line)) {
    // Process line
}
fin.close();
```

### Why We Used It
- Persistent data storage (survives program termination)
- Organized data structure (CSV format)
- Separate files for different data types

---

## 12. STRUCTURES

### Definition
User-defined data types that group related variables.

### Implementation
```cpp
struct userinfo {
    string password;
    string role;
};

struct Medicine {
    string medicineID;
    string name;
    bool isOTC;
    int quantity;
    string dosage;
};
```

### Why We Used It
- Group related data together
- Simple data containers
- Easy to pass multiple values

---

## 🎯 Real-World Application

### Access Control Matrix

| Feature | Patient | Doctor | Chemist |
|---------|---------|--------|---------|
| View own data | ✅ | ✅ | ✅ |
| View patient personal info | ✅ (own) | ✅ (all) | ❌ |
| View patient medical history | ✅ (own) | ✅ (all) | ❌ |
| Write prescription | ❌ | ✅ | ❌ |
| View prescription medicines | ✅ (own) | ✅ (all) | ✅ (medicine data only) |
| Dispense medicine | ❌ | ❌ | ✅ |
| Update medical history | ❌ | ✅ | ❌ |

---

## 🔐 Security Implementation

### 1. OTC vs Non-OTC Classification
```cpp
bool isOTC;  // true = OTC, false = Non-OTC
```
- **OTC:** Over-the-counter, no prescription needed
- **Non-OTC:** Requires valid doctor prescription
- **Prevents:** Fake prescriptions for controlled substances

### 2. Role-Based Access
```cpp
if (role == "patient") {
    currentUser = new Patient(details);
} else if (role == "doctor") {
    currentUser = new Doctor(details);
} else if (role == "chemist") {
    currentUser = new Chemist(details);
}
```

### 3. Prescription Status Tracking
```cpp
Status: PENDING → DISPENSED
```
- Prevents duplicate dispensing
- Complete audit trail

---

## 📊 Data Flow

```
1. Doctor writes prescription
   ↓
2. Saved to patient file (complete info)
   ↓
3. Saved to prescription file (for chemist)
   ↓
4. Chemist views prescription (medicine data only)
   ↓
5. Chemist dispenses medicine
   ↓
6. Status updated to DISPENSED
   ↓
7. Patient can view status
```

---

## 💡 Key Takeaways

1. **Inheritance** reduces code duplication
2. **Polymorphism** enables flexible, extensible code
3. **Abstraction** hides complexity
4. **Encapsulation** protects data
5. **Friend classes** allow controlled access
6. **Static members** share data across instances
7. **File handling** provides persistence
8. **OOP principles** solve real-world problems

---

## 🎓 Learning Outcomes

✅ Understanding of all major OOP concepts  
✅ Real-world application of theory  
✅ Security and privacy implementation  
✅ File-based data management  
✅ Role-based access control  
✅ Clean, maintainable code structure  

---

This project demonstrates how OOP concepts work together to create a secure, maintainable, and extensible system that solves a real-world problem.
