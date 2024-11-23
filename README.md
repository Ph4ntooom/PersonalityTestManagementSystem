# Secure Personality Test and Score Management System  
This project is **Under Development**!
### Description  
The Secure Personality Test and Score Management System is a console-based application written in **C**. This program allows users to:  
- Log in securely using encrypted passwords (with input hidden as `*`).  
- Take personality quizzes to evaluate their traits.
- Save and retrieve test scores across sessions.
- Suggest jobs to the user according to their traits.

The project is available in two versions:  
1. **With UI**: Includes a user-friendly menu and guided navigation.  
2. **Without UI**: Simplified version for quick functionality testing.  

---

### Features  
- **User Authentication**:  
  Users can create accounts and log in securely.  
- **Password Encryption**:  
  Protects user credentials using encryption techniques.  
- **Password Masking**:  
  Password input is hidden and displayed as `*` for better security.  
- **Personality Quizzes**:  
  Interactive tests to evaluate personality traits.  
- **Score Management**:  
  Saves and retrieves user scores for future logins.  

---

### Prerequisites  
To run this program, ensure you have:  
- A C compiler (e.g., GCC).  
- Basic knowledge of terminal/console operations.  

---

### How to Run  
1. Clone this repository to your local machine:  
   ```bash
   git clone https://github.com/yourusername/SecurePersonalityTest.git
   cd SecurePersonalityTest
   ```
2. Compile the program:

   For the version **with UI**:
     ```bash
     gcc -o PersonalityTest_UI "PersonalityTest UI.c" -lm
     ```
    For the version **without UI**:
     ```bash
     gcc -o PersonalityTest PersonalityTest.c -lm
     ```
4. Run the program:

   For the version **with UI**:
     ```bash
     ./PersonalityTest_UI
     ```
    For the version **without UI**:
     ```bash
     ./PersonalityTest
     ```

---

### Learning Insights  
- **Authentication and Encryption**: Secure handling of user credentials.  
- **File I/O**: Reading and writing data to a file for persistent storage.  
- **UI Design**: (For the UI version) Building a user-friendly console interface.  
- **Password Masking**: Ensuring user privacy while entering sensitive information.  

---

### File Structure  
- **`PersonalityTest UI.c`** - The program with a menu-based user interface.
- **`PersonalityTest.c`** - A streamlined version without a user interface.
- **`users.csv`** - File to securely store user data and scores.

---

### License
This project is open-source under the [MIT License](https://opensource.org/licenses/MIT).
