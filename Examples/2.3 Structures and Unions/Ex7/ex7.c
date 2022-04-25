#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
} date;

typedef struct {
    enum tagField {pitcher, hitter} role;
    union {
        int SO;
        int HR;
    } u;
} playerType;

typedef struct {
    char name[40];
    int age;
    float salary;
    date dob;
    playerType playerInfo;
} baseballPlayer;

void printPlayerInfo(baseballPlayer);

int main()
{
    baseballPlayer b1, b2;

    strcpy(b1.name, "Hyun-Jin Ryu");
    b1.age = 32;
    b1.salary = 17900000.0;
    b1.dob.year = 1987;
    b1.dob.month = 3;
    b1.dob.day = 25;
    b1.playerInfo.role = pitcher;
    b1.playerInfo.u.SO = 163;
    b1.playerInfo.u.HR = 3;

    strcpy(b2.name, "Shin-Soo Choo");
    b2.age = 37;
    b2.salary = 21000000.0;
    b2.dob.year = 1982;
    b2.dob.month = 7;
    b2.dob.day = 13;
    b2.playerInfo.role = hitter;
    b2.playerInfo.u.HR = 24;
    b2.playerInfo.u.SO = 170;
    printPlayerInfo(b1);
    printPlayerInfo(b2);
}

void printPlayerInfo(baseballPlayer p)
{
    printf(" name: %s\n", p.name);
    printf(" age : %d\n", p.age);
    printf(" salary: $ %.1f\n", p.salary);
    printf(" dob : %4d/%2d/%2d\n", p.dob.year, p.dob.month, p.dob.day);

    if(p.playerInfo.role == pitcher)
        printf(" PITCHER SO: %d\n", p.playerInfo.u.SO);
    else
        printf(" HITTER  HR: %d\n", p.playerInfo.u.HR);
    printf("\n");    
}