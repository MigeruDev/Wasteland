#include "Character.h"

FILE *file;

BITMAP *buffer;
BITMAP *scoreTable;
BITMAP *backMenu;

typedef struct
{
    BITMAP *ground;
    BITMAP *metaground;
    BITMAP *numbers[14];
    BITMAP *light[3];
    BITMAP *tryitout;
}MiniGame;

MiniGame semaforo;

typedef struct
{
    char type[6];
    int score;
} Locker;

Locker locker[51];                      // Arreglo de estructuras, que representa cada casilla dentro del tablero

typedef struct
{
    char type[6];
    int value;
    int position;
} MetaMap;

MetaMap parameters[12];                 // Arreglo de estructuras, que representa el meta archivo con las casillas y sus posiciones

typedef struct
{
    BITMAP *frame[15];
    int moveFrame;
    int cnstFrame;
    int step_x;
    int metax;
    int step_y;
    int metay;
    int fault;
    int hydra;
    int event;
    int score;
    char *name;
}PJ;

PJ players[5];

typedef struct
{
    BITMAP *cursor;
    BITMAP *background[24];
    int moveGround;
    BITMAP *buffer;
    BITMAP *tablero;
    BITMAP *lockerIcon[9];
    BITMAP *frame;
    BITMAP *clickDice;
    BITMAP  *diceFace[6];
    BITMAP *playerName[5];
    BITMAP *msg[14];
    MIDI *soundtrack;
    SAMPLE *dices;
}Board;

Board ventana3;


int Turno = 0;
int Steps = 0;
int Guess = 0;
int msg = 0;
int x = 0;
int winner = 0;
int exitGame2=0;
int exitWinners=0;


int pass[3];
int tryitout[3];
int Attemp = 3;

int window3(int finish);
void setUp3();
void printMSG();
void motionMaster3();
void motionGround3();
void setPosition();
void clickDice();
void setScore();
void readFile();
void printLocker();
void setLocker();
void doSomething();
void trafficLight();
void checkAttemp();
int winners(int finish);
int winnerMe(int finish);
void exitMe2();
void randomMap();


int window3(int finish)
{
    if (finish==0)
    {
        window2(finish);
    }

    if (finish == 0 && exitGame==0)
    {
        if (mapSelect==1)
            readFile();
        else
        {
            randomMap();
            printf("\nEntro a randomMap");
        }
        setUp3();
        printLocker();
        play_midi(ventana3.soundtrack, 1);
    }


    while (finish == 0 && exitGame==0 && winner==0 && exitGame2==0)
    {
        motionMaster3();
        motionGround3();

        draw_sprite(ventana3.buffer, ventana3.tablero, 0, 0);
        draw_sprite(ventana3.buffer, ventana3.playerName[Turno], 978, 50);

        if (players[Turno].event==0)
        {
            setPosition();
            if (players[Turno].fault==0)
            {
                printMSG();
                clickDice();
            }
            else
                players[Turno].fault--;
        }
        else
        {
            setPosition();
            if (msg==0)
            {
                draw_sprite(ventana3.buffer, ventana3.msg[9], 992, 122);
                blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
                rest(1500);
                msg=1;
            }
            trafficLight();
        }
        exitMe2();
        draw_sprite(ventana3.buffer, ventana3.cursor, mouse_x, mouse_y);
        blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
    }
    finish = winners(finish);
    return finish;
}

void setUp3 ()
{
    ventana3.buffer = create_bitmap(1300, 700);
    ventana3.frame = create_bitmap(1300, 700);
    ventana3.cursor = load_bitmap("Acces/mouse.bmp", NULL);
    ventana3.soundtrack = load_midi("Soundtrack/TheBaseballs_Umbrella.mid");
    ventana3.dices = load_wav("Effect/ShakeDice.wav");

    ventana3.moveGround=0;
    srand(time(NULL));

    char* word = (char *)malloc(10240 * sizeof(char));
    char* aux = (char *)malloc(10240 * sizeof(char));

    int i;

        for (i=0; i < 24; i++)
      {
            strcpy(word, "Board/Cube/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            ventana3.background[i] = load_bitmap(word,NULL);
      }

    ventana3.tablero = load_bitmap("Board/board2.bmp", NULL);

    ventana3.clickDice = load_bitmap("Board/ClickMe2.bmp", NULL);
    ventana3.diceFace[0] = load_bitmap("Acces/face1.bmp", NULL);
    ventana3.diceFace[1] = load_bitmap("Acces/face2.bmp", NULL);
    ventana3.diceFace[2] = load_bitmap("Acces/face3.bmp", NULL);
    ventana3.diceFace[3] = load_bitmap("Acces/face4.bmp", NULL);
    ventana3.diceFace[4] = load_bitmap("Acces/face5.bmp", NULL);
    ventana3.diceFace[5] = load_bitmap("Acces/face6.bmp", NULL);

    ventana3.playerName[0] = load_bitmap("Board/Player1.bmp",NULL);
    ventana3.playerName[1] = load_bitmap("Board/Player2.bmp",NULL);
    ventana3.playerName[2] = load_bitmap("Board/Player3.bmp",NULL);
    ventana3.playerName[3] = load_bitmap("Board/Player4.bmp",NULL);
    ventana3.playerName[4] = load_bitmap("Board/Player5.bmp",NULL);

    ventana3.lockerIcon[0] = load_bitmap("Locker/teleport.bmp", NULL);
    ventana3.lockerIcon[1] = load_bitmap("Locker/bridge.bmp", NULL);
    ventana3.lockerIcon[2] = load_bitmap("Locker/timer.bmp", NULL);
    ventana3.lockerIcon[3] = load_bitmap("Locker/tunel.bmp", NULL);
    ventana3.lockerIcon[4] = load_bitmap("Locker/HailHydra.bmp", NULL);
    ventana3.lockerIcon[5] = load_bitmap("Locker/lights.bmp", NULL);
    ventana3.lockerIcon[6] = load_bitmap("Locker/ravine.bmp", NULL);
    ventana3.lockerIcon[7] = load_bitmap("Locker/Prison.bmp", NULL);
    ventana3.lockerIcon[8] = load_bitmap("Locker/victory.bmp", NULL);

    ventana3.msg[0] = load_bitmap("Board/MsgMeta.bmp", NULL);
    ventana3.msg[1] = load_bitmap("Board/attemp1.bmp", NULL);
    ventana3.msg[2] = load_bitmap("Board/attemp2.bmp", NULL);
    ventana3.msg[3] = load_bitmap("Board/attemp3.bmp", NULL);
    ventana3.msg[4] = load_bitmap("Board/MsgAvanza.bmp", NULL);
    ventana3.msg[5] = load_bitmap("Board/MsgBack.bmp", NULL);
    ventana3.msg[6] = load_bitmap("Board/MsgDice.bmp", NULL);
    ventana3.msg[7] = load_bitmap("Board/MsgGoodJob.bmp", NULL);
    ventana3.msg[8] = load_bitmap("Board/MsgHydra.bmp", NULL);
    ventana3.msg[9] = load_bitmap("Board/MsgSemaforo.bmp", NULL);
    ventana3.msg[10] = load_bitmap("Board/MsgTeleport.bmp", NULL);
    ventana3.msg[11] = load_bitmap("Board/MsgTurno1.bmp", NULL);
    ventana3.msg[12] = load_bitmap("Board/MsgTurno2.bmp", NULL);
    ventana3.msg[13] = load_bitmap("Board/MsgClickMe.bmp", NULL);

    for (i = 0; i < ventana2.playersCant + 1; i++)
    {
        printf("\nThe bug is here, i: %d", i);
        switch(ventana2.orderChamp[i])
        {
         case 0:
             players[i].frame[0] = load_bitmap("Board/Albert/0.bmp", NULL);
             players[i].frame[1] = load_bitmap("Board/Albert/1.bmp", NULL);
             players[i].frame[2] = load_bitmap("Board/Albert/2.bmp", NULL);
             players[i].frame[3] = load_bitmap("Board/Albert/3.bmp", NULL);
             players[i].frame[4] = load_bitmap("Board/Albert/4.bmp", NULL);
             players[i].frame[5] = load_bitmap("Board/Albert/5.bmp", NULL);
             players[i].frame[6] = load_bitmap("Board/Albert/6.bmp", NULL);
             players[i].frame[7] = load_bitmap("Board/Albert/7.bmp", NULL);
             players[i].frame[8] = load_bitmap("Board/Albert/8.bmp", NULL);
             players[i].frame[9] = load_bitmap("Board/Albert/9.bmp", NULL);
             players[i].frame[10] = load_bitmap("Board/Albert/10.bmp", NULL);
             players[i].frame[11] = load_bitmap("Board/Albert/11.bmp", NULL);
             players[i].frame[12] = load_bitmap("Board/Albert/12.bmp", NULL);
             players[i].frame[13] = load_bitmap("Board/Albert/13.bmp", NULL);
             players[i].frame[14] = load_bitmap("Board/Albert/14.bmp", NULL);
             players[i].cnstFrame = 0;
             players[i].moveFrame = 0;
             players[i].score = 1;
             players[i].fault = 0;
             players[i].event=0;
             players[i].hydra = 0;
             players[i].step_x = 0;
             players[i].step_y = 26;
             players[i].metax = 0;
             players[i].metay = 26;
             players[i].name = (char *)malloc(10240 * sizeof(char));
            strcpy(players[i].name,ventana2.playerName[i]);
            break;
         case 1:
             players[i].frame[0] = load_bitmap("Board/Marie/0.bmp", NULL);
             players[i].frame[1] = load_bitmap("Board/Marie/1.bmp", NULL);
             players[i].frame[2] = load_bitmap("Board/Marie/2.bmp", NULL);
             players[i].frame[3] = load_bitmap("Board/Marie/3.bmp", NULL);
             players[i].frame[4] = load_bitmap("Board/Marie/4.bmp", NULL);
             players[i].frame[5] = load_bitmap("Board/Marie/5.bmp", NULL);
             players[i].frame[6] = load_bitmap("Board/Marie/6.bmp", NULL);
             players[i].frame[7] = load_bitmap("Board/Marie/7.bmp", NULL);
             players[i].frame[8] = load_bitmap("Board/Marie/8.bmp", NULL);
             players[i].frame[9] = load_bitmap("Board/Marie/9.bmp", NULL);
             players[i].frame[10] = load_bitmap("Board/Marie/10.bmp", NULL);
             players[i].frame[11] = load_bitmap("Board/Marie/11.bmp", NULL);
             players[i].frame[12] = load_bitmap("Board/Marie/12.bmp", NULL);
             players[i].frame[13] = load_bitmap("Board/Marie/13.bmp", NULL);
             players[i].frame[14] = load_bitmap("Board/Marie/14.bmp", NULL);
             players[i].cnstFrame = 0;
             players[i].moveFrame = 0;
             players[i].score = 1;
             players[i].fault = 0;
             players[i].event=0;
             players[i].hydra = 0;
             players[i].step_x = 34;
             players[i].step_y = 34;
             players[i].metax = 34;
             players[i].metay = 34;
             players[i].name = (char *)malloc(10240 * sizeof(char));
             strcpy(players[i].name,ventana2.playerName[i]);
            break;
         case 2:
             players[i].frame[0] = load_bitmap("Board/Darwin/0.bmp", NULL);
             players[i].frame[1] = load_bitmap("Board/Darwin/1.bmp", NULL);
             players[i].frame[2] = load_bitmap("Board/Darwin/2.bmp", NULL);
             players[i].frame[3] = load_bitmap("Board/Darwin/3.bmp", NULL);
             players[i].frame[4] = load_bitmap("Board/Darwin/4.bmp", NULL);
             players[i].frame[5] = load_bitmap("Board/Darwin/5.bmp", NULL);
             players[i].frame[6] = load_bitmap("Board/Darwin/6.bmp", NULL);
             players[i].frame[7] = load_bitmap("Board/Darwin/7.bmp", NULL);
             players[i].frame[8] = load_bitmap("Board/Darwin/8.bmp", NULL);
             players[i].frame[9] = load_bitmap("Board/Darwin/9.bmp", NULL);
             players[i].frame[10] = load_bitmap("Board/Darwin/10.bmp", NULL);
             players[i].frame[11] = load_bitmap("Board/Darwin/11.bmp", NULL);
             players[i].frame[12] = load_bitmap("Board/Darwin/12.bmp", NULL);
             players[i].frame[13] = load_bitmap("Board/Darwin/13.bmp", NULL);
             players[i].frame[14] = load_bitmap("Board/Darwin/14.bmp", NULL);
             players[i].cnstFrame = 0;
             players[i].moveFrame = 0;
             players[i].score = 1;
             players[i].fault = 0;
             players[i].event=0;
             players[i].hydra = 0;
             players[i].step_x = 57;
             players[i].step_y = 31;
             players[i].metax = 57;
             players[i].metay = 31;
             players[i].name = (char *)malloc(10240 * sizeof(char));
             strcpy(players[i].name,ventana2.playerName[i]);
            break;
         case 3:
             players[i].frame[0] = load_bitmap("Board/Tesla/0.bmp", NULL);
             players[i].frame[1] = load_bitmap("Board/Tesla/1.bmp", NULL);
             players[i].frame[2] = load_bitmap("Board/Tesla/2.bmp", NULL);
             players[i].frame[3] = load_bitmap("Board/Tesla/3.bmp", NULL);
             players[i].frame[4] = load_bitmap("Board/Tesla/4.bmp", NULL);
             players[i].frame[5] = load_bitmap("Board/Tesla/5.bmp", NULL);
             players[i].frame[6] = load_bitmap("Board/Tesla/6.bmp", NULL);
             players[i].frame[7] = load_bitmap("Board/Tesla/7.bmp", NULL);
             players[i].frame[8] = load_bitmap("Board/Tesla/8.bmp", NULL);
             players[i].frame[9] = load_bitmap("Board/Tesla/9.bmp", NULL);
             players[i].frame[10] = load_bitmap("Board/Tesla/10.bmp", NULL);
             players[i].frame[11] = load_bitmap("Board/Tesla/11.bmp", NULL);
             players[i].frame[12] = load_bitmap("Board/Tesla/12.bmp", NULL);
             players[i].frame[13] = load_bitmap("Board/Tesla/13.bmp", NULL);
             players[i].frame[14] = load_bitmap("Board/Tesla/14.bmp", NULL);
             players[i].cnstFrame = 0;
             players[i].moveFrame = 0;
             players[i].score = 1;
             players[i].fault = 0;
             players[i].event=0;
             players[i].hydra = 0;
             players[i].step_x = 34;
             players[i].step_y = 73;
             players[i].metax = 34;
             players[i].metay = 73;
             players[i].name = (char *)malloc(10240 * sizeof(char));
             strcpy(players[i].name,ventana2.playerName[i]);
            break;
         case 4:
             players[i].frame[0] = load_bitmap("Board/Newton/0.bmp", NULL);
             players[i].frame[1] = load_bitmap("Board/Newton/1.bmp", NULL);
             players[i].frame[2] = load_bitmap("Board/Newton/2.bmp", NULL);
             players[i].frame[3] = load_bitmap("Board/Newton/3.bmp", NULL);
             players[i].frame[4] = load_bitmap("Board/Newton/4.bmp", NULL);
             players[i].frame[5] = load_bitmap("Board/Newton/5.bmp", NULL);
             players[i].frame[6] = load_bitmap("Board/Newton/6.bmp", NULL);
             players[i].frame[7] = load_bitmap("Board/Newton/7.bmp", NULL);
             players[i].frame[8] = load_bitmap("Board/Newton/8.bmp", NULL);
             players[i].frame[9] = load_bitmap("Board/Newton/9.bmp", NULL);
             players[i].frame[10] = load_bitmap("Board/Newton/10.bmp", NULL);
             players[i].frame[11] = load_bitmap("Board/Newton/11.bmp", NULL);
             players[i].frame[12] = load_bitmap("Board/Newton/12.bmp", NULL);
             players[i].frame[13] = load_bitmap("Board/Newton/13.bmp", NULL);
             players[i].frame[14] = load_bitmap("Board/Newton/14.bmp", NULL);
             players[i].cnstFrame = 0;
             players[i].moveFrame = 0;
             players[i].score = 1;
             players[i].fault = 0;
             players[i].event=0;
             players[i].hydra = 0;
             players[i].step_x = 11;
             players[i].step_y = 69;
             players[i].metax = 11;
             players[i].metay = 69;
             players[i].name = (char *)malloc(10240 * sizeof(char));
             strcpy(players[i].name,ventana2.playerName[i]);
            break;
        }
    }

    semaforo.ground = load_bitmap ("Board/TrafficLight.bmp", NULL);
    semaforo.metaground = load_bitmap ("Board/TrafficLight.bmp", NULL);
    semaforo.numbers[0] = load_bitmap ("Board/0.bmp", NULL);
    semaforo.numbers[1] = load_bitmap ("Board/1.bmp", NULL);
    semaforo.numbers[2] = load_bitmap ("Board/2.bmp", NULL);
    semaforo.numbers[3] = load_bitmap ("Board/3.bmp", NULL);
    semaforo.numbers[4] = load_bitmap ("Board/4.bmp", NULL);
    semaforo.numbers[5] = load_bitmap ("Board/5.bmp", NULL);
    semaforo.numbers[6] = load_bitmap ("Board/6.bmp", NULL);
    semaforo.numbers[7] = load_bitmap ("Board/7.bmp", NULL);
    semaforo.numbers[8] = load_bitmap ("Board/8.bmp", NULL);
    semaforo.numbers[9] = load_bitmap ("Board/9.bmp", NULL);
    semaforo.numbers[10] = load_bitmap ("Board/10.bmp", NULL);
    semaforo.numbers[11] = load_bitmap ("Board/11.bmp", NULL);
    semaforo.numbers[12] = load_bitmap ("Board/12.bmp", NULL);
    semaforo.numbers[13] = load_bitmap ("Board/try.bmp", NULL);

    semaforo.light[0] = load_bitmap("Board/Green.bmp", NULL);
    semaforo.light[1] = load_bitmap("Board/Yellow.bmp", NULL);
    semaforo.light[2] = load_bitmap("Board/Red.bmp", NULL);

    semaforo.tryitout = load_bitmap("Board/TryItOut2.bmp", NULL);

    for (i=0; i < 3; i++)
    {
        pass[i]=0;
        tryitout[i]=0;
    }


    draw_sprite(ventana3.tablero, ventana3.diceFace[0], 1005, 315);
    draw_sprite(ventana3.tablero, ventana3.diceFace[0], 1145, 315);

}


void printMSG()
{
    draw_sprite(ventana3.buffer, ventana3.msg[13], 992, 122);
    if (players[Turno].fault==2)
        draw_sprite(ventana3.buffer, ventana3.msg[12], 992, 122);
    if (players[Turno].fault==1)
        draw_sprite(ventana3.buffer, ventana3.msg[11], 992, 122);
    if (players[Turno].hydra==1)
    {
        draw_sprite(ventana3.buffer, ventana3.msg[8], 992, 122);
        switch(x)
        {
        case 2:
            draw_sprite(ventana3.buffer, semaforo.numbers[2], 1168, 158);
            break;
        case 3:
            draw_sprite(ventana3.buffer, semaforo.numbers[3], 1168, 158);
            break;
        case 4:
            draw_sprite(ventana3.buffer, semaforo.numbers[4], 1168, 158);
            break;
        case 5:
            draw_sprite(ventana3.buffer, semaforo.numbers[5], 1168, 158);
            break;
        case 6:
            draw_sprite(ventana3.buffer, semaforo.numbers[6], 1168, 158);
            break;
        case 7:
            draw_sprite(ventana3.buffer, semaforo.numbers[7], 1168, 158);
            break;
        case 8:
            draw_sprite(ventana3.buffer, semaforo.numbers[8], 1168, 158);
            break;
        case 9:
            draw_sprite(ventana3.buffer, semaforo.numbers[9], 1168, 158);
            break;
        case 10:
            draw_sprite(ventana3.buffer, semaforo.numbers[10], 1168, 158);
            break;
        case 11:
            draw_sprite(ventana3.buffer, semaforo.numbers[11], 1168, 158);
            break;
        case 12:
            draw_sprite(ventana3.buffer, semaforo.numbers[12], 1168, 158);
            break;
        }
    }
}

void clickDice()
{
    if (mouse_x > 1052 && mouse_x < 1208 && mouse_y > 250 && mouse_y < 281)
    {
        draw_sprite(ventana3.buffer, ventana3.clickDice, 1038, 238);
        if (mouse_b&1)
        {
            int i, dice1, dice2;
            play_sample(ventana3.dices, 200, 0, 1000, 0);
            for (i=0; i < 5; i++)
            {
                dice1 = rand()%6;
                dice2 = rand()%6;
                draw_sprite(ventana3.buffer, ventana3.diceFace[dice1], 1005, 315);
                draw_sprite(ventana3.buffer, ventana3.diceFace[dice2], 1145, 315);
                blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
                rest(200);
            }
                draw_sprite(ventana3.tablero, ventana3.diceFace[dice1], 1005, 315);
                draw_sprite(ventana3.tablero, ventana3.diceFace[dice2], 1145, 315);
            Steps = dice1 + dice2 +2;
            if (players[Turno].hydra==1)
            {
                if (Steps==Guess)
                {
                    //blit(ventana3.msg[1], screen, 0, 0, 440, 35, 1300, 700);
                    //rest(2000);
                    players[Turno].hydra=0;
                    draw_sprite(ventana3.buffer, ventana3.msg[7], 992, 122);
                    blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
                    rest(1500);
                    Steps=1;
                    setScore();
                }
            }
            else
            {
                setScore();
                doSomething();
            }

            if (Turno < ventana2.playersCant)
                Turno++;
            else
                Turno=0;
            rest(1000);
        }
    }
}

void motionMaster3()
{
    int i;
    if (ventana3.moveGround>240)
        ventana3.moveGround=0;
    else
        ventana3.moveGround++;

    for (i = 0; i < ventana2.playersCant + 1; i++)
    {
        if (players[i].moveFrame>140)
            players[i].moveFrame=0;
        else
            players[i].moveFrame++;
    }
}

void motionGround3()
{
    if (ventana3.moveGround<240)
        draw_sprite(ventana3.buffer, ventana3.background[ventana3.moveGround/10], 0, 0);
}

void setPosition()
{
    int i;
    for (i=0; i < ventana2.playersCant +1 ; i++)
    {
        if (players[i].moveFrame%10)
            players[i].cnstFrame = players[i].moveFrame/10;
         draw_sprite(ventana3.buffer, players[i].frame[players[i].cnstFrame], players[i].step_x , players[i].step_y);
    }
}


void readFile ()                    // Complete - > // Lee el archivo que contiene las casillas y sus valores
{
    int i=0;
    char *row = (char*)malloc(10240*sizeof(char));
    char *aux = (char *)malloc(10240*sizeof(char));
    file = fopen("casillas.txt", "r");

    while(!feof(file))
    {
        fgets(row, 7, file);
        aux = strtok(row, "=");
        strcpy(parameters[i].type, aux);
        aux = strtok(NULL, "=");
        parameters[i].position= atoi(aux);
        parameters[i].value=i;
        i++;
    }
}


void printLocker()
{
    int i;
    for (i=0; i < 12; i++)
    {
        if (strcmp(parameters[i].type, "B")==0)
        {
            strcpy(locker[parameters[i].position].type, "B");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[6], parameters[i].position);
        }
        ////////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "S1")==0 || strcmp(parameters[i].type, "S2")==0 || strcmp(parameters[i].type, "S3")==0)
        {
            strcpy(locker[parameters[i].position].type, "S");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[5], parameters[i].position);
        }
        ////////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "R")==0)
        {
            strcpy(locker[parameters[i].position].type, "R");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[4], parameters[i].position);
        }
         ////////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "C")==0)
        {
            strcpy(locker[parameters[i].position].type, "C");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[7], parameters[i].position);
        }
        ////////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "T1")==0 || strcmp(parameters[i].type, "T2")==0)
        {
            strcpy(locker[parameters[i].position].type, "T");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[3], parameters[i].position);
        }
        ///////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "A")==0)
        {
            strcpy(locker[parameters[i].position].type, "A");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[2], parameters[i].position);
        }

        ///////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "P")==0)
        {
            strcpy(locker[parameters[i].position].type, "P");
            locker[parameters[i].position].score=1;
            setLocker(ventana3.lockerIcon[1], parameters[i].position);
        }
        ///////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "X")==0)
        {
            x = parameters[i].position;
        }
        ///////////////////////////////////////////////////////////////////////////////
        if (strcmp(parameters[i].type, "V")==0)
        {
            int j, aux, pos;
            pos = parameters[i].position;
            aux = parameters[i].position;
            for (j=0; j < 49 / parameters[i].position; j++)
            {
                strcpy(locker[pos].type, "V");
               // printf("\nI'm the player %i.This is aux:\t%i", Turno, pos);
                locker[pos].score=1;
                setLocker(ventana3.lockerIcon[0], pos);
                pos += aux;
            }
        }

    }
}

void setLocker (BITMAP *casilla, int score)
{
    draw_sprite(ventana3.tablero, ventana3.lockerIcon[8], 548, 361);
        if (score <10)
            draw_sprite(ventana3.tablero, casilla, 36 + 106*score - 106 , 104 );

        if (score >= 10 && score < 18)
          draw_sprite(ventana3.tablero, casilla, 877 , 170 + 66*(score-9) - 66 );

        if (score >= 18 && score < 26)
          draw_sprite(ventana3.tablero, casilla, 36 + 106*(26-score) - 106, 625 );

        if (score >= 26 && score < 32)
           draw_sprite(ventana3.tablero, casilla, 36, 170 + 66*(33-score)-66 );

        if (score >= 32 && score < 38)
          draw_sprite(ventana3.tablero, casilla, 36 +106*(score-30)-106, 234 );

        if (score >= 38 && score < 42)
          draw_sprite(ventana3.tablero, casilla, 666, 170 + 66*(score-35)-66);

        if (score >= 42 && score < 46)
          draw_sprite(ventana3.tablero, casilla, 36 + 106*(48-score)-106, 495);

        if (score == 46)
          draw_sprite(ventana3.tablero, casilla, 246, 429);

        if (score == 47)
          draw_sprite(ventana3.tablero, casilla, 246, 364);

        if (score == 48)
          draw_sprite(ventana3.tablero, casilla, 351, 364);

        if (score == 49)
          draw_sprite(ventana3.tablero, casilla, 456, 364);
}

void setScore ()
{
    int i;
    draw_sprite(ventana3.frame, ventana3.buffer, 0, 0);

    if (players[Turno].score>=50)
    {
        for (i=0; i < Steps; i++)
        {
            printf("\n[into recursion]This is score of player %i: %i", Turno+1, players[Turno].score);
            draw_sprite(ventana3.buffer, ventana3.frame, 0, 0);
            if (players[Turno].score > 37 && players[Turno].score <= 41)
            {
                players[Turno].step_y -= 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score > 41 && players[Turno].score <= 45)
            {
                players[Turno].step_x += 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score > 45 && players[Turno].score <= 47)
            {
                players[Turno].step_y += 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score > 47 && players[Turno].score <= 50)
            {
                players[Turno].step_x -= 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            players[Turno].score--;
            setPosition();
            blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
        }
    }
    else
    {
        for (i=0; i < Steps; i++)
        {
            printf("\n[out recursion]This is score of player %i: %i", Turno+1, players[Turno].score);
            draw_sprite(ventana3.buffer, ventana3.frame, 0, 0);
            if (players[Turno].score <9)
            {
                players[Turno].step_x += 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score >= 9 && players[Turno].score < 17)
            {
                players[Turno].step_y += 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score >= 17 && players[Turno].score < 25)
            {
                players[Turno].step_x -= 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score >= 25 && players[Turno].score < 31)
            {
                players[Turno].step_y -= 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score >= 31 && players[Turno].score < 37)
            {
                players[Turno].step_x += 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score >= 37 && players[Turno].score < 41)
            {
                players[Turno].step_y += 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score >= 41 && players[Turno].score < 45)
            {
                players[Turno].step_x -= 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score >= 45 && players[Turno].score < 47)
            {
                players[Turno].step_y -= 66;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }

            if (players[Turno].score >= 47 && players[Turno].score < 50)
            {
                players[Turno].step_x += 106;
                draw_sprite(ventana3.buffer, players[Turno].frame[0],players[Turno].step_x  , players[Turno].step_y );
                rest(200);
            }
            if (players[Turno].score>=50)
            {
                Steps -= i;
                setScore();
                i = Steps;
                players[Turno].score--;
            }

            players[Turno].score++;
            setPosition();
            blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
        }
        if (players[Turno].score==50)
            winner=1;
    }

}



void doSomething ()
{

    if (locker[players[Turno].score].score==1)
    {
        printf("\nThis is Turn: %i. And this is score: %i", Turno, players[Turno].score);
        if (strcmp(locker[players[Turno].score].type, "V")==0)
        {
            int i;
            Steps=0;
            for (i=players[Turno].score+1; i < 51;i++)
            {
                if (strcmp(locker[i].type, "V")==0)
                    i=51;
                Steps++;
            }
            rest(500);
            draw_sprite(ventana3.buffer, ventana3.msg[10], 992, 122);
            setScore();

        }
//////////////////////////////////////////////////////////////////////////////////////
        if (strcmp(locker[players[Turno].score].type, "P")==0)
        {
            Steps=10;
            rest(500);
            draw_sprite(ventana3.buffer, ventana3.msg[4], 992, 122);
            setScore();
        }
//////////////////////////////////////////////////////////////////////////////////////
        if (strcmp(locker[players[Turno].score].type, "B")==0)
        {
            players[Turno].score =1;
            switch(Turno)
            {
            case 0:
                players[0].step_x = players[0].metax; players[0].step_y=players[0].metay;
                break;
            case 1:
                players[1].step_x = players[1].metax; players[1].step_y=players[1].metay;
                break;
            case 2:
                players[2].step_x = players[2].metax; players[2].step_y = players[2].metay;
                break;
            case 3:
                players[3].step_x = players[3].metax; players[3].step_y=players[3].metay;
                break;
            case 4:
                players[4].step_x = players[4].metax; players[4].step_y=players[4].metay;
                break;
            }
            draw_sprite(ventana3.buffer, ventana3.msg[5], 992, 122);
            blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest(2000);
        }
//////////////////////////////////////////////////////////////////////////////////////
        if (strcmp(locker[players[Turno].score].type, "A")==0)
        {
            players[Turno].fault = 2;
            draw_sprite(ventana3.buffer, ventana3.msg[12], 992, 122);
            blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest(2000);
        }
//////////////////////////////////////////////////////////////////////////////////////
        if (strcmp(locker[players[Turno].score].type, "T")==0)
        {
            Turno--;
            draw_sprite(ventana3.buffer, ventana3.msg[6], 992, 122);
            blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest(1500);
        }
//////////////////////////////////////////////////////////////////////////////////////
        if (strcmp(locker[players[Turno].score].type, "R")==0)
        {
            int i, key;
            for (i=0; i < 12; i++)
            {
                if (strcmp(parameters[i].type, "C")==0)
                    key = parameters[i].position;
            }
            players[Turno].hydra = 1;
            players[Turno].score =1;
            switch(Turno)
            {
            case 0:
                players[0].step_x = players[0].metax; players[0].step_y=players[0].metay;
                break;
            case 1:
                players[1].step_x = players[1].metax; players[1].step_y=players[1].metay;
                break;
            case 2:
                players[2].step_x = players[2].metax; players[2].step_y=players[2].metay;
                break;
            case 3:
                players[3].step_x = players[3].metax; players[3].step_y=players[3].metay;
                break;
            case 4:
                players[4].step_x = players[4].metax; players[4].step_y=players[4].metay;
                break;
            }

            for (i=0; i < key-1; i++)
            {
                if (players[Turno].score <9)
                    players[Turno].step_x += 106;

                if (players[Turno].score >= 9 && players[Turno].score < 17)
                    players[Turno].step_y += 66;

                if (players[Turno].score >= 17 && players[Turno].score < 25)
                    players[Turno].step_x -= 106;

                if (players[Turno].score >= 25 && players[Turno].score < 31)
                    players[Turno].step_y -= 66;

                if (players[Turno].score >= 31 && players[Turno].score < 37)
                    players[Turno].step_x += 106;

                if (players[Turno].score >= 37 && players[Turno].score < 41)
                    players[Turno].step_y += 66;

                if (players[Turno].score >= 41 && players[Turno].score < 45)
                    players[Turno].step_x -= 106;


                if (players[Turno].score >= 45 && players[Turno].score < 47)
                    players[Turno].step_y -= 66;

                if (players[Turno].score >= 47 && players[Turno].score < 50)
                    players[Turno].step_x -= 106;

            players[Turno].score++;
        }
            rest(500);
        }

        if (strcmp(locker[players[Turno].score].type, "S")==0)
        {
            players[Turno].event=1;
            Turno--;
        }
    }
}


void trafficLight ()
{
    int i;
    if (pass[0]==0 && pass[1]==0 && pass[2] == 0)
    {
        draw_sprite(semaforo.ground, semaforo.metaground, 0 ,0 );
        for (i=0; i < 3; i++)
            pass[i] = rand()%9;
        printf("\nThis is the pass: %i - %i - %i", pass[0], pass[1], pass[2]);
        printf("\nIm in trafficLight, the Turn is: %i", Turno);
        printf("\nThis is the Attemp: %i", Attemp);
        printf("\n////////////////////////////////////////////////");
        //draw_sprite(ventana3.buffer, ventana3.msg[7], 440, 35);
        //blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
       // rest(1500);
    }
      switch (Attemp)
    {
        case 3:
            draw_sprite(ventana3.tablero, ventana3.msg[3], 992, 122);
        break;
        case 2:
            draw_sprite(ventana3.tablero, ventana3.msg[2], 992, 122);
        break;
        case 1:
            draw_sprite(ventana3.tablero, ventana3.msg[1], 992, 122);
        break;
    }

    draw_sprite(ventana3.buffer, semaforo.ground, 975, 462);

    if (mouse_x > 1034 && mouse_x < 1061 && mouse_y > 476 && mouse_y < 494)         // Block 1 - Up
    {
        if (mouse_b&1)
         {
            if (tryitout[0]<9)
                tryitout[0]++;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[0]], 52, 40);
         }

    }
    if (mouse_x > 1034 && mouse_x < 1061 && mouse_y > 542 && mouse_y < 566)         // Block 1 - Down
    {
        if (mouse_b&1)
         {
            if (tryitout[0]>0)
                tryitout[0]--;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[0]], 52, 40);
         }

    }
/////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 1109 && mouse_x < 1138 && mouse_y > 476 && mouse_y < 494)         // Block 2 - Up
    {
        if (mouse_b&1)
         {
            if (tryitout[1]<9)
                tryitout[1]++;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[1]], 129, 40);
         }

    }
    if (mouse_x > 1109 && mouse_x < 1138 && mouse_y > 542 && mouse_y < 566)         // Block 2 - Down
    {
        if (mouse_b&1)
         {
            if (tryitout[1]>0)
                tryitout[1]--;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[1]], 129, 40);
         }

    }
/////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 1186 && mouse_x < 1214 && mouse_y > 476 && mouse_y < 494)         // Block 3 - Up
    {
        if (mouse_b&1)
         {
            if (tryitout[2]<9)
                tryitout[2]++;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[2]], 206, 40);
         }

    }
    if (mouse_x > 1186&& mouse_x < 1214 && mouse_y > 542 && mouse_y < 566)         // Block 3 - Down
    {
        if (mouse_b&1)
         {
            if (tryitout[2]>0)
                tryitout[2]--;
            rest(200);
            draw_sprite(semaforo.ground, semaforo.numbers[tryitout[2]], 206, 40);
         }

    }
////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 1073 && mouse_x < 1171 && mouse_y > 628 && mouse_y < 649)         // Try It Out
    {
        draw_sprite(ventana3.buffer, semaforo.tryitout, 1049, 620);
        if (mouse_b&1)
         {
            checkAttemp();
            rest(250);
         }
    }
}

void checkAttemp()
{
    int i;
    if (Attemp>1)
    {
        printf("\nThis is Attemp into checkAttemp: %i", Attemp);
        if (tryitout[0]==pass[0] && tryitout[1]==pass[1]&& tryitout[2]==pass[2])
        {
         players[Turno].event=0;
         Attemp=3;
         msg=0;

         draw_sprite(ventana3.buffer, semaforo.light[0], 1025, 572);
         draw_sprite(ventana3.buffer, semaforo.light[0], 1100, 572);
         draw_sprite(ventana3.buffer, semaforo.light[0], 1176, 572);
         draw_sprite(ventana3.buffer, ventana3.msg[7], 992, 122);
         blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
         rest(1500);
         Steps=1;
         setScore();
            for (i=0; i < 3; i++)
            {
                pass[i]=0;
                tryitout[i]=0;
            }
         if (Turno < ventana2.playersCant)
            Turno++;
         else
            Turno=0;
        }
        else
        {
            for (i=0; i < 3; i++)
            {
                if (tryitout[i]==pass[0] || tryitout[i]==pass[1] || tryitout[i]==pass[2])
                {
                    if (tryitout[i]==pass[i])
                        draw_sprite(semaforo.ground, semaforo.light[0], 76*i + 50 , 112);
                    else
                        draw_sprite(semaforo.ground, semaforo.light[1], 76*i + 50 , 112);
                }
                else
                    draw_sprite(semaforo.ground, semaforo.light[2], 76*i + 50, 112);
            }
            Attemp--;
        }
    }
    else
    {
            for (i=0; i < 3; i++)
            {
                if (tryitout[i]==pass[0] || tryitout[i]==pass[1] || tryitout[i]==pass[2])
                {
                    if (tryitout[i]==pass[i])
                        draw_sprite(semaforo.ground, semaforo.light[0], 76*i + 50 , 112);
                    else
                        draw_sprite(semaforo.ground, semaforo.light[1], 76*i + 50 , 112);
                }
                else
                    draw_sprite(semaforo.ground, semaforo.light[2], 76*i + 50, 112);
            }
        draw_sprite(ventana3.buffer, semaforo.ground, 975, 462);
        blit(ventana3.buffer, screen, 0, 0, 0, 0, 1300, 700);
        rest(1500);
        Attemp=3;
        for (i=0; i < 3; i++)
        {
            pass[i]=0;
            tryitout[i]=0;
        }
        if (Turno < ventana2.playersCant)
            Turno++;
         else
            Turno=0;
        msg=0;
    }
}

int winners(int finish)
{
    buffer = create_bitmap(1300, 700);
    scoreTable = load_bitmap("Board/Winners.bmp", NULL);
    backMenu = load_bitmap("Board/Back2.bmp", NULL);
    ventana3.cursor = load_bitmap("Acces/mouse.bmp", NULL);
    if (finish==0 && exitGame == 0)
    {
        printf("\nHi, i got in to winners");
    int i, a, index;
    char *aux = (char *)malloc(10240 * sizeof(char));
    for (i=1; i < ventana2.playersCant+1; i++)
    {
        index = players[i].score;
        strcpy(aux, players[i].name);
        a = i-1;
        while (a >= 0 && players[a].score < index)
        {
        players[a + 1].score = players[a].score;
        strcpy(players[a+1].name, players[a].name);
        a--;
        }
        players[a+1].score = index;
        strcpy(players[a+1].name, aux);
    }

    if (ventana2.playersCant < 2)
    {
        for (i=0; i< ventana2.playersCant +1; i++)
        {
            for (a=0; a < strlen(players[i].name); a++)
            {
                if (players[i].name[a] == 'A')
                    draw_sprite(scoreTable, ventana2.letters[0], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'B')
                    draw_sprite(scoreTable, ventana2.letters[1], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'C')
                    draw_sprite(scoreTable, ventana2.letters[2], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'D')
                    draw_sprite(scoreTable, ventana2.letters[3], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'E')
                    draw_sprite(scoreTable, ventana2.letters[4], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'F')
                    draw_sprite(scoreTable, ventana2.letters[5], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'G')
                    draw_sprite(scoreTable, ventana2.letters[6], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'H')
                    draw_sprite(scoreTable, ventana2.letters[7], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'I')
                    draw_sprite(scoreTable, ventana2.letters[8], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'J')
                    draw_sprite(scoreTable, ventana2.letters[9], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'K')
                    draw_sprite(scoreTable, ventana2.letters[10], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'L')
                    draw_sprite(scoreTable, ventana2.letters[11], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'M')
                    draw_sprite(scoreTable, ventana2.letters[12], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'N')
                    draw_sprite(scoreTable, ventana2.letters[13], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'O')
                    draw_sprite(scoreTable, ventana2.letters[14], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'P')
                    draw_sprite(scoreTable, ventana2.letters[15], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Q')
                    draw_sprite(scoreTable, ventana2.letters[16], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'R')
                    draw_sprite(scoreTable, ventana2.letters[17], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'S')
                    draw_sprite(scoreTable, ventana2.letters[18], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'T')
                    draw_sprite(scoreTable, ventana2.letters[19], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'U')
                    draw_sprite(scoreTable, ventana2.letters[20], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'V')
                    draw_sprite(scoreTable, ventana2.letters[21], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'W')
                    draw_sprite(scoreTable, ventana2.letters[22], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'X')
                    draw_sprite(scoreTable, ventana2.letters[23], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Y')
                    draw_sprite(scoreTable, ventana2.letters[24], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Z')
                    draw_sprite(scoreTable, ventana2.letters[25], 534 + 40*a, 185 + 150*i);
            }
        }
    }
    else
    {
        for (i=0; i < 3; i++)
        {
            for (a=0; a < strlen(players[i].name); a++)
            {
                if (players[i].name[a] == 'A')
                    draw_sprite(scoreTable, ventana2.letters[0], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'B')
                    draw_sprite(scoreTable, ventana2.letters[1], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'C')
                    draw_sprite(scoreTable, ventana2.letters[2], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'D')
                    draw_sprite(scoreTable, ventana2.letters[3], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'E')
                    draw_sprite(scoreTable, ventana2.letters[4], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'F')
                    draw_sprite(scoreTable, ventana2.letters[5], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'G')
                    draw_sprite(scoreTable, ventana2.letters[6], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'H')
                    draw_sprite(scoreTable, ventana2.letters[7], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'I')
                    draw_sprite(scoreTable, ventana2.letters[8], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'J')
                    draw_sprite(scoreTable, ventana2.letters[9], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'K')
                    draw_sprite(scoreTable, ventana2.letters[10], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'L')
                    draw_sprite(scoreTable, ventana2.letters[11], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'M')
                    draw_sprite(scoreTable, ventana2.letters[12], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'N')
                    draw_sprite(scoreTable, ventana2.letters[13], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'O')
                    draw_sprite(scoreTable, ventana2.letters[14], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'P')
                    draw_sprite(scoreTable, ventana2.letters[15], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Q')
                    draw_sprite(scoreTable, ventana2.letters[16], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'R')
                    draw_sprite(scoreTable, ventana2.letters[17], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'S')
                    draw_sprite(scoreTable, ventana2.letters[18], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'T')
                    draw_sprite(scoreTable, ventana2.letters[19], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'U')
                    draw_sprite(scoreTable, ventana2.letters[20], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'V')
                    draw_sprite(scoreTable, ventana2.letters[21], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'W')
                    draw_sprite(scoreTable, ventana2.letters[22], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'X')
                    draw_sprite(scoreTable, ventana2.letters[23], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Y')
                    draw_sprite(scoreTable, ventana2.letters[24], 534 + 40*a, 185 + 150*i);
                if (players[i].name[a] == 'Z')
                    draw_sprite(scoreTable, ventana2.letters[25], 534 + 40*a, 185 + 150*i);
            }
        }
    }

    }


    while (finish ==0 && exitWinners==0)
    {
        draw_sprite(buffer, scoreTable, 0, 0);
        finish =winnerMe(finish);
        draw_sprite(buffer, ventana3.cursor, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, 1300, 700);
    }
    exitWinners=0;
    return finish;
}

int winnerMe(int finish)
{
    if (mouse_x > 983 && mouse_x < 1262 && mouse_y > 598 && mouse_y < 671)
    {
        draw_sprite(buffer, backMenu, 972, 586);
        if (mouse_b&1)
        {
            exitWinners = 1;
            exitGame = 0;
            Turno = 0;
            Guess=0;
            Steps=0;
            msg=0;
            winner=0;
            idChamp=0;
            caracter = 0;
            exitGame2=0;
            mapSelect=0;
        }
    }
    return finish;
}

void exitMe2()
{
    if (mouse_x > 0 && mouse_x < 59 && mouse_y > 0 && mouse_y < 37)
    {
        if (mouse_b&1)
        {
            exitGame2 = 1;
        }
    }
}

void randomMap()
{
    strcpy(parameters[0].type, "V");
    parameters[0].position = rand()%7 + 3;

    strcpy(parameters[1].type, "P");
    parameters[1].position = rand()%40 + 2;

    strcpy(parameters[2].type, "A");
    parameters[2].position = rand()%40 + 2;

    strcpy(parameters[3].type, "T1");
    parameters[3].position = rand()%30 + 7;

    strcpy(parameters[4].type, "T2");
    parameters[4].position = rand()%35 + 5;

    strcpy(parameters[5].type, "R");
    parameters[5].position = rand()%37 + 10;

    strcpy(parameters[6].type, "C");
    parameters[6].position = rand()%7 + 3;

    strcpy(parameters[7].type, "X");
    parameters[7].position = rand()%10 + 2;

    strcpy(parameters[8].type, "S1");
    parameters[8].position = rand()%37 + 10;

    strcpy(parameters[9].type, "S2");
    parameters[9].position = rand()%37 + 10;

    strcpy(parameters[10].type, "S3");
    parameters[10].position = rand()%37 + 7;

    strcpy(parameters[11].type, "B");
    parameters[11].position = rand()%37 + 10;
}







