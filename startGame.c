#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include <time.h>
#define NUMB 400
#define SNUMB 100
#define EXPLOSIONS 50
#define BACKGROUNDS 50

struct bullet{
    int x,y;
    int xV,yV;
    int visible;
    int colour;
};

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
struct bullet allBullets[NUMB];
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
int respawns = 0;
int bounceShot = 0;
float starSpinner = 0;
float score = 0;
int currentImage = 0;
int currentBackground = 0;
BITMAP *buffer = NULL; // Declare a BITMAP called buffer.


void fire();
void moveTurret(float);
void playerLose();

int startGame()
{
    
    allegro_init();        // Initialize Allegro
    install_keyboard(); // Initialize keyboard routines 
    set_color_depth(16); // Set the color depth
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024,768,0,0); // Change our graphics mode to 1024x768
    BITMAP *turret = NULL; //Declare a BITMAP called my_pic, setting it to NULL
    turret = load_bitmap("Turret.bmp", NULL); // Load our picture
    
    buffer = create_bitmap(1024,768); //Create an empty bitmap.
    BITMAP *bullet = NULL;
    bullet = load_bitmap("Bullet.bmp", NULL);
    BITMAP *redical = NULL;
    redical = load_bitmap("Redical.bmp", NULL);
    BITMAP *explosion = NULL;
    explosion = load_bitmap("Explosion.bmp", NULL);
    BITMAP *spider[4] = {NULL};
    spider[0] = load_bitmap("Spider2.bmp", NULL); 
    spider[1] = load_bitmap("SpiderEmpty.bmp", NULL);
    spider[2] = load_bitmap("Spider1.bmp", NULL); 
    spider[3] = load_bitmap("SpiderEmpty.bmp", NULL);  
    BITMAP *wheel = NULL;
    wheel = load_bitmap("Wheel.bmp", NULL); 
    BITMAP *pierceBullet = NULL;
    pierceBullet = load_bitmap("PierceBullet.bmp", NULL); 
    BITMAP *tank = NULL;
    tank = load_bitmap("Tank.bmp", NULL); 
    BITMAP *goldTurret = NULL;
    goldTurret = load_bitmap("InvincibleTurret.bmp", NULL); 
    BITMAP *star = NULL;
    star = load_bitmap("Star.bmp", NULL); 
    BITMAP *background;
    background = load_bitmap("Spider 3D.bmp", NULL); 

    
   
    

    
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
                            case ' ':
                                fire();                                
                                break;
                    }
                    if(key[KEY_UP]) 
                    {
                        moveTurret(speedModifier);
                        
                    }
                    else if(key[KEY_DOWN])
                    {
                        moveTurret(-speedModifier);
                    }
                    
                   
                    
                     if(key[KEY_RIGHT]) 
                     {
                                        turretRotation -= 0.02; 
                     }
                     if(key[KEY_LEFT]) 
                     {
                                        turretRotation += 0.02; 
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
                        spiderXVelocity[i] = 0.003*(turretX - spiderX[i]) + rand() %10 - 4.5;
                        spiderYVelocity[i] = 0.003*(turretY - spiderY[i]) + rand() %10 - 4.5;
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
                                              
                                              spiderLives[j] = spiderLives[j] - 1;
                                              
                                              //if (spiderLives < 1)
                                              //{
                                                 spiderIsDead[j] = 1;
                                              //}
                                                 
                                              
                                           }      
                                        }
                                }
                                
                                if (!(bulletX[i] > 10 && bulletX[i] < 970 && bulletY[i] > 10 && bulletY[i] < 718))
                                {
                                   if (!bounceShot)
                                   {
                                      draw_sprite(buffer, explosion, bulletX[i] - 25, bulletY[i] - 25); 
                                      bulletIsDead[i] = 1;
                                      
                                   }
                                   else
                                   bulletXVelocity[i] = -bulletXVelocity[i];
                                   bulletYVelocity[i] = -bulletYVelocity[i];
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
                     
                     draw_sprite(buffer, redical, 100*cosf(turretRotation) + turretX, -100*sinf(turretRotation) + turretY);
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
                                   
                              }
                              else
                              {
                                  spiderIsDead[j] = 1;
                                  draw_sprite(buffer, explosion, spiderX[j], spiderY[j]); 
                                  score = score + 2;
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
     
 
 return 0; // Exit with no errors
 
}
//END_OF_MAIN() //For Allegro, this must be called directly after the closing bracket of the main function.



void fire()
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
    bulletXVelocity[bulletCounter] = 4*(cosf(turretRotation));
    bulletYVelocity[bulletCounter] = 4*(-sinf(turretRotation));
    bulletIsDead[bulletCounter] = 0;
    if (sprayFire != 0) 
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
    bulletXVelocity[bulletCounter] = 4*(cosf(turretRotation + 0.4));
    bulletYVelocity[bulletCounter] = 4*(-sinf(turretRotation + 0.4));
    bulletIsDead[bulletCounter] = 0;
    }
    if (sprayFire != 0)
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
        bulletXVelocity[bulletCounter] = 4*(cosf(turretRotation - 0.4));
        bulletYVelocity[bulletCounter] = 4*(-sinf(turretRotation - 0.4));
        bulletIsDead[bulletCounter] = 0;
    }

    if (score > 0)
    {
              score --;
    }

}

void moveTurret(float angleCoef)
{
    float tempX;
    float tempY;
    tempX = turretX + angleCoef*cosf(turretRotation);
    tempY = turretY - angleCoef*sinf(turretRotation);
 
    if (tempX > 20 && tempX < 950)
    {
            turretX = tempX; 
    }
    if (tempY > 20 && tempY < 698)
    {
            turretY = tempY;
    }
}

void playerLose()
{

     
     BITMAP *loseBackground = NULL;
     loseBackground = load_bitmap("Spider Victor 3D.bmp", NULL); 
     BITMAP *explosion = NULL;
     explosion = load_bitmap("Explosion.bmp", NULL);
     BITMAP *spider = NULL;
     spider = load_bitmap("Spider1.bmp", NULL); 
     
     SAMPLE *death = load_sample("Death.wav");

     play_sample(death, 155, 0, 2000, 0);
  
     playerIsDead = 1;
     clear_bitmap(buffer);
     draw_sprite(buffer, loseBackground, 0, 0);     
     draw_sprite(buffer, explosion, turretX - 20, turretY - 20);
     draw_sprite(buffer, spider, spiderX[j], spiderY[j]);
     currentImage = 2;
     
     


     
}
