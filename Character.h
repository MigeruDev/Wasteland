#include "Heros.h"


typedef struct
{
    BITMAP *buffer;
    BITMAP *background[31];
    int moveGround;
    int okClick;
    int selectClick;
    int playersCant;
    int Turno;
    int mapSelect;
    int orderChamp[5];
    char *playerName[5];
    BITMAP *ground;
    BITMAP *cursor;
    BITMAP *arrow[4];
    BITMAP *ok[3];
    BITMAP *selector[2];
    BITMAP *numbers[5];
    BITMAP *letters[29];
    BITMAP *playerId[5];
    BITMAP *map[2];
    BITMAP *message[3];
    BITMAP *enterName;

    MIDI *soundtrack;
    SAMPLE *click;
    SAMPLE *select;
} Character;

Character ventana2;

int idChamp = 0;
int caracter = 0;
int exitGame = 0;
int mapSelect = 0;

void window2(int finish);
void setUp2();
void motionMaster2();
void motionGround2();
void motionMarrie ();
void motionAlbert ();
void motionDarwin ();
void motionTesla ();
void motionNewton ();
void exitMe();
void clickMe2();
void selectChamp ();
void enterName ();

void window2 (int finish)
{
    if (finish==0)
    {
        setUp2();
        setUpHero();
        play_midi(ventana2.soundtrack, 1);
    }


    while (finish == 0 && exitGame==0 && ventana2.Turno-1 != ventana2.playersCant)
    {
        motionMaster2();
        motionGround2();

        draw_sprite(ventana2.buffer, ventana2.ground, 0, 0);
        selectChamp();
        clickMe2();
        enterName();
        exitMe();
        draw_sprite(ventana2.buffer, ventana2.cursor, mouse_x, mouse_y);
        blit(ventana2.buffer, screen, 0, 0, 0, 0, 1300, 700);
    }
    rest(1000);
}

void setUp2()
{
    ventana2.buffer = create_bitmap(1300,700);
    ventana2.cursor = load_bitmap("Acces/mouse.bmp", NULL);
    ventana2.ground = load_bitmap("Character/character3.bmp", NULL);
    ventana2.moveGround=0;
    ventana2.okClick = 0;
    ventana2.selectClick = 0;
    ventana2.playersCant = 1;
    ventana2.Turno = 0;
   // ventana2.mapSelect = 0;

    ventana2.soundtrack = load_midi("Soundtrack/TheOffspring_TheKidsArentAlright.mid");

    ventana2.playerName[0] = (char *)malloc(10240 * sizeof(char));
    ventana2.playerName[1] = (char *)malloc(10240 * sizeof(char));
    ventana2.playerName[2] = (char *)malloc(10240 * sizeof(char));
    ventana2.playerName[3] = (char *)malloc(10240 * sizeof(char));
    ventana2.playerName[4] = (char *)malloc(10240 * sizeof(char));

    ventana2.playerName[0][0] = '\0';
    ventana2.playerName[1][0] = '\0';
    ventana2.playerName[2][0] = '\0';
    ventana2.playerName[3][0] = '\0';
    ventana2.playerName[4][0] = '\0';


    ventana2.ok[1] = load_bitmap("Character/Ok2.bmp", NULL);
    ventana2.ok[2] = load_bitmap("Character/Ok3.bmp", NULL);

    ventana2.numbers[0] = load_bitmap("Character/uno.bmp", NULL);
    ventana2.numbers[1] = load_bitmap("Character/dos.bmp", NULL);
    ventana2.numbers[2] = load_bitmap("Character/tres.bmp", NULL);
    ventana2.numbers[3] = load_bitmap("Character/cuatro.bmp", NULL);
    ventana2.numbers[4] = load_bitmap("Character/cinco.bmp", NULL);

    ventana2.map[0] = load_bitmap("Character/random.bmp", NULL);
    ventana2.map[1] = load_bitmap("Character/load.bmp", NULL);

    ventana2.selector[0] = load_bitmap("Character/SelectorMix1.bmp", NULL);
    ventana2.selector[1] = load_bitmap("Character/SelectorMix2.bmp", NULL);

    ventana2.arrow[0] = load_bitmap("Character/right1.bmp", NULL);
    ventana2.arrow[1] = load_bitmap("Character/right2.bmp", NULL);
    ventana2.arrow[2] = load_bitmap("Character/left1.bmp", NULL);
    ventana2.arrow[3] = load_bitmap("Character/left2.bmp", NULL);

    ventana2.background[0] = load_bitmap("Character/Nebula/0.bmp", NULL);
    ventana2.background[1] = load_bitmap("Character/Nebula/1.bmp", NULL);
    ventana2.background[2] = load_bitmap("Character/Nebula/2.bmp", NULL);
    ventana2.background[3] = load_bitmap("Character/Nebula/3.bmp", NULL);
    ventana2.background[4] = load_bitmap("Character/Nebula/4.bmp", NULL);
    ventana2.background[5] = load_bitmap("Character/Nebula/5.bmp", NULL);
    ventana2.background[6] = load_bitmap("Character/Nebula/6.bmp", NULL);
    ventana2.background[7] = load_bitmap("Character/Nebula/7.bmp", NULL);
    ventana2.background[8] = load_bitmap("Character/Nebula/8.bmp", NULL);
    ventana2.background[9] = load_bitmap("Character/Nebula/9.bmp", NULL);
    ventana2.background[10] = load_bitmap("Character/Nebula/10.bmp", NULL);
    ventana2.background[11] = load_bitmap("Character/Nebula/11.bmp", NULL);
    ventana2.background[12] = load_bitmap("Character/Nebula/12.bmp", NULL);
    ventana2.background[13] = load_bitmap("Character/Nebula/13.bmp", NULL);
    ventana2.background[14] = load_bitmap("Character/Nebula/14.bmp", NULL);
    ventana2.background[15] = load_bitmap("Character/Nebula/15.bmp", NULL);
    ventana2.background[16] = load_bitmap("Character/Nebula/16.bmp", NULL);
    ventana2.background[17] = load_bitmap("Character/Nebula/17.bmp", NULL);
    ventana2.background[18] = load_bitmap("Character/Nebula/18.bmp", NULL);
    ventana2.background[19] = load_bitmap("Character/Nebula/19.bmp", NULL);
    ventana2.background[20] = load_bitmap("Character/Nebula/20.bmp", NULL);
    ventana2.background[21] = load_bitmap("Character/Nebula/21.bmp", NULL);
    ventana2.background[22] = load_bitmap("Character/Nebula/22.bmp", NULL);
    ventana2.background[23] = load_bitmap("Character/Nebula/23.bmp", NULL);
    ventana2.background[24] = load_bitmap("Character/Nebula/24.bmp", NULL);
    ventana2.background[25] = load_bitmap("Character/Nebula/25.bmp", NULL);
    ventana2.background[26] = load_bitmap("Character/Nebula/26.bmp", NULL);
    ventana2.background[27] = load_bitmap("Character/Nebula/27.bmp", NULL);
    ventana2.background[28] = load_bitmap("Character/Nebula/28.bmp", NULL);
    ventana2.background[29] = load_bitmap("Character/Nebula/29.bmp", NULL);
    ventana2.background[30] = load_bitmap("Character/Nebula/30.bmp", NULL);

    ventana2.enterName = load_bitmap("Character/enterName2.bmp", NULL);

    ventana2.message[0] = load_bitmap("Character/messageLock.bmp", NULL);
    ventana2.message[1] = load_bitmap("Character/messagePlayer.bmp", NULL);
    ventana2.message[2] = load_bitmap("Character/messageLetter.bmp", NULL);

    ventana2.playerId[0] = load_bitmap("Character/Player1.bmp", NULL);
    ventana2.playerId[1] = load_bitmap("Character/Player2.bmp", NULL);
    ventana2.playerId[2] = load_bitmap("Character/Player3.bmp", NULL);
    ventana2.playerId[3] = load_bitmap("Character/Player4.bmp", NULL);
    ventana2.playerId[4] = load_bitmap("Character/Player5.bmp", NULL);

    ventana2.letters[0]= load_bitmap("Character/A.bmp", NULL);
    ventana2.letters[1]= load_bitmap("Character/B.bmp", NULL);
    ventana2.letters[2]= load_bitmap("Character/C.bmp", NULL);
    ventana2.letters[3]= load_bitmap("Character/D.bmp", NULL);
    ventana2.letters[4]= load_bitmap("Character/E.bmp", NULL);
    ventana2.letters[5]= load_bitmap("Character/F.bmp", NULL);
    ventana2.letters[6]= load_bitmap("Character/G.bmp", NULL);
    ventana2.letters[7]= load_bitmap("Character/H.bmp", NULL);
    ventana2.letters[8]= load_bitmap("Character/I.bmp", NULL);
    ventana2.letters[9]= load_bitmap("Character/J.bmp", NULL);
    ventana2.letters[10]= load_bitmap("Character/K.bmp", NULL);
    ventana2.letters[11]= load_bitmap("Character/L.bmp", NULL);
    ventana2.letters[12]= load_bitmap("Character/M.bmp", NULL);
    ventana2.letters[13]= load_bitmap("Character/N.bmp", NULL);
    ventana2.letters[14]= load_bitmap("Character/O.bmp", NULL);
    ventana2.letters[15]= load_bitmap("Character/P.bmp", NULL);
    ventana2.letters[16]= load_bitmap("Character/Q.bmp", NULL);
    ventana2.letters[17]= load_bitmap("Character/R.bmp", NULL);
    ventana2.letters[18]= load_bitmap("Character/S.bmp", NULL);
    ventana2.letters[19]= load_bitmap("Character/T.bmp", NULL);
    ventana2.letters[20]= load_bitmap("Character/U.bmp", NULL);
    ventana2.letters[21]= load_bitmap("Character/V.bmp", NULL);
    ventana2.letters[22]= load_bitmap("Character/W.bmp", NULL);
    ventana2.letters[23]= load_bitmap("Character/X.bmp", NULL);
    ventana2.letters[24]= load_bitmap("Character/Y.bmp", NULL);
    ventana2.letters[25]= load_bitmap("Character/Z.bmp", NULL);
    ventana2.letters[26]= load_bitmap("Character/_.bmp", NULL);
    ventana2.letters[27]= load_bitmap("Character/delete.bmp", NULL);
    ventana2.letters[28]= load_bitmap("Character/eraser.bmp", NULL);

    int i;
    for (i = 0; i < 5; i++)
        ventana2.orderChamp[i]=-1;
}

void motionMaster2()                 // Gestiona las variables de movimiento de las estructuras
{
    if (ventana2.moveGround>915)
        ventana2.moveGround=0;
    else
        ventana2.moveGround++;

    if (hero[1].moveFrame>790)
    {
        hero[1].moveFrame=0;
        hero[1].cnstFrame=0;
    }
    else
        hero[1].moveFrame++;

    if (hero[0].moveFrame>480)
    {
        hero[0].moveFrame=0;
        hero[0].cnstFrame=0;
    }
    else
        hero[0].moveFrame++;

    if (hero[2].moveFrame>530)
    {
        hero[2].moveFrame=0;
        hero[2].cnstFrame=0;
    }
    else
        hero[2].moveFrame++;

    if (hero[3].moveFrame>940)
    {
        hero[3].moveFrame=0;
        hero[3].cnstFrame=0;
    }
    else
        hero[3].moveFrame++;

    if (hero[4].moveFrame>620)
    {
        hero[4].moveFrame=0;
        hero[4].cnstFrame=0;
    }
    else
        hero[4].moveFrame++;

    if (ventana2.okClick==1)
    {
        draw_sprite(ventana2.ground, ventana2.selector[0], 567, 0);
        draw_sprite(ventana2.ground, ventana2.enterName, 0, 48);
        draw_sprite(ventana2.ground, ventana2.playerId[ventana2.Turno], 65, 170);
    }
    else
        draw_sprite(ventana2.ground, ventana2.message[0], 695, 230);


    if (ventana2.okClick==1)
        draw_sprite(ventana2.ground, ventana2.arrow[0], 1200, 235);

    if (ventana2.okClick==1)
        draw_sprite(ventana2.ground, ventana2.arrow[2], 468, 237);


}

void motionGround2 ()                                        // Genera el movimiento para el Fondo
{
    if (ventana2.moveGround<465)
    {
        if (ventana2.moveGround%15)
        draw_sprite(ventana2.buffer, ventana2.background[ventana2.moveGround/15], 0, 0);

    }
    else
    {
        if (ventana2.moveGround%15)
        draw_sprite(ventana2.buffer, ventana2.background[60 - (ventana2.moveGround/15)], 0, 0);
    }
}

void motionMarrie ()
{
    if (hero[1].moveFrame%10)
        hero[1].cnstFrame = hero[1].moveFrame/10;

    draw_sprite(ventana2.buffer, hero[1].frame[hero[1].cnstFrame], 710, 75);
}

void motionAlbert ()
{
    if (hero[0].moveFrame%10)
        hero[0].cnstFrame = hero[0].moveFrame/10;

    draw_sprite(ventana2.buffer, hero[0].frame[hero[0].cnstFrame], 710, 75);
}

void motionDarwin ()
{
    if (hero[2].moveFrame%10)
        hero[2].cnstFrame = hero[2].moveFrame/10;

    draw_sprite(ventana2.buffer, hero[2].frame[hero[2].cnstFrame], 760, 50);
}

void motionTesla ()
{
    if (hero[3].moveFrame%10)
        hero[3].cnstFrame = hero[3].moveFrame/10;

    draw_sprite(ventana2.buffer, hero[3].frame[hero[3].cnstFrame], 760, 50);
}

void motionNewton ()
{
    if (hero[4].moveFrame%10)
        hero[4].cnstFrame = hero[4].moveFrame/10;

    draw_sprite(ventana2.buffer, hero[4].frame[hero[4].cnstFrame], 710, 95);
}

void clickMe2()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 91 && mouse_x < 352 && mouse_y > 461 && mouse_y < 523 && ventana2.okClick==0)            // Buttom - Ok
    {
        draw_sprite(ventana2.buffer, ventana2.ok[1] ,60, 433);
        if (mouse_b&1)
        {
            draw_sprite(ventana2.buffer, ventana2.ok[2], 60 ,433);
            blit(ventana2.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest (250);
            ventana2.okClick = 1;
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 314 && mouse_x < 340 && mouse_y > 188 && mouse_y < 241 && ventana2.okClick == 0)           // Buttom - Numbers
    {
        if (mouse_x > 314 && mouse_x < 340 && mouse_y > 188 && mouse_y < 214)
        {
            if (mouse_b&1)
            {
                if (ventana2.playersCant<4)
                   ventana2.playersCant++;
                draw_sprite(ventana2.ground, ventana2.numbers[ventana2.playersCant], 365, 187);
                rest(100);
            }
        }
        if (mouse_x > 314 && mouse_x < 340 && mouse_y > 214 && mouse_y < 241)
        {
            if (mouse_b&1)
            {
                if (ventana2.playersCant>1)
                   ventana2.playersCant--;
                draw_sprite(ventana2.ground, ventana2.numbers[ventana2.playersCant], 365, 187);
                rest(100);
            }
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 169 && mouse_x < 191 && mouse_y > 311 && mouse_y < 364 && ventana2.okClick == 0)           // Buttom - Map
    {
        if (mouse_x > 169 && mouse_x < 191 && mouse_y > 311 && mouse_y < 337)
        {
            if (mouse_b&1)
            {
                if (mapSelect<1)
                   mapSelect++;
                draw_sprite(ventana2.ground, ventana2.map[mapSelect], 220, 320);
                rest(100);
            }
        }
        if (mouse_x > 169 && mouse_x < 191 && mouse_y > 337 && mouse_y < 364)
        {
            if (mouse_b&1)
            {
                if (mapSelect>0)
                   mapSelect--;
                draw_sprite(ventana2.ground, ventana2.map[mapSelect], 220, 320);
                rest(100);
            }
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 818 && mouse_x < 964 && mouse_y > 608 && mouse_y < 656 && ventana2.okClick==1)            // Buttom - Select
    {
        if (mouse_b&1 && ventana2.orderChamp[0]!=idChamp && ventana2.orderChamp[1]!=idChamp && ventana2.orderChamp[2]!=idChamp && ventana2.orderChamp[3]!=idChamp
                    && ventana2.orderChamp[4]!=idChamp)
        {
            draw_sprite(ventana2.buffer, ventana2.selector[1], 567 ,0);
            switch (idChamp)
            {
            case 0:
                draw_sprite(ventana2.buffer, hero[idChamp].frame[0], 710, 75);
                break;
            case 1:
                draw_sprite(ventana2.buffer, hero[idChamp].frame[0], 710, 75);
                break;
            case 2:
                draw_sprite(ventana2.buffer, hero[idChamp].frame[0], 760, 50);
                break;
            case 3:
                draw_sprite(ventana2.buffer, hero[idChamp].frame[0], 760, 50);
                break;
            case 4:
                draw_sprite(ventana2.buffer, hero[idChamp].frame[0],710, 95);
                break;
            }
            blit(ventana2.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest (750);
            ventana2.orderChamp[ventana2.Turno]=idChamp;
            ventana2.Turno++;
            caracter = 0;
            draw_sprite(ventana2.enterName, ventana2.letters[28], 142,373);
        }
        printf("\n//////////////////////////////////////////////");
        printf("\nThis is Turn: %i", ventana2.Turno);
        printf("\nThis is playersCant: %i", ventana2.playersCant);
        printf("\nThis is orderChamp. [0]: %i; [1]: %i; [2]: %i; [3]: %i; [4]: %i", ventana2.orderChamp[0], ventana2.orderChamp[1]
               , ventana2.orderChamp[2], ventana2.orderChamp[3], ventana2.orderChamp[4]);
        printf("\nThis is playerName: [0]: %s; [1]: %s; [2]: %s; [3]: %s; [4]: %s", ventana2.playerName[0], ventana2.playerName[1]
              , ventana2.playerName[2], ventana2.playerName[3], ventana2.playerName[4]);
        printf("\nThis is caracter: %i", caracter);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 1201 && mouse_x < 1282 && mouse_y > 239 && mouse_y < 421 && ventana2.okClick==1)            // Buttom - Right
    {
        if (mouse_b&1)
        {
            draw_sprite(ventana2.buffer, ventana2.arrow[1], 1197 ,235);
            blit(ventana2.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest (250);
            if (idChamp<4)
                idChamp ++;
            else
                idChamp=0;
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mouse_x > 469 && mouse_x < 560 && mouse_y > 242 && mouse_y < 430 && ventana2.okClick==1)            // Buttom - Left
    {
        if (mouse_b&1)
        {
            draw_sprite(ventana2.buffer, ventana2.arrow[3], 464 ,237);
            blit(ventana2.buffer, screen, 0, 0, 0, 0, 1300, 700);
            rest (250);
            if(idChamp>0)
                idChamp --;
            else
                idChamp=4;
        }
    }


}

void exitMe()
{
    if (mouse_x > 0 && mouse_x < 59 && mouse_y > 0 && mouse_y < 37)
    {
        if (mouse_b&1)
        {
            exitGame = 1;
        }
    }
}

void selectChamp ()
{
    if (ventana2.okClick==1)
    {
        switch(idChamp)
        {
            case 0:
                if (ventana2.orderChamp[0]!=0 && ventana2.orderChamp[1]!=0 && ventana2.orderChamp[2]!=0 && ventana2.orderChamp[3]!=0
                    && ventana2.orderChamp[4]!=0)
                    motionAlbert();
                else
                    draw_sprite(ventana2.buffer, ventana2.message[1], 695, 230);
                break;
            case 1:
                if (ventana2.orderChamp[0]!=1 && ventana2.orderChamp[1]!=1 && ventana2.orderChamp[2]!=1 && ventana2.orderChamp[3]!=1
                    && ventana2.orderChamp[4]!=1)
                motionMarrie();
                else
                    draw_sprite(ventana2.buffer, ventana2.message[1], 695, 230);

                break;
            case 2:
                if (ventana2.orderChamp[0]!=2 && ventana2.orderChamp[1]!=2 && ventana2.orderChamp[2]!=2 && ventana2.orderChamp[3]!=2
                    && ventana2.orderChamp[4]!=2)
                motionDarwin();
                else
                    draw_sprite(ventana2.buffer, ventana2.message[1], 695, 230);
                break;
            case 3:
                if (ventana2.orderChamp[0]!=3 && ventana2.orderChamp[1]!=3 && ventana2.orderChamp[2]!=3 && ventana2.orderChamp[3]!=3
                    && ventana2.orderChamp[4]!=3)
                motionTesla();
                else
                    draw_sprite(ventana2.buffer, ventana2.message[1], 695, 230);
                break;
            case 4:
                if (ventana2.orderChamp[0]!=4 && ventana2.orderChamp[1]!=4 && ventana2.orderChamp[2]!=4 && ventana2.orderChamp[3]!=4
                    && ventana2.orderChamp[4]!=4)
                motionNewton();
                else
                    draw_sprite(ventana2.buffer, ventana2.message[1], 695, 230);
                break;
        }
    }
}

void enterName ()                           // Este metodo permite imprimir en pantalla letras - y las guarda en cadenas dinamicas
{

    if (ventana2.okClick==1)
    {
            draw_sprite(ventana2.buffer, ventana2.letters[26], 143 + caracter*40, 430);
        if (key[KEY_A])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "A");
                draw_sprite(ventana2.enterName, ventana2.letters[0], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_B])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "B");
                draw_sprite(ventana2.enterName, ventana2.letters[1], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_C])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "C");
                draw_sprite(ventana2.enterName, ventana2.letters[2], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_D])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "D");
                draw_sprite(ventana2.enterName, ventana2.letters[3], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_E])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "E");
                draw_sprite(ventana2.enterName, ventana2.letters[4], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_F])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "F");
                draw_sprite(ventana2.enterName, ventana2.letters[5], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_G])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "G");
                draw_sprite(ventana2.enterName, ventana2.letters[6], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_H])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "H");
                draw_sprite(ventana2.enterName, ventana2.letters[7], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_I])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "I");
                draw_sprite(ventana2.enterName, ventana2.letters[8], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_J])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "J");
                draw_sprite(ventana2.enterName, ventana2.letters[9], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_K])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "K");
                draw_sprite(ventana2.enterName, ventana2.letters[10], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_L])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "L");
                draw_sprite(ventana2.enterName, ventana2.letters[11], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_M])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "M");
                draw_sprite(ventana2.enterName, ventana2.letters[12], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_N])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "N");
                draw_sprite(ventana2.enterName, ventana2.letters[13], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_O])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "O");
                draw_sprite(ventana2.enterName, ventana2.letters[14], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_P])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "P");
                draw_sprite(ventana2.enterName, ventana2.letters[15], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_Q])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "Q");
                draw_sprite(ventana2.enterName, ventana2.letters[16], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_R])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "R");
                draw_sprite(ventana2.enterName, ventana2.letters[17], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_S])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "S");
                draw_sprite(ventana2.enterName, ventana2.letters[18], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_T])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "T");
                draw_sprite(ventana2.enterName, ventana2.letters[19], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_U])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "U");
                draw_sprite(ventana2.enterName, ventana2.letters[20], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_V])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "V");
                draw_sprite(ventana2.enterName, ventana2.letters[21], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_W])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "W");
                draw_sprite(ventana2.enterName, ventana2.letters[22], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_X])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "X");
                draw_sprite(ventana2.enterName, ventana2.letters[23], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_Y])
        {
            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "Y");
                draw_sprite(ventana2.enterName, ventana2.letters[24], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }
        if (key[KEY_Z])
        {

            rest(250);
            if (caracter<5)
            {
                strcat(ventana2.playerName[ventana2.Turno], "Z");
                draw_sprite(ventana2.enterName, ventana2.letters[25], 143 + caracter*40, 382);
                caracter++;
            }
            else
                draw_sprite(ventana2.buffer, ventana2.message[2], 68, 521);
        }

        if (key[KEY_BACKSPACE])
        {
            ventana2.playerName[ventana2.Turno][strlen(ventana2.playerName[ventana2.Turno])-1]='\0';
            if (caracter>5)
            {
                draw_sprite(ventana2.enterName, ventana2.letters[27], 143 + caracter*40, 382);
                caracter--;
            }
            else
            {
                if (caracter>0)
                    caracter--;
                draw_sprite(ventana2.enterName, ventana2.letters[27], 143 + caracter*40, 382);
            }
            rest(250);
        }
    }
}
