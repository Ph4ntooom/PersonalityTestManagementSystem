//		Aayan Hassan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERS 100
#define CSV_FILE "users.csv"
#define STRING_LENGTH 50
#define QUESTIONS 5
#define CRYPT_KEY 24568

// MAIN PORTAL STRUCTURE
struct Portal{
    char username[STRING_LENGTH];
    char password[STRING_LENGTH];
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
    printf("Enter Username: ");
    scanf("%s", newUser.username);
	printf("Enter Password: ");
    getPassword(newUser.password);
    
    crypt(newUser.password);
    newUser.quizScore = 0;

    users[userCount++] = newUser;
    printf("User registered successfully!\n");
    
    saveUsersToCSV();
}

// ACCOUNT LOGIN FUNCTION
int loginUser(){
    char username[STRING_LENGTH];
    char password[STRING_LENGTH];
    printf("Enter Username: ");
    scanf("%49s", username);
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
    printf("Invalid username or password.\n");
    return 0;
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
    int choice;
    do {
        printf("\n--- User Menu ---\n");
        printf("1. Take Quiz\n");
        printf("2. View Account Information\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                takeQuiz();
                break;
            case 2:
                viewUserInfo();
                break;
            case 3:
                printf("Logging out...\n");
                loggedInUserIndex = -1;
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }while(choice!=3);
}

int main() {
    loadUsersFromCSV();
    
    
    int choice;
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                registerUser();
                break;
            case 2:
                if(loginUser()){
                    userMenu();
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }while(choice!=3);
    
    
    saveUsersToCSV();
    return 0;
}
