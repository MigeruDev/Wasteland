
typedef struct
{
    BITMAP *frame[100];
    int moveFrame;
    int cnstFrame;
}Hero;

Hero hero[6];

void setUpHero();

void setUpHero()
{
    char* word = (char *)malloc(10240 * sizeof(char));
    char* aux = (char *)malloc(10240 * sizeof(char));
    strcpy(word, "Character/Albert/");
    int i;
    for (i=0; i < 6; i++)
    {
        hero[i].cnstFrame=0;
        hero[i].moveFrame=0;
    }

    int j=1;

      for (i=0; i < 95; i++)
      {
          if (i<49)
          {
            strcpy(word, "Character/Albert/");
            sprintf(aux, "%d", j);
            strcat(word, aux);
            strcat(word, ".bmp");
            hero[0].frame[i] = load_bitmap(word,NULL);
            j++;
          }
         if (i<80)
         {
            strcpy(word, "Character/Marrie/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            hero[1].frame[i] = load_bitmap(word,NULL);
         }
         if (i<54)
         {
             strcpy(word, "Character/Darwin/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            hero[2].frame[i] = load_bitmap(word,NULL);
         }
        if (i<95)
        {
            strcpy(word, "Character/Tesla/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            hero[3].frame[i] = load_bitmap(word,NULL);
        }
        if (i<63)
        {
            strcpy(word, "Character/Newton/");
            sprintf(aux, "%d", i);
            strcat(word, aux);
            strcat(word, ".bmp");
            hero[4].frame[i] = load_bitmap(word,NULL);
        }
      }

}
