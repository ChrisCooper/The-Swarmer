#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>
#include <time.h>

int quitGame();
int gameOptions();
int loadGame();
int newGame();
int toMenu();
int advanceCredits(int, float);
int fallingText();
int startGame();
int showCopyrights();

int main(int argc, char *argv[])
{
    allegro_init();        // Initialize Allegro
    install_keyboard(); // Initialize keyboard routines 
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 'a');
    set_color_depth(16); // Set the color depth
    set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024,768,0,0); // Change our graphics mode to 1024x768
    
    showCopyrights();
    toMenu(); 
    return 0;
}

int toMenu()
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
                newGame();
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
                return 0;
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


}END_OF_MAIN()


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

int gameOptions()
{
 BITMAP *optionsBackground = NULL;
 optionsBackground = load_bitmap("Options Background.bmp", NULL); // Load our picture
 BITMAP *optionsBuffer = NULL;
 optionsBuffer = create_bitmap(1024,768); //Create an empty bitmap.
 
 draw_sprite(optionsBuffer, optionsBackground, 0, 0);
 blit(optionsBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
 readkey();
 return 0;
}

int loadGame()
{
 BITMAP *loadBackground = NULL;
 loadBackground = load_bitmap("Load Background.bmp", NULL); // Load our picture
 BITMAP *loadBuffer = NULL;
 loadBuffer = create_bitmap(1024,768); //Create an empty bitmap.
  
 draw_sprite(loadBuffer, loadBackground, 0, 0);
 blit(loadBuffer, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
 readkey();
 return 0;
}

int newGame()
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
    
    
 
return 0;

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

int fallingText()
{
      
     BITMAP *blackBackground = NULL;
     blackBackground = load_bitmap("Black Background.bmp", NULL); // Load our picture
     BITMAP *blackBuffer = NULL;
     blackBuffer = create_bitmap(1024,768); //Create an empty bitmap.
     BITMAP *text = NULL;
     text = load_bitmap("Falling Text.bmp", NULL); // Load our picture

     float textPositionY[20];
     float textPositionX[20];
     int i = 0;
     int j = 0;

     for (i = 0; i <= 19; i++)
     {
         textPositionX[i] = rand() %1000 - 500;
         textPositionY[i] = rand() %1000 - 500;
     }

     keypressed();

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

int showCopyrights()
{
 BITMAP *copyrights = NULL;
    copyrights = load_bitmap("Copyrights.bmp", NULL);
    blit(copyrights, screen, 0,0,0,0,1024,768);//Draw the buffer to the screen
    sleep(1000);
    readkey();
}


//int startGame()
