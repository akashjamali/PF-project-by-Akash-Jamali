/*We both Akash Jamali And Hussian are Student of BSCS-25F.
Name : AKash or Hussian
Roll number: CSC-25F-014
SUbject: Programing Fundamentals By sir Ameen Khawaja
Project is Related to Disaster Rashan Distribution*/

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <commdlg.h> 
#define BG_COLOR WHITE
#define TEXT_COLOR BLACK
#define BTN_COLOR COLOR(240, 240, 240)      
#define BTN_SHADOW COLOR(100, 100, 100)     
#define HEADER_BG COLOR(0, 51, 102)         
#define ACCENT_COLOR COLOR(255, 140, 0)     

const char* DB_FILE = "rashan_records.dat";

typedef struct {
    char name[50];
    char cnic[20];
    char contact[20];
    int grade;
    long income;
    int isGovt;
    char imagePath[260]; // Increased size for full paths
    int trackingID;
    char status[20];
    char rashanPkg[50];
    char bonusPkg[50];
    char date[20];
    char validDate[20]; // New: Last Date
} Record;
int W, H; 
int mainWin;
void drawHeaderFooter();
void drawShadowButton(int x1, int y1, int x2, int y2, const char* text);
int isButtonClicked(int x1, int y1, int x2, int y2);
int inputText(int x, int y, const char* prompt, char* buffer, int isPassword);
void showMessage(const char* msg, int isError);
void openFileBrowser(char* buffer); 
void calculatePackages(Record* r);
void saveRecord(Record r);
int getNextID();
void getCurrentDate(char* buffer);
void getValidDate(char* buffer);
void loginScreen();
void mainMenu();
void registrationScreen();
void checkStatusScreen();
void distributionScreen();
void recordsScreen();
void dataControlPanel();
void manageRecordsScreen();
void deleteRecordScreen();
void editRecordScreen();

int main() {
    FreeConsole();
    W = GetSystemMetrics(SM_CXSCREEN);
    H = GetSystemMetrics(SM_CYSCREEN) - 60; 
    mainWin = initwindow(W, H, (char*)"Disaster Rashan Distributer", 0, 0);
    HWND hwnd = FindWindow(NULL, "Disaster Rashan Distributer");
    HICON hIcon = (HICON)LoadImage(NULL, "logo.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

    if (hwnd && hIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
    setbkcolor(BG_COLOR);
    cleardevice();
    loginScreen(); 
    closegraph();
    return 0;
}

void openFileBrowser(char* buffer) {
    OPENFILENAME ofn;
    char szFile[260] = {0};
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Images\0*.jpg;*.jpeg;*.bmp;*.gif\0All Files\0*.*\0";
    ofn.nFilterIndex = 2;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        strcpy(buffer, szFile);
        showMessage("Image Selected!", 0);
    }
}
void drawHeaderFooter() {
    setfillstyle(SOLID_FILL, HEADER_BG);
    bar(0, 0, W, 80);
    
    setcolor(WHITE);
    setbkcolor(HEADER_BG);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy((W - textwidth((char*)"Disaster Rashan Distributer"))/2, 20, (char*)"Disaster Rashan Distributer");
    int footerHeight = 100; 
    int footerY = H - footerHeight;

    bar(0, footerY, W, H);
    
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    char* foot = (char*)"Developed by Akash Jamali & Hussain";
    outtextxy((W - textwidth(foot))/2, footerY + 25, foot);
    
    setbkcolor(BG_COLOR);
    setcolor(TEXT_COLOR);
}

void drawShadowButton(int x1, int y1, int x2, int y2, const char* text) {
    setfillstyle(SOLID_FILL, BTN_SHADOW);
    bar(x1 + 6, y1 + 6, x2 + 6, y2 + 6); 

    setfillstyle(SOLID_FILL, BTN_COLOR);
    bar(x1, y1, x2, y2);
    setcolor(HEADER_BG);
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(x1, y1, x2, y2);
    setlinestyle(SOLID_LINE, 0, 1);

    setbkcolor(BTN_COLOR);
    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(x1 + (x2-x1)/2 - textwidth((char*)text)/2, y1 + (y2-y1)/2 - textheight((char*)text)/2, (char*)text);
    setbkcolor(BG_COLOR);
}

int isButtonClicked(int x1, int y1, int x2, int y2) {
    if (mousex() > x1 && mousex() < x2 && mousey() > y1 && mousey() < y2) return 1;
    return 0;
}

int inputText(int x, int y, const char* prompt, char* buffer, int isPassword) {
    char ch;
    int i = strlen(buffer); 
    
    setcolor(HEADER_BG);
    setbkcolor(BG_COLOR);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(x, y, (char*)prompt);
    
    int boxX = x + 350; int boxY = y - 5; int boxW = 400; int boxH = 40;
    setfillstyle(SOLID_FILL, BTN_SHADOW); bar(boxX+5, boxY+5, boxX+boxW+5, boxY+boxH+5);
    setfillstyle(SOLID_FILL, WHITE); bar(boxX, boxY, boxX+boxW, boxY+boxH);
    setcolor(BLACK); rectangle(boxX, boxY, boxX+boxW, boxY+boxH);
    setbkcolor(WHITE); setcolor(BLACK); settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    if(!isPassword) outtextxy(boxX+10, boxY+8, buffer);
    setbkcolor(BG_COLOR);
    while(kbhit()) getch();

    while (1) {
        if (kbhit()) {
            ch = getch();
            if (ch == 27) return 0; 
            if (ch == 13) return 1; 
            if (ch == 8) { if(i>0){i--; buffer[i]='\0';} }
            else if (i<250 && ch>=32 && ch<=126) { buffer[i]=ch; i++; buffer[i]='\0'; }
            setfillstyle(SOLID_FILL, WHITE);
            bar(boxX+2, boxY+2, boxX+boxW-2, boxY+boxH-2);
            setbkcolor(WHITE); setcolor(BLACK);
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
            if(isPassword){ char s[50]; memset(s,'*',i); s[i]='\0'; outtextxy(boxX+10, boxY+8, s); }
            else outtextxy(boxX+10, boxY+8, buffer); 
            setbkcolor(BG_COLOR);
        }
        delay(5);
    }
}

void showMessage(const char* msg, int isError) {
    int color = isError ? RED : GREEN;
    setcolor(color);
    setbkcolor(BG_COLOR);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy((W - textwidth((char*)msg))/2, H - 150, (char*)msg);
    delay(1000);
    setfillstyle(SOLID_FILL, BG_COLOR);
    bar(0, H - 160, W, H - 60); 
}

int getNextID() { return (rand() % 9000) + 1000; }

void getCurrentDate(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void getValidDate(char* buffer) {
    time_t t = time(NULL);
    t += 30 * 24 * 60 * 60; 
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void calculatePackages(Record* r) {
    if (r->income < 20000) strcpy(r->rashanPkg, "30k Rashan");
    else if (r->income < 50000) strcpy(r->rashanPkg, "20k Rashan");
    else if (r->income < 80000) strcpy(r->rashanPkg, "10k Rashan");
    else strcpy(r->rashanPkg, "Not Eligible");

    strcpy(r->bonusPkg, "None");
    if (r->isGovt) {
        if (r->grade >= 3 && r->grade <= 6) strcpy(r->bonusPkg, "+15k Bag");
        else if (r->grade >= 7 && r->grade <= 12) strcpy(r->bonusPkg, "+8k Bag");
        else if (r->grade >= 13 && r->grade <= 16) strcpy(r->bonusPkg, "+5k Bag");
    }
    strcpy(r->status, "Registered"); 
}

void saveRecord(Record r) {
    FILE *fp = fopen(DB_FILE, "ab");
    if (fp) { fwrite(&r, sizeof(Record), 1, fp); fclose(fp); }
}


void loginScreen() {
    char user[50] = "", pass[50] = "";
    while (1) {
        cleardevice();
        drawHeaderFooter();
        
        int boxW = 850, boxH = 400;
        int bx = (W - boxW)/2;
        int by = (H - boxH)/2;
        
        setfillstyle(SOLID_FILL, BTN_SHADOW); bar(bx+10, by+10, bx+boxW+10, by+boxH+10);
        setfillstyle(SOLID_FILL, COLOR(230, 230, 230)); bar(bx, by, bx+boxW, by+boxH);
        setcolor(HEADER_BG); rectangle(bx, by, bx+boxW, by+boxH);

        setbkcolor(COLOR(230, 230, 230));
        settextstyle(BOLD_FONT, HORIZ_DIR, 6);
        outtextxy(bx + (boxW - textwidth((char*)"ADMIN LOGIN"))/2, by + 40, (char*)"ADMIN LOGIN");

        if (!inputText(bx + 50, by + 120, "Username:", user, 0)) exit(0);
        if (!inputText(bx + 50, by + 200, "Password:", pass, 1)) exit(0);

        drawShadowButton(bx + 50, by + 300, bx + 200, by + 350, "Login");
        drawShadowButton(bx + 350, by + 300, bx + 500, by + 350, "Exit");

        while(1) {
            if(ismouseclick(WM_LBUTTONDOWN)){
                int mx, my; getmouseclick(WM_LBUTTONDOWN, mx, my);
                if (mx > bx+350 && mx < bx+500 && my > by+300 && my < by+350) exit(0);
                if (mx > bx+50 && mx < bx+200 && my > by+300 && my < by+350) break;
            }
            if(kbhit()) break; 
            delay(10);
        }
        
        if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) { //password
            setbkcolor(BG_COLOR); showMessage("Login Successful!", 0); mainMenu(); return;
        }
        setbkcolor(BG_COLOR); showMessage("Invalid Credentials!", 1);
    }
}

void registrationScreen() {
    Record r = {0}; 
    char temp[20] = ""; // Buffer for numeric inputs
    cleardevice(); 
    drawHeaderFooter();
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(50, 90, (char*)"Fresh Registration");

    int startY = 140, gap = 50;

    // String inputs (Directly into struct)
    if (!inputText(100, startY, "Full Name:", r.name, 0)) { mainMenu(); return; }
    if (!inputText(100, startY+gap, "CNIC:", r.cnic, 0)) { mainMenu(); return; }
    if (!inputText(100, startY+gap*2, "Contact:", r.contact, 0)) { mainMenu(); return; }

    // Numeric input: Income
    strcpy(temp, ""); // Reset buffer
    if (!inputText(100, startY+gap*3, "Income:", temp, 0)) { mainMenu(); return; } 
    r.income = atol(temp);

    // Numeric input: Job Type
    strcpy(temp, ""); // Reset buffer
    if (!inputText(100, startY+gap*4, "Job (1=Govt 0=Pvt):", temp, 0)) { mainMenu(); return; } 
    r.isGovt = atoi(temp);

    r.grade = 0;
    if (r.isGovt) { 
        strcpy(temp, ""); // Reset buffer for Grade
        if (!inputText(100, startY+gap*5, "Grade (3-18):", temp, 0)) { mainMenu(); return; } 
        r.grade = atoi(temp); 
    }

    // Image section
    int btnY = startY+gap*6;
    drawShadowButton(100, btnY, 300, btnY+40, "Browse Picture");
    outtextxy(320, btnY+10, (char*)"Or type path below...");
    strcpy(r.imagePath, "");     
    
    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my; 
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if(isButtonClicked(100, btnY, 300, btnY+70)) {
                openFileBrowser(r.imagePath); 
                break;
            }
        }
        if(kbhit()) break; 
        delay(10);
    }
    
    // Allow manual path entry if browser wasn't used/failed
    if (!inputText(100, btnY+100, "Image Path:", r.imagePath, 0)) { mainMenu(); return; }

    // Logic and Saving
    r.trackingID = getNextID(); 
    getCurrentDate(r.date); 
    getValidDate(r.validDate);
    calculatePackages(&r); 
    saveRecord(r);

    // Receipt UI
    cleardevice(); 
    drawHeaderFooter();
    int rx = W/2 - 400, ry = 90;
    rectangle(rx, ry, rx+800, ry+520);
    
    setfillstyle(SOLID_FILL, HEADER_BG); 
    bar(rx, ry, rx+800, ry+60);
    setbkcolor(HEADER_BG); 
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(rx+150, ry+10, (char*)"DISASTER RASHAN DISTRIBUTER");
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(rx+300, ry+50, (char*)"REGISTRATION SLIP");
    
    setbkcolor(BG_COLOR); 
    setcolor(BLACK);
    char buf[100]; 
    int ty = ry+100, tx = rx+50;
    
    sprintf(buf,"Tracking ID:  %d", r.trackingID); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"Name:         %s", r.name); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"CNIC:         %s", r.cnic); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"Contact:      %s", r.contact); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"Income:       %ld", r.income); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"Job Type:     %s", r.isGovt ? "Govt" : "Private"); outtextxy(tx,ty,buf); ty+=40;
    
    if(r.isGovt) { 
        sprintf(buf,"Grade:        %d", r.grade); 
        outtextxy(tx,ty,buf); 
        ty+=40; 
    }
    
    setcolor(BLUE);
    sprintf(buf,"Reg Date:     %s", r.date); outtextxy(tx,ty,buf); ty+=40;
    sprintf(buf,"Valid Until:  %s", r.validDate); outtextxy(tx,ty,buf); 
    
    // Display Image
    int px = rx+500, py = ry+100; 
    rectangle(px,py,px+150,py+150);
    if(strlen(r.imagePath) > 0) {
        readimagefile(r.imagePath, px+1, py+1, px+149, py+149);
    } else {
        outtextxy(px+40, py+60, (char*)"No Pic");
    }

    setcolor(GREEN);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(rx+50, ry+450, (char*)"STATUS: REGISTERED");
    
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(rx+550, ry+480, (char*)"Devs: Akash & Hussain");

    outtextxy(W/2-100, ry+540, (char*)"Press Key to Continue..."); 
    getch(); 
    mainMenu();
}
void distributionScreen() {
    char idStr[20]=""; int tid; Record r; FILE *fp, *tmp; int found=0;
    cleardevice(); drawHeaderFooter();
    outtextxy(50, 100, (char*)"Distribution (ESC to Cancel)");
    if(!inputText(100, 200, "Tracking ID:", idStr, 0)){ mainMenu(); return; } tid=atoi(idStr);

    fp=fopen(DB_FILE,"rb"); tmp=fopen("temp.dat","wb");
    while(fread(&r,sizeof(Record),1,fp)){
        if(r.trackingID==tid){
            found=1;
            
            setcolor(BLUE); outtextxy(100, 280, (char*)"--- Confirm Identity ---");
            char buf[100]; setcolor(BLACK);
            sprintf(buf,"Name: %s", r.name); outtextxy(100, 320, buf);
            sprintf(buf,"CNIC: %s", r.cnic); outtextxy(100, 360, buf);
            
            rectangle(500, 250, 650, 400);
            if(strlen(r.imagePath)>0) readimagefile(r.imagePath, 501, 251, 649, 399);

            if(strcmp(r.status,"Handed Over")==0) { showMessage("Already Distributed!",1); }
            else {
                outtextxy(100, 450, (char*)"Press 'Y' to Confirm Handover");
                if(getch()=='y' || getch()=='Y'){
                    strcpy(r.status,"Handed Over"); 
                    showMessage("Distribution Successful!",0);
                    
                    cleardevice(); drawHeaderFooter();
                    int rx = W/2 - 400, ry = 90;
                    rectangle(rx, ry, rx+800, ry+520);
                    
                    setfillstyle(SOLID_FILL, HEADER_BG); bar(rx, ry, rx+800, ry+60);
                    setbkcolor(HEADER_BG); setcolor(WHITE);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
                    outtextxy(rx+150, ry+10, (char*)"DISASTER RASHAN DISTRIBUTER");
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                    outtextxy(rx+300, ry+50, (char*)"DISTRIBUTION SLIP");

                    setbkcolor(BG_COLOR); setcolor(BLACK);
                    int tx = rx+50, ty = ry+100;
                    sprintf(buf,"Tracking ID:  %d",r.trackingID); outtextxy(tx,ty,buf); ty+=40;
                    sprintf(buf,"Name:         %s",r.name); outtextxy(tx,ty,buf); ty+=40;
                    sprintf(buf,"CNIC:         %s",r.cnic); outtextxy(tx,ty,buf); ty+=40;
                    
                    setcolor(BLUE);
                    sprintf(buf,"Package:      %s",r.rashanPkg); outtextxy(tx,ty,buf); ty+=40;
                    sprintf(buf,"Bonus:        %s",r.bonusPkg); outtextxy(tx,ty,buf); ty+=40;

                    int px = rx+500, py = ry+100; rectangle(px,py,px+150,py+150);
                    if(strlen(r.imagePath)>0) readimagefile(r.imagePath, px+1, py+1, px+149, py+149);

                    setcolor(GREEN);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
                    outtextxy(rx+50, ry+400, (char*)"STATUS: HANDED OVER");
                    
                    setcolor(BLACK);
                    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
                    outtextxy(rx+550, ry+480, (char*)"Devs: Akash & Hussain");
                    
                    outtextxy(W/2-100, ry+540, (char*)"Press Key to Print..."); getch(); 
                }
            }
        }
        fwrite(&r,sizeof(Record),1,tmp);
    }
    fclose(fp); fclose(tmp); remove(DB_FILE); rename("temp.dat",DB_FILE);
    if(!found) showMessage("ID Not Found",1);
    mainMenu();
}

void editRecordScreen() {
    char idStr[20] = {}; int tid; int found=0; Record r;
    cleardevice(); drawHeaderFooter();
    outtextxy(50, 100, (char*)"EDIT RECORD (ESC to Back)");
    
    if(!inputText(100, 200, "Enter ID to Edit:", idStr, 0)) { manageRecordsScreen(); return; }
    tid = atoi(idStr);

    FILE *fp = fopen(DB_FILE, "rb");
    FILE *tmp = fopen("temp.dat", "wb");
    
    while(fread(&r, sizeof(Record), 1, fp)) {
        if(r.trackingID == tid) {
            found = 1;
            char temp[260];
            outtextxy(100, 260, (char*)"EDITING MODE: Leave empty to keep existing.");
            
            // Sequential Editing
            char p[100]; 
            sprintf(p, "Name      (%s):", r.name);
            if(inputText(100, 300, p, temp, 0) && strlen(temp)>0) strcpy(r.name, temp);
            
            sprintf(p, "CNIC      (%s):", r.cnic);
            if(inputText(100, 350, p, temp, 0) && strlen(temp)>0) strcpy(r.cnic, temp);
            
            sprintf(p, "Contact   (%s):", r.contact);
            if(inputText(100, 400, p, temp, 0) && strlen(temp)>0) strcpy(r.contact, temp);

            sprintf(p, "Income    (%ld):", r.income);
            if(inputText(100, 450, p, temp, 0) && strlen(temp)>0) { r.income = atol(temp); calculatePackages(&r);
            }
        
            sprintf(p, "Job (1=Govt, 0=Pvt):");
            if(inputText(100, 500, p, temp, 0) && strlen(temp)>0) { 
                r.isGovt = atoi(temp);
                if(r.isGovt) {
                    if(inputText(100, 550, "Grade (3-18):", temp, 0) && strlen(temp)>0) r.grade = atoi(temp);
                } else {
                    r.grade = 0; 
                }
                calculatePackages(&r); 
            }

            // Image Edit
            drawShadowButton(100, 500, 300, 540, "Change Picture");
            while(1) {
                if(ismouseclick(WM_LBUTTONDOWN)){
                   int x,y; getmouseclick(WM_LBUTTONDOWN, x,y);
                   if(isButtonClicked(100,500,300,540)){
                       openFileBrowser(r.imagePath); break;
                   }
                }
                if(kbhit()) break; // Skip logic
                delay(10);
            }

            showMessage("Record Updated!", 0);
        }
        fwrite(&r, sizeof(Record), 1, tmp);
    }
    fclose(fp); fclose(tmp); remove(DB_FILE); rename("temp.dat", DB_FILE);
    if(!found) showMessage("ID Not Found.", 1);
    manageRecordsScreen();
}

void deleteRecordScreen() {
    char idStr[20]; int tid; int found=0; Record r;
    cleardevice(); drawHeaderFooter();
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(50, 100, (char*)"DELETE RECORD");
    
    if(!inputText(100, 200, "Enter ID to Delete:", idStr, 0)) { manageRecordsScreen(); return; }
    tid = atoi(idStr);

    FILE *fp = fopen(DB_FILE, "rb");
    FILE *tmp = fopen("temp.dat", "wb");
    
    while(fread(&r, sizeof(Record), 1, fp)) {
        if(r.trackingID == tid) {
            found = 1;
            char msg[100]; sprintf(msg, "Deleting: %s (Y/N)?", r.name);
            outtextxy(100, 300, msg);
            char c = getch();
            if(c != 'y' && c != 'Y') fwrite(&r, sizeof(Record), 1, tmp); 
            else showMessage("Record Deleted.", 0);
        } else {
            fwrite(&r, sizeof(Record), 1, tmp);
        }
    }
    fclose(fp); fclose(tmp); remove(DB_FILE); rename("temp.dat", DB_FILE);
    if(!found) showMessage("ID Not Found.", 1);
    manageRecordsScreen();
}

void manageRecordsScreen() {
    clearmouseclick(WM_LBUTTONDOWN);
    cleardevice(); drawHeaderFooter();
    outtextxy(50, 100, (char*)"MANAGE RECORDS");

    int bx = W/2 - 200, by = 200;
    drawShadowButton(bx, by, bx+400, by+60, "1. Edit Record");
    drawShadowButton(bx, by+80, bx+400, by+140, "2. Delete Record");
    drawShadowButton(bx, by+160, bx+400, by+220, "3. Back to Menu");

    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x,y; getmouseclick(WM_LBUTTONDOWN, x, y);
            if(isButtonClicked(bx, by, bx+400, by+60)) { editRecordScreen(); return; }
            if(isButtonClicked(bx, by+80, bx+400, by+140)) { deleteRecordScreen(); return; }
            if(isButtonClicked(bx, by+160, bx+400, by+220)) { mainMenu(); return; }
        }
        delay(10);
    }
}

void checkStatusScreen() {
    char s[20] = ""; 
    Record r; 
    FILE *fp; 
    int y = 300; // Starting Y position for data
    
    // --- 1. DEFINE COLUMN POSITIONS ---
    int x_Name   = 50;
    int x_CNIC   = 300;
    int x_Status = 600;
    // ----------------------------------

    cleardevice(); 
    drawHeaderFooter();
    
    // Title
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(50, 100, (char*)"Check Status");
    
    // Search Input
    if(!inputText(100, 180, "Search CNIC or Name:", s, 0)) { mainMenu(); return; }
    
    fp = fopen(DB_FILE, "rb");
    if (!fp) { showMessage("No records found.", 1); mainMenu(); return; }

    // --- 2. DRAW HEADERS ---
    settextstyle(BOLD_FONT, HORIZ_DIR, 2); 
    setcolor(BLACK);
    
    outtextxy(x_Name,   250, (char*)"Name");
    outtextxy(x_CNIC,   250, (char*)"CNIC");
    outtextxy(x_Status, 250, (char*)"Status");
    
    // Blue Underline
    setcolor(HEADER_BG);
    setlinestyle(SOLID_LINE, 0, 3);
    line(50, 280, W-50, 280);
    setlinestyle(SOLID_LINE, 0, 1);

    // --- 3. DRAW DATA LOOP ---
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2); 
    int found = 0;

    while(fread(&r, sizeof(Record), 1, fp)) {
        if(strcmp(r.cnic, s) == 0 || strcmpi(r.name, s) == 0) {
            found = 1;
            setcolor(BLACK);
            
            // Print Name
            outtextxy(x_Name, y, r.name);
            
            // Print CNIC
            outtextxy(x_CNIC, y, r.cnic);
            
            // Print Status (Color Coded)
            if(strcmp(r.status, "Registered") == 0) setcolor(ACCENT_COLOR); // Orange
            else if(strcmp(r.status, "Handed Over") == 0) setcolor(GREEN);
            else setcolor(RED);
            
            outtextxy(x_Status, y, r.status);
            
            y += 40; // Row Spacing
            
            // Separator Line
            setcolor(COLOR(220,220,220));
            line(50, y-5, W-50, y-5);
        }
    }
    fclose(fp);
    
    if(!found) showMessage("Record Not Found.", 1);
    
    setcolor(TEXT_COLOR);
    outtextxy(100, H-150, (char*)"Press Key to Return..."); 
    getch(); 
    mainMenu();
}

void recordsScreen() {
    Record r; 
    FILE *fp = fopen(DB_FILE, "rb"); 
    int y = 200; 
    int x_ID     = 50;
    int x_Name   = 150;  
    int x_CNIC   = 400;  
    int x_Pkg    = 650;  
    cleardevice(); 
    drawHeaderFooter();
    
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(50, 100, (char*)"All Records");
    settextstyle(BOLD_FONT, HORIZ_DIR, 2); 
    setcolor(BLACK);
    outtextxy(x_ID,   150, (char*)"ID");
    outtextxy(x_Name, 150, (char*)"Name");
    outtextxy(x_CNIC, 150, (char*)"CNIC");
    outtextxy(x_Pkg,  150, (char*)"Package");
    setcolor(HEADER_BG);
    setlinestyle(SOLID_LINE, 0, 3);
    line(50, 180, W-50, 180);
    setlinestyle(SOLID_LINE, 0, 1); 
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2); 

    if(fp){
        while(fread(&r, sizeof(Record), 1, fp)){
            if(y > H-100) break; 
            char buf[50];
            setcolor(BLACK);
            sprintf(buf, "%d", r.trackingID);
            outtextxy(x_ID, y, buf);
            outtextxy(x_Name, y, r.name);
            outtextxy(x_CNIC, y, r.cnic);
            setcolor(BLUE);
            outtextxy(x_Pkg, y, r.rashanPkg);
            
            y += 40;
            setcolor(COLOR(220,220,220));
            line(50, y-5, W-50, y-5);
        } 
        fclose(fp);
    }
    
    setcolor(TEXT_COLOR);
    outtextxy(100, H-100, (char*)"Press Key to Return..."); 
    getch(); 
    mainMenu();
}

void dataControlPanel() {
    Record r; 
    FILE *fp = fopen(DB_FILE, "rb");
    
    // --- 1. DATA PROCESSING ---
    int total = 0, handed = 0, pending = 0;
    int govt = 0, pvt = 0;
    long totalMoney = 0; 

    if(fp) { 
        while(fread(&r, sizeof(Record), 1, fp)) {
            total++;
            // Count Status
            if(strcmp(r.status, "Registered") == 0) pending++; else handed++; 
            // Count Job
            if(r.isGovt) govt++; else pvt++;
            // Calculate Money (Rashan)
            if(strstr(r.rashanPkg, "30k")) totalMoney += 30000;
            else if(strstr(r.rashanPkg, "20k")) totalMoney += 20000;
            else if(strstr(r.rashanPkg, "10k")) totalMoney += 10000;
            // Calculate Money (Bonus)
            if(strstr(r.bonusPkg, "15k")) totalMoney += 15000;
            else if(strstr(r.bonusPkg, "8k")) totalMoney += 8000;
            else if(strstr(r.bonusPkg, "5k")) totalMoney += 5000;
        } 
        fclose(fp); 
    }
    if(total == 0) total = 1; // Prevent division by zero

    // --- 2. DRAW UI ---
    cleardevice(); 
    drawHeaderFooter();

    // Page Title
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(HEADER_BG);
    outtextxy((W - textwidth((char*)"ANALYTICS DASHBOARD"))/2, 100, (char*)"ANALYTICS DASHBOARD");

    // --- 3. SUMMARY CARDS ---
    int cardW = 350;
    int cardH = 100;
    int cardY = 150;
    
    // Left Card (Applications)
    int c1_x = (W / 4) - (cardW / 2);
    setfillstyle(SOLID_FILL, HEADER_BG);
    bar(c1_x, cardY, c1_x + cardW, cardY + cardH);
    
    // Right Card (Budget)
    int c2_x = (3 * W / 4) - (cardW / 2);
    setfillstyle(SOLID_FILL, ACCENT_COLOR);
    bar(c2_x, cardY, c2_x + cardW, cardY + cardH);

    // Text for Cards
    setcolor(WHITE); setbkcolor(HEADER_BG);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(c1_x + 20, cardY + 15, (char*)"TOTAL APPLICANTS");
    
    char numBuf[50]; sprintf(numBuf, "%d", total);
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    outtextxy(c1_x + 20, cardY + 45, numBuf);

    setbkcolor(ACCENT_COLOR);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(c2_x + 20, cardY + 15, (char*)"ESTIMATED BUDGET");
    
    sprintf(numBuf, "Rs. %ld", totalMoney);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(c2_x + 20, cardY + 50, numBuf);

    // --- 4. ACCURATE GRAPHS SECTION ---
    int graphY_Base = H - 180; // Bottom line of graphs
    int maxBarH = 180;         // Max height (100%)
    int barW = 70;             // Width of bars

    // Helper to draw Grid Lines
    setlinestyle(DOTTED_LINE, 0, 1);
    setcolor(COLOR(200, 200, 200)); // Light Gray
    // Draw 50% line
    line(50, graphY_Base - (maxBarH/2), W-50, graphY_Base - (maxBarH/2));
    // Draw 100% line
    line(50, graphY_Base - maxBarH, W-50, graphY_Base - maxBarH);
    setlinestyle(SOLID_LINE, 0, 1);

    // --- GRAPH 1: STATUS (Left Side) ---
    setbkcolor(BG_COLOR); setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char* t1 = (char*)"DISTRIBUTION STATUS";
    outtextxy((W/4) - (textwidth(t1)/2), graphY_Base - maxBarH - 40, t1);

    // Axis Line
    setcolor(BLACK); setlinestyle(SOLID_LINE, 0, 3);
    line((W/4) - 100, graphY_Base, (W/4) + 100, graphY_Base); // X-Axis
    line((W/4) - 100, graphY_Base, (W/4) - 100, graphY_Base - maxBarH); // Y-Axis
    setlinestyle(SOLID_LINE, 0, 1);

    // Green Bar (Done)
    float hPerc = (float)handed / total;     // Exact Percentage
    int hH = (int)(hPerc * maxBarH);         // Exact Height
    int xGreen = (W/4) - barW - 10;
    setfillstyle(SOLID_FILL, GREEN);
    bar(xGreen, graphY_Base - hH, xGreen + barW, graphY_Base);
    
    // Red Bar (Pending)
    float pPerc = (float)pending / total;
    int pH = (int)(pPerc * maxBarH);
    int xRed = (W/4) + 10;
    setfillstyle(SOLID_FILL, RED);
    bar(xRed, graphY_Base - pH, xRed + barW, graphY_Base);

    // Labels & Percentages G1
    setcolor(BLACK); settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    
    sprintf(numBuf, "%d (%.0f%%)", handed, hPerc*100); 
    outtextxy(xGreen, graphY_Base - hH - 20, numBuf);
    outtextxy(xGreen + 10, graphY_Base + 5, (char*)"Done");
    
    sprintf(numBuf, "%d (%.0f%%)", pending, pPerc*100); 
    outtextxy(xRed, graphY_Base - pH - 20, numBuf);
    outtextxy(xRed + 5, graphY_Base + 5, (char*)"Pending");


    // --- GRAPH 2: EMPLOYMENT RATIO (Right Side) ---
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char* t2 = (char*)"EMPLOYMENT RATIO";
    outtextxy((3*W/4) - (textwidth(t2)/2), graphY_Base - maxBarH - 40, t2);

    // Axis Line
    setcolor(BLACK); setlinestyle(SOLID_LINE, 0, 3);
    line((3*W/4) - 100, graphY_Base, (3*W/4) + 100, graphY_Base); // X-Axis
    line((3*W/4) - 100, graphY_Base, (3*W/4) - 100, graphY_Base - maxBarH); // Y-Axis
    setlinestyle(SOLID_LINE, 0, 1);

    // Blue Bar (Govt)
    float gPerc = (float)govt / total;
    int gH = (int)(gPerc * maxBarH);
    int xBlue = (3*W/4) - barW - 10;
    setfillstyle(SOLID_FILL, BLUE);
    bar(xBlue, graphY_Base - gH, xBlue + barW, graphY_Base);

    // Gray Bar (Private)
    float pvPerc = (float)pvt / total;
    int pvH = (int)(pvPerc * maxBarH);
    int xGray = (3*W/4) + 10;
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(xGray, graphY_Base - pvH, xGray + barW, graphY_Base);

    // Labels & Percentages G2
    setcolor(BLACK); settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    sprintf(numBuf, "%d (%.0f%%)", govt, gPerc*100); 
    outtextxy(xBlue, graphY_Base - gH - 20, numBuf);
    outtextxy(xBlue + 10, graphY_Base + 5, (char*)"Govt");

    sprintf(numBuf, "%d (%.0f%%)", pvt, pvPerc*100); 
    outtextxy(xGray, graphY_Base - pvH - 20, numBuf);
    outtextxy(xGray + 5, graphY_Base + 5, (char*)"Private");

    // Footer Hint
    setcolor(TEXT_COLOR);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy((W - textwidth((char*)"Press Key to Return..."))/2, H - 100, (char*)"Press Key to Return...");
    
    getch(); 
    mainMenu();
}
void mainMenu() {
    clearmouseclick(WM_LBUTTONDOWN);
    while (1) {
        cleardevice(); drawHeaderFooter();
        int btnW=500, btnH=50, gap=15, cx=(W-btnW)/2, sy=120;

        drawShadowButton(cx, sy, cx+btnW, sy+btnH, "1. Registration");
        drawShadowButton(cx, sy+(btnH+gap)*1, cx+btnW, sy+btnH+(btnH+gap)*1, "2. Distribution");
        drawShadowButton(cx, sy+(btnH+gap)*2, cx+btnW, sy+btnH+(btnH+gap)*2, "3. Check Status");
        drawShadowButton(cx, sy+(btnH+gap)*3, cx+btnW, sy+btnH+(btnH+gap)*3, "4. All Records");
        drawShadowButton(cx, sy+(btnH+gap)*4, cx+btnW, sy+btnH+(btnH+gap)*4, "5. Edit / Delete Records");
        drawShadowButton(cx, sy+(btnH+gap)*5, cx+btnW, sy+btnH+(btnH+gap)*5, "6. Control Panel");
        drawShadowButton(cx, sy+(btnH+gap)*6, cx+btnW, sy+btnH+(btnH+gap)*6, "7. Logout");

        while (1) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                int x, y; getmouseclick(WM_LBUTTONDOWN, x, y);
                if (isButtonClicked(cx, sy, cx+btnW, sy+btnH)) { registrationScreen(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*1, cx+btnW, sy+btnH+(btnH+gap)*1)) { distributionScreen(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*2, cx+btnW, sy+btnH+(btnH+gap)*2)) { checkStatusScreen(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*3, cx+btnW, sy+btnH+(btnH+gap)*3)) { recordsScreen(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*4, cx+btnW, sy+btnH+(btnH+gap)*4)) { manageRecordsScreen(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*5, cx+btnW, sy+btnH+(btnH+gap)*5)) { dataControlPanel(); break; }
                if (isButtonClicked(cx, sy+(btnH+gap)*6, cx+btnW, sy+btnH+(btnH+gap)*6)) { loginScreen(); break; }
            }
            delay(10);
        }
    }
}
