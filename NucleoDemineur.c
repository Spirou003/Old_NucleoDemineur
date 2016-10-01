#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/**///tricherie désactivée
#define _TRICHE 1/**/
/*///tricherie activée
#define _TRICHE 0/**/
#define _LVL 0
/*/
#define _R 255//*65536
#define _G 0//*256
#define _B 0//*1
/**/
/*

Facultatif: curseur perso
            Anim' en cours de jeu (un peu trop plat) (boost score rapide, carte retournée, coeur disparait progressivement,...)
*/



void genereniveau (char pions[], char newp[], char colonnes[], char lignes[], int niveau);       //OK!
int trouvei (int positionx, int positiony);                                                      //OK!
void montrerinstructions (int expliqueintro, char *continuer);                                   //OK!
void menusdescores (int scores[], char *continuer, int rescore);                                 //OK!
void blitteuse (char pions[], char newp[]);                                                      //OK!
void blitbord (char colonnes[], char lignes[], char niveau);                                     //OK!
void blitscore (int scoreactuel);                                                                //OK!
void decoupescore (int score, int chiffres[]);                                                   //OK!
int calculescore (char pions[], char newp[], char final);                                        //OK!
char jeu (char niveau, int *score, int *nombrevie);                                              //OK!
void blitscoreactuel (int scoreactuel);                                                          //OK!
int puis10 (char nombre);                                                                        //OK!
int selectionnecase (int positionx, int positiony);                                              //OK!
void tableorder (int scores[]);                                                                  //OK!
SDL_Surface* creerscore (int meilleurscore);                                                     //OK! à améliorer
void vieperdu (void);                                                                            //OK!
int loadimages(int meilleurscore);                                                               //OK!
int freeimages(void);                                                                            //OK!
void blitvies (int vies);                                                                        //OK!
void loadpseudo (void);                                                                          //OK!
void blittebleu (int score, int x, int y, SDL_Surface* surface);                                 //OK!
void blittenom (char pseudo[], int x, int y, SDL_Surface* surface, int i, int unelettre);        //OK!
int selectioncase (int x, int y);                                                                //OK!
int confirmefface (char* continuer);                                                             //OK!
int trouveconf (int x, int y);                                                                   //OK!
SDL_Surface* PJ_SDL_Load(char nomfichier[]);                                                     //OK!
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);                                 //OK!
void Infovers(char* continuer);                                                                  //OK!
int trouveinf(int x, int y);                                                                     //OK!

             
SDL_Surface *s_ecran = NULL;//                                  chargé+free
SDL_Surface *s_infovers = NULL;//                               
SDL_Surface *s_fond = NULL;//intro                              chargé+free
SDL_Surface *s_fond2 = NULL;//instructions1                     chargé+free
SDL_Surface *s_fond3 = NULL;//instructions2                     chargé+free
SDL_Surface *s_boutton = NULL;//bouton                          chargé+free
SDL_Surface *s_boutton2 = NULL;//bouton                         
SDL_Surface *s_bouttondown = NULL;//bouton enfoncé              chargé+free
SDL_Surface *s_boutdownsurv = NULL;//bouton enfoncé survolé     chargé+free
SDL_Surface *s_boutsurv = NULL;//bouton survolé                 chargé+free
//---------------------------------------
SDL_Surface *s_mbout = NULL;//                                  
SDL_Surface *s_mboutenf = NULL;//                               
SDL_Surface *s_mboutsurv = NULL;//                              
SDL_Surface *s_mboutsurvenf = NULL;//                           
SDL_Surface *s_cadreconf = NULL;//                              
SDL_Surface *s_infbout = NULL;//                                  
SDL_Surface *s_infboutenf = NULL;//                               
SDL_Surface *s_infboutsurv = NULL;//                              
SDL_Surface *s_infboutsurvenf = NULL;//                           
SDL_Surface *s_cadrinf = NULL;//                              
SDL_Surface *s_fondconf = NULL;//                               
SDL_Surface *s_textea = NULL;//texte d'intro                    chargé+free
SDL_Surface *s_texteb = NULL;//texte de bestscore new           chargé+free
SDL_Surface *s_textec = NULL;//texte de bestscore non           chargé+free
SDL_Surface *s_texted = NULL;//texte confirm. effac.            
SDL_Surface *s_cadre = NULL;//cadre d'intro                     chargé+free
SDL_Surface *s_icone = NULL;//                                  chargé+free
SDL_Surface *s_meilleurscore = NULL;//                          chargé+free
SDL_Surface *s_fondmeilleurscore = NULL;//                      chargé+free
//---------------------------------------              
SDL_Surface *s_bleu0 = NULL;//                                  chargé+free
SDL_Surface *s_bleu1 = NULL;//                                  chargé+free
SDL_Surface *s_bleu2 = NULL;//                                  chargé+free
SDL_Surface *s_bleu3 = NULL;//                                  chargé+free
SDL_Surface *s_bleu4 = NULL;//                                  chargé+free
SDL_Surface *s_bleu5 = NULL;//                                  chargé+free
SDL_Surface *s_bleu6 = NULL;//                                  chargé+free
SDL_Surface *s_bleu7 = NULL;//                                  chargé+free
SDL_Surface *s_bleu8 = NULL;//                                  chargé+free
SDL_Surface *s_bleu9 = NULL;//                                  chargé+free
SDL_Surface *s_bleuno = NULL;//                                 créé+free
//----------------------------------------
SDL_Surface *s_petit0 = NULL;//                                 chargé+free
SDL_Surface *s_petit1 = NULL;//                                 chargé+free
SDL_Surface *s_petit2 = NULL;//                                 chargé+free
SDL_Surface *s_petit3 = NULL;//                                 chargé+free
SDL_Surface *s_petit4 = NULL;//                                 chargé+free
SDL_Surface *s_petit5 = NULL;//                                 chargé+free
//----------------------------------------             
SDL_Surface *s_petit0n = NULL;//                                chargé+free
SDL_Surface *s_petit1n = NULL;//                                chargé+free
SDL_Surface *s_petit2n = NULL;//                                chargé+free
SDL_Surface *s_petit3n = NULL;//                                chargé+free
SDL_Surface *s_petit4n = NULL;//                                chargé+free
SDL_Surface *s_petit5n = NULL;//                                chargé+free
SDL_Surface *s_petit6n = NULL;//                                chargé+free
SDL_Surface *s_petit7n = NULL;//                                chargé+free
SDL_Surface *s_petit8n = NULL;//                                chargé+free
SDL_Surface *s_petit9n = NULL;//                                chargé+free
//----------------------------------------             
SDL_Surface *s_casejeu = NULL;//carte non cliquée               chargé+free
SDL_Surface *s_casejeudown = NULL;//carte enfoncée              chargé+free
SDL_Surface *s_carte1 = NULL;//carte 1                          chargé+free
SDL_Surface *s_carte2 = NULL;//carte 2                          chargé+free
SDL_Surface *s_carte3 = NULL;//carte 3                          chargé+free
SDL_Surface *s_carte4 = NULL;//carte 4                          chargé+free
SDL_Surface *s_carte5 = NULL;//carte 5                          chargé+free
SDL_Surface *s_bombe = NULL;//carte bombe                       chargé+free
SDL_Surface *s_casejeuno = NULL;//carte ?                       chargé+free
SDL_Surface *s_cadrejeu = NULL;//cadre carte                    chargé+free
SDL_Surface *s_ecranjeu = NULL;//utile                          créé+free
SDL_Surface *s_fondjeu = NULL;//fond du jeu                     chargé+free
//----------------------------------------             
SDL_Surface *s_fondniveau = NULL;//                             chargé+free
SDL_Surface *s_fondnoir = NULL;//                               créé+free
SDL_Surface *s_vrainiveau = NULL;//                             créé+free
SDL_Surface *s_lvl0 = NULL;//                                   chargé+free
SDL_Surface *s_lvl1 = NULL;//                                   chargé+free
SDL_Surface *s_lvl2 = NULL;//                                   chargé+free
SDL_Surface *s_lvl3 = NULL;//                                   chargé+free
SDL_Surface *s_lvl4 = NULL;//chiffres niveau                    chargé+free
SDL_Surface *s_lvl5 = NULL;//                                   chargé+free
SDL_Surface *s_lvl6 = NULL;//                                   chargé+free
SDL_Surface *s_lvl7 = NULL;//                                   chargé+free
SDL_Surface *s_lvl8 = NULL;//                                   chargé+free
SDL_Surface *s_lvl9 = NULL;//                                   chargé+free
//----------------------------------------           
SDL_Surface *s_best0 = NULL;//                                  chargé+free
SDL_Surface *s_best1 = NULL;//                                  chargé+free
SDL_Surface *s_best2 = NULL;//                                  chargé+free
SDL_Surface *s_best3 = NULL;//                                  chargé+free
SDL_Surface *s_best4 = NULL;//                                  chargé+free
SDL_Surface *s_best5 = NULL;//chiffres meilleurscore            chargé+free
SDL_Surface *s_best6 = NULL;//                                  chargé+free
SDL_Surface *s_best7 = NULL;//                                  chargé+free
SDL_Surface *s_best8 = NULL;//                                  chargé+free
SDL_Surface *s_best9 = NULL;//                                  chargé+free
//----------------------------------------
SDL_Surface *s_coeur = NULL;//                                  chargé+free
SDL_Surface *s_nocoeur = NULL;//                                créé+free
//----------------------------------------
SDL_Surface *s_pseudo[66] = {NULL};//                             chargés+frees
SDL_Surface *s_cpseudo = NULL;//cadre lettre                    chargé+free
//----------------------------------------             
SDL_Surface *s_confmeilfond = NULL;
SDL_Surface *s_confmeiltexte = NULL;
SDL_Surface *s_confmeilbouton = NULL;
SDL_Surface *s_confmeilboutonsurv = NULL;
SDL_Surface *s_confmeilboutondown = NULL;
SDL_Surface *s_confmeilboutondownsurv = NULL;
SDL_Surface *s_confmeilcadre = NULL;
SDL_Surface *s_qwerty = NULL;
SDL_Surface *s_azerty = NULL;
SDL_Surface *s_menuprinc = NULL;
//----------------------------------------             
SDL_Rect posin;//position des cartes jeu               
SDL_Rect poschiffr;//spécial chiffre, pas touche       
SDL_Rect posfond;//                                    
SDL_Rect postexte;//                                   
SDL_Rect posbutton;//                                  
SDL_Rect poscadre;//         
SDL_Rect posnew;
char c_pseudo[21] = "images/pseudos/aa.png";
char c_scores[77] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
char interpseudo[7] = "";
int nouveauscore = 0;
FILE* f_scores = NULL;
char clavier = 0, azerty = 0;

int main(int argc, char *argv[])
{
    SDL_Event event;
    char pions[25] = {0};
    char colonnes[10] = {0};
    char lignes[10] = {0};
    char newp[25] = {0};
    int meilleurscores[11] = {0};
    int points = 0, niveau = 0, nbvies = 3;
    char continuer = 1, clic = 0, ouiclic = 0, premierclic = 0;
    int  lol = 0, expliqueintro = 0, menuscores = 0, demarrerjeu = 0, i = 0, okclic = 0, infovers = 0;
    char cadrechoix = 1, cadrechois = 1, mcadre = 1, ccadre = 1;
    
    i = 0;
    posfond.x = 0;
    posfond.y = 0;
    postexte.x = 59;
    postexte.y = 129;
    posbutton.x = 61;
    poscadre.x = 59;
    srand(time(NULL));
    while (i < 71)
    {
       c_scores[i] = 0;
       i++;
    }
    i = 0;
    f_scores = fopen("Application.exe", "r");
    while (i < 10)
    {
       fscanf(f_scores, "%d\t%c%c%c%c%c%c%c\n", &meilleurscores[i], &c_scores[i*7], &c_scores[(i*7)+1], &c_scores[(i*7)+2], &c_scores[(i*7)+3], &c_scores[(i*7)+4], &c_scores[(i*7)+5], &c_scores[(i*7)+6]);
       i++;
    }
    fscanf(f_scores, "\n%d", &azerty);
    fclose(f_scores);
    if(!(SDL_Init(SDL_INIT_VIDEO) < 0))
    {
        SDL_WM_SetCaption("NucleoDemineur", NULL);
        if (loadimages(meilleurscores[0]) != 162)
        {
           freeimages();
           system("error.txt");
           return 0;
        }
        SDL_WM_SetIcon(s_icone, 0);
        s_ecran = SDL_SetVideoMode(220, 250, 32, SDL_HWSURFACE | SDL_DOUBLEBUF/*/ | SDL_NOFRAME/**/);
        SDL_FillRect(s_bleuno, NULL, SDL_MapRGB(s_ecran->format, 0, 0, 0));
        SDL_FillRect(s_pseudo[0], NULL, SDL_MapRGB(s_ecran->format, 255, 153, 0));
        poscadre.x = 59;
        poscadre.y = 129;
        posnew.x = 59;
        posnew.y = 129;
        if(s_ecran != NULL)
        {
           SDL_SetColorKey(s_cpseudo, SDL_SRCCOLORKEY, SDL_MapRGB(s_ecran->format, 255, 153, 0));
           SDL_BlitSurface(s_fond, NULL, s_ecran, &posfond);
           SDL_BlitSurface(s_textea, NULL, s_ecran, &postexte);
           SDL_BlitSurface(s_cadre, NULL, s_ecran, &postexte);
           SDL_Flip(s_ecran);
           premierclic = 1;
           mcadre = 50;
           ccadre = 50;
           while (continuer == 1)
           {
              event.type = SDL_KEYUP;
              SDL_PollEvent(&event);
              okclic = 1;
              niveau = _LVL;
              if (cadrechoix != 50)
              {
                 cadrechois = cadrechoix;
              }
              else
              {
                  cadrechoix = cadrechois;
              }
              SDL_BlitSurface(s_boutton, NULL, s_ecran, &posnew);
              if (mcadre != 50)
              {
                 poscadre.y = 114+ 15*mcadre;
                 SDL_BlitSurface(s_boutsurv, NULL, s_ecran, &poscadre);
              }
              if (ccadre != 50 && premierclic == 2)
              {
                 poscadre.y = 114+ 15*ccadre;
                 SDL_BlitSurface(s_bouttondown, NULL, s_ecran, &poscadre);
              }
              if (mcadre == ccadre && mcadre != 50 && premierclic == 2)
              {
                 poscadre.y = 114+ 15*mcadre;
                 SDL_BlitSurface(s_boutdownsurv, NULL, s_ecran, &poscadre);
              }
              poscadre.y = 114 + 15*cadrechois;
              if (clavier == 1)
              {
                 SDL_BlitSurface(s_cadre, NULL, s_ecran, &poscadre);
              }
              SDL_BlitSurface(s_textea, NULL, s_ecran, &postexte);
              SDL_Flip(s_ecran);
              if (event.type == SDL_QUIT)
              {
                 continuer++;
              }
              else if (event.type == SDL_KEYDOWN && premierclic == 1)
              {
                 clavier = 1;
                 if (event.key.keysym.sym == SDLK_ESCAPE)
                 {
                    continuer++;
                 }
                 else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_KP8)
                 {
                    cadrechoix--;
                    if (cadrechoix < 1)
                    {
                       cadrechoix = 5;
                    }
                 }
                 else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_KP2)
                 {
                    cadrechoix++;
                    if (cadrechoix > 5)
                    {
                       cadrechoix = 1;
                    }
                 }
                 else if(event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP5)
                 {
                    if (cadrechoix == 1)
                    {
                       demarrerjeu = 1;
                    }
                    else if (cadrechoix == 2)
                    {
                       expliqueintro = 1;
                    }
                    else if (cadrechoix == 3)
                    {
                       menuscores = 1;
                    }
                    else if (cadrechoix == 4)
                    {
                       continuer++;
                    }
                    else if (cadrechoix == 5)
                    {
                       infovers = 1;
                    }
                 }
              }
              else if (event.type == SDL_KEYUP)
              {
                 lol++;
              }
              else if (event.type == SDL_MOUSEBUTTONDOWN && premierclic == 1 && event.button.button == SDL_BUTTON_LEFT)
              {
                 premierclic++;
                 ccadre = selectionnecase(event.button.x, event.button.y);
                 clavier = 0;
              }
              else if (event.type == SDL_MOUSEBUTTONUP && premierclic != 1 && event.button.button == SDL_BUTTON_LEFT)
              {
                 premierclic = 1;
                 if (mcadre == ccadre)
                 {
                    switch(ccadre)
                    {
                       case 1:
                            demarrerjeu = 1;
                            break;
                       case 2:
                            expliqueintro = 1;
                            break;
                       case 3:
                            menuscores = 1;
                            break;
                       case 4:
                            continuer++;
                            break;
                       case 5:
                            infovers = 1;
                            break;
                    }
                 }
              }
              else
              {
                  lol++;
              }
              mcadre = selectionnecase(event.button.x, event.button.y);
              SDL_Delay(10);
              if (infovers == 1)
              {
                 Infovers(&continuer);
                 infovers = 0;
                 SDL_SetAlpha(s_fond, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
                 SDL_BlitSurface(s_fond, NULL, s_ecranjeu, &posfond);
                 SDL_BlitSurface(s_textea, NULL, s_ecranjeu, &postexte);
                 if (clavier == 1)
                 {
                    SDL_BlitSurface(s_cadre, NULL, s_ecranjeu, &postexte);
                 }
                 SDL_BlitSurface(s_ecran, NULL, s_fondnoir, &posfond);
                 i = 0;
                 while (i < 25 && continuer == 1)
                 {
                    SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, i*10);
                    SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
                    SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
                    SDL_Flip(s_ecran);
                    i++;
                    SDL_Delay(10);
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                    {
                       i = 1300;
                       continuer++;
                    }
                 }
                 SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
                 SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
                 SDL_Flip(s_ecran);
              }
              if (menuscores == 1)
              {
                 menusdescores(meilleurscores, &continuer, -1);
                 postexte.x = 59;
                 postexte.y = 129;
                 posbutton.x = 59;
                 poscadre.x = 59;
                 menuscores = 0;
                 mcadre = 50;
                 event.motion.x = 0;
                 ccadre = 50;
                 okclic = 0;
              }
              if (expliqueintro == 1)
              {
                 montrerinstructions(expliqueintro, &continuer);
                 expliqueintro = 3;
                 mcadre = 50;
                 ccadre = 50;
                 okclic = 0;
                 event.motion.x = 0;
              }
              while (demarrerjeu == 1)
              {//boucle principale du jeu
                 niveau++;
                 SDL_BlitSurface(s_fondniveau, NULL, s_vrainiveau, &posfond);
                 SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
                 lol = 0;
                 poschiffr.x = 105;
                 poschiffr.y = 37;
                 if(niveau > 9)
                 {
                    i = niveau/10;
                    switch (i)
                    {
                       case 1:
                            SDL_BlitSurface(s_lvl1, NULL, s_vrainiveau, &poschiffr);
                            poschiffr.x = poschiffr.x + 10;
                            break;
                       case 2:
                            SDL_BlitSurface(s_lvl2, NULL, s_vrainiveau, &poschiffr);
                            poschiffr.x = poschiffr.x + 14;
                            break;
                       case 3:
                            poschiffr.y--;
                            SDL_BlitSurface(s_lvl3, NULL, s_vrainiveau, &poschiffr);
                            poschiffr.x = poschiffr.x + 11;
                            poschiffr.y++;
                            break;
                       case 4:
                            poschiffr.y--;
                            SDL_BlitSurface(s_lvl4, NULL, s_vrainiveau, &poschiffr);
                            poschiffr.x = poschiffr.x + 14;
                            poschiffr.y++;
                            break;
                    }
                 }
                 i = niveau%10;
                 if (niveau < 10)
                 {
                    poschiffr.x = poschiffr.x + 2;
                    poschiffr.y--;
                 }
                 switch (i)
                 {
                    case 0:
                         poschiffr.x--;
                         SDL_BlitSurface(s_lvl0, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 1:
                         poschiffr.x = poschiffr.x - 2;
                         SDL_BlitSurface(s_lvl1, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 2:
                         poschiffr.x = poschiffr.x - 4;
                         SDL_BlitSurface(s_lvl2, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 3:
                         poschiffr.y = poschiffr.y - 1;
                         poschiffr.x = poschiffr.x - 2;
                         SDL_BlitSurface(s_lvl3, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 4:
                         poschiffr.y--;
                         poschiffr.x = poschiffr.x - 4;
                         SDL_BlitSurface(s_lvl4, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 5:
                         poschiffr.x = poschiffr.x - 2;
                         SDL_BlitSurface(s_lvl5, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 6:
                         poschiffr.x--;
                         SDL_BlitSurface(s_lvl6, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 7:
                         poschiffr.x = poschiffr.x - 2;
                         SDL_BlitSurface(s_lvl7, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 8:
                         poschiffr.x--;
                         SDL_BlitSurface(s_lvl8, NULL, s_vrainiveau, &poschiffr);
                         break;
                    case 9:
                         poschiffr.x--;
                         SDL_BlitSurface(s_lvl9, NULL, s_vrainiveau, &poschiffr);
                         break;
                 }
                 i = 0;
                 lol = 0;
                 poschiffr.x = 70;
                 poschiffr.y = 83;
                 SDL_FillRect(s_fondnoir, NULL, SDL_MapRGB(s_ecran->format, 0, 0, 0));
                 while (i < 50 && lol == 0)
                 {
                    if ((i%2) == 0)
                    {
                       poschiffr.x--;
                       SDL_BlitSurface(s_vrainiveau, NULL, s_fondnoir, &poschiffr);
                    }
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                    {
                       lol = 1000;
                       demarrerjeu = 10;
                       i = 1000;
                    }
                    SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
                    SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, i*5);
                    SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
                    SDL_Flip(s_ecran);
                    SDL_Delay(20);
                    SDL_PollEvent(&event);
                    i++;
                 }
                 SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, 255);
                 SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
                 while (i < 60)
                 {
                    if ((i%2) == 0)
                    {
                       poschiffr.x--;
                       SDL_BlitSurface(s_vrainiveau, NULL, s_ecran, &poschiffr);
                    }
                    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                    {
                       lol = 1000;
                       demarrerjeu = 10;
                       i = 1000;
                    }
                    SDL_Flip(s_ecran);
                    SDL_Delay(20);
                    SDL_PollEvent(&event);
                    i++;
                 }
                 if (lol == 0 && niveau < 50)
                 {
                    demarrerjeu = jeu(niveau, &points, &nbvies);
                 }
                 if (niveau > 48)
                 {
                    demarrerjeu = 0;
                 }
                 if (demarrerjeu == 0)
                 {
                    nbvies = 3;
                    meilleurscores[10] = points;
                    if (points > meilleurscores[0])
                    {
                       SDL_FreeSurface(s_meilleurscore);
                       s_meilleurscore = creerscore(points);
                    }
                    tableorder(meilleurscores);
                    SDL_FillRect(s_fondnoir, NULL, SDL_MapRGB(s_ecran->format, 255, 153, 0));
                    SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
                    i = 0;
                    while (i < 50 && lol == 0)
                    {
                       if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                       {
                          lol = 1000;
                          continuer++;
                          i = 1000;
                       }
                       SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
                       SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, i*5);
                       SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
                       SDL_Flip(s_ecran);
                       SDL_Delay(20);
                       SDL_PollEvent(&event);
                       i++;
                    }
                    if (lol != 1000)
                    {
                       menusdescores(meilleurscores, &continuer, points);
                       event.motion.x = 0;
                       mcadre = 50;
                    }
                    points = 0;
                    SDL_BlitSurface(s_fond, NULL, s_ecran, &posfond);
                    SDL_Flip(s_ecran);
                 }
                 else if (demarrerjeu == 10)
                 {
                    continuer++;
                 }
                 posfond.x = 0;
                 posfond.y = 0;
                 postexte.x = 59;
                 postexte.y = 129;
                 posbutton.x = 61;
                 poscadre.x = 59;
              }//boucle principale du jeu
           }//boucle principale du programme
        }
        freeimages();
        SDL_Quit();
    }
    return 0;
}

void genereniveau (char pions[], char newp[], char colonnes[], char lignes[], int niveau)
{
   char nombrebombe = (niveau+4), nombrebonus = (niveau+4);
   int alea = 0, i = 0, j = 0;
   while (i < 25)
   {
      pions[i] = 1;
      newp[i] = 0;
      i++;
   }
   i = 0;
   while (i < 10)
   {
      lignes[i] = 0;
      colonnes[i] = 0;
      i++;
   }
   if (niveau > 8)
   {
      nombrebombe = 12;
      nombrebonus = 12;
   }
   while (nombrebombe > 0)
   {
      alea = rand()%25;
      if (pions[alea] != 10)
      {
         pions[alea] = 10;
         nombrebombe--;
      }
   }
   i = 0;
   while (i == 0)
   {
      alea = rand()%25;
      if (pions[alea] != 10)
      {
         i = alea;
      }
   }
   while (nombrebonus > 0)
   {
      alea = rand()%25;
      if (pions[alea] != 10 && pions[alea] != 5 && alea != i)
      {
         pions[alea]++;
         nombrebonus--;
      }
   }
   i = 0;
   while (j < 10)
   {
      if (pions[i] == 10)
      {
         colonnes[j+1]++;
      }
      else
      {
         colonnes[j] = colonnes[j] + pions[i];
      }
      if (i%5 == 4)
      {
         j = j + 2;
      }
      i++;
   }
   i = 0;
   j = 0;
   while (j < 5)
   {
      if (pions[i*5+j] == 10)
      {
         lignes[j+5]++;
      }
      else
      {
         lignes[j] = lignes[j] + pions[i*5+j];
      }
      if (i%5 == 4)
      {
         j++;
         i = -1;
      }
      i++;
   }
}

int trouvei (int positionx, int positiony)
{
    int newposx = 0, newposy = 0, i = 0, posdetx = 0, posdety = 0, sommedet = 0, sommedetinv = 0, nouveaux = 0;
    newposx = (positionx - 2)/36;
    newposy = (positiony - 2)/36;
    posdetx = (positionx - 2)%36;
    posdety = (positiony - 2)%36;
    sommedet = posdety + posdetx;
    nouveaux = 33-posdetx;
    if (nouveaux < 0)
    {
       nouveaux = 0;
    }
    sommedetinv = (posdety) + nouveaux;
    i = newposx + (5*newposy);
    if (positionx > 1 && positionx < 180 && positiony > 1 && positiony < 180 && posdety < 34 && posdetx < 34 && sommedet > 2 && sommedet < 64 && sommedetinv > 2 && sommedetinv < 64)
    {
       return (i); //réussi, on est sur une case
    }
    return 50;//raté, on est pas sur une case
}

void montrerinstructions (int expliqueintro, char *continuer)
{
     SDL_Event event;
     int i = 0;
     SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
     SDL_Flip(s_ecran);
     while (i < 17)
     {
        SDL_SetAlpha(s_fond2, SDL_SRCALPHA, i*15);
        SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
        SDL_BlitSurface(s_fond2, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
        SDL_Delay(26);
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           (*continuer)++;
           return;
        }
        i++;
     }
     i = 0;
     SDL_SetAlpha(s_fond2, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
     SDL_BlitSurface(s_fond2, NULL, s_ecran, &posfond);
     SDL_Flip(s_ecran);
     while (expliqueintro == 1)
     {
           SDL_Delay(5);
           SDL_WaitEvent(&event);
           if (event.type == SDL_MOUSEBUTTONUP)
           {
              expliqueintro++;
              clavier = 0;
           }
           else if (event.type == SDL_QUIT)
           {
                (*continuer)++;
                expliqueintro = 1000;
           }
           else if (event.type == SDL_KEYDOWN)
           {
                if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)
                {
                   expliqueintro++;
                   clavier = 1;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                   (*continuer)++;
                   expliqueintro++;
                }
           }
     }
     if (expliqueintro == 2)
     {
        while (i < 17)
        {
           SDL_SetAlpha(s_fond3, SDL_SRCALPHA, i*15);
           SDL_BlitSurface(s_fond2, NULL, s_ecran, &posfond);
           SDL_BlitSurface(s_fond3, NULL, s_ecran, &posfond);
           SDL_Flip(s_ecran);
           SDL_Delay(26);
           SDL_PollEvent(&event);
           if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
           {
              (*continuer)++;
              return;
           }
           i++;
        }
        i = 0;
        SDL_SetAlpha(s_fond3, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
        SDL_BlitSurface(s_fond3, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
     }
     while (expliqueintro == 2)
     {
           SDL_Delay(5);
           SDL_WaitEvent(&event);
           if (event.type == SDL_MOUSEBUTTONUP)
           {
               expliqueintro++;
               clavier = 0;
           }
           else if (event.type == SDL_QUIT)
           {
                (*continuer)++;
                expliqueintro = 1000;
           }
           else if (event.type == SDL_KEYDOWN)
           {
                if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)
                {
                    expliqueintro++;
                    clavier = 1;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                     (*continuer)++;
                     expliqueintro++;
                }
           }
     }
     if (expliqueintro == 3)
     {
        poscadre.x = 59;
           poscadre.y = 129;
           SDL_BlitSurface(s_fond, NULL, s_ecranjeu, &posfond);
           SDL_BlitSurface(s_textea, NULL, s_ecranjeu, &postexte);
           if (clavier == 1)
           {
              SDL_BlitSurface(s_cadre, NULL, s_ecranjeu, &poscadre);
           }
        while (i < 17)
        {
           SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, i*15);
           SDL_BlitSurface(s_fond3, NULL, s_ecran, &posfond);
           SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
           SDL_Flip(s_ecran);
           SDL_Delay(26);
           SDL_PollEvent(&event);
           if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
           {
              (*continuer)++;
              return;
           }
           i++;
        }
        i = 0;
        SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
        SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
     }
}

void blitteuse (char pions[], char newp[])
{
   int i = 0, lol = 0;
   while (i < 25)
   {
      posin.x = ((i%5)*36)+2;
      posin.y = (((i-(i%5))/5)*36)+2;
      if (newp[i] == 1)
      {
         switch (pions[i])
         {
            case 1:
                 SDL_BlitSurface(s_carte1, NULL, s_ecran, &posin);
                 break;
            case 2:
                 SDL_BlitSurface(s_carte2, NULL, s_ecran, &posin);
                 break;
            case 3:
                 SDL_BlitSurface(s_carte3, NULL, s_ecran, &posin);
                 break;
            case 4:
                 SDL_BlitSurface(s_carte4, NULL, s_ecran, &posin);
                 break;
            case 5:
                 SDL_BlitSurface(s_carte5, NULL, s_ecran, &posin);
                 break;
            case 10:
                 SDL_BlitSurface(s_bombe, NULL, s_ecran, &posin);
                 break;
            default:
                 lol++;
                 break;
         }
      }
      i++;
   }
}

void blitbord (char colonnes[], char lignes[], char niveau)
{
   int i = 0, j = 0, continuer = 0;
   char chiffres[2];
   while (i < 5)
   {
      j = 0;
      poschiffr.x = 186 + 15*(colonnes[i*2]/10);
      poschiffr.y = 3 + i*36;
      blittebleu(colonnes[i*2], poschiffr.x, poschiffr.y, s_ecran);
      poschiffr.x = 197;
      poschiffr.y = 25+ i*36;
      switch (colonnes[(i*2)+1])
      {
         case 0:
              SDL_BlitSurface(s_petit0, NULL, s_ecran, &poschiffr);
              break;
         case 1:
              SDL_BlitSurface(s_petit1, NULL, s_ecran, &poschiffr);
              break;
         case 2:
              SDL_BlitSurface(s_petit2, NULL, s_ecran, &poschiffr);
              break;
         case 3:
              SDL_BlitSurface(s_petit3, NULL, s_ecran, &poschiffr);
              break;
         case 4:
              SDL_BlitSurface(s_petit4, NULL, s_ecran, &poschiffr);
              break;
         case 5:
              SDL_BlitSurface(s_petit5, NULL, s_ecran, &poschiffr);
              break;
         default:
              break;
      }
      i++;
   }
   while (i < 10)
   {
      j = 0;
      poschiffr.x = (i-5)*36 + 4 + 15*(lignes[i-5]/10);
      poschiffr.y = 185;
      blittebleu(lignes[i-5], poschiffr.x, poschiffr.y, s_ecran);
      poschiffr.x = 15 + (i%5)*36;
      poschiffr.y = 207;
      chiffres[0] = lignes[i-5]/10;
      chiffres[1] = lignes[i-5]%10;
      switch (lignes[i])
      {
         case 0:
              SDL_BlitSurface(s_petit0, NULL, s_ecran, &poschiffr);
              break;
         case 1:
              SDL_BlitSurface(s_petit1, NULL, s_ecran, &poschiffr);
              break;
         case 2:
              SDL_BlitSurface(s_petit2, NULL, s_ecran, &poschiffr);
              break;
         case 3:
              SDL_BlitSurface(s_petit3, NULL, s_ecran, &poschiffr);
              break;
         case 4:
              SDL_BlitSurface(s_petit4, NULL, s_ecran, &poschiffr);
              break;
         case 5:
              SDL_BlitSurface(s_petit5, NULL, s_ecran, &poschiffr);
              break;
         default:
              break;
      }
      i++;
   }
   poschiffr.x = 210;
   poschiffr.y = 206;
   switch (niveau%10)
   {
      case 0:
           SDL_BlitSurface(s_petit0n, NULL, s_ecran, &poschiffr);
           break;
      case 1:
           SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
           break;
      case 2:
           SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
           break;
      case 3:
           SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
           break;
      case 4:
           SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
           break;
      case 5:
           SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
           break;
      case 6:
           SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
           break;
      case 7:
           SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
           break;
      case 8:
           SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
           break;
      case 9:
           SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
           break;
   }
   poschiffr.x = poschiffr.x - 10;
   if (niveau > 9)
   {
      switch (niveau/10)
      {
         case 1:
              SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
              break;
         case 2:
              SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
              break;
         case 3:
              SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
              break;
         case 4:
              SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
              break;
         case 5:
              SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
              break;
         case 6:
              SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
              break;
         case 7:
              SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
              break;
         case 8:
              SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
              break;
         case 9:
              SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
              break;
      }
   }
}

char jeu (char niveau, int *score, int *nombrevie)
{
     SDL_Event event, event2;
     int i = 0, lol = 0, k = 0, ok = 0, scoreniveau = 0, copievraiscore = 0;
     char continuer = 0, cadrechoix = 12, nouveaucadre = 0, premierclic = 0, ouiclic = 0, boutonenfonce = 0, cadreblock = 0, fin = 0, repasse = 0, dernierclic = 0;
     char pions[25] = {0};
     char colonnes[10] = {0};
     char lignes[10] = {0};
     char newp[25] = {0};
     SDL_BlitSurface(s_fondjeu, NULL, s_ecran, &posfond);
     genereniveau(pions, newp, colonnes, lignes, niveau);
     blitteuse (pions, newp);
     while (i < 25)
     {
        if (pions[i] != 1 && pions[i] != 10)
        {
           fin++;
        }
        i++;
     }
     i = 0;
     blitbord(colonnes, lignes, niveau);
     blitscore(*score);
     blitscoreactuel(0);
     poscadre.x = 2 + (cadrechoix%5)*36;
     poscadre.y = 2 + (cadrechoix/5)*36;
     SDL_BlitSurface(s_cadrejeu, NULL, s_ecran, &poscadre);
     poschiffr.x = (s_ecran->w) - (s_meilleurscore->w);
     poschiffr.y = (s_ecran->h) - (s_meilleurscore->h);
     SDL_BlitSurface(s_meilleurscore, NULL, s_ecran, &poschiffr);
     blitvies(*nombrevie);
     SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
     poschiffr.x = 40;
     poschiffr.y = 83;
     SDL_FillRect(s_fondnoir, NULL, SDL_MapRGB(s_ecran->format, 0, 0, 0));
     while (i < 50 && lol == 0)
     {
        if ((i%2) == 0)
        {
           poschiffr.x--;
           SDL_BlitSurface(s_vrainiveau, NULL, s_fondnoir, &poschiffr);
        }
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           return 10;
        }
        SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
        SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, 255-(i*5));
        SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
        SDL_Delay(20);
        SDL_PollEvent(&event);
        i++;
     }
     SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
     SDL_Flip(s_ecran);
     while (continuer == 0)
     {
        dernierclic = 0;
        i = cadrechoix;
        SDL_PollEvent(&event);
        if (cadrechoix < 0)
        {
           cadrechoix = 0;
        }
        else if (cadrechoix > 24)
        {
           cadrechoix = 24;
        }
        if (event.type == SDL_QUIT)
        {
           continuer = 1;
           return 10;
        }
        else if (event.type == SDL_KEYDOWN)
        {
           if (event.key.keysym.sym == SDLK_ESCAPE)
           {
              continuer = 1;
              return 10;
           }
           else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_KP8)
           {
              if (cadrechoix > 4)
              {
                 cadrechoix = cadrechoix - 5;
              }
           }
           else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_KP2)
           {
              if (cadrechoix < 20)
              {
                 cadrechoix = cadrechoix + 5;
              }
           }
           else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_KP6)
           {
              if (cadrechoix%5 != 4)
              {
                 cadrechoix++;
              }
              else
              {
                  cadrechoix = cadrechoix - (cadrechoix%5);
              }
           }
           else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_KP4)
           {
              if (cadrechoix%5 != 0)
              {
                 cadrechoix--;
              }
              else
              {
                  cadrechoix = cadrechoix + 4;
              }
           }
           else if (event.key.keysym.sym < (SDLK_z+1) && event.key.keysym.sym > (SDLK_a-1))
           {
              if (newp[cadrechoix] == 0)
              {
                 newp[cadrechoix] = 2;
              }
              else if (newp[cadrechoix] == 2)
              {
                 newp[cadrechoix] = 0;
              }
           }
           else if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)
           {
              if (newp[cadrechoix] == 0)
              {
                 newp[cadrechoix] = 1;
                 if (pions[i] < 6 && pions[i] > 1)
                 {
                    fin--;
                 }
                 else if (pions[i] == 10)
                 {
                    (*nombrevie)--;
                    dernierclic = 1;
                    if ((*nombrevie) == 0)
                    {
                       fin = -20;
                    }
                 }
              }
           }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
           nouveaucadre = trouvei(event.motion.x, event.motion.y);
           if (nouveaucadre != 50)
           {
              cadrechoix = nouveaucadre;
           }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
           k = trouvei(event.button.x, event.button.y);
           repasse = 0;
           if (k != 50)
           {
              if (premierclic != 0)
              {
                 ouiclic = 1;
              }
           }
           premierclic = 1;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT && premierclic != 1)
        {
           k = trouvei(event.button.x, event.button.y);
           if (k != 50 && ok == 0)
           {
              if (newp[k] == 0)
              {
                 newp[k] = 2;
              }
              else if (newp[k] == 2)
              {
                 newp[k] = 0;
              }
           }
           ok = 1;
        }
        else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT)
        {
           ok = 0;
        }
        else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        {
           ok = 0;
           if (repasse == 0)
           {
              premierclic = 0;
              ouiclic = 0;
              repasse++;
              boutonenfonce = 0;
              if (trouvei(event.button.x, event.button.y) == cadreblock && newp[cadreblock] == 0)
              {
                 newp[cadreblock] = 1;
                 if (pions[cadreblock] != 1 && pions[cadreblock] != 10)
                 {
                    fin--;
                 }
                 else if (pions[cadreblock] == 10)
                 {
                    (*nombrevie)--;
                    dernierclic = 1;
                    if ((*nombrevie) == 0)
                    {
                       fin = -20;
                    }
                 }
              }
           }
        }
        if (premierclic == 1 && ouiclic == 0)
        {
           k = trouvei(event.button.x, event.button.y);
           if (k != 50)
           {
              boutonenfonce = 1;
              cadreblock = k;
           }
           ouiclic = 1;
           if (newp[cadreblock] != 0)
           {
              boutonenfonce = 0;
              ouiclic = 0;
           }
        }
        SDL_Delay(7);
        event.key.keysym.sym = SDLK_PAGEUP;
        if (boutonenfonce == 1)
        {
           cadrechoix = cadreblock;
        }
        poscadre.x = 2 + (cadrechoix%5)*36;
        poscadre.y = 2 + (cadrechoix/5)*36;
        posin.x = ((i%5)*36)+2;
        posin.y = (((i-(i%5))/5)*36)+2;
        if (newp[i] == 1)
        {
           switch (pions[i])
           {
              case 1:
                   SDL_BlitSurface(s_carte1, NULL, s_ecran, &posin);
                   break;
              case 2:
                   SDL_BlitSurface(s_carte2, NULL, s_ecran, &posin);
                   break;
              case 3:
                   SDL_BlitSurface(s_carte3, NULL, s_ecran, &posin);
                   break;
              case 4:
                   SDL_BlitSurface(s_carte4, NULL, s_ecran, &posin);
                   break;
              case 5:
                   SDL_BlitSurface(s_carte5, NULL, s_ecran, &posin);
                   break;
              case 10:
                   SDL_BlitSurface(s_bombe, NULL, s_ecran, &posin);
                   break;
              default:
                   lol++;
                   break;
           }
        }
        else if (newp[i] == 0)
        {
           SDL_BlitSurface(s_casejeu, NULL, s_ecran, &posin);
        }
        else if (newp[i] == 2)
        {
           SDL_BlitSurface(s_casejeuno, NULL, s_ecran, &posin);
        }
        if (boutonenfonce == 1 && newp[cadreblock] == 0)
        {
           SDL_BlitSurface(s_casejeudown, NULL, s_ecran, &poscadre);
        }
        if (fin > 0)
        {
           SDL_BlitSurface(s_cadrejeu, NULL, s_ecran, &poscadre);
        }
        scoreniveau = calculescore(pions, newp, _TRICHE);
        blitscoreactuel(scoreniveau);
        SDL_Flip(s_ecran);
        if (dernierclic == 1)
        {
           blitvies(*nombrevie);
           vieperdu();
        }
        if (fin < 1)
        {
           continuer++;
           lol = 0;
           if (*nombrevie != 0)
           {
              scoreniveau = calculescore(pions, newp, 0);
           }
           else
           {
               scoreniveau = calculescore(pions, newp, 1);
           }
           blitscoreactuel(scoreniveau);
           SDL_Flip(s_ecran);
           while (lol < 20)
           {
              SDL_Delay(25);
              SDL_PollEvent(&event);
              if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
              {
                 lol = 100;
              }   
              lol++;
           }
           if (lol != 100)
           {
              lol = 0;
           }
           while (scoreniveau%10 != 0 && lol == 0)
           {
              (*score)++;
              scoreniveau--;
              blitscoreactuel(scoreniveau);
              blitscore(*score);
              SDL_Flip(s_ecran);
              SDL_Delay(40);
              SDL_PollEvent(&event);
              if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
              {
                 return 10;
              }
           }
           scoreniveau = scoreniveau/10;
           while (scoreniveau%10 != 0 && lol == 0)
           {
              scoreniveau--;
              (*score) = (*score) + 10;
              blitscoreactuel(scoreniveau*10);
              blitscore(*score);
              SDL_Flip(s_ecran);
              SDL_Delay(40);
              SDL_PollEvent(&event);
              if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
              {
                 return 10;
              }
           }
           scoreniveau = scoreniveau/10;
           while (scoreniveau%10 != 0 && lol == 0)
           {
              scoreniveau--;
              (*score) = (*score) + 100;
              blitscoreactuel(scoreniveau*100);
              blitscore(*score);
              SDL_Flip(s_ecran);
              SDL_Delay(40);
              SDL_PollEvent(&event);
              if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
              {
                 return 10;
              }
           }
           scoreniveau = scoreniveau/10;
           while (scoreniveau%10 != 0 && lol == 0)
           {
              scoreniveau--;
              (*score) = (*score) + 1000;
              blitscoreactuel(scoreniveau*1000);
              blitscore(*score);
              SDL_Flip(s_ecran);
              SDL_Delay(40);
              SDL_PollEvent(&event);
              if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
              {
                 return 10;
              }
           }
        }
     }
     i = 0;
     SDL_Flip(s_ecran);
     while (i < 70)
     {
        SDL_Delay(10);
        SDL_PollEvent(&event);
        i++;
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           return 10;
        }
     }
     if (fin == -20)
     {
        i = 0;
        while (i < 25)
        {
           newp[i] = 1;
           i++;
        }
        i = 0;
        SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
        while (i < 15 && lol == 0)
        {
           SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, 255-(17*i));
           blitteuse(pions, newp);
           SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
           SDL_Flip(s_ecran);
           SDL_Delay(8);
           SDL_PollEvent(&event);
           if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
           {
              return 10;
           }
           i++;
        }
        blitteuse(pions, newp);
        SDL_Flip(s_ecran);
        i = 0;
        event.key.keysym.sym = 0;
        event.type == 0;
        while (i == 0)
        {
           SDL_PollEvent(&event2);
           SDL_Delay(10);
           if (event2.type == SDL_QUIT || event2.key.keysym.sym == SDLK_ESCAPE)
           {
              return 10;
           }
           else if ((event2.type == SDL_MOUSEBUTTONUP && event2.button.button == SDL_BUTTON_LEFT) || event2.key.keysym.sym == SDLK_KP_ENTER || event2.key.keysym.sym == SDLK_SPACE)
           {
              i++;
           }
           else if (event2.key.keysym.sym == SDLK_RETURN)
           {
              i++;
           }
        }
        return 0;
     }
     return 1;
}

int calculescore (char pions[], char newp[], char final)
{
    int somme = 0, produit = 1, i = 0;
    while (i < 25)
    {
       if (newp[i] == 1)
       {
          if (pions[i] == 1)
          {
             somme++;
          }
          else if (pions[i] > 1 && pions[i] < 6)
          {
             produit = produit * pions[i];
          }
       }
       else if (newp[i] == 2 && pions[i] == 10 && final == 0)
       {
          somme++;
       }
       i++;
    }
    i = somme*produit;
    if (i > 9999)
    {
       return 9999;
    }
    return (somme*produit);
}

void blitscoreactuel (int scoreactuel)
{
   int score[4] = {0};
   if (scoreactuel > 9999)
   {
      scoreactuel = 9999;
   }
   score[0] = (scoreactuel/1000);
   score[1] = (scoreactuel/100)%10;
   score[2] = (scoreactuel/10)%10;
   score[3] = scoreactuel%10;
   poschiffr.y = 185;
   poschiffr.x = 182;
   SDL_BlitSurface(s_bleuno, NULL, s_ecran, &poschiffr);
   switch (score[0])
   {
      case 1:
           SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
           break;
      case 2:
           SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
           break;
      case 3:
           SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
           break;
      case 4:
           SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
           break;
      case 5:
           SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
           break;
      case 6:
           SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
           break;
      case 7:
           SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
           break;
      case 8:
           SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
           break;
      case 9:
           SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
           break;
   }
   poschiffr.x = 191;
   SDL_BlitSurface(s_bleuno, NULL, s_ecran, &poschiffr);
   switch (score[1])
   {
      case 0:
           if (score[0] != 0)
           {
              SDL_BlitSurface(s_petit0n, NULL, s_ecran, &poschiffr);
           }
           break;
      case 1:
           SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
           break;
      case 2:
           SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
           break;
      case 3:
           SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
           break;
      case 4:
           SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
           break;
      case 5:
           SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
           break;
      case 6:
           SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
           break;
      case 7:
           SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
           break;
      case 8:
           SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
           break;
      case 9:
           SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
           break;
   }
   poschiffr.x = 200;
   SDL_BlitSurface(s_bleuno, NULL, s_ecran, &poschiffr);
   switch (score[2])
   {
      case 0:
           if (scoreactuel > 99)
           {
              SDL_BlitSurface(s_petit0n, NULL, s_ecran, &poschiffr);
           }
           break;
      case 1:
           SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
           break;
      case 2:
           SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
           break;
      case 3:
           SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
           break;
      case 4:
           SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
           break;
      case 5:
           SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
           break;
      case 6:
           SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
           break;
      case 7:
           SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
           break;
      case 8:
           SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
           break;
      case 9:
           SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
           break;
   }
   poschiffr.x = 209;
   SDL_BlitSurface(s_bleuno, NULL, s_ecran, &poschiffr);
   switch (score[3])
   {
      case 0:
           SDL_BlitSurface(s_petit0n, NULL, s_ecran, &poschiffr);
           break;
      case 1:
           SDL_BlitSurface(s_petit1n, NULL, s_ecran, &poschiffr);
           break;
      case 2:
           SDL_BlitSurface(s_petit2n, NULL, s_ecran, &poschiffr);
           break;
      case 3:
           SDL_BlitSurface(s_petit3n, NULL, s_ecran, &poschiffr);
           break;
      case 4:
           SDL_BlitSurface(s_petit4n, NULL, s_ecran, &poschiffr);
           break;
      case 5:
           SDL_BlitSurface(s_petit5n, NULL, s_ecran, &poschiffr);
           break;
      case 6:
           SDL_BlitSurface(s_petit6n, NULL, s_ecran, &poschiffr);
           break;
      case 7:
           SDL_BlitSurface(s_petit7n, NULL, s_ecran, &poschiffr);
           break;
      case 8:
           SDL_BlitSurface(s_petit8n, NULL, s_ecran, &poschiffr);
           break;
      case 9:
           SDL_BlitSurface(s_petit9n, NULL, s_ecran, &poschiffr);
           break;
   }
}

void blitscore (int scoreactuel)
{
   int chifscore[6] = {0};
   int i = 0;
   poschiffr.y = 225;
   poschiffr.x = 2;
   decoupescore(scoreactuel, chifscore);
   while (i < 6)
   {
      SDL_BlitSurface(s_bleuno, NULL, s_ecran, &poschiffr);
      switch (chifscore[i])
      {
         case 0:
              if (scoreactuel > (puis10(5-i)-1) || i == 5)
              {
                 SDL_BlitSurface(s_bleu0, NULL, s_ecran, &poschiffr);
                 poschiffr.x = poschiffr.x + 15;
              }
              poschiffr.x = poschiffr.x - 15;
              break;
         case 1:
              SDL_BlitSurface(s_bleu1, NULL, s_ecran, &poschiffr);
              break;
         case 2:
              SDL_BlitSurface(s_bleu2, NULL, s_ecran, &poschiffr);
              break;
         case 3:
              SDL_BlitSurface(s_bleu3, NULL, s_ecran, &poschiffr);
              break;
         case 4:
              SDL_BlitSurface(s_bleu4, NULL, s_ecran, &poschiffr);
              break;
         case 5:
              SDL_BlitSurface(s_bleu5, NULL, s_ecran, &poschiffr);
              break;
         case 6:
              SDL_BlitSurface(s_bleu6, NULL, s_ecran, &poschiffr);
              break;
         case 7:
              SDL_BlitSurface(s_bleu7, NULL, s_ecran, &poschiffr);
              break;
         case 8:
              SDL_BlitSurface(s_bleu8, NULL, s_ecran, &poschiffr);
              break;
         case 9:
              SDL_BlitSurface(s_bleu9, NULL, s_ecran, &poschiffr);
              break;
      }
      poschiffr.x = poschiffr.x + 15;
      i++;
   }
}

void decoupescore (int score, int chiffres[])
{
   chiffres[0] = (score/100000)%10;
   chiffres[1] = (score/10000)%10;
   chiffres[2] = (score/1000)%10;
   chiffres[3] = (score/100)%10;
   chiffres[4] = (score/10)%10;
   chiffres[5] = score%10;
}

int puis10 (char nombre)
{
    if (nombre == 0)
    {
       return 1;
    }
    return (10 * puis10(nombre-1));
}

int selectionnecase (int positionx, int positiony)
{
    int newposx = 0, newposy = 0, i = 0, posdetx = 0, posdety = 0, sommedet = 0, sommedetinv = 0, nouveaux = 0;
    if (positionx < 60 || positionx > 157 || positiony > 204 || positiony < 130)
    {
       return 50;
    }
    i = 1+((positiony - 130)/15);
    return i;
}

void tableorder (int scores[])
{
   int i = 0, j = 0, k = 0, lol = 0;
   int ordonne[11] = {0};
   int copiescore[11] = {0};
   char copiepseudo[77] = "";
   while (i < 11)
   {
      copiescore[i] = scores[i];
      i++;
   }
   while (k < 11)
   {
      i = 0;
      while (i < 11)
      {
         if (copiescore[i] > 0)
         {
            copiescore[i]--;
         }
         else if (copiescore[i] == 0)
         {
             ordonne[10-k] = scores[i];
             j = 0;
             while (j < 7)
             {
                copiepseudo[7*(10-k) + j] = c_scores[7*i + j];
                j++;
             }
             copiescore[i]--;
             k++;
         }
         else
         {
            lol++;
         }
         i++;
      }
   }
   i = 0;
   while (i < 11)
   {
      scores[i] = ordonne[i];
      i++;
   }
   j = 0;
   while (j < 77)
   {
      c_scores[j] = copiepseudo[j];
      j++;
   }
}

SDL_Surface* creerscore (int meilleurscore)
{
   int x = 1, y = 14, i = 0;
   int score[6] = {0};
   SDL_Surface *s_provisoire = NULL;
   decoupescore(meilleurscore, score);
   while (i < 6)
   {
      switch (score[i])
      {
         case 0:
              if (meilleurscore > (puis10(5-i)-1) || i == 5)
              {
                 x = x + 11;
              }
              break;
         case 1:
              x = x + 9;
              break;
         case 2:
              x = x + 13;
              if (y < 16)
              {
                 y = 16;
              }
              break;
         case 3:
              if (y < 17)
              {
                 y = 17;
              }
              x = x + 10;
              break;
         case 4:
              if (y < 16)
              {
                 y = 16;
              }
              x = x + 15;
              break;
         case 5:
              x = x + 10;
              break;
         case 6:
              x = x + 10;
              break;
         case 7:
              x = x + 10;
              break;
         case 8:
              x = x + 11;
              break;
         case 9:
              x = x + 10;
              break;
      }
      i++;
   }
   i = 0;
   s_provisoire = SDL_CreateRGBSurface(SDL_HWSURFACE, x, y, 32, 0, 0, 0, 0);
   if (s_provisoire == NULL)
   {
      return NULL;
   }
   poschiffr.x = 0;
   poschiffr.y = 0;
   while (i < 6)
   {
      switch (score[i])
      {
         case 0:
              if (meilleurscore > (puis10(5-i)-1) || i == 5)
              {
                 poschiffr.y = (y-14)/2;
                 SDL_BlitSurface(s_best0, NULL, s_provisoire, &poschiffr);
                 poschiffr.x = poschiffr.x + 11;
              }
              break;
         case 1:
              poschiffr.y = (y-14)/2;
              SDL_BlitSurface(s_best1, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 9;
              break;
         case 2:
              poschiffr.y = (y-16)/2;
              SDL_BlitSurface(s_best2, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 13;
              break;
         case 3:
              poschiffr.y = (y-17)/2;
              SDL_BlitSurface(s_best3, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 10;
              break;
         case 4:
              poschiffr.y = (y-16)/2;
              SDL_BlitSurface(s_best4, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 15;
              break;
         case 5:
              poschiffr.y = (y-14)/2;
              SDL_BlitSurface(s_best5, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 10;
              break;
         case 6:
              poschiffr.y = (y-14)/2;
              SDL_BlitSurface(s_best6, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 10;
              break;
         case 7:
              poschiffr.y = (y-13)/2;
              SDL_BlitSurface(s_best7, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 10;
              break;
         case 8:
              poschiffr.y = (y-14)/2;
              SDL_BlitSurface(s_best8, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 11;
              break;
         case 9:
              poschiffr.y = (y-14)/2;
              SDL_BlitSurface(s_best9, NULL, s_provisoire, &poschiffr);
              poschiffr.x = poschiffr.x + 10;
              break;
      }
      i++;
   }
   return s_provisoire;
}

void vieperdu (void)
{
   int i = 25;
   SDL_FillRect(s_fondnoir, NULL, SDL_MapRGB(s_ecran->format, 255, 0, 0));
   SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
   while (i < 51)
   {
      SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, 255-(i*5));
      SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
      SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
      SDL_Flip(s_ecran);
      SDL_Delay(10);
      i++;
   }
}

void blitvies (int vies)
{
   int i = 0;
   poschiffr.x = 211;
   poschiffr.y = 220;
   while (i < 3)
   {
      if (vies == 0)
      {
         SDL_BlitSurface(s_nocoeur, NULL, s_ecran, &poschiffr);
         poschiffr.x = poschiffr.x - 10;
      }
      else
      {
         vies--;
         SDL_BlitSurface(s_coeur, NULL, s_ecran, &poschiffr);
         poschiffr.x = poschiffr.x - 10;
      }
      i++;
   }
}

void loadpseudo (void)
{
   int i = 0;
   s_pseudo[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 13, 21, 32, 0, 0, 0, 0);
   while (i < 65)
   {
      i++;
      c_pseudo[15] = 48 + i/10;
      c_pseudo[16] = 48 + i%10;
      s_pseudo[i] = IMG_Load(c_pseudo);
   }
}

void menusdescores (int scores[], char *continuer, int rescore)
{
     SDL_Event event;
     SDLMod touche;
     int expliqueintro = 1, i = 0, newscore = -1, majuscule = 0, appui = 0, cadre = 1, mcadre = 10, /**/ncadre = 1,/**/ ccadre = 1, clic = 0, okclic = 0;
     SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
     SDL_BlitSurface(s_fondmeilleurscore, NULL, s_fondnoir, &posfond);
     while (i < 7)
     {
        interpseudo[i] = '!';
        i++;
     }
     i = 0;
     while (i < 10)
     {
        blittebleu(scores[i], 100, 7+(22*i), s_fondnoir);
        blittenom(c_scores, 122, 7+(22*i), s_fondnoir, i*7, 0);
        if (rescore == scores[i])
        {
           newscore = i;
        }
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           (*continuer)++;
           return;
        }
        i++;
     }
     if (newscore != -1)
     {
        blittenom(interpseudo, 122, 7+(22*newscore), s_fondnoir, 0, 0);
     }
     postexte.x = 7;
     postexte.y = 226;
     poscadre.x = 7;
     poscadre.y = 226;
     posbutton.y = 226;
     if (rescore == -1)
     {
        SDL_BlitSurface(s_texteb, NULL, s_fondnoir, &postexte);
     }
     else if (rescore >= 0)
     {
        if (newscore == -1)
        {
           SDL_BlitSurface(s_texteb, NULL, s_fondnoir, &postexte);
        }
        else
        {
           SDL_BlitSurface(s_textec, NULL, s_fondnoir, &postexte);
        }
     }
     if (clavier == 1)
     {
        SDL_BlitSurface(s_cadre, NULL, s_fondnoir, &poscadre);
     }
     i = 0;
     SDL_Flip(s_ecran);
     while (i < 17)
     {
        SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, i*15);
        SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
        SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           (*continuer)++;
           return;
        }
        SDL_Delay(26);
        i++;
     }
     i = 0;
     SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
     SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
     SDL_Flip(s_ecran);
     i = 0;
     posin.y = 7+(22*newscore);
     posin.x = 122 + i*13;
     while (newscore < 10 && newscore >= 0)
     {
        if (i > 6)
        {
           i = 6;
        }
        posin.x = 122 + i*13;
        event.key.keysym.sym = SDLK_TAB;
        SDL_BlitSurface(s_textec, NULL, s_ecran, &postexte);
        if (clavier == 1)
        {
           SDL_BlitSurface(s_cadre, NULL, s_ecran, &poscadre);
        }
        SDL_Flip(s_ecran);
        SDL_Delay(5);
        SDL_PollEvent(&event);
        touche = SDL_GetModState();
        if ((touche & KMOD_LSHIFT) == KMOD_LSHIFT || (touche & KMOD_RSHIFT) == KMOD_RSHIFT || (touche & KMOD_CAPS) == KMOD_CAPS)
        {
           majuscule = 1;
        }
        else
        {
            majuscule = 0;
        }
        SDL_BlitSurface(s_pseudo[0], NULL, s_ecran, &posin);
        blittenom(interpseudo, 122, 7+(22*newscore), s_ecran, 0, 0);
        if (SDL_GetTicks()%1000 < 500)
        {
           SDL_BlitSurface(s_cpseudo, NULL, s_ecran, &posin);
        }
        if (event.type == SDL_QUIT)
        {
           (*continuer)++;
           expliqueintro = 1000;
           newscore = 100;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
           mcadre = selectioncase(event.motion.x, event.motion.y);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
           if (okclic == 1 && okclic == selectioncase(event.button.x, event.button.y))
           {
              i = 0;
              while (i < 7)
              {
                 c_scores[(newscore*7)+i] = interpseudo[i];
                 c_scores[70+i] = '!';
                 i++;
              }
              i = 0;
              f_scores = fopen("Application.exe", "w+");
              while (i < 10)
              {
                 fprintf(f_scores, "%d\t%c%c%c%c%c%c%c\n", scores[i], c_scores[i*7], c_scores[(i*7)+1], c_scores[(i*7)+2], c_scores[(i*7)+3], c_scores[(i*7)+4], c_scores[(i*7)+5], c_scores[(i*7)+6]);
                 i++;
              }
              fprintf(f_scores, "\n%d", azerty);
              fclose(f_scores);
              newscore = 100;
           }
           else if (okclic == 2 && okclic == selectioncase(event.button.x, event.button.y))
           {
              scores[newscore] = 0;
              i = 0;
              while (i < 7)
              {
                 c_scores[newscore*7 + i] = '!';
                 i++;
              }
              tableorder(scores);
              i = 0;
              f_scores = fopen("Application.exe", "w+");
              while (i < 10)
              {
                 fprintf(f_scores, "%d\t%c%c%c%c%c%c%c\n", scores[i], c_scores[i*7], c_scores[(i*7)+1], c_scores[(i*7)+2], c_scores[(i*7)+3], c_scores[(i*7)+4], c_scores[(i*7)+5], c_scores[(i*7)+6]);
                 i++;
              }
              fprintf(f_scores, "\n%d", azerty);
              fclose(f_scores);
              newscore = 100;
           }
           clic = 0;
           okclic = 0;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
           clavier = 0;
           ccadre = selectioncase(event.button.x, event.button.y);
           if (ccadre != 50 && clic == 0)
           {
              okclic = ccadre;
              SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
           }
           clic = 1;
        }
        else if (event.type == SDL_KEYUP)
        {
           appui = 0;
           if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN)
           {
              if (cadre == 1)
              {
                 i = 0;
                 while (i < 7)
                 {
                    c_scores[(newscore*7)+i] = interpseudo[i];
                    c_scores[70+i] = '!';
                    i++;
                 }
                 i = 0;
                 f_scores = fopen("Application.exe", "w+");
                 while (i < 10)
                 {
                    fprintf(f_scores, "%d\t%c%c%c%c%c%c%c\n", scores[i], c_scores[i*7], c_scores[(i*7)+1], c_scores[(i*7)+2], c_scores[(i*7)+3], c_scores[(i*7)+4], c_scores[(i*7)+5], c_scores[(i*7)+6]);
                    i++;
                 }
                 fprintf(f_scores, "\n%d", azerty);
                 fclose(f_scores);
                 newscore = 100;
              }
              else if (cadre == 2)
              {
                 scores[newscore] = 0;
                 i = 0;
                 while (i < 7)
                 {
                    c_scores[newscore*7 + i] = '!';
                    i++;
                 }
                 tableorder(scores);
                 i = 0;
                 f_scores = fopen("Application.exe", "w+");
                 while (i < 10)
                 {
                    fprintf(f_scores, "%d\t%c%c%c%c%c%c%c\n", scores[i], c_scores[i*7], c_scores[(i*7)+1], c_scores[(i*7)+2], c_scores[(i*7)+3], c_scores[(i*7)+4], c_scores[(i*7)+5], c_scores[(i*7)+6]);
                    i++;
                 }
                 fprintf(f_scores, "\n%d", azerty);
                 fclose(f_scores);
                 newscore = 100;
              }
           }
        }
        else if (event.type == SDL_KEYDOWN && appui == 0)
        {
           clavier = 1;
           if (event.key.keysym.sym == SDLK_UP)
           {
              poscadre.x = 7;
              cadre = 1;
           }
           if (event.key.keysym.sym == SDLK_DOWN)
           {
              poscadre.x = 113;
              cadre = 2;
           }
           if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
           {
              appui = 1;
              if (event.key.keysym.sym != SDLK_m && azerty == 1)
              {
                 if (majuscule%2 == 1)
                 {
                    interpseudo[i] = 65-SDLK_a+event.key.keysym.sym;
                    if (event.key.keysym.sym == SDLK_q)
                    {
                       interpseudo[i] = 65;
                    }
                    if (event.key.keysym.sym == SDLK_w)
                    {
                        interpseudo[i] = 90;
                    }
                    if (event.key.keysym.sym == SDLK_a)
                    {
                       interpseudo[i] = 81;
                    }
                    if (event.key.keysym.sym == SDLK_z)
                    {
                       interpseudo[i] = 87;
                    }
                 }
                 else
                 {
                     interpseudo[i] = 97-SDLK_a+event.key.keysym.sym;
                    if (event.key.keysym.sym == SDLK_q)
                    {
                       interpseudo[i] = 97;
                    }
                    if (event.key.keysym.sym == SDLK_w)
                    {
                       interpseudo[i] = 122;
                    }
                    if (event.key.keysym.sym == SDLK_a)
                    {
                       interpseudo[i] = 113;
                    }
                    if (event.key.keysym.sym == SDLK_z)
                    {
                       interpseudo[i] = 119;
                    }
                 }
                 i++;
              }
              else if (azerty == 0)
              {
                 interpseudo[i] = 65-SDLK_a+event.key.keysym.sym + 32*(1-(majuscule%2));
                 i++;
              }
           }
           else if (azerty == 1)
           {
              if (event.key.keysym.sym == 61 || event.key.keysym.sym == SDLK_KP_MINUS)
              {
                 interpseudo[i] = '-';
                 appui = 1;
                 if (majuscule == 1 && event.key.keysym.sym == 61)
                 {
                    interpseudo[i] = '_';
                 }
                 i++;
              }
              else if (event.key.keysym.sym == 59)
              {
                 interpseudo[i] = 'm';
                 appui = 1;
                 if (majuscule == 1)
                 {
                    interpseudo[i] = 'M';
                 }
                 i++;
              }
              else if ((event.key.keysym.sym == 44 && majuscule == 1) || event.key.keysym.sym == SDLK_KP_PERIOD)
              {
                 interpseudo[i] = '.';
                 appui = 1;
                 i++;
              }
              else if (event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == 8 || event.key.keysym.sym == SDLK_LEFT)
              {
                 interpseudo[i] = '!';
                 if (i != 0)
                 {
                    i--;
                 }
              }
           }
           else if (azerty == 0)
           {
              if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS)
              {
                 interpseudo[i] = '-';
                 appui = 1;
                 i++;
              }
              else if (event.key.keysym.sym == SDLK_UNDERSCORE)
              {
                 interpseudo[i] = '_';
                 appui = 1;
                 i++;
              }
              else if (event.key.keysym.sym == SDLK_PERIOD || event.key.keysym.sym == SDLK_KP_PERIOD)
              {
                 interpseudo[i] = '.';
                 appui = 1;
                 i++;
              }
              else if (event.key.keysym.sym == SDLK_DELETE || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_LEFT)
              {
                 interpseudo[i] = '!';
                 if (i != 0)
                 {
                    i--;
                 }
              }
           }
           else if (event.key.keysym.sym == SDLK_SPACE)
           {
              interpseudo[i] = '!';
              appui = 1;
              i++;
           }
           else if (event.key.keysym.sym >= SDLK_KP0 && event.key.keysym.sym <= SDLK_KP9)
           {
              interpseudo[i] = 48-SDLK_KP0+event.key.keysym.sym;
              appui = 1;
              i++;
           }
           else if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9 && majuscule == 1)
           {
              interpseudo[i] = 48-SDLK_0+event.key.keysym.sym;
              appui = 1;
              i++;
           }
           else if (event.key.keysym.sym == SDLK_ESCAPE)
           {
              (*continuer)++;
              expliqueintro++;
              newscore = 100;
           }
           if (appui == 1)
           {
              SDL_BlitSurface(s_pseudo[0], NULL, s_ecran, &posin);
           }
        }
        posbutton.y = 226;
        /**/posbutton.x = 7;
        SDL_BlitSurface(s_boutton2, NULL, s_ecran, &posbutton);
        posbutton.x = 113;
        SDL_BlitSurface(s_boutton2, NULL, s_ecran, &posbutton);/**/
        if (mcadre != 50)
        {
           posbutton.x = 7 + 106*(mcadre - 1);
           SDL_BlitSurface(s_boutsurv, NULL, s_ecran, &posbutton);
        }
        if (okclic != 0)
        {
           posbutton.x = 7 + 106*(okclic - 1);
           SDL_BlitSurface(s_bouttondown, NULL, s_ecran, &posbutton);
        }
        if (okclic == mcadre && mcadre != 50)
        {
           posbutton.x = 7 + 106*(mcadre - 1);
           SDL_BlitSurface(s_boutdownsurv, NULL, s_ecran, &posbutton);
        }
     }
     SDL_BlitSurface(s_fondmeilleurscore, NULL, s_ecran, &posfond);
     i = 0;
     while (i < 7)
     {
        interpseudo[i] = '!';
        i++;
     }
     i = 0;
     while (i < 10)
     {
        blittebleu(scores[i], 100, 7+(22*i), s_ecran);
        blittenom(c_scores, 122, 7+(22*i), s_ecran, i*7, 0);
        i++;
     }
     SDL_BlitSurface(s_texteb, NULL, s_ecran, &postexte);
     i = 0;
     clic = 0;
     okclic = 0;
     cadre = 1;
     ncadre = 1;
     ccadre = 1;
     majuscule = 0;
     SDL_Flip(s_ecran);
     SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
     while (expliqueintro == 1)
     {
        SDL_Delay(5);
        SDL_PollEvent(&event);
        if (clavier == 1)
        {
           SDL_BlitSurface(s_cadre, NULL, s_ecran, &poscadre);
        }
        SDL_Flip(s_ecran);
        mcadre = selectioncase(event.motion.x, event.motion.y);
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
           (*continuer)++;
           expliqueintro = 1000;
        }
        else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_UP))
        {
           cadre = 1;
           poscadre.x = 7;
           clavier = 1;
        }
        else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_DOWN))
        {
           cadre = 2;
           poscadre.x = 113;
           clavier = 1;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
           if (okclic == 1 && okclic == selectioncase(event.button.x, event.button.y))
           {
              majuscule = 1;
           }
           else if (okclic == 2 && okclic == selectioncase(event.button.x, event.button.y))
           {
              expliqueintro = 2;
           }
           clic = 0;
           okclic = 0;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
           ccadre = selectioncase(event.button.x, event.button.y);
           clavier = 0;
           if (ccadre != 50 && clic == 0)
           {
              okclic = ccadre;
              SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
           }
           clic = 1;
        }
        else if (event.type == SDL_KEYDOWN)
        {
           clavier = 1;
           if (cadre == 1 && (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE))
           {
              majuscule = 1;
              event.key.keysym.sym = SDLK_a;
           }
           if (cadre == 2 && (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE))
           {
              expliqueintro = 2;
           }
        }
        posbutton.x = 7;
        SDL_BlitSurface(s_boutton2, NULL, s_ecran, &posbutton);
        posbutton.x = 113;
        SDL_BlitSurface(s_boutton2, NULL, s_ecran, &posbutton);
        if (okclic != 0)
        {
           posbutton.x = 7 + 106*(okclic - 1);
           SDL_BlitSurface(s_bouttondown, NULL, s_ecran, &posbutton);
        }
        if (mcadre != 50)
        {
           posbutton.x = 7 + 106*(mcadre-1);
           SDL_BlitSurface(s_boutsurv, NULL, s_ecran, &posbutton);
        }
        if (okclic == mcadre && mcadre != 50)
        {
           posbutton.x = 7 + 106*(mcadre-1);
           SDL_BlitSurface(s_boutdownsurv, NULL, s_ecran, &posbutton);
        }
        SDL_BlitSurface(s_texteb, NULL, s_ecran, &postexte);
        if (majuscule == 1)
        {
           majuscule = confirmefface(continuer);
           SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
           if (majuscule == 3)
           {
              expliqueintro = 1570;
              *continuer = 255;
           }
           if (majuscule == 1)
           {
              i = 0;
              while (i < 77)
              {
                 c_scores[i] = '!';
                 i++;
              }
              i = 0;
              while (i < 11)
              {
                 scores[i] = 0;
                 i++;
              }
              i = 0;
              SDL_BlitSurface(s_fondmeilleurscore, NULL, s_ecran, &posfond);
              SDL_BlitSurface(s_texteb, NULL, s_ecran, &postexte);
              while (i < 10)
              {
                 blittebleu(scores[i], 100, 7+(22*i), s_ecran);
                 blittenom(c_scores, 122, 7+(22*i), s_ecran, i*7, 0);
                 i++;
              }
              i = 0;
              f_scores = fopen("Application.exe", "w+");
              while (i < 10)
              {
                 fprintf(f_scores, "%d\t%c%c%c%c%c%c%c\n", scores[i], c_scores[i*7], c_scores[(i*7)+1], c_scores[(i*7)+2], c_scores[(i*7)+3], c_scores[(i*7)+4], c_scores[(i*7)+5], c_scores[(i*7)+6]);
                 i++;
              }
              fprintf(f_scores, "\n%d", azerty);
              fclose(f_scores);
              i = 0;
              majuscule = 0;
           }
           majuscule = 0;
           postexte.x = 7;
           postexte.y = 226;
           poscadre.x = 7;
           poscadre.y = 226;
           posbutton.y = 226;
        }
     }
     posfond.x = 0;
     posfond.y = 0;
     postexte.x = 59;
     postexte.y = 129;
     posbutton.x = 61;
     poscadre.x = 59;
     if (expliqueintro == 2)
     {
           poscadre.x = 59;
           poscadre.y = 129;
           SDL_BlitSurface(s_fond, NULL, s_ecranjeu, &posfond);
           SDL_BlitSurface(s_textea, NULL, s_ecranjeu, &postexte);
           if (clavier == 1)
           {
              SDL_BlitSurface(s_cadre, NULL, s_ecranjeu, &poscadre);
           }
           SDL_BlitSurface(s_ecran, NULL, s_fondnoir, &posfond);
        while (i < 17)
        {
           SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, i*15);
           SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
           SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
           SDL_Flip(s_ecran);
           SDL_Delay(26);
           SDL_PollEvent(&event);
           if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
           {
              (*continuer)++;
              return;
           }
           i++;
        }
        i = 0;
        SDL_SetAlpha(s_ecranjeu, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
        SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
        SDL_Flip(s_ecran);
     }
}

void blittebleu (int score, int x, int y, SDL_Surface* surface)
{
   int chiffres[6] = {0};
   int i = 5, j = 0;
   decoupescore(score, chiffres);
   poschiffr.y = y;
   while (i >= 0)
   {
      poschiffr.x = x - j*15;
      switch (chiffres[i])
      {
         case 0:
              if (i == 5 || score/puis10(5-i) > 0)
              {
                 SDL_BlitSurface(s_bleu0, NULL, surface, &poschiffr);
                 j++;
              }
              break;
         case 1:
              SDL_BlitSurface(s_bleu1, NULL, surface, &poschiffr);
              j++;
              break;
         case 2:
              SDL_BlitSurface(s_bleu2, NULL, surface, &poschiffr);
              j++;
              break;
         case 3:
              SDL_BlitSurface(s_bleu3, NULL, surface, &poschiffr);
              j++;
              break;
         case 4:
              SDL_BlitSurface(s_bleu4, NULL, surface, &poschiffr);
              j++;
              break;
         case 5:
              SDL_BlitSurface(s_bleu5, NULL, surface, &poschiffr);
              j++;
              break;
         case 6:
              SDL_BlitSurface(s_bleu6, NULL, surface, &poschiffr);
              j++;
              break;
         case 7:
              SDL_BlitSurface(s_bleu7, NULL, surface, &poschiffr);
              j++;
              break;
         case 8:
              SDL_BlitSurface(s_bleu8, NULL, surface, &poschiffr);
              j++;
              break;
         case 9:
              SDL_BlitSurface(s_bleu9, NULL, surface, &poschiffr);
              j++;
              break;
      }
      i--;
   }
}

void blittenom (char pseudo[], int x, int y, SDL_Surface* surface, int i, int unelettre)
{
   int j = 0;
   poschiffr.y = y;
   while (j < 7)
   {
      poschiffr.x = x + j*13;
      if (unelettre == 1)
      {
         j = 1000;
      }
      if (pseudo[i] <= 'Z' && pseudo[i] >= 'A')
      {
         SDL_BlitSurface(s_pseudo[pseudo[i]-64], NULL, surface, &poschiffr);
      }
      else if (pseudo[i] > 96 && pseudo[i] < 123)
      {
         SDL_BlitSurface(s_pseudo[pseudo[i]-70], NULL, surface, &poschiffr);
      }
      else if (pseudo[i] > 47 && pseudo[i] < 58)
      {
         SDL_BlitSurface(s_pseudo[pseudo[i]+5], NULL, surface, &poschiffr);
      }
      else if (pseudo[i] == 95)
      {
         SDL_BlitSurface(s_pseudo[65], NULL, surface, &poschiffr);
      }
      else if (pseudo[i] == 45)
      {
         SDL_BlitSurface(s_pseudo[64], NULL, surface, &poschiffr);
      }
      else if (pseudo[i] == 46)
      {
         SDL_BlitSurface(s_pseudo[63], NULL, surface, &poschiffr);
      }
      else
      {
         SDL_BlitSurface(s_pseudo[0], NULL, surface, &poschiffr);
      }
      i++;
      j++;
   }
}

int selectioncase (int x, int y)
{
    if (x > 211 || x < 8 || y < 227 || y > 241)
    {
       return 50;
    }
    if (x < 106)
    {
       return 1;
    }
    else if (x > 113)
    {
       return 2;
    }
    return 50;
}

int confirmefface (char* continuer)
{
    int i = 0, cadre = 1, mcadre = 0, ccadre = 0, ncadre = 0, clic = 0, okclic = 0, continuee = 2;
    SDL_Event event;
    SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
    SDL_FillRect(s_fondnoir, NULL, SDL_MapRGB(s_ecran->format, 0, 0, 0));
    poschiffr.x = 11;
    poschiffr.y = 80;
    poscadre.x = 72;
    poscadre.y = 139;
    posbutton.x = 74;
    posbutton.y = 141;
    while (i < 20)
    {
       SDL_SetAlpha(s_fondnoir, SDL_SRCALPHA, i*4);
       SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
       SDL_BlitSurface(s_fondnoir, NULL, s_ecran, &posfond);
       SDL_BlitSurface(s_fondconf, NULL, s_ecran, &poschiffr);
       if (clavier == 1)
       {
          SDL_BlitSurface(s_cadreconf, NULL, s_ecran, &poscadre);
       }
       SDL_Flip(s_ecran);
       SDL_Delay(10);
       SDL_PollEvent(&event);
       i++;
    }
    while (continuee == 2)
    {
       SDL_PollEvent(&event);
       SDL_Delay(10);
       mcadre = trouveconf(event.motion.x, event.motion.y);
       if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
       {
          continuee++;
          (*continuer)++;
       }
       else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
       {
           ccadre = trouveconf(event.button.x, event.button.y);
           clavier = 0;
           if (ccadre != 50 && clic == 0)
           {
              okclic = ccadre;
           }
           clic = 1;
       }
       else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
       {
          ncadre = trouveconf(event.motion.x, event.motion.y);
          if (ncadre != 50 && ncadre == okclic)
          {
             continuee = 2 - ncadre;
          }
          clic = 0;
          ccadre = 50;
          okclic = 50;
       }
       else if (event.type == SDL_KEYDOWN)
       {
          clavier = 1;
          if (event.key.keysym.sym == SDLK_LEFT)
          {
             cadre = 1;
          }
          else if (event.key.keysym.sym == SDLK_RIGHT)
          {
             cadre = 2;
          }
          else if (event.key.keysym.sym == SDLK_o || event.key.keysym.sym == SDLK_y || (cadre == 1 && (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)))
          {
             continuee = 1;
             cadre = 1;
          }
          else if (event.key.keysym.sym == SDLK_n || (cadre == 2 && (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)))
          {
             continuee = 0;
             cadre = 2;
          }
       }
       SDL_BlitSurface(s_fondconf, NULL, s_ecran, &poschiffr);
       if (clavier == 1 && cadre != 0)
       {
          poscadre.x = 72 + (cadre-1)*38;
          SDL_BlitSurface(s_cadreconf, NULL, s_ecran, &poscadre);
       }
        if (okclic != 0 && okclic != 50)
        {
           posbutton.x = 74 + 38*(okclic - 1);
           SDL_BlitSurface(s_mboutenf, NULL, s_ecran, &posbutton);
        }
        if (mcadre != 50)
        {
           posbutton.x = 74 + 38*(mcadre-1);
           SDL_BlitSurface(s_mboutsurv, NULL, s_ecran, &posbutton);
        }
        if (okclic == mcadre && mcadre != 50)
        {
           posbutton.x = 74 + 38*(mcadre-1);
           SDL_BlitSurface(s_mboutsurvenf, NULL, s_ecran, &posbutton);
        }
       SDL_BlitSurface(s_texted, NULL, s_ecran, &poschiffr);
       SDL_Flip(s_ecran);
    }
    return continuee;
}

int trouveconf(int x, int y)
{
   if (x < 74 || y < 141 || y > 158 || x > 144)
   {
      return 50;
   }
   if (x < 107)
   {
      return 1;
   }
   if (x > 111)
   {
      return 2;
   }
   return 50;
}

SDL_Surface* PJ_SDL_Load(char nomfichier[])
{
   int i = 0, j = 0, couleur, lol = 0;
   unsigned char w, ww, hh, h, r, g, b;
   SDL_Rect clip_rect;
   SDL_Surface* load;
   SDL_PixelFormat* format;
   FILE* image;
   image = fopen(nomfichier, "r");
   if (image != NULL)
   {
      fscanf(image, "%c%c%c%c", &w, &ww, &h, &hh);
      w = w*256 + ww;
      h = h*256 + hh;
      load = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
      while (i < h && load != NULL)
      {
         while (j < w)
         {
            fscanf(image, "%c%c%c", &r, &g, &b);
            couleur = 65536*r + 256*g + b;
            setPixel(load, j, i, couleur);
            j++;
         }
         j = 0;
         i++;
      }
      fclose(image);
      return load;
   }
   return NULL;
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void Infovers(char* continuer)
{
   SDL_Event event;
   SDL_Rect pospetit, posgrand;
   pospetit.x = 148;
   pospetit.y = 151;
   posgrand.x = 62;
   posgrand.y = 185;
   int i = 0, infovers = 1, cadre = 1, ccadre = 0, mcadre = 0, ncadre = 0, clic = 0, okclic = 0, appui = 0;
   SDL_BlitSurface(s_ecran, NULL, s_ecranjeu, &posfond);
   while (i < 25)
   {
      SDL_SetAlpha(s_infovers, SDL_SRCALPHA, i*10);
      SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
      SDL_BlitSurface(s_infovers, NULL, s_ecran, &posfond);
      if (azerty == 1)
      {
         SDL_BlitSurface(s_infbout, NULL, s_ecran, &pospetit);
         SDL_BlitSurface(s_azerty, NULL, s_ecran, &pospetit);
      }
      if (clavier == 1)
      {
         SDL_BlitSurface(s_cadre, NULL, s_ecran, &posgrand);
      }
      SDL_PollEvent(&event);
      SDL_Flip(s_ecran);
      SDL_Delay(10);
      i++;
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
      {
         i = 1355;
         (*continuer)++;
         infovers = 333;
      }
      if (i == 25)
      {
         SDL_SetAlpha(s_infovers, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
         SDL_BlitSurface(s_ecranjeu, NULL, s_ecran, &posfond);
         SDL_BlitSurface(s_infovers, NULL, s_ecran, &posfond);
         if (azerty == 1)
         {
            SDL_BlitSurface(s_infbout, NULL, s_ecran, &pospetit);
            SDL_BlitSurface(s_azerty, NULL, s_ecran, &pospetit);
         }
         if (clavier == 1)
         {
            SDL_BlitSurface(s_cadre, NULL, s_ecran, &posgrand);
         }
         SDL_Flip(s_ecran);
         SDL_Delay(10);
      }
   }
   while (infovers == 1)
   {
       SDL_PollEvent(&event);
       SDL_Delay(10);
       mcadre = trouveinf(event.motion.x, event.motion.y);
       if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
       {
          (*continuer)++;
          infovers = 0;
       }
       else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
       {
           ccadre = trouveinf(event.button.x, event.button.y);
           clavier = 0;
           if (ccadre != 50 && clic == 0)
           {
              okclic = ccadre;
           }
           clic = 1;
       }
       else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
       {
          ncadre = trouveinf(event.motion.x, event.motion.y);
          if (ncadre == 1 && ncadre == okclic)
          {
             infovers = 0;
          }
          else if (ncadre == 2 && ncadre == okclic)
          {
             azerty = 1 - azerty;
          }
          clic = 0;
          ccadre = 50;
          okclic = 50;
       }
       else if (event.type == SDL_KEYUP)
       {
          appui = 0;
       }
       else if (event.type == SDL_KEYDOWN && appui == 0)
       {
          clavier = 1;
          if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_4)
          {
             cadre = 1;
             appui = 1;
          }
          else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_KP6 || event.key.keysym.sym == SDLK_6)
          {
             cadre = 2;
             appui = 1;
          }
          else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_SPACE)
          {
             if (cadre == 1)
             {
                infovers = 0;
             }
             else if (cadre == 2)
             {
                azerty = 1 - azerty;
                appui = 1;
             }
          }
       }
       SDL_BlitSurface(s_boutton2, NULL, s_ecran, &posgrand);
       SDL_BlitSurface(s_infbout, NULL, s_ecran, &pospetit);
       if (mcadre != 50)
       {
          if (mcadre == 1)
          {
             SDL_BlitSurface(s_boutsurv, NULL, s_ecran, &posgrand);
          }
          else if (mcadre == 2)
          {
             SDL_BlitSurface(s_infboutsurv, NULL, s_ecran, &pospetit);
          }
       }
       if (okclic != 50 && okclic != 0)
       {
          if (okclic == 1)
          {
             SDL_BlitSurface(s_bouttondown, NULL, s_ecran, &posgrand);
          }
          else if (okclic == 2)
          {
             SDL_BlitSurface(s_infboutenf, NULL, s_ecran, &pospetit);
          }
       }
       if (mcadre == okclic && mcadre != 50)
       {
          if (mcadre == 1)
          {
             SDL_BlitSurface(s_boutdownsurv, NULL, s_ecran, &posgrand);
          }
          else if (mcadre == 2)
          {
             SDL_BlitSurface(s_infboutsurvenf, NULL, s_ecran, &pospetit);
          }
       }
       SDL_BlitSurface(s_menuprinc, NULL, s_ecran, &posgrand);
       if (azerty == 1)
       {
          SDL_BlitSurface(s_azerty, NULL, s_ecran, &pospetit);
       }
       else if (azerty == 0)
       {
          SDL_BlitSurface(s_qwerty, NULL, s_ecran, &pospetit);
       }
       if (clavier == 1)
       {
          if (cadre == 1)
          {
             SDL_BlitSurface(s_cadre, NULL, s_ecran, &posgrand);
          }
          else if (cadre == 2)
          {
             SDL_BlitSurface(s_cadrinf, NULL, s_ecran, &pospetit);
          }
       }
       SDL_Flip(s_ecran);
   }
}

int trouveinf(int x, int y)
{
    if (x > 148 && y > 151 && x < 204 && y < 167)
    {
       return 2;
    }
    if (x > 62 && y > 185 && x < 161 && y < 201)
    {
       return 1;
    }
    return 50;
}

int freeimages (void)
{
    int i = 0, j = 0;
    if (s_infovers != NULL)
    {
       SDL_FreeSurface(s_infovers);
       i++;
    }
    if (s_fond != NULL)
    {
       SDL_FreeSurface(s_fond);
       i++;
    }
    if (s_fond2 != NULL)
    {
       SDL_FreeSurface(s_fond2);
       i++;
    }
    if (s_fond3 != NULL)
    {
       SDL_FreeSurface(s_fond3);
       i++;
    }
    if (s_boutton != NULL)
    {
       SDL_FreeSurface(s_boutton);
       i++;
    }
    if (s_boutton2 != NULL)
    {
       SDL_FreeSurface(s_boutton2);
       i++;
    }
    if (s_bouttondown != NULL)
    {
       SDL_FreeSurface(s_bouttondown);
       i++;
    }
    if (s_boutdownsurv != NULL)
    {
       SDL_FreeSurface(s_boutdownsurv);
       i++;
    }
    if (s_boutsurv != NULL)
    {
       SDL_FreeSurface(s_boutsurv);
       i++;
    }
    if (s_mbout != NULL)
    {
       SDL_FreeSurface(s_mbout);
       i++;
    }
    if (s_mboutenf != NULL)
    {
       SDL_FreeSurface(s_mboutenf);
       i++;
    }
    if (s_mboutsurv != NULL)
    {
       SDL_FreeSurface(s_mboutsurv);
       i++;
    }
    if (s_mboutsurvenf != NULL)
    {
       SDL_FreeSurface(s_mboutsurvenf);
       i++;
    }
    if (s_cadreconf != NULL)
    {
       SDL_FreeSurface(s_cadreconf);
       i++;
    }
    if (s_infbout != NULL)
    {
       SDL_FreeSurface(s_infbout);
       i++;
    }
    if (s_infboutenf != NULL)
    {
       SDL_FreeSurface(s_infboutenf);
       i++;
    }
    if (s_infboutsurv != NULL)
    {
       SDL_FreeSurface(s_infboutsurv);
       i++;
    }
    if (s_infboutsurvenf != NULL)
    {
       SDL_FreeSurface(s_infboutsurvenf);
       i++;
    }
    if (s_cadrinf != NULL)
    {
       SDL_FreeSurface(s_cadrinf);
       i++;
    }
    if (s_fondconf != NULL)
    {
       SDL_FreeSurface(s_fondconf);
       i++;
    }
    if (s_textea != NULL)
    {
       SDL_FreeSurface(s_textea);
       i++;
    }
    if (s_texteb != NULL)
    {
       SDL_FreeSurface(s_texteb);
       i++;
    }
    if (s_textec != NULL)
    {
       SDL_FreeSurface(s_textec);
       i++;
    }
    if (s_texted != NULL)
    {
       SDL_FreeSurface(s_texted);
       i++;
    }
    if (s_cadre != NULL)
    {
       SDL_FreeSurface(s_cadre);
       i++;
    }
    if (s_icone != NULL)
    {
       SDL_FreeSurface(s_icone);
       i++;
    }
    if (s_meilleurscore != NULL)
    {
       SDL_FreeSurface(s_meilleurscore);
       i++;
    }
    if (s_fondmeilleurscore != NULL)
    {
       SDL_FreeSurface(s_fondmeilleurscore);
       i++;
    }
    if (s_bleu0 != NULL)
    {
       SDL_FreeSurface(s_bleu0);
       i++;
    }
    if (s_bleu1 != NULL)
    {
       SDL_FreeSurface(s_bleu1);
       i++;
    }
    if (s_bleu2 != NULL)
    {
       SDL_FreeSurface(s_bleu2);
       i++;
    }
    if (s_bleu3 != NULL)
    {
       SDL_FreeSurface(s_bleu3);
       i++;
    }
    if (s_bleu4 != NULL)
    {
       SDL_FreeSurface(s_bleu4);
       i++;
    }
    if (s_bleu5 != NULL)
    {
       SDL_FreeSurface(s_bleu5);
       i++;
    }
    if (s_bleu6 != NULL)
    {
       SDL_FreeSurface(s_bleu6);
       i++;
    }
    if (s_bleu7 != NULL)
    {
       SDL_FreeSurface(s_bleu7);
       i++;
    }
    if (s_bleu8 != NULL)
    {
       SDL_FreeSurface(s_bleu8);
       i++;
    }
    if (s_bleu9 != NULL)
    {
       SDL_FreeSurface(s_bleu9);
       i++;
    }
    if (s_bleuno != NULL)
    {
       SDL_FreeSurface(s_bleuno);
       i++;
    }
    if (s_petit0 != NULL)
    {
       SDL_FreeSurface(s_petit0);
       i++;
    }
    if (s_petit1 != NULL)
    {
       SDL_FreeSurface(s_petit1);
       i++;
    }
    if (s_petit2 != NULL)
    {
       SDL_FreeSurface(s_petit2);
       i++;
    }
    if (s_petit3 != NULL)
    {
       SDL_FreeSurface(s_petit3);
       i++;
    }
    if (s_petit4 != NULL)
    {
       SDL_FreeSurface(s_petit4);
       i++;
    }
    if (s_petit5 != NULL)
    {
       SDL_FreeSurface(s_petit5);
       i++;
    }
    if (s_petit0n != NULL)
    {
       SDL_FreeSurface(s_petit0n);
       i++;
    }
    if (s_petit1n != NULL)
    {
       SDL_FreeSurface(s_petit1n);
       i++;
    }
    if (s_petit2n != NULL)
    {
       SDL_FreeSurface(s_petit2n);
       i++;
    }
    if (s_petit3n != NULL)
    {
       SDL_FreeSurface(s_petit3n);
       i++;
    }
    if (s_petit4n != NULL)
    {
       SDL_FreeSurface(s_petit4n);
       i++;
    }
    if (s_petit5n != NULL)
    {
       SDL_FreeSurface(s_petit5n);
       i++;
    }
    if (s_petit6n != NULL)
    {
       SDL_FreeSurface(s_petit6n);
       i++;
    }
    if (s_petit7n != NULL)
    {
       SDL_FreeSurface(s_petit7n);
       i++;
    }
    if (s_petit8n != NULL)
    {
       SDL_FreeSurface(s_petit8n);
       i++;
    }
    if (s_petit9n != NULL)
    {
       SDL_FreeSurface(s_petit9n);
       i++;
    }
    if (s_lvl0 != NULL)
    {
       SDL_FreeSurface(s_lvl0);
       i++;
    }
    if (s_lvl1 != NULL)
    {
       SDL_FreeSurface(s_lvl1);
       i++;
    }
    if (s_lvl2 != NULL)
    {
       SDL_FreeSurface(s_lvl2);
       i++;
    }
    if (s_lvl3 != NULL)
    {
       SDL_FreeSurface(s_lvl3);
       i++;
    }
    if (s_lvl4 != NULL)
    {
       SDL_FreeSurface(s_lvl4);
       i++;
    }
    if (s_lvl5 != NULL)
    {
       SDL_FreeSurface(s_lvl5);
       i++;
    }
    if (s_lvl6 != NULL)
    {
       SDL_FreeSurface(s_lvl6);
       i++;
    }
    if (s_lvl7 != NULL)
    {
       SDL_FreeSurface(s_lvl7);
       i++;
    }
    if (s_lvl8 != NULL)
    {
       SDL_FreeSurface(s_lvl8);
       i++;
    }
    if (s_lvl9 != NULL)
    {
       SDL_FreeSurface(s_lvl9);
       i++;
    }
    if (s_casejeu != NULL)
    {
       SDL_FreeSurface(s_casejeu);
       i++;
    }
    if (s_casejeudown != NULL)
    {
       SDL_FreeSurface(s_casejeudown);
       i++;
    }
    if (s_carte1 != NULL)
    {
       SDL_FreeSurface(s_carte1);
       i++;
    }
    if (s_carte2 != NULL)
    {
       SDL_FreeSurface(s_carte2);
       i++;
    }
    if (s_carte3 != NULL)
    {
       SDL_FreeSurface(s_carte3);
       i++;
    }
    if (s_carte4 != NULL)
    {
       SDL_FreeSurface(s_carte4);
       i++;
    }
    if (s_carte5 != NULL)
    {
       SDL_FreeSurface(s_carte5);
       i++;
    }
    if (s_bombe != NULL)
    {
       SDL_FreeSurface(s_bombe);
       i++;
    }
    if (s_casejeuno != NULL)
    {
       SDL_FreeSurface(s_casejeuno);
       i++;
    }
    if (s_cadrejeu != NULL)
    {
       SDL_FreeSurface(s_cadrejeu);
       i++;
    }
    if (s_ecranjeu != NULL)
    {
       SDL_FreeSurface(s_ecranjeu);
       i++;
    }
    if (s_fondjeu != NULL)
    {
       SDL_FreeSurface(s_fondjeu);
       i++;
    }
    if (s_fondniveau != NULL)
    {
       SDL_FreeSurface(s_fondniveau);
       i++;
    }
    if (s_fondnoir != NULL)
    {
       SDL_FreeSurface(s_fondnoir);
       i++;
    }
    if (s_vrainiveau != NULL)
    {
       SDL_FreeSurface(s_vrainiveau);
       i++;
    }
    if (s_best0 != NULL)
    {
       SDL_FreeSurface(s_best0);
       i++;
    }
    if (s_best1 != NULL)
    {
       SDL_FreeSurface(s_best1);
       i++;
    }
    if (s_best2 != NULL)
    {
       SDL_FreeSurface(s_best2);
       i++;
    }
    if (s_best3 != NULL)
    {
       SDL_FreeSurface(s_best3);
       i++;
    }
    if (s_best4 != NULL)
    {
       SDL_FreeSurface(s_best4);
       i++;
    }
    if (s_best5 != NULL)
    {
       SDL_FreeSurface(s_best5);
       i++;
    }
    if (s_best6 != NULL)
    {
       SDL_FreeSurface(s_best6);
       i++;
    }
    if (s_best7 != NULL)
    {
       SDL_FreeSurface(s_best7);
       i++;
    }
    if (s_best8 != NULL)
    {
       SDL_FreeSurface(s_best8);
       i++;
    }
    if (s_best9 != NULL)
    {
       SDL_FreeSurface(s_best9);
       i++;
    }
    if (s_coeur != NULL)
    {
       SDL_FreeSurface(s_coeur);
       i++;
    }
    if (s_nocoeur != NULL)
    {
       SDL_FreeSurface(s_nocoeur);
       i++;
    }
    if (s_cpseudo != NULL)
    {
       SDL_FreeSurface(s_cpseudo);
       i++;
    }
    if (s_confmeilfond != NULL)
    {
       SDL_FreeSurface(s_confmeilfond);
       i++;
    }
    if (s_confmeiltexte != NULL)
    {
       SDL_FreeSurface(s_confmeiltexte);
       i++;
    }
    if (s_confmeilbouton != NULL)
    {
       SDL_FreeSurface(s_confmeilbouton);
       i++;
    }
    if (s_confmeilboutonsurv != NULL)
    {
       SDL_FreeSurface(s_confmeilboutonsurv);
       i++;
    }
    if (s_confmeilboutondown != NULL)
    {
       SDL_FreeSurface(s_confmeilboutondown);
       i++;
    }
    if (s_confmeilboutondownsurv != NULL)
    {
       SDL_FreeSurface(s_confmeilboutondownsurv);
       i++;
    }
    if (s_confmeilcadre != NULL)
    {
       SDL_FreeSurface(s_confmeilcadre);
       i++;
    }
    if (s_qwerty != NULL)
    {
       SDL_FreeSurface(s_qwerty);
       i++;
    }
    if (s_azerty != NULL)
    {
       SDL_FreeSurface(s_azerty);
       i++;
    }
    if (s_menuprinc != NULL)
    {
       SDL_FreeSurface(s_menuprinc);
       i++;
    }
    while (j < 66)
    {
       if (s_pseudo[j] != NULL)
       {
          SDL_FreeSurface(s_pseudo[j]);
          i++;
       }
       j++;
    }
    return i;
}

int loadimages(int meilleurscore)
{
        FILE* error = NULL;
        error = fopen("error.txt", "w+");
        int i = 0, j = 0;
        if ((s_bouttondown = IMG_Load("images/autres/1.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/1.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/1.bmp: \t\t FAILURE\n");
            s_bouttondown = NULL;
        }
        if ((s_infboutenf = IMG_Load("images/autres/1a.png")) != NULL)
        {
           fprintf(error, "Load images/autres/1a.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/1a.png: \t\t FAILURE\n");
            s_infboutenf = NULL;
        }
        if ((s_boutton2 = IMG_Load("images/autres/2.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/2.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/2.bmp: \t\t FAILURE\n");
            s_boutton2 = NULL;
        }
        if ((s_infbout = IMG_Load("images/autres/2a.png")) != NULL)
        {
           fprintf(error, "Load images/autres/2a.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/2a.png: \t\t FAILURE\n");
            s_infbout = NULL;
        }
        if ((s_boutdownsurv = IMG_Load("images/autres/3.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/3.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/3.bmp: \t\t FAILURE\n");
            s_boutdownsurv = NULL;
        }
        if ((s_infboutsurvenf = IMG_Load("images/autres/3a.png")) != NULL)
        {
           fprintf(error, "Load images/autres/3a.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/3a.png: \t\t FAILURE\n");
            s_infboutsurvenf = NULL;
        }
        if ((s_boutsurv = IMG_Load("images/autres/4.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/4.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/4.bmp: \t\t FAILURE\n");
            s_boutsurv = NULL;
        }
        if ((s_infboutsurv = IMG_Load("images/autres/4a.png")) != NULL)
        {
           fprintf(error, "Load images/autres/4a.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/4a.png: \t\t FAILURE\n");
            s_infboutsurv = NULL;
        }
        if ((s_cadrejeu = IMG_Load("images/autres/cadrecarte.png")) != NULL)
        {
           fprintf(error, "Load images/autres/cadrecarte.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/cadrecarte.png: \t FAILURE\n");
            s_cadrejeu = NULL;
        }
        if ((s_cadre = IMG_Load("images/autres/cadrechoix.png")) != NULL)
        {
           fprintf(error, "Load images/autres/cadrechoix.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/cadrechoix.png: \t FAILURE\n");
            s_cadre = NULL;
        }
        if ((s_cadrinf = IMG_Load("images/autres/cadrechoixa.png")) != NULL)
        {
           fprintf(error, "Load images/autres/cadrechoixa.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/cadrechoixa.png: \t FAILURE\n");
            s_cadrinf = NULL;
        }
        if ((s_cadreconf = IMG_Load("images/autres/cadreconf.png")) != NULL)
        {
           fprintf(error, "Load images/autres/cadreconf.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/cadreconf.png: \t FAILURE\n");
            s_cadreconf = NULL;
        }
        if ((s_carte1 = IMG_Load("images/autres/carte1.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/carte1.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/carte1.bmp: \t\t FAILURE\n");
            s_carte1 = NULL;
        }
        if ((s_carte2 = IMG_Load("images/autres/carte2.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/carte2.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/carte2.bmp: \t\t FAILURE\n");
            s_carte2 = NULL;
        }
        if ((s_carte3 = IMG_Load("images/autres/carte3.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/carte3.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/carte3.bmp: \t\t FAILURE\n");
            s_carte3 = NULL;
        }
        if ((s_carte4 = IMG_Load("images/autres/carte4.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/carte4.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/carte4.bmp: \t\t FAILURE\n");
            s_carte4 = NULL;
        }
        if ((s_carte5 = IMG_Load("images/autres/carte5.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/carte5.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/carte5.bmp: \t\t FAILURE\n");
            s_carte5 = NULL;
        }
        if ((s_casejeu = IMG_Load("images/autres/casejeu.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/casejeu.bmp: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/casejeu.bmp: \t FAILURE\n");
            s_casejeu = NULL;
        }
        if ((s_casejeudown = IMG_Load("images/autres/casejeudown.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/casejeudown.bmp: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/casejeudown.bmp: \t FAILURE\n");
            s_casejeudown = NULL;
        }
        if ((s_casejeuno = IMG_Load("images/autres/casejeuno.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/casejeuno.bmp: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/casejeuno.bmp: \t FAILURE\n");
            s_casejeuno = NULL;
        }
        if ((s_coeur = IMG_Load("images/autres/coeur.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/coeur.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/coeur.bmp: \t\t FAILURE\n");
            s_coeur = NULL;
        }
        if ((s_icone = IMG_Load("images/autres/icong.png")) != NULL)
        {
           fprintf(error, "Load images/autres/icong.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/icong.png: \t\t FAILURE\n");
            s_icone = NULL;
        }
        if ((s_fondconf = IMG_Load("images/autres/metal.png")) != NULL)
        {
           fprintf(error, "Load images/autres/metal.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/metal.png: \t\t FAILURE\n");
            s_fondconf = NULL;
        }
        if ((s_mbout = IMG_Load("images/autres/metalbout.png")) != NULL)
        {
           fprintf(error, "Load images/autres/metalbout.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/metalbout.png: \t FAILURE\n");
            s_mbout = NULL;
        }
        if ((s_mboutenf = IMG_Load("images/autres/metalboutenf.png")) != NULL)
        {
           fprintf(error, "Load images/autres/metalboutenf.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/metalboutenf.png: \t FAILURE\n");
            s_mboutenf = NULL;
        }
        if ((s_mboutsurv = IMG_Load("images/autres/metalboutsurv.png")) != NULL)
        {
           fprintf(error, "Load images/autres/metalboutsurv.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/metalboutsurv.png: \t FAILURE\n");
            s_mboutsurv = NULL;
        }
        if ((s_mboutsurvenf = IMG_Load("images/autres/metalboutsurvenf.png")) != NULL)
        {
           fprintf(error, "Load images/autres/metalboutsurvenf.png: SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/metalboutsurvenf.png: FAILURE\n");
            s_mboutsurvenf = NULL;
        }
        if ((s_boutton = IMG_Load("images/autres/pleinbouton.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/pleinbouton.bmp: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/pleinbouton.bmp: \t FAILURE\n");
            s_boutton = NULL;
        }
        if ((s_bombe = IMG_Load("images/autres/radio.bmp")) != NULL)
        {
           fprintf(error, "Load images/autres/radio.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/autres/radio.bmp: \t\t FAILURE\n");
            s_bombe = NULL;
        }
        if ((s_best0 = IMG_Load("images/chiffres/best0.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best0.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best0.png: \t FAILURE\n");
            s_best0 = NULL;
        }
        if ((s_best1 = IMG_Load("images/chiffres/best1.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best1.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best1.png: \t FAILURE\n");
            s_best1 = NULL;
        }
        if ((s_best2 = IMG_Load("images/chiffres/best2.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best2.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best2.png: \t FAILURE\n");
            s_best2 = NULL;
        }
        if ((s_best3 = IMG_Load("images/chiffres/best3.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best3.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best3.png: \t FAILURE\n");
            s_best3 = NULL;
        }
        if ((s_best4 = IMG_Load("images/chiffres/best4.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best4.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best4.png: \t FAILURE\n");
            s_best4 = NULL;
        }
        if ((s_best5 = IMG_Load("images/chiffres/best5.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best5.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best5.png: \t FAILURE\n");
            s_best5 = NULL;
        }
        if ((s_best6 = IMG_Load("images/chiffres/best6.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best6.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best6.png: \t FAILURE\n");
            s_best6 = NULL;
        }
        if ((s_best7 = IMG_Load("images/chiffres/best7.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best7.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best7.png: \t FAILURE\n");
            s_best7 = NULL;
        }
        if ((s_best8 = IMG_Load("images/chiffres/best8.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best8.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best8.png: \t FAILURE\n");
            s_best8 = NULL;
        }
        if ((s_best9 = IMG_Load("images/chiffres/best9.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/best9.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/best9.png: \t FAILURE\n");
            s_best9 = NULL;
        }
        if ((s_bleu0 = IMG_Load("images/chiffres/bleu0.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu0.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu0.png: \t FAILURE\n");
            s_bleu0 = NULL;
        }
        if ((s_bleu1 = IMG_Load("images/chiffres/bleu1.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu1.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu1.png: \t FAILURE\n");
            s_bleu1 = NULL;
        }
        if ((s_bleu2 = IMG_Load("images/chiffres/bleu2.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu2.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu2.png: \t FAILURE\n");
            s_bleu2 = NULL;
        }
        if ((s_bleu3 = IMG_Load("images/chiffres/bleu3.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu3.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu3.png: \t FAILURE\n");
            s_bleu3 = NULL;
        }
        if ((s_bleu4 = IMG_Load("images/chiffres/bleu4.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu4.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu4.png: \t FAILURE\n");
            s_bleu4 = NULL;
        }
        if ((s_bleu5 = IMG_Load("images/chiffres/bleu5.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu5.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu5.png: \t FAILURE\n");
            s_bleu5 = NULL;
        }
        if ((s_bleu6 = IMG_Load("images/chiffres/bleu6.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu6.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu6.png: \t FAILURE\n");
            s_bleu6 = NULL;
        }
        if ((s_bleu7 = IMG_Load("images/chiffres/bleu7.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu7.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu7.png: \t FAILURE\n");
            s_bleu7 = NULL;
        }
        if ((s_bleu8 = IMG_Load("images/chiffres/bleu8.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu8.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu8.png: \t FAILURE\n");
            s_bleu8 = NULL;
        }
        if ((s_bleu9 = IMG_Load("images/chiffres/bleu9.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/bleu9.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/bleu9.png: \t FAILURE\n");
            s_bleu9 = NULL;
        }
        if ((s_lvl0 = IMG_Load("images/chiffres/lvl0.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl0.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl0.png: \t\t FAILURE\n");
            s_lvl0 = NULL;
        }
        if ((s_lvl1 = IMG_Load("images/chiffres/lvl1.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl1.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl1.png: \t\t FAILURE\n");
            s_lvl1 = NULL;
        }
        if ((s_lvl2 = IMG_Load("images/chiffres/lvl2.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl2.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl2.png: \t\t FAILURE\n");
            s_lvl2 = NULL;
        }
        if ((s_lvl3 = IMG_Load("images/chiffres/lvl3.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl3.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl3.png: \t\t FAILURE\n");
            s_lvl3 = NULL;
        }
        if ((s_lvl4 = IMG_Load("images/chiffres/lvl4.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl4.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl4.png: \t\t FAILURE\n");
            s_lvl4 = NULL;
        }
        if ((s_lvl5 = IMG_Load("images/chiffres/lvl5.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl5.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl5.png: \t\t FAILURE\n");
            s_lvl5 = NULL;
        }
        if ((s_lvl6 = IMG_Load("images/chiffres/lvl6.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl6.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl6.png: \t\t FAILURE\n");
            s_lvl6 = NULL;
        }
        if ((s_lvl7 = IMG_Load("images/chiffres/lvl7.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl7.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl7.png: \t\t FAILURE\n");
            s_lvl7 = NULL;
        }
        if ((s_lvl8 = IMG_Load("images/chiffres/lvl8.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl8.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl8.png: \t\t FAILURE\n");
            s_lvl8 = NULL;
        }
        if ((s_lvl9 = IMG_Load("images/chiffres/lvl9.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/lvl9.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/lvl9.png: \t\t FAILURE\n");
            s_lvl9 = NULL;
        }
        if ((s_petit0n = IMG_Load("images/chiffres/npetit0.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit0.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit0.png: \t FAILURE\n");
            s_petit0n = NULL;
        }
        if ((s_petit1n = IMG_Load("images/chiffres/npetit1.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit1.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit1.png: \t FAILURE\n");
            s_petit1n = NULL;
        }
        if ((s_petit2n = IMG_Load("images/chiffres/npetit2.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit2.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit2.png: \t FAILURE\n");
            s_petit2n = NULL;
        }
        if ((s_petit3n = IMG_Load("images/chiffres/npetit3.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit3.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit3.png: \t FAILURE\n");
            s_petit3n = NULL;
        }
        if ((s_petit4n = IMG_Load("images/chiffres/npetit4.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit4.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit4.png: \t FAILURE\n");
            s_petit4n = NULL;
        }
        if ((s_petit5n = IMG_Load("images/chiffres/npetit5.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit5.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit5.png: \t FAILURE\n");
            s_petit5n = NULL;
        }
        if ((s_petit6n = IMG_Load("images/chiffres/npetit6.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit6.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit6.png: \t FAILURE\n");
            s_petit6n = NULL;
        }
        if ((s_petit7n = IMG_Load("images/chiffres/npetit7.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit7.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit7.png: \t FAILURE\n");
            s_petit7n = NULL;
        }
        if ((s_petit8n = IMG_Load("images/chiffres/npetit8.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit8.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit8.png: \t FAILURE\n");
            s_petit8n = NULL;
        }
        if ((s_petit9n = IMG_Load("images/chiffres/npetit9.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/npetit9.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/npetit9.png: \t FAILURE\n");
            s_petit9n = NULL;
        }
        if ((s_petit0 = IMG_Load("images/chiffres/petit0.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit0.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit0.png: \t FAILURE\n");
            s_petit0 = NULL;
        }
        if ((s_petit1 = IMG_Load("images/chiffres/petit1.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit1.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit1.png: \t FAILURE\n");
            s_petit1 = NULL;
        }
        if ((s_petit2 = IMG_Load("images/chiffres/petit2.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit2.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit2.png: \t FAILURE\n");
            s_petit2 = NULL;
        }
        if ((s_petit3 = IMG_Load("images/chiffres/petit3.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit3.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit3.png: \t FAILURE\n");
            s_petit3 = NULL;
        }
        if ((s_petit4 = IMG_Load("images/chiffres/petit4.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit4.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit4.png: \t FAILURE\n");
            s_petit4 = NULL;
        }
        if ((s_petit5 = IMG_Load("images/chiffres/petit5.png")) != NULL)
        {
           fprintf(error, "Load images/chiffres/petit5.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/chiffres/petit5.png: \t FAILURE\n");
            s_petit5 = NULL;
        }
        if ((s_fondnoir = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 250, 32, 0, 0, 0, 0)) != NULL)
        {
           i++;
        }
        else
        {
            s_fondnoir = NULL;
        }
        if ((s_ecranjeu = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 250, 32, 0, 0, 0, 0)) != NULL)
        {
           i++;
        }
        else
        {
            s_ecranjeu = NULL;
        }
        if ((s_vrainiveau = SDL_CreateRGBSurface(SDL_HWSURFACE, 165, 84, 32, 0, 0, 0, 0)) != NULL)
        {
           i++;
        }
        else
        {
            s_vrainiveau = NULL;
        }
        if ((s_bleuno = SDL_CreateRGBSurface(SDL_HWSURFACE, 15, 20, 32, 0, 0, 0, 0)) != NULL)
        {
           i++;
        }
        else
        {
            s_bleuno = NULL;
        }
        if ((s_azerty = IMG_Load("images/fonds/azerty.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/azerty.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/azerty.png: \t\t FAILURE\n");
            s_azerty = NULL;
        }
        if ((s_fondmeilleurscore = IMG_Load("images/fonds/bestscore.bmp")) != NULL)
        {
           fprintf(error, "Load images/fonds/bestscore.bmp: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/bestscore.bmp: \t FAILURE\n");
            s_fondmeilleurscore = NULL;
        }
        if ((s_infovers = PJ_SDL_Load("images/fonds/infovers.PJ_SDL")) != NULL)
        {
           fprintf(error, "Load images/fonds/infovers.PJ_SDL: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/infovers.PJ_SDL: \t FAILURE\n");
            s_infovers = NULL;
        }
        if ((s_fond = IMG_Load("images/fonds/intro.bmp")) != NULL)
        {
           fprintf(error, "Load images/fonds/intro.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/intro.bmp: \t\t FAILURE\n");
            s_fond = NULL;
        }
        if ((s_fond2 = IMG_Load("images/fonds/intro2.bmp")) != NULL)
        {
           fprintf(error, "Load images/fonds/intro2.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/intro2.bmp: \t\t FAILURE\n");
            s_fond2 = NULL;
        }
        if ((s_fond3 = IMG_Load("images/fonds/intro3.bmp")) != NULL)
        {
           fprintf(error, "Load images/fonds/intro3.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/intro3.bmp: \t\t FAILURE\n");
            s_fond3 = NULL;
        }
        if ((s_fondjeu = IMG_Load("images/fonds/jeu.bmp")) != NULL)
        {
           fprintf(error, "Load images/fonds/jeu.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/jeu.bmp: \t\t FAILURE\n");
            s_fondjeu = NULL;
        }
        if ((s_menuprinc = IMG_Load("images/fonds/menuprinc.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/menuprinc.png: \t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/menuprinc.png: \t FAILURE\n");
            s_menuprinc = NULL;
        }
        if ((s_fondniveau = IMG_Load("images/fonds/niveau.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/niveau.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/niveau.png: \t\t FAILURE\n");
            s_fondniveau = NULL;
        }
        if ((s_qwerty = IMG_Load("images/fonds/qwerty.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/qwerty.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/qwerty.png: \t\t FAILURE\n");
            s_qwerty = NULL;
        }
        if ((s_textea = IMG_Load("images/fonds/texte.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/texte.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/texte.png: \t\t FAILURE\n");
            s_textea = NULL;
        }
        if ((s_texteb = IMG_Load("images/fonds/texteb.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/texteb.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/texteb.png: \t\t FAILURE\n");
            s_texteb = NULL;
        }
        if ((s_textec = IMG_Load("images/fonds/textec.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/textec.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/textec.png: \t\t FAILURE\n");
            s_textec = NULL;
        }
        if ((s_texted = IMG_Load("images/fonds/texted.png")) != NULL)
        {
           fprintf(error, "Load images/fonds/texted.png: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/fonds/texted.png: \t\t FAILURE\n");
            s_texted = NULL;
        }
        if ((s_nocoeur = SDL_CreateRGBSurface(SDL_HWSURFACE, 9, 9, 32, 0, 0, 0, 0)) != NULL)
        {
           i++;
        }
        else
        {
            s_nocoeur = NULL;
        }
        if ((s_meilleurscore = creerscore(meilleurscore)) != NULL)
        {
           i++;
        }
        else
        {
            s_meilleurscore = NULL;
        }
        loadpseudo();
        while (j < 66)
        {
           if (s_pseudo[j] != NULL)
           {
              if (j > 0)
              {
                 fprintf(error, "Load images/pseudos/%d%d.bmp: \t\t SUCCESS\n", j/10, j%10);
              }
              i++;
           }
           else
           {
              if (j > 0)
              {
                 fprintf(error, "Load images/pseudos/%d%d.bmp: \t\t FAILURE\n", j/10, j%10);
                 s_pseudo[j] = NULL;
              }
           }
           j++;
        }
        if ((s_cpseudo = SDL_LoadBMP("images/pseudos/cadre.bmp")) != NULL)
        {
           fprintf(error, "Load images/pseudos/cadre.bmp: \t\t SUCCESS\n");
           i++;
        }
        else
        {
            fprintf(error, "Load images/pseudos/cadre.bmp: \t\t FAILURE\n");
            s_cpseudo = NULL;
        }
        fclose(error);
        return i;
}


