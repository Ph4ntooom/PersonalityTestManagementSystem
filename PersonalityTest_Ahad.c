#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <winuser.h>
#include <stdlib.h>

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

void hideScrollBar() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &csbi);
    csbi.dwSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(hConsole, csbi.dwSize);
}


int main(){
	setFullScreen();
	
	simulateF11Keypress();
	
	hideScrollBar();
	
	hideTypeCursor();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                                                                                                      ");
	printf("What is it that you like?");
	printf("\n                                                                                                    ");
	printf("Agree    Disagree    Nuetral");
	printf("\n");
	int var;
	printf("                                                                                                                ^");
	int score = 1;
	while (var != '\r') {
        var = getch();

        if (var == 224){
        	var = getch();
        	if (var == 75 && score > 0){
        		switch (score){
        			case 1:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b");
        				break;
        			case 2:
        				printf("\b \b\b\b\b\b\b\b\b\b\b\b\b\b");
        				break;
				}
        		printf("^");
        		score--;
			}
			else if (var == 77 && score < 2){
				switch (score){
        			case 0:
        				printf("\b \b          ");
        				break;
        			case 1:
        				printf("\b \b            ");
        				break;
				}
				printf("^");
				score++;
			}
		}   
		else if(var == 'x'){
			system("cls");
		}
    }
    printf("\n%d",score);
	return 0;
}
