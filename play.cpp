//UNDER DEVELOPMENT


#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>

int health=5;

//detect clash between Jet and alienship
bool isClashAlienShip(sf::RectangleShape &jet,sf::RectangleShape &alienship){
    sf::Vector2f jetPos=jet.getPosition();
    sf::Vector2f alienshipPos=alienship.getPosition();
    return ((jetPos.x>alienshipPos.x && jetPos.x<alienshipPos.x+100) && (jetPos.y>alienshipPos.y && jetPos.y<alienshipPos.y+100));
}

//detect clash with fireball
bool isClashFireball(sf::RectangleShape &jet, sf::RectangleShape &ball){
    sf::Vector2f jetPos=jet.getPosition();
    sf::Vector2f ballPos=ball.getPosition();
    return ((jetPos.x>=ballPos.x && jetPos.x<=ballPos.x+70) && (jetPos.y>=ballPos.y && jetPos.y<ballPos.y+70));
}

//detect power star hit
bool isPowerStarHit(sf::RectangleShape &jet, sf::RectangleShape &power){
    sf::Vector2f jetPos=jet.getPosition();
    sf::Vector2f powerPos=power.getPosition();
    return ((jetPos.x>powerPos.x && jetPos.x<powerPos.x+50) && (jetPos.y>=powerPos.y && jetPos.y<powerPos.y+50));
}


//check if object has reached window boundary
bool hasReachedBoundary(sf::RectangleShape &obj){
    sf::Vector2f objPos=obj.getPosition();
    return (objPos.y>590);
}

//detect missile hit alienship
bool missileHitAlienship(sf::RectangleShape &missile,sf::RectangleShape &alienship){
    sf::Vector2f missilePos=missile.getPosition();
    sf::Vector2f alienshipPos=alienship.getPosition();
    return ((missilePos.x>alienshipPos.x && missilePos.x<alienshipPos.x+150) && (missilePos.y>alienshipPos.y && missilePos.y<alienshipPos.y+150));
}



int main(){
    /*
    //Texture (background)
    sf::Texture background;
    background.loadFromFile("images/background.png");
    //Rectangular shape for background
     sf::RectangleShape recBackground;
    recBackground.setSize(sf::Vector2f(750,600));
    recBackground.setPosition(0,0);
    recBackground.setTexture(&background);
    */


    //Texture (Health)
    sf::Texture healthIcon;
    healthIcon.loadFromFile("images/health.png");
    //RectangularShape for Health
     sf::RectangleShape recHealth;
    recHealth.setSize(sf::Vector2f(30,30));
    recHealth.setTexture(&healthIcon);

    //Texture (Jet stage 01)
    sf::Texture jet01;
    jet01.loadFromFile("images/jet_01.png");
    //RectangularShape for Jet stage 01
     sf::RectangleShape recJet;
    recJet.setSize(sf::Vector2f(70,70));
    recJet.setPosition(375,500);
    recJet.setTexture(&jet01);

     //Texture (Missile 01)
    sf::Texture missileIcon;
    missileIcon.loadFromFile("images/missile_01.png");
    //RectangularShape for Jet stage 01
     sf::RectangleShape recMissile;
    recMissile.setSize(sf::Vector2f(0,0));
    recMissile.setTexture(&missileIcon);

    //Texture (Enemy 01)
    sf::Texture alienShipIcon;
    alienShipIcon.loadFromFile("images/enemy_01.png");
    //RectangularShape for Alienship stage 01

    //container for all alienship
    sf::RectangleShape recAlienShip;
    recAlienShip.setPosition(500,0);
    recAlienShip.setSize(sf::Vector2f(150,150));
    recAlienShip.setTexture(&alienShipIcon);


     //Texture (Blast fire 01)
    sf::Texture blastIcon;
    blastIcon.loadFromFile("images/blast01.png");
    //RectangularShape for Alienship stage 01
     sf::RectangleShape recBlast;
    recBlast.setSize(sf::Vector2f(40,40));
    recBlast.setTexture(&blastIcon);

    //Texture (rock 01)
    sf::Texture rockIcon;
    rockIcon.loadFromFile("images/rock_01.png");
    //RectangularShape for Rock stage 01
     sf::RectangleShape recRock;
    recRock.setSize(sf::Vector2f(70,70));
    recRock.setPosition(100,50);
    recRock.setTexture(&rockIcon);

    //Texture (fireball 01)
    sf::Texture fireballIcon;
    fireballIcon.loadFromFile("images/fireball_01.png");
    //RectangularShape for fireball (right side)
    sf::RectangleShape recFireball;
    recFireball.setSize(sf::Vector2f(70,50));
    recFireball.setPosition(650,0);
    recFireball.setTexture(&fireballIcon);


    //RectangularShape for fireball (Left side)
    sf::RectangleShape recFireball02;
    recFireball02.setSize(sf::Vector2f(70,50));
    recFireball02.setPosition(150,0);
    recFireball02.setTexture(&fireballIcon);

    //Texture for power star
    sf::Texture powerStarIcon;
    powerStarIcon.loadFromFile("images/power.png");
    //RectangularShape for Powerstar
    sf::RectangleShape recPowerStar;
    recPowerStar.setTexture(&powerStarIcon);

    //Texture Missile hit blast
    sf::Texture missileHitIcon;
    missileHitIcon.loadFromFile("images/missileBlast.png");
    //RectangleShape for missile hit
    sf::RectangleShape recMissileHit;
    recMissileHit.setSize(sf::Vector2f(70,70));
    recMissileHit.setTexture(&missileHitIcon);

//main window
    sf::RenderWindow window(sf::VideoMode(800,630), "Star-Fighters");
    bool missileFire=false;
    int i;
    int posX,posY;
    bool showPowerStar=false,powerHit=false;
    bool missileHit=false;

    long int powerCount=1;
    int alienHitCount=0;


    //Audio
    //alienship hit
    sf::Music alienShipHit;
    alienShipHit.openFromFile("audio/alienshipHit.wav");
    alienShipHit.setVolume(40);         // reduce the volume

     //missile  hit
    sf::Music missileFireLaunch;
    missileFireLaunch.openFromFile("audio/missileFire.wav");
    missileFireLaunch.setVolume(50);

     //explosion  effect
    sf::Music explosion;
    explosion.openFromFile("audio/explosion.wav");
    explosion.setVolume(40);



//GAME LOOP
    while (window.isOpen()){
        showPowerStar=false;
        window.clear(sf::Color::Black);
        recAlienShip.move(0,.03);
        recRock.move(0,0.05);
        recFireball.move(0,.1);
        recFireball02.move(0,0.1);
    //move missile if fired
        if(missileFire){
            recMissile.move(0,-0.25);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
        if (event.type == sf::Event::Closed){
            window.close();
            }
        }

        //key for jet movement
        sf::Vector2f jetPos=recJet.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                recJet.setPosition(jetPos.x,jetPos.y-.25);
                recAlienShip.move(0,.05);
                recRock.move(0,.25);
                recFireball.move(0,0.25);
                recFireball02.move(0,0.05);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            recJet.setPosition(jetPos.x,jetPos.y+.25);
            //recAlienShip.move(0,-2);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            recJet.setPosition(jetPos.x-.25,jetPos.y);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            recJet.setPosition(jetPos.x+.25,jetPos.y);
        }

        //Missile positioning
        //FIX SHIT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        missileFireLaunch.stop();
        missileFireLaunch.play();
        jetPos=recJet.getPosition();
        recMissile.setSize(sf::Vector2f(30,50));
        recMissile.setPosition(jetPos.x+20,jetPos.y-30);
        missileFire=true;
    }
    if(missileHitAlienship(recMissile,recAlienShip) && missileFire){
        alienShipHit.play();
        alienHitCount++;
        missileFire=false;
        recMissile.setSize(sf::Vector2f(0,0));
        sf::Vector2f alienShipPos=recAlienShip.getPosition();
        recMissileHit.setPosition(alienShipPos.x,alienShipPos.y+20);
    }
    if(alienHitCount>=5){
        recAlienShip.setSize(sf::Vector2f(0,0));
        missileHit=true;
    }
    if(missileHit){
        recAlienShip.move(0,+.5);
        recMissileHit.move(0,+.5);
        window.draw(recMissileHit);
    }

//jet and alien ship clash
    if(isClashAlienShip(recJet,recAlienShip)){
        recAlienShip.setTexture(&blastIcon);
        recJet.setPosition(375,500);
        health--;
        explosion.play();
    }
//jet and fireball clash
    if(isClashFireball(recJet,recFireball)){
        recFireball.setTexture(&blastIcon);
        recJet.setPosition(375,500);
        health--;
        explosion.play();

    }
    if(isClashFireball(recJet,recFireball02)){
        recFireball02.setTexture(&blastIcon);
        recJet.setPosition(375,500);
        health--;
        explosion.play();

    }

//show health
    for(int i=1;i<=health;i++){
        recHealth.setPosition(i*20,10);
        window.draw(recHealth);
    }
    if(hasReachedBoundary(recAlienShip)){
        recAlienShip.setSize(sf::Vector2f(150,150));
        recAlienShip.setPosition(jetPos.x-10,-10);
        recAlienShip.setTexture(&alienShipIcon);
        missileHit=false;
        alienHitCount=0;
    }
    if(hasReachedBoundary(recRock)){
        recRock.setPosition(jetPos.x+20,0);
        posX=std::rand()%700;
        posY=std::rand()%500;
        recPowerStar.setSize(sf::Vector2f(50,50));
        recPowerStar.setPosition(posX,posY);
        powerHit=false;
    }
    if(!powerHit){
            showPowerStar=true;
        }
    if(hasReachedBoundary(recFireball)){
        recFireball.setPosition(650,0);
        recFireball.setTexture(&fireballIcon);

    }
    if(hasReachedBoundary(recFireball02)){
        recFireball02.setPosition(150,0);
        recFireball02.setTexture(&fireballIcon);
    }

//display power pack
    if(showPowerStar){
        window.draw(recPowerStar);
         if(isPowerStarHit(recJet,recPowerStar)){
                if(health<=9){
                    health++;
                    recPowerStar.setSize(sf::Vector2f(0,0));
                }
                powerHit=true;
            }
    }


//for clash with rock
    if(isClashFireball(recJet,recRock)){
        recJet.setPosition(375,500);
    }

        window.draw(recMissile);
        window.draw(recFireball02);
        window.draw(recFireball);
        window.draw(recRock);
        //window.draw(recBackground);
        window.draw(recAlienShip);
        //window.draw(recMissile);
        window.draw(recJet);
        window.display();

        }
    }



