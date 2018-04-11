#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "Lobby.h"
#include "Board.h"

int finish=0;

int main ()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_volume(230, 200);
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1300, 700, 0, 0);

    while (!key[KEY_ESC] && finish==0)
    {
        finish = window1(finish);
        finish = window3(finish);
    }



    return 0;
}
END_OF_MAIN ();
