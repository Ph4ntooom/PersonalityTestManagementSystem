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
	int extraversion, introversion, sensing, intuition, thinking, feeling, judging, perceiving;
};


struct Portal users[USERS]; // ARRAY TO BE USED FOR STORING EVERYTHING BACK AND FORTH FROM THE CSV
int userCount = 0;
int loggedInUserIndex = -1;

char *questions[51]={
    "You regularly make new friends?",
    "You feel comfortable just walking up to someone you find interesting and striking up a conversation?",
    "You usually prefer to be around others rather than on your own?",
    "You enjoy participating in team-based activities?",
    "You can easily connect with people you have just met?",
    "Your friends would describe you as lively and outgoing?",
    "You feel more drawn to busy, bustling atmospheres than to quiet, intimate places?",
    

    "You find the idea of networking or promoting yourself to strangers very daunting?",
    "You rarely worry about whether you make a good impression on people you meet?",
    "You enjoy solitary hobbies or activities more than group ones?",
    "You usually wait for others to introduce themselves first at social gatherings?",
    "You avoid making phone calls?",
    

    "You enjoy exploring unfamiliar ideas and viewpoints?",
    "You are drawn to various forms of creative expression, such as writing?",
    "Complex and novel ideas excite you more than simple and straightforward ones?",
    "You enjoy experimenting with new and untested approaches?",
    "You prefer tasks that require you to come up with creative solutions rather than follow concrete steps?",
    "You actively seek out new experiences and knowledge areas to explore?",
    
    
    "You are not too interested in discussions about various interpretations of creative works?",
    "You become bored or lose interest when the discussion gets highly theoretical?",
    "You like to use organizing tools like schedules and lists?",
    "You struggle with deadlines?",
    "You are not too interested in discussing theories on what the world could look like in the future?",
    
    
    "When facts and feelings conflict, you usually find yourself following your heart?",
    "You often feel overwhelmed?",
    "Your mood can change very quickly?",
    "You prioritize facts over peoples feelings when determining a course of action?",
    "Peoples stories and emotions speak louder to you than numbers or data?",
    "Your emotions control you more than you control them?",
    "You prioritize proving your point over preserving the feelings of others?",
    "When making decisions, you focus more on how the affected people might feel than on what is most logical or efficient?",
    "In disagreements, you prioritize being sensitive over being completely honest?",
    "You rarely second-guess the choices that you have made?",
    "Your living and working spaces are clean and organized?",
    
    
    "You are still bothered by mistakes that you made a long time ago?",
    "You usually base your choices on objective facts rather than emotional impressions?",
    "You are not easily swayed by emotional arguments?",
    "You favor efficiency in decisions, even if it means disregarding some emotional aspects?",
    "You enjoy debating ethical dilemmas?",
    "If a decision feels right to you, you often act on it without needing further proof?",
    "When someone thinks highly of you, you wonder how long it will take them to feel disappointed in you?",
    
    
    "You prioritize and plan tasks effectively, often completing them well before the deadline?",
    "You are prone to worrying that things will take a turn for the worse?",
    "You prefer to do your chores before allowing yourself to relax?",
    "You like to have a to-do list for each day?",
    "Your personal work style is closer to spontaneous bursts of energy than organized and consistent efforts?",
    "You complete things methodically without skipping over any steps?",
    
    
    "You struggle with deadlines?",
    "You rarely feel insecure?",
    "You find it challenging to maintain a consistent work or study schedule?",
    "If your plans are interrupted, your top priority is to get back on track as soon as possible?"
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
// Pretty Printing Function Ends



// FUNCTION FOR ENCRYPTING AND DECRYPTING THE PASSWORD
void crypt(char *password){
	int i;
    for(i=0; i<strlen(password); i++){
        password[i] ^= CRYPT_KEY;
    }
}

// VALIDATING USERNAME TO BE UNIQUE
int validateUsername(char *username){
	for(int i=0; i<userCount; i++){
		if(strcmp(username, users[i].username)==0){
			return 1;
		}
	}
	return 0;
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
    while(fscanf(file, "%49[^,],%49[^,],%d,%d,%d,%d,%d,%d,%d,%d\n",
                  users[userCount].username,
                  users[userCount].password,
                  &users[userCount].extraversion,
                  &users[userCount].introversion,
                  &users[userCount].sensing,
                  &users[userCount].intuition,
                  &users[userCount].thinking,
                  &users[userCount].feeling,
                  &users[userCount].judging,
                  &users[userCount].perceiving)==10){
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
        fprintf(file, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                users[i].username,
                users[i].password,
                users[i].extraversion,
                users[i].introversion,
                users[i].sensing,
                users[i].intuition,
                users[i].thinking,
                users[i].feeling,
                users[i].judging,
                users[i].perceiving);
    }
    fclose(file);
    printf("%s*\n", CSV_FILE);
}

// ACCOUNT REGISTRATION FUNCTION
void registerUser(){
    if(userCount>=USERS){
        printf("Cannot register more users. Maximum capacity reached.\n");
        return;
    }
	
    struct Portal newUser;
    printf("--- REGISTER ---\n");
    printf("Set Username: ");
    scanf("%s", newUser.username);
    while(validateUsername(newUser.username)){
		system("cls");
    	printf("Username already exists, try again!\n");
    	printf("Set Username: ");
    	scanf("%s", newUser.username);
	}
    printf("Set Password: ");
    getPassword(newUser.password);
    
    crypt(newUser.password);
    
    newUser.extraversion = 0;
    newUser.introversion = 0;
    newUser.sensing = 0;
    newUser.intuition = 0;
    newUser.thinking = 0;
    newUser.feeling = 0;
    newUser.judging = 0;
    newUser.perceiving = 0;
    
    users[userCount++] = newUser;
    printf("User registered successfully!\n");
    
    saveUsersToCSV();
    mainMenu();
}

// ACCOUNT LOGIN FUNCTION
int loginUser(){
    char username[STRING_LENGTH];
    char password[STRING_LENGTH];

    printf("--- LOGIN ---\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    getPassword(password);
    
    crypt(password);
    for(int i=0; i<userCount; i++){
        if(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0){
        	system("cls");
            printf("Login successful!\n");
            loggedInUserIndex = i;
            return 1;
        }
    }
	system("cls");
    printf("Invalid username or password.\n");
	mainMenu();
}

void askQue(int n){
    int points, choice = 3, score = 3, space = (137 - strlen(questions[n])) / 2 , i;
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (i = 0; i < space ; i++){
    	printf(" ");
	}
    printf("%d- %s\n",n+1,questions[n]);
    printf("\n                                     ");
    printf("Strongly Agree   Agree   Nuetral   Disagree   Strongly Disagree\n");
    printf("                                                                 ^");
    while (choice != '\r') {
		choice = getch();
    	if (choice == 224){
        	choice = getch();
        	if (choice == 75 && score > 1){ //to move left
        		switch (score){
        			case 2:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b");
        				break;
	        		case 3:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b");
	        			break;
	        		case 4:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b\b");
	        			break;
	        		case 5:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	        			break;
					}
	        	printf("^");
	        	score--;
			}
			else if (choice == 77 && score < 5){ //to move right
				switch (score){
	        		case 1:
	        			printf("\b \b            ");
	        			break;
	        		case 2:
	        			printf("\b \b         ");
	        			break;
	        		case 3:
	        			printf("\b \b          ");
	        			break;
	        		case 4:
	        			printf("\b \b               ");
	        			break;
				}
				printf("^");
				score++;
			}
		}  
    }
    
    points = score;

    if(points>=4)
    {
        if(n<7)
        	users[loggedInUserIndex].extraversion++;
        else if(n<12)
        	users[loggedInUserIndex].introversion++;
        else if (n<18)
        	users[loggedInUserIndex].intuition++;
        else if (n<23)
        	users[loggedInUserIndex].sensing++;
        else if (n<34)
        	users[loggedInUserIndex].feeling++;
        else if (n<41)
        	users[loggedInUserIndex].thinking++;
        else if (n<48)
        	users[loggedInUserIndex].judging++;
        else
        	users[loggedInUserIndex].perceiving++;
    }
    else if(points<=2)
    {
        if(n<7)
        users[loggedInUserIndex].introversion++;
        else if(n<12)
        users[loggedInUserIndex].extraversion++;
        else if (n<18)
        users[loggedInUserIndex].sensing++;
        else if (n<23)
        users[loggedInUserIndex].intuition++;
        else if (n<34)
        users[loggedInUserIndex].thinking++;
        else if (n<41)
        users[loggedInUserIndex].feeling++;
        else if (n<48)
        users[loggedInUserIndex].perceiving++;
        else
        users[loggedInUserIndex].judging++;
    }
    else
    {
        if(n<12)
        {
            users[loggedInUserIndex].extraversion++;
            users[loggedInUserIndex].introversion++;
        }
        else if(n<23)
        {
            users[loggedInUserIndex].sensing++;
            users[loggedInUserIndex].intuition++;
        }
        else if(n<41)
        {
            users[loggedInUserIndex].thinking++;
            users[loggedInUserIndex].feeling++;
        }
        else
        {
            users[loggedInUserIndex].perceiving++;
            users[loggedInUserIndex].judging++;
        }
    }

}

void results(){
	system("cls");
	printf("\nYour Personality Results:\n");
    printf("Extraversion: %d, Introversion: %d\n",users[loggedInUserIndex].extraversion,users[loggedInUserIndex].introversion);
    printf("Sensing: %d, Intuition: %d\n",users[loggedInUserIndex].sensing,users[loggedInUserIndex].intuition);
    printf("Thinking: %d, Feeling: %d\n",users[loggedInUserIndex].thinking,users[loggedInUserIndex].feeling);
    printf("Judging: %d, Perceiving: %d\n",users[loggedInUserIndex].judging,users[loggedInUserIndex].perceiving);
    printf("\nCareer Suggestions:\n");
    if(users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion)
    {
        printf("the most suiitable career for you would be carrer related to Education and training,Marketing,Politics and Journalism.\n");
    }
    else if(users[loggedInUserIndex].extraversion < users[loggedInUserIndex].introversion)
    {
        printf("You may excel in  more solitary research-based careers like Writer, Analyst,Skilled trader or Scientist.\n");
    }
    else
    {
        printf("You have a balanced preference for both social and isolated environments, so careers like Project Management, Consulting, or Entrepreneurship might suit you.\n");
    }
    if(users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition)
    {
        printf("You might be suited to practical careers such as Engineering, Accounting, or Healthcare.\n");
    }
    else if(users[loggedInUserIndex].sensing < users[loggedInUserIndex].intuition)
    {
        printf("You may thrive in creative or theoretical fields like Design, Psychology, or Innovation.\n");
    }
    else
    {
        printf("You have a balanced approach to both practical and creative tasks, making you well-suited for careers in Research, Urban Planning, or Product Management.\n");
    }
    if(users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling)
    {
        printf("you may consider analytical careers like Law, IT, or Data Analysis.\n");
    }
    else if(users[loggedInUserIndex].thinking < users[loggedInUserIndex].feeling)
    {
        printf("you are more likely to enjoy  careers which are focused on empathy, such as Counseling, HR, or Social Work.\n");
    }
    else
    {
        printf("You have a very strong approach to decision-making, which may make you excel in roles such as Mediator, Consultant, or Executive Leadership.\n");
    }
    if(users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving)
    {
        printf("You will be good at structured careers like Project Management, Business, or Law.\n");
    }
    else if(users[loggedInUserIndex].judging < users[loggedInUserIndex].perceiving)
    {
        printf("You may excel in flexible careers like Entrepreneurship, Consulting, or the Arts.\n");
    }
    else
    {
        printf("You have a flexible and organized approach, making you ideal for roles in Operations, Event Planning, or Freelancing.\n");
    }
    getch();
    userMenu();
}

// SAMPLE TEST-TAKING FUNCTION
void takeQuiz(){
    if(loggedInUserIndex==-1){
        printf("You must be logged in to take the quiz.\n");
        return;
    }
    printf("\n--- Quiz Time! ---\n");
    for(int i=0; i < 51 ; i++){
        askQue(i);
    }
	
	results();
	
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
    results();
}

// OUTPUT TO SHOW AFTER USER HAVE SUCCEESSFULLY LOGGED IN
void userMenu(){
    int choice, score = 1;
    printf("\n                                                            ");
    printf("--- Main Menu ---\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\n                                                      ");
    printf("Play     Your Results     Sign out\n");
	printf("                                                                     ^");
	while (choice != '\r') {
		choice = getch();
    	if (choice == 224){
        	choice = getch();
        	if (choice == 75 && score > 0){ //to move left
        		switch (score){
        			case 1:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        				break;
	        		case 2:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	        			break;
					}
	        	printf("^");
	        	score--;
			}
			else if (choice == 77 && score < 2){ //to move right
				switch (score){
	        		case 0:
	        			printf("\b \b              ");
	        			break;
	        		case 1:
	        			printf("\b \b              ");
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
            takeQuiz();
            saveUsersToCSV();
            break;
        case 1:
            viewUserInfo();
            break;
        case 2:
            system("cls");
            saveUsersToCSV();
            mainMenu();
            loggedInUserIndex = -1;
            break;
        }
}

void mainMenu(){
	int choice, score = 1;
    printf("\n                                                            ");
    printf("    Main Menu    \n\n\n");
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
                saveUsersToCSV();
            	exit(0);
        }
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

    saveUsersToCSV();
    
    return 0;
}
