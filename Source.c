#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define D0 "□□□"
#define DM "□■□"
#define DL "■□□"
#define DR "□□■"
#define DD "■□■"


struct Player
{
    char name[10];
    int score[14];
    bool scoreRisistered[14];
};
typedef struct Player Player;
char screen[150][20];


void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}
void sort(int arr[], int n)
{
    int min_idx;

    for (int i = 0; i < n - 1; i++) {

        min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
    return;
}
void resetStr(char str[], int length)
{
    for (int i = 0; i < length; i++)
        str[i] = ' ';
    return;
}
void copyArr(int* n, int* m, int length)
{
    for (int i = 0; i < length; i++)
        m[i] = n[i];
}
void copyStr(char* str2, int x, int y)
{
    for (int i = 0; i < 6; i++)
        screen[x + i][y] = str2[i];
    return;
}
int checkinvert(int score,bool risistered)
{
    if (risistered)
        return score;
    else
        return score * -1;

}
int stringLenght(char* str)
{
    int length = 0;
    while (1)
    {
        if (str[length] == '\0')
            return length;
        else length++;
    }
}
void moveStrToEnd(char* str,int size)
{
    int length = stringLenght(str);
    for (int i = 0; i < length; i++)
        str[size - length + i] = str[i];
    for (int i = 0; i < size - length; i++)
        str[i] = ' ';
    str[size] = '\0';
    return;
}
void stringAppend(char* str1, char* str2,int size1,int size2)
{

    for (int i = 0; i < size2; i++)
        str1[size1 + i] = str2[i];

    return;
}

void addTextOnScreen(char s[], int x, int y)
{
    for (int i = 0; i < stringLenght(s); i++)
        screen[x + i - 1][y - 1] = s[i];
    return;
}
void drawLine(int x, int y, int length, char c, bool direction)
{
    if (!direction)
        for (int i = 0; i < length; i++)
            screen[x + i][y] = c;
    else
        for (int i = 0; i < length; i++)
            screen[x][y + i] = c;

    return;
}
void setScreenEdge()
{
    drawLine(0, 0, 14, '|', true);
    drawLine(58, 0, 14, '|', true);
    drawLine(59, 0, 14, '|', true);
    drawLine(117, 0, 14, '|', true);
    for (int i = 0; i < 5; i++)
        drawLine(18 + 10 * i, 0, 9, '|', true);
    for (int i = 0; i < 5; i++)
        drawLine(77 + 10 * i, 0, 9, '|', true);
    drawLine(0, 0, 118, '=', false);
    drawLine(0, 9, 118, '=', false);
    drawLine(0, 13, 118, '=', false);

}
void setScreenText()
{
    addTextOnScreen("player name", 3, 2);
    addTextOnScreen("Aces", 3, 3);
    addTextOnScreen("Twos", 3, 4);
    addTextOnScreen("Threes", 3, 5);
    addTextOnScreen("Fours", 3, 6);
    addTextOnScreen("Fives", 3, 7);
    addTextOnScreen("Sixes", 3, 8);
    addTextOnScreen("Bonus", 3, 9);
    addTextOnScreen("player name", 62, 2);
    addTextOnScreen("Full House", 62, 3);
    addTextOnScreen("Four Of a Kind", 62, 4);
    addTextOnScreen("Little Straight", 62, 5);
    addTextOnScreen("Big Straight", 62, 6);
    addTextOnScreen("Choice", 62, 7);
    addTextOnScreen("Yacht", 62, 8);
    addTextOnScreen("Total", 62, 9);
    return;
}
void resetScreen()
{
    for (int y = 0; y < 20; y++)
        for (int x = 0; x < 120; x++)
            screen[x][y] = ' ';

    return;
}
void printScreen()
{
    system("cls");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 150; j++)
            printf("%c", screen[j][i]);
        printf("\n");
    }
}

void removeTextOnScreen(int x, int y, int length)
{
    for (int i = 0; i < length; i++)
        screen[x + i - 1][y - 1] = ' ';
    return;
}
void writeconsole(char s[])
{
    removeTextOnScreen(3, 11, 56);
    addTextOnScreen(s, 3, 11);
    return;
}

void resetplayer(Player p[4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
            p[i].name[j] = ' ';
        for (int j = 0; j < 14; j++)
        {
            p[i].score[j] = -256;
            p[i].scoreRisistered[j] = false;
        }
        p[i].scoreRisistered[6] = true;
        p[i].scoreRisistered[13] = true;
        
    }

}
void getPlayerinfo(Player p[4])
{
    writeconsole("플래이어의 이름을 입력해 주세요", 31);
    printScreen();
    for (int i = 0; i < 4; i++)
    {
        gotoxy(20 + 10 * i, 2);
        scanf_s("%9s", p[i].name, 9);
        addTextOnScreen(p[i].name, 20 + 10 * i, 2);
        addTextOnScreen(p[i].name, 79 + 10 * i, 2);
    }

    printScreen();


}

void refreshScreen(Player p[4])
{

    char str[3] = { ' ' };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 14; j++)
        {
            if (p[i].score[j] == -1)
                continue;
            snprintf(str, 0, "%d", p[i].score[j]);
            addTextOnScreen(screen, str, ((j < 7) ? 21 : 80, 3 + j), ((j < 7) ? 1 : 2));
        }
    return;
}
void gameSetup(Player p[4])
{
    resetplayer(p);
    resetScreen();
    setScreenEdge();
    setScreenText();
    getPlayerinfo(p);
    return;
}

void setDice(int* n, int lenght)
{
    for (int i = 0; i < lenght; i++)
        n[i] = rand() % 6 + 1;
}
void renderDice(int dice[])
{
    for (int i = 0; i < 5; i++)
        switch (dice[i])
        {
        case 1:
            copyStr(D0, 65 + i * 11, 10);
            copyStr(DM, 65 + i * 11, 11);
            copyStr(D0, 65 + i * 11, 12);
            break;
        case 2:
            copyStr(D0, 65 + i * 11, 10);
            copyStr(DD, 65 + i * 11, 11);
            copyStr(D0, 65 + i * 11, 12);
            break;
        case 3:
            copyStr(DL, 65 + i * 11, 10);
            copyStr(DM, 65 + i * 11, 11);
            copyStr(DR, 65 + i * 11, 12);
            break;
        case 4:
            copyStr(DD, 65 + i * 11, 10);
            copyStr(D0, 65 + i * 11, 11);
            copyStr(DD, 65 + i * 11, 12);
            break;
        case 5:
            copyStr(DD, 65 + i * 11, 10);
            copyStr(DM, 65 + i * 11, 11);
            copyStr(DD, 65 + i * 11, 12);
            break;
        case 6:
            copyStr(DD, 65 + i * 11, 10);
            copyStr(DD, 65 + i * 11, 11);
            copyStr(DD, 65 + i * 11, 12);
            break;

        }



    return;

}
void reRollDice(int* dice, int count)
{
    if (count == 2)
        return;
    int changed = 0;
    char input[20] = "";

    writeconsole("다시 돌릴 주사위를 입력해주세요.");
    printScreen();
    gotoxy(3, 12);
    scanf_s(" %19[^\n]", input, 20);
    for (int i = 0; i < 20; i++)
    {
        switch (input[i])
        {
        case '1':case '2':case '3':case '4':case '5':
            dice[input[i] - '0' - 1] = rand() % 6 + 1; changed++;
        default:break;
        }
    }
    sort(dice, 5);
    renderDice(dice);
    if (changed != 0)
        reRollDice(dice, count + 1);
    return;
}

int scoreAces(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 1)
            score += 1;
    }
    return score;
}
int scoreTwos(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 2)
            score += 2;
    }
    return score;
}
int scoreThrees(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 3)
            score += 3;
    }
    return score;
}
int scoreFours(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 4)
            score += 4;
    }
    return score;
}
int scoreFives(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 5)
            score += 5;
    }
    return score;
}
int scoreSixes(int dice[]) {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        if (dice[i] == 6)
            score += 6;
    }
    return score;
}
int scoreBonus(Player p)
{
    int score = 0;
    for (int i = 0; i < 6; i++)
        score += (p.score[i] > 0) ? p.score[i] : 0;
    return (score >= 63) ? 35 : 0;


}
int scoreFullHouse(int dice[5])
{
    int score = 0;
    for (int i = 0; i < 5; i++)
    {
        if (dice[i] == dice[i + 1])
            score++;
    }
    if (score == 3)
    {
        for (int i = 0; i < 5; i++)
            score += dice[i];
        return score;
    }
    else return 0;
}
int scoreFourOfAKind(int dice[5])
{
    int score = 0;
    int d = 0;
    for (int i = 0; i < 4; i++)
        if (dice[i] == dice[i + 1])
        {
            score++;
            d = dice[i];
        }
    if (score > 3)
        return d * 4;
    
    return 0;
}
int scoreLittleStraight(int dice[5])
{
    int straight = 0;
    for (int i = 0; i < 4; i++)
        if (dice[i] + 1 == dice[i + 1])
            straight++;
    return (straight == 3) ? 30 : 0;

}
int scoreBigStraight(int dice[5])
{
    int straight = 0;
    for (int i = 0; i < 4; i++)
        if (dice[i] + 1 == dice[i + 1])
            straight++;
        else break;
    return (straight == 4) ? 40 : 0;
}
int scoreChoice(int dice[5])
{
    int score = 0;
    for (int i = 0; i < 5; i++)
        score += dice[i];
    return score;
}
int scoreYacht(int dice[5])
{

    for (int i = 0; i < 4; i++)
        if (dice[i] != dice[i + 1])
            return 0;
    return 50;
}
int scoreTotal(Player p)
{
    int score = 0;
    for (int i = 0; i < 13; i++)
        if (p.score[i] > 0)
            score += p.score[i];
    return score;
}

void scoreToText(int score, char scoreStr[])
{
    if (score > 0)
        _itoa_s(score, scoreStr,9, 10);
    else
        _itoa_s(score * -1, scoreStr,9, 10);
    return;
}
void scoreToScreen(Player p, int turn,bool mode)
{
    char str[10] = { ' ' };
    resetStr(str,10);
    int x, y;

    if (mode)
    {
        for (int i = 0; i < 14; i++)
            if (p.scoreRisistered[i])
            {
                x = (i < 7) ? 20 + turn * 10 : 79 + turn * 10;
                y = (i < 7) ? 3 + i : -4 + i;
                scoreToText(p.score[i], str);
                moveStrToEnd(str, 9);
                removeTextOnScreen(x, y, 9);
                addTextOnScreen(str, x, y);
            }

    }
    else
        for (int i = 0; i < 14; i++)
        {
            if (!p.scoreRisistered[i])
            {
                x = (i < 7) ? 20 + turn * 10 : 79 + turn * 10;
                y = (i < 7) ? 3 + i : -4 + i;
                scoreToText(p.score[i], str);
                removeTextOnScreen(x, y, 3);
                addTextOnScreen(str, x, y);
            }
        }

    return;
}

int choiceToInt(char str[20])
{
    switch (str[0])
    {
    case 'A':case 'a': return 1;                        //Aces
    case 'S':case 's': return 6;                        //Sixes
    case 'L':case 'l': return 10;                       //LitlteStraight
    case 'B':case 'b': return 11;                       //BigStraight
    case 'C':case 'c': return 12;                       //Choice
    case 'Y':case 'y': return 13;                       //Twos
    case 'T':case 't': return (str[1] == 'w') ? 2 : 3;  //Threes
    case 'F':case 'f':                                  //
        if (str[1] == 'i')                              //Five
            return 5;                                   //
        else if (str[1] == 'u')                         //FullHouse
            return 8;                                   //
        else if (str[4] == 's')                         //Fours
            return 4;                                   //
        else return 9;                                  //Four of a kind
    default: return -1;                                 //Error
    }
}

void scoreF(int dice[5], Player* p)
{
        p[0].score[0] = checkinvert(scoreAces(dice), p[0].scoreRisistered[0]);
        p[0].score[1] = checkinvert(scoreTwos(dice), p[0].scoreRisistered[1]);
        p[0].score[2] = checkinvert(scoreThrees(dice), p[0].scoreRisistered[2]);
        p[0].score[3] = checkinvert(scoreFours(dice), p[0].scoreRisistered[3]);
        p[0].score[4] = checkinvert(scoreFives(dice), p[0].scoreRisistered[4]);
        p[0].score[5] = checkinvert(scoreSixes(dice), p[0].scoreRisistered[5]);
                        
        p[0].score[6] = scoreBonus(p[0]);
                        
        p[0].score[7] = checkinvert(scoreFullHouse(dice), p[0].scoreRisistered[7]);
        p[0].score[8] = checkinvert(scoreFourOfAKind(dice), p[0].scoreRisistered[8]);
        p[0].score[9] = checkinvert(scoreLittleStraight(dice), p[0].scoreRisistered[9]);
        p[0].score[10] =checkinvert(scoreBigStraight(dice), p[0].scoreRisistered[10]);
        p[0].score[11] =checkinvert(scoreChoice(dice), p[0].scoreRisistered[11]);
        p[0].score[12] =checkinvert(scoreYacht(dice), p[0].scoreRisistered[12]);
                         
        p[0].score[13] = scoreTotal(p[0]);
    return;
}
void resetscore(Player *p,int turn)
{
        int x, y;
    for (int i = 0; i < 13; i++)
        if (!p[0].scoreRisistered[i])
        {
            x = (i < 7) ? 20 + turn * 10 : 79 + turn * 10;
            y = (i < 7) ? 3 + i : -4 + i;
            p[0].score[i] = 0;
            removeTextOnScreen(x, y, 9);
        }
    return;
}
void gchoice(int dice[], Player p)
{

    writeconsole("다시돌리려면 Y 아니면 N를 입력해주세요.");
    printScreen();
    char choice;
    gotoxy(3, 12);
    scanf_s(" %c", &choice);
    if (choice == 'Y')
        reRollDice(dice, 0);
    else if (choice == 'N')
        return;
    else
    {
        writeconsole("잘못된 입력입니다.");
        printScreen();
        getchar();
        gchoice(dice, p);
    }
    return;
}
void choseScore(int dice[], Player *p,int turn)
{
    char choiceStr[20] = "";
    int choice = 0;
    scoreF(dice, &p);
    scoreToScreen(p[0], turn,false);
    writeconsole("주사위를 적용할 점수표를 선택해주세요.");
    printScreen();
    gotoxy(3, 12);
    scanf_s(" %19[^\n]", choiceStr,19);
    choice = choiceToInt(choiceStr);
    if (choice > 0 && choice < 13 && !p[0].scoreRisistered[choice - 1])
    {
        p[0].score[choice - 1] *= -1;
        p[0].scoreRisistered[choice - 1] = true;
    }
    else
    {
        writeconsole("잘못된 입력입니다.");
        printScreen();
        gotoxy(3, 12);
        system("pause");
        choseScore(dice, p, turn);
    }
    printScreen();
    return;
}

void gameend(Player p[])
{
    char message[50] = { ' ' };
    resetStr(message, 50);
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p[index].score[13] > p[i].score[13])
            index = i;
    }
    writeconsole(p[index].name);
    addTextOnScreen(" (이)가 이겼습니다", 3 + stringLenght(p[index].name), 11);
}
void gametest(Player p[])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 14; j++)
        {
            p[i].score[j] = (i + 1) * (j+1);
            p[i].scoreRisistered[j] = true;
        }
    return;
}

void yacht()
{
    int dice[5] = { 0 };
    int sortedDice[5] = { 0 };
    int gameturn = 0;
    int gameround = 0;
    Player p[4];
    gameSetup(p);


    for (int round = 0; round < 14; round++)
    {
        for (int turn = 0; turn < 4; turn++)
        {
            setDice(dice, 5);
            sort(dice,5);
            renderDice(dice);
            scoreF(dice, &p[turn]);

            scoreToScreen(p[turn], turn, false);
            gchoice(dice, p[turn]);
            choseScore(dice, &p[turn], turn);
            resetscore(&p[turn],turn);
            scoreToScreen(p[turn], turn, true);
        }
    }

    //gametest(p);
    gameend(p);
    printScreen();
    return;
}


void menu() {

    printf("==============================================================================================================================\n");
    printf("==============================================================================================================================\n");
    printf("==============================================================================================================================\n");
    printf("===================================================== Y A C H T  D I C E =====================================================\n");
    printf("==============================================================================================================================\n");
    printf("==============================================================================================================================\n");
    printf("==============================================================================================================================\n");
    int number = 1;
    while (number != 3) {

        printf("\n번호를 입력하시오.\n");
        printf("1번을 입력하면 게임 룰이 나옵니다.\n");
        printf("2번을 입력하면 족보가 나옵니다.\n");
        printf("3번을 입력하면 게임을 시작합니다.\n");
        scanf_s("%d", &number);
        system("cls");
        switch (number) {
        case 1:

            printf("게임 설명을 시작합니다.\n");
            printf("Yacht Dice 게임은 주사위를 사용해 포커처럼 '족보'를 만드는 게임입니다. \n");
            printf(" 주사위를 최대 세 번까지 던져서 맞는 족보를 만든 후 점수를 얻어내는 게 목표입니다.\n");
            printf("1. 주사위 5개를 던집니다.\n");
            printf("2. 이 중 원하는 주사위들은 남겨두고, 나머지 주사위들을 다시 던집니다. 다시 던지기는 한 라운드에 2번까지(즉, 한 라운드에 최대 3번까지 던질 수 있습니다.) 가능하며, 앞에서 던지지 않았던 주사위도 원한다면 다시 던질 수 있습니다.\n");
            printf("3. 주사위 던지기가 끝난 후 나온 최종 조합으로, 아래 제시된 족보 중 아직까지 기록되지 않은 하나를 반드시 선택하여, 점수판에 해당 족보의 점수를 규칙에 맞게 기록해야 합니다.\n");
            printf("4. 기록되지 않은 족보 중에서 만족하는 족보가 없거나, 있더라도 점수 기대값이 마음에 들지 않는 등의 사유로, 만족하지 않는 족보를 선택하는 경우, 선택한 족보의 점수칸에 0점으로 기록해야 합니다.\n");
            printf("5. 모든 플레이어가 점수판을 모두 채우면 게임이 끝납니다. 점수판에 기록한 점수 총합이 가장 높은 사람이 승리하며, 순위를 가릴 경우 점수 총합이 높은 순서대로 순위를 결정한다.\n");

            break;

        case 2:

            printf("______________________________________________________________________________________________________\n");
            printf("이름    ㅣ               설명                       ㅣ                    예시\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ□ □ □  □ □ □  □ □ □  ■ □ ■  ■ □ ■\n");
            printf("Aces    ㅣ 1이 나온 주사위 눈의 총합,               ㅣ□ ■ □  □ ■ □  □ ■ □  □ ■ □  ■ □ ■  =3점\n");
            printf("        ㅣ    최대 5점                              ㅣ□ □ □  □ □ □  □ □ □  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ□ □ □  □ □ □  □ □ □  ■ □ ■  ■ □ ■\n");
            printf("Twos    ㅣ 2가 나온 주사위 눈의 총합,               ㅣ■ □ ■  ■ □ ■  ■ □ ■  □ ■ □  ■ □ ■  =6점\n");
            printf("        ㅣ    최대 10점                             ㅣ□ □ □  □ □ □  □ □ □  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ □  ■ □ □  ■ □ ■  ■ □ ■\n");
            printf("Threes  ㅣ 3이 나온 주사위 눈의 총합,               ㅣ□ ■ □  □ ■ □  □ ■ □  □ ■ □  ■ □ ■  =9점\n");
            printf("        ㅣ    최대 15점                             ㅣ□ □ ■  □ □ ■  □ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Fours   ㅣ 4가 나온 주사위 눈의 총합,               ㅣ□ □ □  □ □ □  □ □ □  □ ■ □  ■ □ ■  =12점\n");
            printf("        ㅣ    최대 20점                             ㅣ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Fives   ㅣ 5가 나온 주사위 눈의 총합,               ㅣ□ ■ □  □ ■ □  □ ■ □  □ ■ □  □ ■ □  =15점\n");
            printf("        ㅣ    최대 25점                             ㅣ□ □ ■  □ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Sixes   ㅣ 6이 나온 주사위 눈의 총합,               ㅣ□ ■ □  □ ■ □  ■ □ ■  ■ □ ■  ■ □ ■  =18점\n");
            printf("        ㅣ    최대 30점                             ㅣ□ □ ■  □ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ                                                 \n");
            printf("Bonus   ㅣ Aces, Twos, Threes, Fours,Fives,         ㅣ                                                 \n");
            printf("        ㅣ Sixes의 합이 65이상일때 고정 35점        ㅣ                                                 \n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Four of ㅣ동일한 주사위 눈이 4개 이상일 때,         ㅣ□ ■ □  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  =24점\n");
            printf("a Kind  ㅣ동일한 주사위 눈 4개의 총합 최대 24점     ㅣ□ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Full    ㅣ동일한 주사위 눈 한 종류가 3개,다른 종류가ㅣ□ ■ □  □ ■ □  ■ □ ■  ■ □ ■  ■ □ ■  =24점\n");
            printf("House   ㅣ2개일 때, 주사위 눈 5개의 총합, 최대 28점 ㅣ□ □ ■  □ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ□ □ □  □ □ □  ■ □ □  ■ □ ■  ■ □ ■\n");
            printf("Small   ㅣ주사위 눈4개가 순차적일 때,               ㅣ□ ■ □  ■ □ ■  □ ■ □  □ □ □  □ ■ □  =30점\n");
            printf("Straightㅣ   고정 30점                              ㅣ□ □ □  □ □ □  □ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ□ □ □  ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Big     ㅣ주사위 눈 5개가 순차적일 때,              ㅣ■ □ ■  □ ■ □  □ □ □  □ ■ □  ■ □ ■  =18점\n");
            printf("Straightㅣ   고정 40점                              ㅣ□ □ □  □ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ □  ■ □ □  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Chance  ㅣ주사위 눈 5개의 총합,                     ㅣ□ ■ □  □ ■ □  ■ □ ■  ■ □ ■  ■ □ ■  =18점\n");
            printf("        ㅣ   최대 30점                              ㅣ□ □ ■  □ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");
            printf("        ㅣ                                          ㅣ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("Yahtzee ㅣ동일한 주사위 눈이 5개 이상일 때,         ㅣ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  =50점\n");
            printf("        ㅣ   고정 50점                              ㅣ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■  ■ □ ■\n");
            printf("--------ㅣ------------------------------------------ㅣ-------------------------------------------------\n");

            break;

        case 3:
            system("cls");
            printf("==============================================================================================================================\n");
            printf("==============================================================================================================================\n");
            printf("==============================================================================================================================\n");
            printf("==================================================== 게임을 시작합니다. ======================================================\n");
            printf("==============================================================================================================================\n");
            printf("==============================================================================================================================\n");
            printf("==============================================================================================================================\n");
            Sleep(500);
            break;

        default:
            printf("잘못 입력하셨습니다.\n");
            break;
        }
    }




    //종료

}
bool programEnd()
{
    char key;
    printf("게임을 종료하려면 'q'를 입력하시고, 다시 시작하려면 아무 키나 누르시오 : ");
    scanf_s(" %c", &key, 1);

    if (key == 'q') {

        printf("게임을 종료합니다.\n");
        Sleep(500);
        return false;
    }
    else {
        printf("게임을 다시 시작합니다.\n");
        Sleep(500);
        system("cls");
        
    }
    return true;
}

void main()
{
    time_t t;
    srand((unsigned)time(&t));
    
    bool gamecontinue = true;
    
    while (gamecontinue)
    {
        menu();
        yacht();
        gamecontinue = programEnd();
    }

    return;
}

//======================================================================================================================
//| player          |  name1  |  name2  |  name3  |  name4  || player          |  name1  |  name2  |  name3  |  name4  |
//| Aces            |         |         |         |         || Full House      |         |         |         |         |
//| TWO             |         |         |         |         || Four Of a Kind  |         |         |         |         |
//| THREE           |         |         |         |         || Little Straight |         |         |         |         |
//| FOUR            |         |         |         |         || Big Straight    |         |         |         |         |
//| FIVE            |         |         |         |         || Chice           |         |         |         |         |
//| SIX             |         |         |         |         || Yacht           |         |         |         |         |
//| BONUS           |         |         |         |         || Total           |         |         |         |         |
//======================================================================================================================
//|                                                         ||    ■□■     ■□■     ■□■     ■□■     ■□■   |      
//|                                                         ||    ■□■     ■□■     ■□■     ■□■     ■□■   |
//|                                                         ||    ■□■     ■□■     ■□■     ■□■     ■□■   |
//======================================================================================================================
