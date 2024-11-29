# Secure Personality Test and Score Management System  

### Description  
The Secure Personality Test and Score Management System is a console-based application written in **C**. This program allows users to:  
- Log in securely using encrypted passwords and unique usernames (with input hidden as `*`).  
- Take personality quizzes to evaluate their traits.
- Save and retrieve test scores across sessions.
- Suggest jobs to the user according to their traits.

The project includes:  
- **UI**: Includes a user-friendly menu and arrow-key-guided navigation. 

---

### Features  
- **User Authentication**:  
  Users can create accounts and log in securely.  
- **Username Validation**:  
  Username acts as a unique identifier for each user to avoid overwriting.  
- **Password Encryption**:  
  Protects user credentials using encryption techniques.  
- **Password Masking**:  
  Password input is hidden and displayed as `*` for better security.  
- **Personality Quizzes**:  
  Interactive tests to evaluate personality traits.  
- **Score Management**:  
  Saves and retrieves user scores for future logins.  
- **Job Suggestions**:  
  Suggests jobs according to the user's traits.  

---

### Prerequisites  
To run this program, ensure you have:  
- A C compiler (e.g., GCC).  
- Basic knowledge of terminal/console operations.  

---

### How to Run  
1. Clone this repository to your local machine:  
   ```bash
   git clone https://github.com/yourusername/PersonalityTestManagementSystem.git
   cd SecurePersonalityTest
   ```
2. Compile the program:

     ```bash
     gcc -o PersonalityTest_UI "PersonalityTest UI.c" -lm
     ```
3. Run the program:

     ```bash
     ./PersonalityTest_UI
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
- **`users.csv`** - File to securely store user data and scores.

---

### License
This project is open-source under the [MIT License](https://opensource.org/licenses/MIT).
