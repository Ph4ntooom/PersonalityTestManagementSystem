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

void goodbye(){
	setConsoleFontSize(80);
	printf("                     GoodBye\n");
	printf("                   .''.    .'',\n");
	printf("                   |  |   /  /\n");
	printf("                   |  |  /  /\n");
	printf("                   |  | /  /\n");
	printf("                   |  |/  ;-._\n");
	printf("                   }  ` _/  / ;\n");
	printf("                   |  /` ) /  /\n");
	printf("                   | /  /_/\\_/\\ \n");
	printf("                   |/  /      |\n");
	printf("                   (  ' \\ '-  |\n");
	printf("                    \\    `.  /\n");
	printf("                     |      |\n");
	printf("                     |      |\n");
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
	int i;
	for(i=0; i<userCount; i++){
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
    int i;
    for(i=0; i<userCount; i++){
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
    int i;
    for(i=0; i<userCount; i++){
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
    printf("Strongly Disagree   Disagree   Nuetral   Agree   Strongly Agree\n");
    printf("                                                                       ^");
    while (choice != '\r') {
		choice = getch();
    	if (choice == 224){
        	choice = getch();
        	if (choice == 75 && score > 1){ //to move left
        		switch (score){
        			case 2:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        				break;
	        		case 3:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b\b\b");
	        			break;
	        		case 4:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b");
	        			break;
	        		case 5:
	        			printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	        			break;
					}
	        	printf("^");
	        	score--;
			}
			else if (choice == 77 && score < 5){ //to move right
				switch (score){
	        		case 1:
	        			printf("\b \b              ");
	        			break;
	        		case 2:
	        			printf("\b \b           ");
	        			break;
	        		case 3:
	        			printf("\b \b         ");
	        			break;
	        		case 4:
	        			printf("\b \b             ");
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
        	users[loggedInUserIndex].extraversion = points;
        else if(n<12)
        	users[loggedInUserIndex].introversion = points;
        else if (n<18)
        	users[loggedInUserIndex].intuition = points;
        else if (n<23)
        	users[loggedInUserIndex].sensing = points;
        else if (n<34)
        	users[loggedInUserIndex].feeling = points;
        else if (n<41)
        	users[loggedInUserIndex].thinking = points;
        else if (n<48)
        	users[loggedInUserIndex].judging = points;
        else
        	users[loggedInUserIndex].perceiving = points;
    }
    else if(points<=2)
    {
        if(n<7)
        users[loggedInUserIndex].introversion = points;
        else if(n<12)
        users[loggedInUserIndex].extraversion = points;
        else if (n<18)
        users[loggedInUserIndex].sensing = points;
        else if (n<23)
        users[loggedInUserIndex].intuition = points;
        else if (n<34)
        users[loggedInUserIndex].thinking = points;
        else if (n<41)
        users[loggedInUserIndex].feeling = points;
        else if (n<48)
        users[loggedInUserIndex].perceiving = points;
        else
        users[loggedInUserIndex].judging = points;
    }
    else
    {
        if(n<12)
        {
            users[loggedInUserIndex].extraversion = points;
            users[loggedInUserIndex].introversion = points;
        }
        else if(n<23)
        {
            users[loggedInUserIndex].sensing = points;
            users[loggedInUserIndex].intuition = points;
        }
        else if(n<41)
        {
            users[loggedInUserIndex].thinking = points;
            users[loggedInUserIndex].feeling = points;
        }
        else
        {
            users[loggedInUserIndex].perceiving = points;
            users[loggedInUserIndex].judging = points;
        }
    }

}

void introvert(){
	printf("\n\n");
	printf("As an introvert, you are likely well-suited to many situations.");
	printf("Your tendency to be reserved helps you pace yourself effectively. You\n");
	printf("likely listen to others more carefully than most people.");
	printf("Being introspective, you enjoy focused 'alone time' for insights. You may be\n");
	printf("You may be sensitive to your environment, picking up cues quickly.");
	printf("This ability makes you great at reading many different situations.\n");
}

void extrovert(){
	printf("\n\n");
	printf("As an extrovert, you are naturally drawn to engaging with others.");
	printf("You thrive on the responses of people and events around you.\n");
	printf("You enjoy pushing limits and discovering what the world can do.");
	printf("While life has its limits, you lean toward taking the initiative.\n");
	printf("You often rely on the world around you for energy and validation.\n");
}

void intuitive(){
	printf("\n\n");
	printf("As someone with the Intuitive trait, you prefer to use your imagination.");
	printf("You seek new ideas and possibilities in your daily life.\n");
	printf("Your mind tends to point inward while focusing beyond the horizon.");
	printf("You likely live a life of questioning, wondering, and connecting \n");
	printf("dots. You may love the theoretical and think about the 'bigger picture.'");
	printf("You often ask, 'What if?' and ponder future possibilities.\n");
}

void sensing(){
	printf("\n\n");
	printf("As a Sensing individual, you're most in touch with the present.");
	printf("You focus on what occurs in front of you right now. This doesn't mean\n");
	printf("you disregard the past or future entirely.");
	printf("You view both from the perspective of how they influence your actions. This makes you a\n");
	printf("focused and practical person.");
	printf("You root your thinking in the actionable, tangible, and useful. But make no mistake, you can be creative\n");
	printf("within that realm.\n");
}

void thinking(){
	printf("\n\n");
	printf("As someone with the Thinking trait, you lean on objective information.");
	printf("Knowledge is your indispensable tool when making decisions. Once \n");
	printf("you gather the facts, you test alternatives against logic and reason.");
	printf("You seek the most effective or realistic decision based on those \n");
	printf("standards. You manage your relationships with fairness and effectiveness.");
	printf("Your passions are born from respect for others.\n");
}

void feeling(){
	printf("\n\n");
	printf("As someone with the Feeling trait, you often follow your heart and emotions.");
	printf("Sometimes, you may do this without even realizing it.\n");
	printf("You may show it in different ways, but you tend to be caring and warm.");
	printf("You're compassionate and often protective of those you care about.\n");
	printf("Whether it's your family or people in need, you're deeply concerned.\n");
}

void judging(){
	printf("\n\n");
	printf("As someone with the Judging trait, you feel most comfortable when the path is clear.");
	printf("You'd rather have five backup plans than deal with \n");
	printf("events as they come. You prefer to consider your options ahead of time for clarity and closure.");
	printf("You tend to stick with the plan rather \n");
	printf("than go with the flow. It's as if you always keep a mental checklist of tasks to complete.");
	printf("When you cross something off or start an item,\nyou consider it done.\n");
}

void perceiving(){
	printf("\n\n");
	printf("As someone with the Perceiving trait, you're flexible in dealing with challenges.");
	printf("This flexibility helps you seize unexpected \n");
	printf("opportunities. You tend to react to your environment rather than try to control it.");
	printf("This helps you make your own luck with whatever the\n");
	printf("world delivers. You believe life is full of possibilities.\n");

}

void results(){
	system("cls");
	int i;
	float percentage, till;
	printf("\n                                                    ");
	printf("Your Personality Results\n\n");
	// Introversion & Extroversion
	if (users[loggedInUserIndex].introversion == users[loggedInUserIndex].extraversion){
		users[loggedInUserIndex].introversion += 5;
	}
	printf("\n                                           ");
	percentage = ((float)users[loggedInUserIndex].introversion/(users[loggedInUserIndex].extraversion+users[loggedInUserIndex].introversion))*100;

    printf("Introversion %.f ",percentage);
    till = percentage / 10;
    for (i = 0; i < till ; i++){
    	printf("%c",178);
	}
	for (i = 0; i < 10 - till ; i++){
    	printf("%c",176);
	}
	printf(" %.f Extraversion\n",100 - percentage);
	// Sensing & Intuition
	if (users[loggedInUserIndex].sensing == users[loggedInUserIndex].intuition){
		users[loggedInUserIndex].sensing += 5;
	}
	printf("\n                                                ");
	percentage = ((float)users[loggedInUserIndex].sensing/(users[loggedInUserIndex].sensing+users[loggedInUserIndex].intuition))*100;
    printf("Sensing %.f ",percentage);
    till = percentage / 10;
    for (i = 0; i < till ; i++){
    	printf("%c",178);
	}
	for (i = 0; i < 10 - till ; i++){
    	printf("%c",176);
	}
	printf(" %.f Intuitive\n",100 - percentage);
	// Thinking & Feeling
	if (users[loggedInUserIndex].thinking == users[loggedInUserIndex].feeling){
		users[loggedInUserIndex].thinking += 5;
	}
	printf("\n                                               ");
    percentage = ((float)users[loggedInUserIndex].thinking/(users[loggedInUserIndex].thinking+users[loggedInUserIndex].feeling))*100;
    printf("Thinking %.f ",percentage);
    till = percentage / 10;
    for (i = 0; i < till ; i++){
    	printf("%c",178);
	}
	for (i = 0; i < 10 - till ; i++){
    	printf("%c",176);
	}
	printf(" %.f Feeling\n",100 - percentage);
	// Judging & Perceiving
	if (users[loggedInUserIndex].judging == users[loggedInUserIndex].perceiving){
		users[loggedInUserIndex].judging += 5;
	}
	printf("\n                                                ");
    percentage = ((float)users[loggedInUserIndex].judging/(users[loggedInUserIndex].judging+users[loggedInUserIndex].perceiving))*100;
    printf("Judging %.f ",percentage);
    till = percentage / 10;
    for (i = 0; i < till ; i++){
    	printf("%c",178);
	}
	for (i = 0; i < 10 - till ; i++){
    	printf("%c",176);
	}
	printf(" %.f Perceiving\n",100 - percentage);
	printf("\n                                                      ");
	printf("Personlity Type: ");
	if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	    users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	    users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	    users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // INTJ
	    	printf("INTJ");
		    introvert();
	        intuitive();
	        thinking();
	        judging();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // INTP
	    	printf("INTJ");
	    	introvert();
            intuitive();
            thinking();
            perceiving();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // INFJ
	    	printf("INFJ");
	    	introvert();
            intuitive();
            feeling();
            judging();
	    
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // INFP
	    	printf("INFP");
	    	introvert();
            intuitive();
            feeling();
            perceiving();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ISTJ
	    	printf("ISTJ");
	    	introvert();
            sensing();
            thinking();
            judging();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ISTP
	    	printf("ISTP");
	    	introvert();
            sensing();
            thinking();
            perceiving();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ISFJ
	    	printf("ISFJ");
	     	introvert();
            sensing();
            feeling();
            judging();
	} 
	else if (users[loggedInUserIndex].introversion > users[loggedInUserIndex].extraversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ISFP
	    	printf("ISFP");
	   		introvert();
            sensing();
            feeling();
            perceiving();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ENTJ
	    	printf("ENTJ");
	    	extrovert();
            intuitive();
            thinking();
            judging();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ENTP
	    	printf("ENTP");
	    	extrovert();
            intuitive();
            thinking();
            perceiving();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ENFJ
	    	printf("ENFJ");
	    	extrovert();
            intuitive();
            feeling();
            judging();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].intuition > users[loggedInUserIndex].sensing &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ENFP
	    	printf("ENFP");
	    	extrovert();
            intuitive();
            feeling();
            perceiving();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ESTJ
	    	printf("ESTJ");
	    	extrovert();
            sensing();
            thinking();
            judging();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].thinking > users[loggedInUserIndex].feeling &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ESTP
	    	printf("ESTP");
	    	extrovert();
            sensing();
            thinking();
            perceiving();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].judging > users[loggedInUserIndex].perceiving) {
	    // ESFJ
	    	printf("ESFJ");
	    	extrovert();
            sensing();
            feeling();
            judging();
	} 
	else if (users[loggedInUserIndex].extraversion > users[loggedInUserIndex].introversion &&
	           users[loggedInUserIndex].sensing > users[loggedInUserIndex].intuition &&
	           users[loggedInUserIndex].feeling > users[loggedInUserIndex].thinking &&
	           users[loggedInUserIndex].perceiving > users[loggedInUserIndex].judging) {
	    // ESFP
	    	printf("ESFP");
	    	extrovert();
            sensing();
            feeling();
            perceiving();
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
    int i;
    for(i=0; i < 51 ; i++){
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
    results();
}

void intialiseScore(){
	users[loggedInUserIndex].introversion = 0;
    users[loggedInUserIndex].extraversion = 0;
    users[loggedInUserIndex].sensing = 0;
    users[loggedInUserIndex].intuition = 0;
    users[loggedInUserIndex].thinking = 0;
    users[loggedInUserIndex].feeling = 0;
    users[loggedInUserIndex].judging = 0;
    users[loggedInUserIndex].perceiving = 0;
}

// OUTPUT TO SHOW AFTER USER HAVE SUCCEESSFULLY LOGGED IN
void userMenu(){
	system("cls");
    int choice, score = 1;
    printf("\n                                                          ");
    printf("    User Menu    \n\n\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\n                                                   ");
    printf("Play     Your Results     Sign out\n");
	printf("                                                                  ^");
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
            intialiseScore();
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
	system("cls");
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
                system("cls");
                goodbye();
            	exit(0);
        }
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
