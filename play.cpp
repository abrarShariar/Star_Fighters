//UNDER DEVELOPMENT
//January 2016

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>

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

//check if object has crossed top window
bool hasReachedTop(sf::RectangleShape &obj){
    sf::Vector2f objPos=obj.getPosition();
    return (objPos.y<10);
}

//detect missile hit alienship
bool missileHitAlienship(sf::RectangleShape &missile,sf::RectangleShape &alienship){
    sf::Vector2f missilePos=missile.getPosition();
    sf::Vector2f alienshipPos=alienship.getPosition();
    return ((missilePos.x>alienshipPos.x && missilePos.x<alienshipPos.x+150) && (missilePos.y>alienshipPos.y && missilePos.y<alienshipPos.y+150));
}

//detect bomb hit
bool hasHitBomb(sf::RectangleShape &jet,sf::RectangleShape &bomb){
    sf::Vector2f bombPos=bomb.getPosition();
    sf::Vector2f jetPos=jet.getPosition();
    return ((bombPos.x>jetPos.x && bombPos.x<jetPos.x+100) && (bombPos.y>jetPos.y && bombPos.y<jetPos.y+100));
}

//detect missile hit alien jet
bool hasHitAlienJet(sf::RectangleShape &missile,sf::RectangleShape &alienJet){
     sf::Vector2f missilePos=missile.getPosition();
     sf::Vector2f alienPos=alienJet.getPosition();
     return ((missilePos.x>alienPos.x && missilePos.x<missilePos.x+100) && (missilePos.y>alienPos.y && missilePos.y<alienPos.y+100));
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

     //load font
    sf::Font font;
    font.loadFromFile("font/Timeless.ttf");
    std::string gameText="Destroy Alien Ships to Earn Sliver Wings";
    //text for displaying game directions
    sf::Text gameDirection(gameText,font);
    gameDirection.setCharacterSize(15);
    gameDirection.setPosition(300,5);
    gameDirection.setColor(sf::Color::Red);



    //Text for achievement text
    sf::Text achieveText;
    achieveText.setFont(font);
    achieveText.setCharacterSize(25);
    achieveText.setPosition(250,250);
    achieveText.setColor(sf::Color::Red);


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

     //Texture Power Badge
    sf::Texture badgeIcon;
    badgeIcon.loadFromFile("images/badge.png");
    //RectangleShape for missile hit
    sf::RectangleShape recBadge;
    recBadge.setSize(sf::Vector2f(60,30));
    recBadge.setTexture(&badgeIcon);

      //Texture Enemy jet
    sf::Texture enemyJetIcon;
    enemyJetIcon.loadFromFile("images/enemyJet.png");
    //RectangleShape for jet
    sf::RectangleShape recEnemyJet;
    recEnemyJet.setSize(sf::Vector2f(100,100));
    recEnemyJet.setTexture(&enemyJetIcon);
    recEnemyJet.setPosition(400,50);


      //Texture Enemy jet
    sf::Texture enemyBombIcon;
    enemyBombIcon.loadFromFile("images/bomb.png");
    //RectangleShape for jet
    sf::RectangleShape recEnemyBomb;
    recEnemyBomb.setSize(sf::Vector2f(30,50));
    recEnemyBomb.setTexture(&enemyBombIcon);

//main window
    sf::RenderWindow window(sf::VideoMode(850,630), "Star-Fighters");
    bool missileFire=false;
    int i;
    int posX,posY;
    bool showPowerStar=false,powerHit=false;
    bool missileHit=false;
    int badgeHit=0;
    bool alienJetHit=false;

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

     //Power star achieve effect
    sf::Music beepPowerStar;
    beepPowerStar.openFromFile("audio/beepStar.wav");
    beepPowerStar.setVolume(40);

    bool badgeUpdate;
    bool bombAgain=false;
    int bombCount=0;
    bool bombHit=false;

    //alien jet health
    int alienJetHealth=10;


//GAME LOOP
    while (window.isOpen()){
        showPowerStar=false;
        window.clear(sf::Color::Black);
        recAlienShip.move(0,.05);
        recRock.move(0,0.05);
        recFireball.move(0,.1);
        recFireball02.move(0,0.1);

        sf::Event event;
        while (window.pollEvent(event))
        {
        if (event.type == sf::Event::Closed){
            window.close();
            }
        }
         //move missile if fired
        if(missileFire){
            recMissile.move(0,-0.25);
        }


        //key for jet movement
        sf::Vector2f jetPos=recJet.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                recJet.setPosition(jetPos.x,jetPos.y-.25);
                recAlienShip.move(0,.05);
                recRock.move(0,.30);
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

        //show health
    for(int i=1;i<=health;i++){
        recHealth.setPosition(i*20,10);
        window.draw(recHealth);
    }
    //show badge
    for(int i=1;i<=badgeHit;i++){
        recBadge.setPosition(10,i*40);
        window.draw(recBadge);
    }


         if(alienJetHealth==0){
            recEnemyJet.setTexture(&missileHitIcon);
            recEnemyJet.setSize(sf::Vector2f(150,150));
            recEnemyBomb.setSize(sf::Vector2f(0,0));
            gameText="MISSION COMPLETE !!";

            std::string achivementText="YOU HAVE EARNED ";
            std::stringstream ss;
            ss<<badgeHit;
            std::string temp;
            ss>>temp;
            achivementText=achivementText+temp+" SILVER WINGS !!";
            achieveText.setString(achivementText);
            gameDirection.setString(gameText);
            gameDirection.setCharacterSize(25);
            //for enemy jet
        sf::Vector2f recEnemyJetPos=recEnemyJet.getPosition();
        //recEnemyJet.setPosition(400,50);
        if(recEnemyJetPos.x>700){
            recEnemyJet.setPosition(0,50);
        }
        recEnemyJet.move(+.15,0);

            window.draw(recEnemyJet);
            window.draw(recJet);
            window.draw(achieveText);
            window.draw(gameDirection);
            window.draw(recEnemyJet);
            window.display();


            continue;
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

    if(alienHitCount==5){
        recAlienShip.setSize(sf::Vector2f(0,0));
        missileHit=true;
    }
    if(missileHit){
        recAlienShip.move(0,+.5);
        recMissileHit.move(0,+.5);
        window.draw(recMissileHit);
        if(!badgeUpdate){
            badgeHit++;
            badgeUpdate=true;
        }
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


    if(hasReachedBoundary(recAlienShip)){
        recAlienShip.setSize(sf::Vector2f(150,150));
        recAlienShip.setPosition(jetPos.x-10,-10);
        recAlienShip.setTexture(&alienShipIcon);
        missileHit=false;
        alienHitCount=0;
        badgeUpdate=false;
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
    if(hasReachedTop(recJet)){
        recJet.setPosition(375,500);
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
            beepPowerStar.stop();
                if(health<=9){
                    beepPowerStar.play();
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


    if(badgeHit>=3){
        gameText="Complete this mission by destroying this alien jet (10 Hit)";
        gameDirection.setString(gameText);
        sf::Vector2f recEnemyJetPos=recEnemyJet.getPosition();
        //recEnemyJet.setPosition(400,50);
        if(recEnemyJetPos.x>700){
            recEnemyJet.setPosition(0,50);
        }
        recEnemyJet.move(+.15,0);
        if(hasReachedBoundary(recEnemyBomb)){
           bombAgain=true;
        }
        if(bombAgain){
            recEnemyBomb.setPosition(recEnemyJetPos.x+30,recEnemyJetPos.y+100);
            bombAgain=false;
        }else{
            recEnemyBomb.move(0,.6);
        }
        if(hasHitBomb(recJet,recEnemyBomb)){
            recEnemyBomb.setTexture(&missileHitIcon);
            recEnemyBomb.setSize(sf::Vector2f(500,500));
            alienShipHit.play();

            if(!bombHit){
                bombCount++;
                bombHit=true;
                health--;
                //std::cout<<bombCount<<std::endl;
            }
        }
        if(hasReachedBoundary(recEnemyBomb)){
            bombHit=false;
            recEnemyBomb.setTexture(&enemyBombIcon);
            recEnemyBomb.setSize(sf::Vector2f(40,50));
        }
        window.draw(recEnemyBomb);
        window.draw(recEnemyJet);

        if(hasHitAlienJet(recMissile,recEnemyJet) && missileFire){
            alienShipHit.play();
            missileFire=false;
            recMissile.setSize(sf::Vector2f(0,0));
            alienJetHealth--;
            //std::cout<<alienJetHealth<<"\t";
        }
    }




        window.draw(gameDirection);
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



