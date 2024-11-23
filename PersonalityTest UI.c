#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <winuser.h>

#define USERS 100
#define CSV_FILE "users.csv"
#define STRING_LENGTH 50
#define QUESTIONS 5
#define CRYPT_KEY 24568

int loginUser();
void userMenu();
void mainMenu();
int main();

// MAIN PORTAL STRUCTURE
struct Portal{
    char username[STRING_LENGTH];
    char password[STRING_LENGTH];
    float grade;
    int age;
    char nationality[STRING_LENGTH];
    int quizScore;
};


struct Portal users[USERS]; // ARRAY TO BE USED FOR STORING EVERYTHING BACK AND FORTH FROM THE CSV
int userCount = 0;
int loggedInUserIndex = -1;


// SAMPLE QUESTIONS AND ANSWERS
const char *questions[QUESTIONS]={
    "Is FAST University Good for CS? (Yes)",
    "What is 5 + 7? (12)",
    "Who teaches you PF? (Dr.FarrukhShahid)",
    "How many hours does a lab unit last? (3)",
    "Full form of \"WTF\"? (WelcomeToFAST)"
};

const char *answers[QUESTIONS]={
    "Yes",
    "12",
    "Dr.FarrukhShahid",
    "3",
    "WelcomeToFAST"
};

//Pretty Printing Functions start
void hideTypeCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;                     
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void setFullScreen() {
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void simulateF11Keypress() {
    keybd_event(VK_F11, 0, 0, 0); // Press F11
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0); // Release F11
}

void simulateEnterKeypress() {
    keybd_event(VK_RETURN, 0, 0, 0); // Press F11
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // Release F11
}

void hideScrollBar() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &csbi);
    csbi.dwSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(hConsole, csbi.dwSize);
}

void setConsoleColor(int textColor, int backgroundColor) {
    char colorCode[3];
    sprintf(colorCode, "%X", (backgroundColor << 4) | textColor);
    char command[10];
    sprintf(command, "color %s", colorCode);
    system(command);
}

void setConsoleFontSize(int fontSize) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    
    // Get the current font info
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    
    // Set new font size (width and height)
    cfi.dwFontSize.X = fontSize;  // Width
    cfi.dwFontSize.Y = fontSize;  // Height
    
    // Set the new font
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}
//Pretty Printing Function Ends



// FUNCTION FOR ENCRYPTING AND DECRYPTING THE PASSWORD
void crypt(char *password){
    for(int i=0; i<strlen(password); i++){
        password[i] ^= CRYPT_KEY;
    }
}

// HIDDEN PASSWORD INPUT
void getPassword(char *password){
	int j=0;
    char var;
    do{
        var = getch();
        if((var == '\b' || var == 127) && j > 0){
            printf("\b \b");
            j--;
        }
        else if(var=='\r'){
            j++;
        	break;
		}
        else if(var != '\b'){
            printf("*");
            password[j] = var;
            j++;
        }
    }while (var != '\r');
    password[j-1] = '\0';
    printf("\n");
}

// LOAD THE DATA VALUES FORM THE CSV FILE TO THE "users" ARRAY
void loadUsersFromCSV(){
    FILE *file = fopen(CSV_FILE, "r");
    if(file==NULL){
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    while(fscanf(file, "%49[^,],%49[^,],%d\n",
                  users[userCount].username,
                  users[userCount].password,
                  &users[userCount].quizScore)==3){
        userCount++;
    }
    fclose(file);
}

// SAVING USERS TO CSV FILE // NEED TO USE THIS WHEN EVER THERE's A CHANGE IN VALUES
void saveUsersToCSV(){
    FILE *file = fopen(CSV_FILE, "w");
    if(file==NULL){
        printf("Error opening file for writing.\n");
        return;
    }
	
    for(int i=0; i<userCount; i++){
        fprintf(file, "%s,%s,%d\n",
                users[i].username,
                users[i].password,
                users[i].quizScore);
    }
    fclose(file);
    printf("Data saved to %s successfully!\n", CSV_FILE);
}

// ACCOUNT REGISTRATION FUNCTION
void registerUser(){
    if(userCount>=USERS){
        printf("Cannot register more users. Maximum capacity reached.\n");
        return;
    }
	
    struct Portal newUser;
    printf("Set Username: ");
    scanf("%s", newUser.username);
    printf("Set Password: ");
    getPassword(newUser.password);
    
    crypt(newUser.password);
    newUser.quizScore = 0;
    
    users[userCount++] = newUser;
    printf("User registered successfully!\n");
    
    saveUsersToCSV();
    mainMenu();
}

// ACCOUNT LOGIN FUNCTION
int loginUser(){
    char username[STRING_LENGTH];
    char password[STRING_LENGTH];
    int j = 0;
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    getPassword(password);
    
    crypt(password);
    
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0){
            printf("Login successful!\n");
            loggedInUserIndex = i;
            return 1;
        }
    }
	system("cls");
    printf("Invalid username or password.\n");
	mainMenu();
}

// SAMPLE TEST-TAKING FUNCTION
void takeQuiz(){
    if(loggedInUserIndex==-1){
        printf("You must be logged in to take the quiz.\n");
        return;
    }

    int score = 0;
    char answer[STRING_LENGTH];

    printf("\n--- Quiz Time! ---\n");
    for(int i=0; i<QUESTIONS; i++){
        printf("Q%d: %s\n", i + 1, questions[i]);
        printf("Your answer: ");
        scanf("%s", answer);
        
        if(strcmp(answer, answers[i]) == 0){
            score++;
        }
    }

    printf("You scored %d out of %d!\n", score, QUESTIONS);

    users[loggedInUserIndex].quizScore = score;
    saveUsersToCSV();
}

// FETCHING THE LOGGED-IN USER's INFORMATION FROM THE ARRAY
void viewUserInfo(){
    if (loggedInUserIndex == -1) {
        printf("You must be logged in to view account information.\n");
        return;
    }

    struct Portal user = users[loggedInUserIndex];
    printf("\n--- Account Information ---\n");
    printf("Username: %s\n", user.username);
    printf("Quiz Score: %d out of %d\n", user.quizScore, QUESTIONS);
}

// OUTPUT TO SHOW AFTER USER HAVE SUCCEESSFULLY LOGGED IN
void userMenu(){
    int choice, score = 1;
    printf("\n                                                            ");
    printf("--- Main Menu ---\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\n                                                      ");
    printf("Play     Your Results     Exit\n");
	printf("                                                                     ^");

    switch(choice){
        case 0:
            takeQuiz();
            break;
        case 1:
            viewUserInfo();
            break;
        case 2:
            printf("Logging out...\n");
            loggedInUserIndex = -1;
            break;
        }
}

void mainMenu(){
	int choice, score = 1;
    printf("\n                                                            ");
    printf("--- Main Menu ---\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\n                                                      ");
    printf("Register     Login     Exit\n");
	printf("                                                                     ^");
		
	while (choice != '\r') {
		choice = getch();
    	if (choice == 224){
        	choice = getch();
        	if (choice == 75 && score > 0){ //to move left
        		switch (score){
        			case 1:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b");
        				break;
	        		case 2:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b");
	        			break;
					}
	        	printf("^");
	        	score--;
			}
			else if (choice == 77 && score < 2){ //to move right
				switch (score){
	        		case 0:
	        			printf("\b \b            ");
	        			break;
	        		case 1:
	        			printf("\b \b         ");
	        			break;
				}
				printf("^");
				score++;
			}
		}  
    }
	choice = score;
	system("cls");
        switch(choice){
            case 0:
                registerUser();
                break;
            case 1:
                if(loginUser()){
                	userMenu();
                	break;
				}
				else{
					mainMenu();
					break;
				}
            case 2:
            	exit(0);
        }
    saveUsersToCSV();
    system("cls");
}

int main() {
	setFullScreen();
	
	simulateF11Keypress();
	
	hideScrollBar();
	
	hideTypeCursor();
	
	setConsoleColor(0,9);
	
	setConsoleFontSize(30);
	
    loadUsersFromCSV();
    
    mainMenu();
    
    return 0;
}
