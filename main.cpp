#include "Pokitto.h"
#include "Synth.h"

Pokitto::Core pok;
Pokitto::Display display;
Pokitto::Sound snd;
Pokitto::Buttons btn;

int tonefreq=33;
uint8_t amplitude = 255;//127;
uint8_t wavetype = 1, arpmode=0;
uint32_t changed = 1;;
uint8_t sbindx=0,sbx=0,prevy=0;

bool titleEnd = false;
bool despa = true;
int showver = 0;
bool menu = true;
int notshown = 1;
int pause = 0;
int level;
bool ending = true;
bool levelstart;
int x1 = 10;
int x2 = 10;
int y1 = 80;
int y2 = 90;
int version1 = 1;
int versiondec = 0;
bool cheat = false;

void turtleLogo(){
    pok.display.clear();
    pok.display.setCursor(70,40);
    pok.display.print("Turtle");
    pok.display.setCursor(63, 70);
    pok.display.print("presents");
    pok.display.update();
    //snd.playTone(0,975,5, 590);
    wait(5);
    titleEnd = true;
    pok.display.clear();
}

void menuScreen(){//title
    display.clear();
    display.setCursor(40,10);
    display.print("Is this Loss?");
    display.setCursor(0 , 35);
    display.print("         THE GAME");
    //divide line down
    display.drawLine(105,70,105,127);
    //divide line right
    display.drawLine(77,99,135,99);
    //frame 1
    display.drawLine(87,95,87,78);
    //first person frame two
    display.drawLine(110,95,110,78);
    //second person frame two
    display.drawLine(120,95,120,85);
    //first person frame 3
    display.drawLine(82,124,82,107);
    //2 person frame 3
    display.drawLine(95,124,95,107);
    //1 person frame 4
    display.drawLine(110,124,110,107);
    //laid down persom frame 4
    display.drawLine(118,118,132,118);
    //does nothing until buttons are pressed
    display.update();
    while (btn.aBtn() == false){
       btn.pollButtons();
    }
    menu = false;
    display.clear();
}

void level1(){
    //clear display
    display.clear();
    btn.pollButtons();
    //draw door
    display.drawLine(157,79,157,90);
    display.drawLine(147,90,147,79);
    display.drawLine(147,78,157,78);
  //draw character based on choords
    display.drawLine(x1,y1,x2,y2);
    //move right
    if (btn.rightBtn()){
        x1 = x1 + 1;
        x2 = x2 + 1;
    }
    //move left
    if (btn.leftBtn()){
        x1 = x1 - 1;
        x2 = x2 - 1;
    }
    //pause menu
    if (btn.cBtn()){
        display.setCursor(50,30);
        display.print("Pause");
        display.update();
        wait(0.5);
        //makes it so it doesn't unpause automatically
        while (btn.aBtn() == false && btn.bBtn() == false && btn.cBtn() == false){
            //infinite waiting til it unpauses
            btn.pollButtons();
        }
        display.update();
        wait(0.5);
    }
    // off screen checks
    //right side
    if (x1 > 219){
        x1 = 218;
        x2 = 218;
        display.update();
    }
    //left side
    if (x1 < 0){
        x1 = 1;
        x2 = 1;
    }
    display.update();
    if(x1 > 147){
        if (x1 < 158){
            //advance the level with a
            if (btn.aBtn() || btn.bBtn() || btn.upBtn()){
                //sound.tone(500, 23);
                display.clear();
                display.update();
                level = 2;
                //move character back 100 pixels, because the door moves back
                //100 pixels
                x2 = x2 - 120;
                x1 = x1 - 120;
            }
        }
    }
}

void level2(){
    display.clear();
    //poll buttons
    btn.pollButtons();
    //drawdoor (130 less than last position)
    display.drawLine(27,79,27,90);
    display.drawLine(17,90,17,79);
    display.drawLine(17,78,27,78);
    //draw character based on choords
    display.drawLine(x1,y1,x2,y2);
    //draw hospital reception desk
    // move down
    display.drawLine(147,85,152,85);
    display.drawLine(147,85,147,90);
    display.drawLine(152,90,152,85);
    //draw receptionist
    display.drawLine(160,90,160,83);
    //move right
    if (btn.rightBtn()){
        x1 = x1 + 1;
        x2 = x2 + 1;
    }
    //move left
    if (btn.leftBtn()){
        x1 = x1 - 1;
        x2 = x2 - 1;
    }
    //detect position
    if (x1 < 147 && x1 > 140){
        if (btn.aBtn() || btn.bBtn() || btn.upBtn()){
            //sound.tone(500, 23);
            display.print("The doctor knows her");
            display.update();
            wait(0.5);
            while (!btn.aBtn() && !btn.bBtn() & !btn.cBtn() && !btn.upBtn()) { }
            //sound.tone(500, 23);
            display.clear();
            level = 3;
            x1 = 1;
            x2 = 1;
        }
    }
    //detect pause
    if (btn.cBtn()){
        //sound.tone(500,23);
        display.setCursor(50,30);
        display.print("Pause");
        wait(0.5);
        while (!btn.aBtn() && !btn.bBtn() & !btn.cBtn() && !btn.upBtn()) { }
    }
    //check if off right of reception
    if (x1 > 146){
        x1 = 146;
        x2 = 146;
  }
  //check if off left of the screen 
  if (x1 < 0){
    x1 = 1;
    x2 = 1;
  }
    display.update();
}
void level3(){
    display.clear();
    //draw character based on choords
    display.drawLine(x1,y1,x2,y2);
    //draw doctor based on choords
    display.drawLine(x1 + 5,y1 - 1,x2 + 5,y2);
    display.update();
    while (notshown == 1){
        display.clear();
        display.print("Here she lays );");
        display.update();
        wait(2.1);
        //Closes dialog
        if (btn.aBtn() || btn.bBtn){
            //sound.tone(500, 23);
            notshown = 0;
        }
  }
  //moves characters forward
  x1 = x1 + 2;
  x2 = x2 + 2;
  wait(0.1);
  if (x1 > 220){
    display.clear();
    x1 = 0;
    x2 = 0;
    level = 4;
  }
    display.update();
}

void playdespa(){
    snd.playTone(1,587,amplitude,wavetype,arpmode);
  //sound.tone(587, 500);
  //delay(500);
  //sound.tone(554, 300);
  //delay(300);
  //sound.tone(494, 250);
  //delay(255);
  //sound.tone(370, 250);
  //delay(250);
  
}
void restart(){
  display.clear();
  wait(0.2);
  titleEnd = false;
  despa = true;
  menu = 1;
  level = 0;
}

void level4(){
    display.clear();
    //draw character based on choords
    display.drawLine(x1,y1,x2,y2);
    //draw person2
    display.drawLine(55,55,65,55);
    //increase choords until at the bed
    for( ; x1 < 50; ){
        display.clear();
        x1 = x1 + 2;
        x2 = x2 + 2;
        display.drawLine(x1,y1,x2,y2);
        display.drawLine(55,85,65,85);
        display.update();
        wait(0.1);
    }
    display.print("So sad...");
    display.update();
    wait(1.5);
    display.setCursor(0,25);
    display.print("Alexa, ");
    display.setCursor(0,41);
    display.print("play despacito");
    display.update();
    display.clear();
    while(despa == true){
        playdespa();
        despa = false;
    }
    wait(0.2);
    while (!btn.aBtn() && !btn.bBtn()){}
    restart();
    display.update();
}

int main(){
    pok.begin();
    snd.setVolume(snd.getMaxVol());
    pok.display.persistence = true;
    pok.display.invisiblecolor = 0;
    display.fontSize = 2;
    display.setFont(font5x7);
    snd.ampEnable(1);
    snd.playTone(1,tonefreq,amplitude,wavetype,arpmode);
    while( pok.isRunning() ){
        if( !pok.update() ) 
            continue;
        snd.playTone(1,tonefreq,amplitude,wavetype,arpmode);
        tonefreq++;
        if (!titleEnd){
            turtleLogo();
        }
        if(menu){
            menuScreen();
        }
        level = 1;
        levelstart = true;
        switch (level){
            case 1: 
            while (level == 1) level1();
            case 2: 
            while (level == 2) level2();
            case 3: 
            while (level == 3) level3();
            case 4: 
            while (level ==4) level4();
            default: level = 1;
        }
    }
    
    return 0;
}
