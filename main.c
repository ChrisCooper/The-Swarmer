#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include <time.h>
#define NUMB 400
#define SNUMB 100
#define EXPLOSIONS 50
#define BACKGROUNDS 50
#define FALSE 0


int i = 0;
int j = 0;
int k = 0;
float turretX = 512;
float turretY = 384; 
int bulletNumber = NUMB - 1;
float bulletY[NUMB] = {0}; 
float bulletX[NUMB] = {0};
float bulletXVelocity[NUMB] = {0};
float bulletYVelocity[NUMB] = {0};
int bulletIsDead[NUMB] = {0};
int spiderNumber = SNUMB - 1;
int spiderMaker = 1;
int spiderCounter = 0;
int spiderLives[SNUMB] = {0};
float spiderY[SNUMB] = {0}; 
float spiderX[SNUMB] = {0};
float spiderXVelocity[SNUMB] = {0};
float spiderYVelocity[SNUMB] = {0};
int spiderIsDead[SNUMB] = {0};
float turretRotation = 0; // Holds the turret's rotation
int bulletCounter = -1;
int nextKey = 0;
int loopEnder =0;
int explosionCounter = EXPLOSIONS - 1; 
float explosionX[EXPLOSIONS];
float explosionY[EXPLOSIONS];
int spiderSpawner = 0;
int playerIsDead = 0;
int bulletsPierce = 0;
int slowMo = 1;
int sprayFire = 0;
float speedModifier = 2.5;
int bulletDamage = 1;
int playerInvincible = 1;
int playerCloak = 0;
int respawns = 0;
int bounceShot = 0;
float starSpinner = 0;
float score = 0;
int currentImage = 0;
int currentBackground = 0;
int bulletDelay = 0;
int fireSpeed = 7;
int isXenoPatriots = 0;

BITMAP *buffer = NULL; // Declare a BITMAP called buffer.
BITMAP *mouse = NULL;


int quitGame();
void gameOptions();
void loadGame();
void newGame();
void toMenu();
int advanceCredits(int, float);
void fallingText();
void startGame();
void showCopyrights();
void fire();
void playerLose();
void vertMoveTank(float, float);
void horzMoveTank(float, float);
void advanceTank(float, float, float, float);
int selectRace();

int main(int argc, char *argv[])
{
    allegro_init();        // Initialize Allegro
    install_keyboard(); // Initialize keyboard routines 
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(16); // Set the color depth
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024,768,0,0); // Change our graphics mode to 1024x768
    mouse = load_bitmap("Mouse.bmp", NULL);
    
    //showCopyrights();
    toMenu();
    //startGame();
    return 0;
}
END_OF_MAIN()

void toMenu()
{
    
    
    BITMAP *menuBuffer = NULL;
    menuBuffer = create_bitmap(1024,768); //Create an empty bitmap.
    BITMAP *menuBackground = NULL;
    menuBackground = load_bitmap("Menu Background.bmp", NULL); // Load our picture
    BITMAP *highlighter = NULL; 
    highlighter = load_bitmap("Menu Highlighter.bmp", NULL); // Load our picture
    BITMAP *smoke = NULL; 
    smoke = load_bitmap("Menu Smoke.bmp", NULL); // Load our picture

    MIDI *menuMusic = NULL;
    menuMusic = load_midi("Soundtrack1.mid");

    
    SAMPLE *menuClick = load_sample("Click.wav");

 
    clear_bitmap(menuBuffer); // Clear the contents of the buffer bitmap
    
    int highlightedOption = 1;
    int inMenu = 1;
    int smokePosition = 1024;
    int smokePosition2 = 1024;

    
    draw_sprite(menuBuffer, menuBackground, 0, 0);
    draw_sprite(menuBuffer, highlighter, 6, 186);
    blit(menuBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
    play_midi(menuMusic, 1);
    while (inMenu == 1)
    {
        draw_sprite(menuBuffer, menuBackground, 0, 0);
        
        smokePosition --;
        smokePosition2 -= 3;
        if (smokePosition <= -1024)
        {
           smokePosition = 0;
        }   

         
        readkey();
        
        if(key[KEY_UP]) 
        {
            play_sample(menuClick, 155, 0, 2000, 0);
            highlightedOption--;
            if (highlightedOption <= 0)
            {
               highlightedOption = 5;
            }
           
        }
        else if(key[KEY_DOWN])
        {
           play_sample(menuClick, 155, 0, 2000, 0);
           highlightedOption++;
            if (highlightedOption >= 6)
            {
               highlightedOption = 1;
            }  
        }   
        else if(key[KEY_ENTER])
        {
            play_sample(menuClick, 155, 0, 4000, 0);
            switch (highlightedOption)
            {
            case 1:
                isXenoPatriots = selectRace();
                newGame();
                startGame();
                play_midi(menuMusic, 1);
                break;
            case 2:
                loadGame();
                break;
            case 3:
                gameOptions();
                break;
            case 4:
                
                break;
            case 5:
                quitGame();
                inMenu ^= 0;
                return;
                
                break;
            }
         }

       
    
        switch (highlightedOption)
        {
            case 1:
                draw_sprite(menuBuffer, highlighter, 6, 186);
                break;
            case 2:
                draw_sprite(menuBuffer, highlighter, 6, 278);
                break;
            case 3:
                draw_sprite(menuBuffer, highlighter, 6, 373);
                break;
            case 4:
                draw_sprite(menuBuffer, highlighter, 6, 465);
                break;
            case 5:
                draw_sprite(menuBuffer, highlighter, 6, 629);
                break;
         }
         /*draw_sprite(menuBuffer, smoke, smokePosition, 0);
         draw_sprite(menuBuffer, smoke, smokePosition + 1024, 0);
         draw_sprite(menuBuffer, smoke, smokePosition2, 0);
         draw_sprite(menuBuffer, smoke, smokePosition2 + 1024, 0);*/
         blit(menuBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
         
     }  


}


int quitGame()
{
 BITMAP *quitBackground = NULL;
 quitBackground = load_bitmap("Quit Background.bmp", NULL); // Load our picture
 BITMAP *quitBuffer = NULL;
 quitBuffer = create_bitmap(1024,768); //Create an empty bitmap.
 
 
 MIDI *midSuspense = NULL;
 midSuspense = load_midi("Suspense.mid");
 MIDI *midResolve = NULL;
 midResolve = load_midi("Resolve.mid");

 draw_sprite(quitBuffer, quitBackground, 0, 0);
 blit(quitBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen

 play_midi(midSuspense, 1);
 readkey();
 play_midi(midResolve, 0);
 clear_bitmap(quitBuffer); // Clear the contents of the buffer bitmap
 blit(quitBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
 sleep(700);
 return 0;
}

void gameOptions()
{
 BITMAP *optionsBackground = NULL;
 optionsBackground = load_bitmap("Options Background.bmp", NULL); // Load our picture
 BITMAP *optionsBuffer = NULL;
 optionsBuffer = create_bitmap(1024,768); //Create an empty bitmap.
 
 draw_sprite(optionsBuffer, optionsBackground, 0, 0);
 blit(optionsBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
 readkey();
 return;
}

void loadGame()
{
 BITMAP *loadBackground = NULL;
 loadBackground = load_bitmap("Load Background.bmp", NULL); // Load our picture
 BITMAP *loadBuffer = NULL;
 loadBuffer = create_bitmap(1024,768); //Create an empty bitmap.
  
 draw_sprite(loadBuffer, loadBackground, 0, 0);
 blit(loadBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
 readkey();
 return;
}

void newGame()
{

    BITMAP *loadScreen = NULL;
    loadScreen = load_bitmap("Loading Screen.bmp", NULL); // Load our picture
    BITMAP *newBuffer = NULL;
    newBuffer = create_bitmap(1024,768); //Create an empty bitmap.


    float creditPosition = 1024;
    int aKey = -1;

    creditPosition = advanceCredits(0, creditPosition);
    creditPosition = advanceCredits(735, creditPosition);
    creditPosition = advanceCredits(1590, creditPosition);
    creditPosition = advanceCredits(2500, creditPosition);

    
    stop_midi();
    SAMPLE *transmission1 = load_sample("Transmission1.wav");
    play_sample(transmission1, 255, 0, 1000, 0);
    fallingText();
    stop_sample(transmission1);
    draw_sprite(newBuffer, loadScreen, 0, 0);
    blit(newBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
    
    while (!key[KEY_SPACE])
    {
          readkey();
    }
    
    
 
return;

}

int advanceCredits(int position, float creditPosition)
{
      
     BITMAP *credits1 = NULL;
     credits1 = load_bitmap("Intro Credits 1.bmp", NULL); // Load our picture
     BITMAP *newBuffer = NULL;
     newBuffer = create_bitmap(1024,768); //Create an empty bitmap.
     BITMAP *newBackground = NULL;
     newBackground = load_bitmap("Intro Background 1.bmp", NULL); // Load our picture
 
     while(!key[KEY_ESC] && creditPosition >= -position)
     {
         draw_sprite(newBuffer, newBackground, 0, 0);
         draw_sprite(newBuffer, credits1, 0, creditPosition);
         blit(newBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
         creditPosition -= 0.01*(creditPosition + position + 30);
     }
     readkey();
     clear_keybuf();
     return(creditPosition);
}

void fallingText()
{
      
     BITMAP *blackBackground = NULL;
     blackBackground = load_bitmap("Black Background.bmp", NULL); // Load our picture
     BITMAP *blackBuffer = NULL;
     blackBuffer = create_bitmap(1024,768); //Create an empty bitmap.
     BITMAP *text = NULL;
     text = load_bitmap("Falling Text.bmp", NULL); // Load our picture

     float textPositionY[40];
     float textPositionX[40];
     int i = 0;
     int j = 0;

     for (i = 0; i <= 39; i++)
     {
         textPositionX[i] = rand() %1000 - 500;
         textPositionY[i] = rand() %1000 - 500;
     }

     keypressed();

         while (j <= 2000 && !key[KEY_ESC])
         {
             j++;
             draw_sprite(blackBuffer, blackBackground, 0, 0);
             for (i = 0; i <= 39; i++)
             {
                  draw_sprite(blackBuffer, text, textPositionX[i], textPositionY[i]);
             }
             for (i = 0; i <= 39; i++)
             {
                 textPositionY[i] = textPositionY[i] + 0.01*(textPositionX[i]);
             }
            
             blit(blackBuffer, screen, 0,0,0,0,1024,768);
         }
         j = 0;
         while (j <= 2000 && !key[KEY_ESC])
         {
             j++;
             draw_sprite(blackBuffer, blackBackground, 0, 0);
             for (i = 0; i <= 19; i++)
             {
                  draw_sprite(blackBuffer, text, textPositionX[i], textPositionY[i]);
             }
             for (i = 0; i <= 19; i++)
             {
                 textPositionY[i] = textPositionY[i] - 0.01*(textPositionX[i]);
             }
            
             blit(blackBuffer, screen, 0,0,0,0,1024,768);
         }
        
     
     
 
}

void showCopyrights()
{
 BITMAP *copyrights = NULL;
    copyrights = load_bitmap("Copyrights.bmp", NULL);
    blit(copyrights, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
    sleep(1000);
    readkey();
}


void startGame()
{
    
    //allegro_init();        // Initialize Allegro
    //install_keyboard(); // Initialize keyboard routines 
    //set_color_depth(16); // Set the color depth
    //set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024,768,0,0); // Change our graphics mode to 1024x768
    BITMAP *turret = NULL; //Declare a BITMAP called my_pic, setting it to NULL
    turret = load_bitmap("Tank.bmp", NULL); // Load our picture
    
    buffer = create_bitmap(1024,768); //Create an empty bitmap.
    BITMAP *bullet = NULL;
    bullet = load_bitmap("Bullet.bmp", NULL);
    BITMAP *redical = NULL;
    redical = load_bitmap("Redical.bmp", NULL);
    BITMAP *explosion = NULL;
    explosion = load_bitmap("Explosion.bmp", NULL);
    BITMAP *spider[4] = {NULL};
    spider[0] = load_bitmap("Spider2.bmp", NULL); 
    spider[1] = load_bitmap("Spider2.bmp", NULL);
    spider[2] = load_bitmap("Spider1.bmp", NULL); 
    spider[3] = load_bitmap("Spider1.bmp", NULL);  
    BITMAP *wheel = NULL;
    wheel = load_bitmap("Wheel.bmp", NULL); 
    BITMAP *pierceBullet = NULL;
    pierceBullet = load_bitmap("PierceBullet.bmp", NULL); 
    BITMAP *tank = NULL;
    tank = load_bitmap("Bullet.bmp", NULL); 
    BITMAP *goldTurret = NULL;
    goldTurret = load_bitmap("InvincibleTurret.bmp", NULL); 
    BITMAP *star = NULL;
    star = load_bitmap("Star.bmp", NULL); 
    BITMAP *background;
    background = load_bitmap("Spider 3D.bmp", NULL); 
 

    SAMPLE *spiderDeath = load_sample("Explosion.wav");
    SAMPLE *ricochet1 = load_sample("Bullet Ricochet1.wav");
    SAMPLE *ricochet2 = load_sample("Bullet Ricochet2.wav");
    SAMPLE *ricochet3 = load_sample("Bullet Ricochet3.wav");
    SAMPLE *ricochet4 = load_sample("Bullet Ricochet4.wav");
    SAMPLE *ricochet5 = load_sample("Bullet Ricochet5.wav");
    SAMPLE *ricochet6 = load_sample("Bullet Ricochet6.wav");
    SAMPLE *ricochet7 = load_sample("Bullet Ricochet7.wav");
    SAMPLE *ricochet8 = load_sample("Bullet Ricochet8.wav");
   


    for (i = 0; i <= spiderNumber; i++)
    {
        spiderLives[i] = 2;
    }
    
        
    

    while(!key[KEY_ESC])//If the user hits escape, quit the program
    {
           while(playerIsDead != 1 && !key[KEY_ESC])
           {           
                     score = score + 0.01;                 
                     if (keypressed()) // If the user hits the space key, fire missile
                     { 
                                       nextKey = readkey();
                     }
                     else
                     {
                                       nextKey = -1;
                     }
                     
                     switch ((nextKey & 0xff))
                     {
                            case 'q':
                                slowMo ^= 1;
                                break;
                            case 'o':
                                respawns ^= 1;
                                break;
                            case 'w':
                                bulletsPierce ^= 1;
                                break;
                            case 'e':
                                sprayFire ^= 1;
                                break;
                            case 'r':
                                bounceShot ^= 1;
                                break;
                            case 't':
                                playerInvincible ^= 1;
                                break;
                            case 'y':
                                playerCloak ^= 1;
                                break;                                    
                    }
                    if(mouse_b & 1)
                    {
                                fire();
                                play_sample(spiderDeath, 155, 0, 2000, 0);
                    }
                    
                    bulletDelay++;
                    if(bulletDelay >= fireSpeed)
                    {
                       bulletDelay  = 0;
                    }
                    if(key[KEY_UP]) 
                    {
                        vertMoveTank(0, speedModifier);
  
                    }
                    else if(key[KEY_DOWN])
                    {
                        vertMoveTank(0, -speedModifier);
                    }
                    
                   
                    
                     if(key[KEY_RIGHT]) 
                     {
                        horzMoveTank(-speedModifier, 0);
                        
                     }
                     if(key[KEY_LEFT]) 
                     {
                       horzMoveTank(speedModifier, 0);
                     }
                   
                     
                     
                     
                     if (spiderMaker > 0 && spiderCounter < spiderNumber)
                     {
                        spiderSpawner = rand() % 4 + 1;
                        
                        if (spiderSpawner < 3)
                        {
                                          spiderX[spiderCounter] = rand()%984;
                                          spiderY[spiderCounter] = rand()%2;
                                          if (spiderY[spiderCounter] == 1)
                                          {   
                                             spiderY[spiderCounter] = 728;
                                          }
                                          else
                                          {   
                                             spiderY[spiderCounter] = 0;
                                          }
                        }
                        if (spiderSpawner >= 3)
                        {
                                          spiderY[spiderCounter] = rand()%728;
                                          spiderX[spiderCounter] = rand()%2;
                                          if (spiderX[spiderCounter] == 1)
                                          {   
                                             spiderX[spiderCounter] = 984;
                                          }
                                          else
                                          {   
                                             spiderX[spiderCounter] = 0;
                                          }
                        }
                        
                        spiderCounter++;
                     }
                     
                     for (i = 0; i <= spiderNumber; i++)
                     { 
                        /*if (playerCloak)
                        {
                           spiderXVelocity[i] =  0.001*(500 - spiderX[i]) + rand() %10 - 4.5;
                           spiderYVelocity[i] =  0.001*(350 - spiderY[i]) + rand() %10 - 4.5;
                        }
                        else
                        {
                            spiderXVelocity[i] = 0.003*(turretX - spiderX[i]) + rand() %10 - 4.5;
                            spiderYVelocity[i] = 0.003*(turretY - spiderY[i]) + rand() %10 - 4.5;
                        }*/
                        spiderXVelocity[i] = 0.003*(mouse_x - spiderX[i]) + rand() %10 - 4.5;
                        spiderYVelocity[i] = 0.003*(mouse_y - spiderY[i]) + rand() %10 - 4.5;
                     }
                     
                     for (i = 0; i <= spiderNumber; i++)
                     { 
                        spiderX[i] = spiderX[i] + spiderXVelocity[i];
                        spiderY[i] = spiderY[i] + spiderYVelocity[i];
                     }
                     
                     for (i = 0; i <= bulletNumber; i++)
                     { 
                        bulletX[i] = bulletX[i] + bulletXVelocity[i];
                        bulletY[i] = bulletY[i] + bulletYVelocity[i];
                     }
                     
                     clear_bitmap(buffer); // Clear the contents of the buffer bitmap
                     draw_sprite(buffer, background, 0, 0);
                     currentImage ++;
                     if (currentImage == 4)
                     {
                        currentImage = 0;
                     }
                     
                     for (i = 0; i <= bulletNumber; i++)
                     { 
                        if (bulletIsDead[i] != 1)
                        {
                                if ((bulletX[i] > 10 && bulletX[i] < 1014 && bulletY[i] > 10 && bulletY[i] < 758) && bulletIsDead[i] != 1)
                                {
                                   if (!bulletsPierce)
                                   {
                                                    draw_sprite(buffer, bullet, bulletX[i], bulletY[i]);
                                   }
                                   else
                                   {
                                                    draw_sprite(buffer, pierceBullet, bulletX[i], bulletY[i]);
                                   }

                                }

                                
                                
                                if (sprayFire)
                                {
                                    for (j = 0; j <= spiderCounter; j++)
                                    {
                                            if (spiderIsDead[j] != 1 && (bulletX[i] > spiderX[j] && bulletX[i] < spiderX[j] + 40))
                                            {
                                               if (spiderIsDead[j] != 1 && (bulletY[i] > spiderY[j] && bulletY[i] < spiderY[j] + 40))
                                               {
                                                  if (bulletsPierce == 0)
                                                  {
                                                        bulletIsDead[i] = 1;
                                                   }
                                                  draw_sprite(buffer, explosion, bulletX[i] - 30, bulletY[i] - 30);
                                                  play_sample(spiderDeath, 155, 0, 1000, 0); 
                                                  
                                                  spiderLives[j] = spiderLives[j] - 1;
                                                  
                                                  //if (spiderLives < 1)
                                                  //{
                                                     spiderIsDead[j] = 1;
                                                  //}
                                                     
                                                  
                                               }      
                                            }
                                    }
                                }
                                if (!(bulletX[i] > 10 && bulletX[i] < 1000 && bulletY[i] > 10 && bulletY[i] < 748))
                                {
                                   if (!bounceShot)
                                   {
                                      draw_sprite(buffer, explosion, bulletX[i] - 25, bulletY[i] - 25); 
                                      bulletIsDead[i] = 1;
                                      play_sample(spiderDeath, 255, 0, 1000, 0); 
                                      
                                   }
                                   else
                                   bulletXVelocity[i] = -bulletXVelocity[i];
                                   bulletYVelocity[i] = -bulletYVelocity[i];
                                   j = rand() %7 + 1;
                                   switch (j)
                                   {
                                            case 1:
                                                play_sample(ricochet1, 255, 0, 1000, 0); 
                                                break;
                                            case 2:
                                                play_sample(ricochet2, 255, 0, 1000, 0); 
                                                break;
                                            case 3:
                                                play_sample(ricochet3, 255, 0, 1000, 0); 
                                                break;
                                            case 4:
                                                play_sample(ricochet4, 255, 0, 1000, 0); 
                                                break;
                                            case 5:
                                                play_sample(ricochet5, 255, 0, 1000, 0); 
                                                break;
                                            case 6:
                                                play_sample(ricochet6, 255, 0, 1000, 0); 
                                                break;                                
                                            case 7:
                                                play_sample(ricochet7, 255, 0, 1000, 0);                                 
                                                break;
                                            case 8:
                                                play_sample(ricochet8, 255, 0, 1000, 0);                                 
                                                break;
                                            
                                  }
                                }
                                
                                
                        }
                     }
                     
                     if(respawns == 1)
                     {
                             for (i = 0; i <= spiderNumber; i++)
                             { 
                                    if (spiderIsDead[i] == 1)
                                    {
                                        spiderSpawner = rand() % 4 + 1;
                                        
                                        if (spiderSpawner < 3)
                                        {
                                          spiderX[i] = rand()%984;
                                          spiderY[i] = rand()%2;
                                          if (spiderY[i] == 1)
                                          {   
                                             spiderY[i] = 728;
                                          }
                                          else
                                          {   
                                             spiderY[i] = 0;
                                          }
                                        }
                                        if (spiderSpawner >= 3)
                                        {
                                          spiderY[i] = rand()%728;
                                          spiderX[i] = rand()%2;
                                          if (spiderX[i] == 1)
                                          {   
                                             spiderX[i] = 984;
                                          }
                                          else
                                          {   
                                             spiderX[i] = 0;
                                          }
                                        }  
                             
                                        spiderIsDead[i] = 0;
                                 
                                    }
                             } 
                     }
                     
                     starSpinner = starSpinner + 0.1;
                     if (starSpinner > 314)
                     {
                                     starSpinner = 0;
                     }
                     if (playerInvincible != 0)
                     {
                        draw_sprite(buffer, goldTurret, turretX, turretY);
                        draw_sprite(buffer, star, -35*cosf(starSpinner + 40) + turretX + 10, 35*sinf(starSpinner + 40) + turretY + 10);
                        draw_sprite(buffer, star, -35*cosf(starSpinner - 40) + turretX + 10, 35*sinf(starSpinner - 40) + turretY + 10);
                        draw_sprite(buffer, star, 35*cosf(starSpinner + 40) + turretX + 10, -35*sinf(starSpinner + 40) + turretY + 10);
                        draw_sprite(buffer, star, 35*cosf(starSpinner - 40) + turretX + 10, -35*sinf(starSpinner - 40) + turretY + 10);
                        
                     }
                     else
                     {
                         draw_sprite(buffer, turret, turretX, turretY);
                     }
                     
                     //draw_sprite(buffer, redical, 100*cosf(turretRotation) + turretX, -100*sinf(turretRotation) + turretY);
                     draw_sprite(buffer, redical, mouse_x - 10,mouse_y - 10);
                     draw_sprite(buffer, wheel, -25*cosf(turretRotation + 45) + turretX + 15, 25*sinf(turretRotation + 45) + turretY + 15);
                     draw_sprite(buffer, wheel, -25*cosf(turretRotation - 45) + turretX + 15, 25*sinf(turretRotation -45 ) + turretY + 15);
                     draw_sprite(buffer, wheel, 25*cosf(turretRotation + 45) + turretX + 15, -25*sinf(turretRotation + 45) + turretY + 15);
                     draw_sprite(buffer, wheel, 25*cosf(turretRotation - 45) + turretX + 15, -25*sinf(turretRotation - 45 ) + turretY + 15);
                     
                     
                     
                   
                     if (slowMo != 0)
                     {
                                sleep(6);  
                     }
                     
                     for (j = 0; j <= spiderCounter; j++)
                     {
                        if (spiderIsDead[j] != 1 && (turretX + 20 > spiderX[j] && turretX + 20 < spiderX[j] + 40))
                        {
                           if (spiderIsDead[j] != 1 && (turretY + 20 > spiderY[j] && turretY + 20 < spiderY[j] + 40))
                           {
                              if (playerInvincible != 1)
                              {  
                                   playerLose();
                                    sleep(2000);
                                    readkey();
                                    return;
                                   
                              }
                              else
                              {
                                  spiderIsDead[j] = 1;
                                  draw_sprite(buffer, explosion, spiderX[j], spiderY[j]); 
                                  score = score + 2;
                                  play_sample(spiderDeath, 255, 0, 1000, 0); 
                              }
                           }
                        }
                     }
                      
                     for (i = 0; i <= spiderNumber; i++)
                     { 
                            if (spiderIsDead[i] != 1)
                            {
                              draw_sprite(buffer, spider[currentImage], spiderX[i], spiderY[i]);
                            }
                     } 

                     blit(buffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
           }
             
     }
     
 
 return; // Exit with no errors
 
}




void fire()
{

     if (bulletDelay == 0)
     {
         if (bulletCounter >= bulletNumber)
         {
            bulletCounter = 0;
                    
            for (i = 0; i >= bulletNumber; i++)
            {
                bulletX[i] = 10000;
            }
         }
                
                
        bulletCounter++;
        bulletX[bulletCounter] = turretX + 15;
        bulletY[bulletCounter] = turretY + 15;
        bulletXVelocity[bulletCounter] = 5*(mouse_x - 20 - turretX)/sqrt((mouse_x - 20 - turretX)*(mouse_x - 20 - turretX) + (mouse_y - 20 - turretY)*(mouse_y - 20 - turretY));
        bulletYVelocity[bulletCounter] = 5*(mouse_y - 20 - turretY)/sqrt((mouse_x - 20 - turretX)*(mouse_x - 20 - turretX) + (mouse_y - 20 - turretY)*(mouse_y - 20 - turretY));
        bulletIsDead[bulletCounter] = 0;
    
        if (score > 0)
        {
                  score --;
        }
    }

}


void playerLose()
{

     
    SAMPLE *death = load_sample("Death.wav");
     
 
     BITMAP *loseBackground = NULL;
     loseBackground = load_bitmap("Spider Victor 3D.bmp", NULL); 
     BITMAP *explosion = NULL;
     explosion = load_bitmap("Explosion.bmp", NULL);
     BITMAP *spider = NULL;
     spider = load_bitmap("Spider1.bmp", NULL); 
     
     
  
     playerIsDead = 1;
     clear_bitmap(buffer);
     draw_sprite(buffer, loseBackground, 0, 0);     
     draw_sprite(buffer, explosion, turretX - 20, turretY - 20);
     draw_sprite(buffer, spider, spiderX[j], spiderY[j]);
     currentImage = 2;
     play_sample(death, 255, 0, 500, 0);
     return;
     
     


     
}
void vertMoveTank(float vX, float vY)
{
     int tempX = 0;
     int tempY = 0;
     
     tempX = turretX - speedModifier;
     tempY = turretY - speedModifier;
     if (vY > 0)
     {
         if (sin(turretRotation) >= 0.99)
        {

              advanceTank(tempX, tempY, -vX, -vY);
              
              turretRotation = asin(1);
        }
        else
        {
          if (cos(turretRotation) > 0)
            {
               turretRotation += 0.1;
            }
            else
            {
                turretRotation -= 0.1;
            }
        }
     }
     else
     {    
         if (sin(turretRotation) <= -0.99)
        {
              advanceTank(tempX, tempY, -vX, -vY);
              
              turretRotation = asin(-1);
        }
        else
        {
            if (cos(turretRotation) > 0)
            {
               turretRotation -= 0.1;
            }
            else
            {
                turretRotation += 0.1;
            }
        }
    }
    
}
void horzMoveTank(float vX, float vY)
{
     int tempX = 0;
     int tempY = 0;
     
     tempX = turretX - speedModifier;
     tempY = turretY - speedModifier;

     if (vX < 0)
     {
         if (cos(turretRotation) >= 0.99)
        {

              advanceTank(tempX, tempY, -vX, -vY);
              
              turretRotation = acos(1);
        }
        else
        {
          if (sin(turretRotation) > 0)
            {
               turretRotation -= 0.1;
            }
            else
            {
                turretRotation += 0.1;
            }
        }
     }
     else
     {    
         if (cos(turretRotation) <= -0.99)
        {
              advanceTank(tempX, tempY, -vX, -vY);
              
              turretRotation = acos(-1);
        }
        else
        {
            if (sin(turretRotation) > 0)
            {
               turretRotation += 0.1;
            }
            else
            {
                turretRotation -= 0.1;
            }
        }
    }
    
}


/*Moves the tank foreward once it is rotated into position*/
void advanceTank(float positionX, float positionY, float addX, float addY)
{
     if (positionX > 10 && positionX < 960)
      {
                turretX += addX; 
      }
      if (positionY > 10 && positionY < 708)
      {
                turretY += addY;
      }
      if (turretX < 13 || turretX > 957)
      {
                turretX += 0.01*(500 - turretX); 
      }
      if (turretY < 13 || turretY > 705)
      {
                turretY += 0.01*(350 - turretY); 
      }
}

int selectRace()
{
    BITMAP *raceBuffer = NULL;
    raceBuffer = create_bitmap(1024,768); //Create an empty bitmap.
    BITMAP *raceXeno = NULL;
    raceXeno = load_bitmap("Select Screen Xenopatriots.bmp", NULL); // Load our picture
    BITMAP *raceExped = NULL;
    raceExped = load_bitmap("Select Screen Expeditiones.bmp", NULL); // Load our picture
    while (!mouse_b)
          {
                   if (mouse_x > 518)
                   {
                      draw_sprite(raceBuffer, raceXeno, 0, 0);
                   }
                   else
                   {
                       draw_sprite(raceBuffer, raceExped, 0, 0);
                   }
                   draw_sprite(raceBuffer, mouse, mouse_x, mouse_y);
                   blit(raceBuffer, screen, 0,0,0,0,1024,768);
                   clear_bitmap(raceBuffer);
          }
          if (mouse_x > 380)
           {
              return 1;
           }
           else
           {
               return 0;
           }

}
