

typedef struct
{
    BITMAP *buffer;
    BITMAP *ground;
    BITMAP *background[60];
    BITMAP *howToPlay[4];
    BITMAP *credits;
    int moveGround;
    BITMAP *cursor;
    BITMAP *banner[3];
    BITMAP *buttom[9];
    BITMAP *albert[49];
    int moveAlbert;
    int cnstAlbert;
    MIDI *soundtrack;
    SAMPLE *click;
    SAMPLE *select;
} Lobby;

Lobby ventana1;                             // Estructura para la ventana de Lobby, contiene el fondo, los botones y efectos
                              // Variable que permite simiular el movimiento de los personajes u objetos
int select=0;                               // Variable auxiliar que permite controlar el sonido
int salir=0;
int creditos = 0;
int comoJugar = 0;
//int finish = 0;                                // Variable que define la salida de la ventana

int window1(int finish);
void setUp1();
void clickMe1();
int finishMe(int finish);
void motionMaster();
void motionAlbert1();
void motionBanner();
void motionGround();
void extraButtom();


int window1 (int finish)
{
    if (finish==0)
    {
        setUp1();
        play_midi(ventana1.soundtrack, 1);
    }


   // BITMAP *aux = ventana1.ground;
    while (finish == 0 && salir == 0)
    {
        if (creditos==0 && comoJugar == 0)
        {
            motionMaster();
            motionGround();
            draw_sprite(ventana1.buffer, ventana1.ground, 0, 0);
            clickMe1();
            motionAlbert1();
            motionBanner();
            finish = finishMe(finish);
        }
        else
            extraButtom();
        draw_sprite(ventana1.buffer, ventana1.cursor, mouse_x, mouse_y);
        blit(ventana1.buffer, screen, 0, 0, 0, 0, 1300, 700);
    }
    salir = 0;
    return finish;
}

void setUp1 ()                                                  // Inicializa las estructuras y demas recursos que se vayan a utilizar
{

    ventana1.buffer = create_bitmap(1300,700);
    ventana1.cursor = load_bitmap("Acces/mouse.bmp", NULL);
    ventana1.ground = load_bitmap("Lobby/Lobby6.bmp", NULL);
    ventana1.banner[0] = load_bitmap("Lobby/Wasteland1.bmp", NULL);
    ventana1.banner[1] = load_bitmap("Lobby/Wasteland2.bmp", NULL);
    ventana1.banner[2] = load_bitmap("Lobby/Wasteland3.bmp", NULL);
    ventana1.buttom[0] = load_bitmap("Lobby/Play1.bmp", NULL);
    ventana1.buttom[1] = load_bitmap("Lobby/Play2.bmp", NULL);
    ventana1.buttom[2] = load_bitmap("Lobby/Play3.bmp", NULL);
    ventana1.buttom[3] = load_bitmap("Lobby/Credits1.bmp", NULL);
    ventana1.buttom[4] = load_bitmap("Lobby/Credits2.bmp", NULL);
    ventana1.buttom[5] = load_bitmap("Lobby/Credits3.bmp", NULL);
    ventana1.buttom[6] = load_bitmap("Lobby/HowToPlay1.bmp", NULL);
    ventana1.buttom[7] = load_bitmap("Lobby/HowToPlay2.bmp", NULL);
    ventana1.buttom[8] = load_bitmap("Lobby/HowToPlay3.bmp", NULL);
    ventana1.soundtrack = load_midi ("Soundtrack/CalvinHarris_OutSide.mid");
    ventana1.click = load_wav("Effect/BeepPing.wav");
    ventana1.select = load_wav("Effect/Toggle.wav");

    ventana1.howToPlay[0] = load_bitmap("Lobby/Instructions1.bmp", NULL);
    ventana1.howToPlay[1] = load_bitmap("Lobby/Instructions2.bmp", NULL);
    ventana1.howToPlay[2] = load_bitmap("Lobby/Instructions3.bmp", NULL);
    ventana1.howToPlay[3] = load_bitmap("Lobby/Instructions4.bmp", NULL);

    ventana1.credits = load_bitmap("Lobby/Creditos.bmp", NULL);


    char* word = (char *)malloc(10240 * sizeof(char));
    char* aux = (char *)malloc(10240 * sizeof(char));
    strcpy(word, "Character/Albert/");

    int i;

        ventana1.moveAlbert=0;
        ventana1.cnstAlbert=0;

    int j=1;

      for (i=0; i < 49; i++)
      {
            sprintf(aux, "%d", j);
            strcat(word, aux);
            strcat(word, ".bmp");
            ventana1.albert[i] = load_bitmap(word,NULL);
            strcpy(word, "Character/Albert/");
            j++;
       }

       ventana1.moveGround=0;

       for (i=0; i < 60; i++)
      {
            strcpy(word, "Lobby/Space/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            ventana1.background[i] = load_bitmap(word,NULL);
       }

}

void clickMe1()                                                        // Maneja la interaccion del usuario con cada uno de los botones
{
        if (mouse_x > 117 && mouse_x < 402 && mouse_y > 301 && mouse_y < 355)       // Buttom-Play
        {
            draw_sprite(ventana1.buffer, ventana1.buttom[1],108, 272);
            if (select==0)
                play_sample(ventana1.select, 200, 0, 1000, 0);

            if (mouse_b&1)
            {
                play_sample(ventana1.click, 200, 0, 1000, 0);
                draw_sprite(ventana1.buffer, ventana1.buttom[2],108 ,272);
                blit(ventana1.buffer, screen, 0, 0, 0, 0, 1300, 700);
                rest (1000);
                salir=1;
            }
            select = 1;
        }
        else
        {
           // draw_sprite(ventana1.buffer, ventana1.buttom[0],108, 272);
            if (mouse_x > 117 && mouse_x < 402 && mouse_y > 410 && mouse_y < 470)     // Buttom - Credits
            {
                    draw_sprite(ventana1.buffer, ventana1.buttom[4],108, 387);
                if (select==0)
                    play_sample(ventana1.select, 200, 0, 1000, 0);
                if (mouse_b&1)
                {
                    play_sample(ventana1.click, 200, 0, 1000, 0);
                    draw_sprite(ventana1.buffer, ventana1.buttom[5],108, 387);
                    blit(ventana1.buffer, screen, 0, 0, 0, 0, 1300, 700);
                    rest(1000);
                    creditos=1;
                }
                select = 1;
            }
            else
            {
                //draw_sprite(ventana1.buffer, ventana1.buttom[3],365, 387);
                if (mouse_x > 117 && mouse_x < 402 && mouse_y > 545 && mouse_y < 6000)     // Buttom - HowToPlay
                {
                        draw_sprite(ventana1.buffer, ventana1.buttom[7],108, 514);
                    if (select==0)
                        play_sample(ventana1.select, 200, 0, 1000, 0);
                    if (mouse_b&1)
                    {
                        play_sample(ventana1.click, 200, 0, 1000, 0);
                        draw_sprite(ventana1.buffer, ventana1.buttom[8],108, 514);
                        blit(ventana1.buffer, screen, 0, 0, 0, 0, 1300, 700);
                        rest(1000);
                        comoJugar=1;
                    }
                    select = 1;
                }
                else
                {
                    select = 0;
                }
            }
        }
}

int finishMe(int finish)
{
    if (mouse_x > 1249 && mouse_x < 1300 && mouse_y > 667 && mouse_y < 700)
    {
        if (mouse_b&1)
        {
            finish = 1;
        }
    }
    return finish;
}

void motionMaster()
{
    if (ventana1.moveGround>590)
        ventana1.moveGround=0;
    else
        ventana1.moveGround++;

    if (ventana1.moveAlbert>480)
    {
        ventana1.moveAlbert=0;
        ventana1.cnstAlbert=0;
    }
    else
        ventana1.moveAlbert++;
}

void motionAlbert1 ()                                        // Genera el movimiento para Albert
{
    if (ventana1.moveAlbert%10)
        ventana1.cnstAlbert = ventana1.moveAlbert/10;

    draw_sprite(ventana1.buffer, ventana1.albert[ventana1.cnstAlbert], 900, 250);
}

void motionGround()
{
    if (ventana1.moveGround%10)
        draw_sprite(ventana1.buffer, ventana1.background[ventana1.moveGround/10], 0, 0);
}

void motionBanner ()                                        // Cambia el color del banner
{
    if (ventana1.moveAlbert==0)
        draw_sprite(ventana1.ground, ventana1.banner[0], 141, 0);
    if (ventana1.moveAlbert==180)
        draw_sprite(ventana1.ground, ventana1.banner[1], 141, 0);
    if (ventana1.moveAlbert==380)
        draw_sprite(ventana1.ground, ventana1.banner[2], 141, 0);
}

void extraButtom()
{
    if (comoJugar>0)
    {
        draw_sprite(ventana1.buffer, ventana1.howToPlay[comoJugar-1], 0, 0);
        if (mouse_x > 0 && mouse_x < 1300 && mouse_y > 0 && mouse_y < 700)
        {
            if (mouse_b&1)
            {
                rest(200);
                if (comoJugar<5)
                    comoJugar++;
                else
                    comoJugar=0;
            }
        }
    }
    if (creditos==1)
    {
        draw_sprite(ventana1.buffer, ventana1.credits, 0, 0);
        if (mouse_x > 0 && mouse_x < 1300 && mouse_y > 0 && mouse_y < 700)
        {
            if (mouse_b&1)
            {
                rest(200);
                creditos=0;
            }
        }
    }

}


