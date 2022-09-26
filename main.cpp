#include<iostream>
#include<SFML/Graphics.hpp>
#include<ctime>
#include<random>
#include<sstream>
#include<map>
#include<chrono>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<stdlib.h>
#include <SFML/Window.hpp> 
using namespace std;

map<string, sf::Texture> tileTextures;


class Tile{
public:
    
    vector<Tile*> adjacentTiles;
    
	sf::Sprite mine;
    sf::Sprite flag;
    sf::Sprite number;
    

	sf::Sprite foreground;
	sf::Sprite background;
    
    bool isFlaged;
    bool isRevealed;
	bool bomb;
    bool num;
    
    unsigned int n=0;
    
};


class Board{
    
public:
    vector<Tile> tiles;
    bool win=false;
    bool lose=false;


    unsigned int tilesRevealed=0;


void RevealRecursion(Tile & t){
    
   t.isRevealed=true;
   t.foreground=t.background;
    
    
    for(int i=0;i<t.adjacentTiles.size();i++){
        if(t.adjacentTiles.at(i)->num==false && t.adjacentTiles.at(i)->bomb==false&&t.adjacentTiles.at(i)->isRevealed==false){
            t.adjacentTiles.at(i)->isRevealed=true;
            tilesRevealed++;
            t.adjacentTiles.at(i)->foreground=t.adjacentTiles.at(i)->background;
            RevealRecursion(*t.adjacentTiles.at(i));
        }
        if(t.adjacentTiles.at(i)->bomb==false&&t.adjacentTiles.at(i)->isFlaged==false&& t.adjacentTiles.at(i)->isRevealed==false&&t.adjacentTiles.at(i)->num==true){
           t.adjacentTiles.at(i)->foreground=t.adjacentTiles.at(i)->background;
           t.adjacentTiles.at(i)->isRevealed=true;
            tilesRevealed++;
        }
    }


}
 
};

void reset(Board &b){
    Tile t;
    int mineCount=0;
    b.tiles.clear();
    
    int i=0;
    for(int y=0;y<16;y++)
    {
        for(int x=0;x<25;x++)
        {       
            t.foreground.setTexture(tileTextures["hiddenTile"]);
            t.bomb=false;
            t.n=0;
            t.num=false;
            t.background.setTexture(tileTextures["revealedTile"]);
            t.number.setTexture(tileTextures["revealedTile"]);
            t.mine.setTexture(tileTextures["mine"]);
                    
            t.flag.setTexture(tileTextures["flag"]);
            t.isFlaged = false;
            t.isRevealed = false;
                                             
            b.tiles.push_back(t);
            b.win=false;
            b.lose=false;
            
            b.tilesRevealed=0;
            b.tiles.at(i).flag.setPosition(x*32,y*32);
            b.tiles.at(i).mine.setPosition(x*32, y*32);
            b.tiles.at(i).number.setPosition(x*32,y*32);
            b.tiles.at(i).foreground.setPosition(x*32,y*32);
            b.tiles.at(i).background.setPosition(x*32,y*32);
     
            i++;
        }
    }
    
    while(mineCount<50){
        int x=rand()%400;
        if(b.tiles.at(x).bomb==false){
            b.tiles.at(x).bomb=true;
            mineCount++;
            
        }
        
    }
    
    
    
}
void num2put(Board& boardObj){
    for(int i=0;i<400;i++){
        
        
        if(boardObj.tiles.at(i).n==0&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["revealedTile"]);
            boardObj.tiles.at(i).num=false;
         
            
        }
        
        if(boardObj.tiles.at(i).n==1&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number1"]);
            boardObj.tiles.at(i).num=true;
          
            
        }
        if(boardObj.tiles.at(i).n==2&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number2"]);
            boardObj.tiles.at(i).num=true;
            
        }
        if(boardObj.tiles.at(i).n==3&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number3"]);
            boardObj.tiles.at(i).num=true;
            
        }
        if(boardObj.tiles.at(i).n==4&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number4"]);
            boardObj.tiles.at(i).num=true;
            
        }
        if(boardObj.tiles.at(i).n==5&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number5"]);
            boardObj.tiles.at(i).num=true;
            
        }
        if(boardObj.tiles.at(i).n==6&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number6"]);
            boardObj.tiles.at(i).num=true;
            
        }
        if(boardObj.tiles.at(i).n==7&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number7"]);
			boardObj.tiles.at(i).num = true;
            
        }
        if(boardObj.tiles.at(i).n==8&&boardObj.tiles.at(i).bomb==false){
            boardObj.tiles.at(i).number.setTexture(tileTextures["number8"]);
            boardObj.tiles.at(i).num=true;
            
        }
        
    }
}

void adjacentMines(Board& boardObj){
    
    for(unsigned int i=0;i<400;i++){
        if(i==0){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(26));
        }
        
        else if(i==375){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(350));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(376));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(351));
        }
        
        else if(i==24){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(23));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(48));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(49));
        }
        
        else if(i==399){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(398));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(374));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(373));
        }
        
        
        else if(i<24&& i>0){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+24));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+26));
        }
        
        
        else  if(i<399&& i>375){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-26));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-24));
        }
        
        
        else if(i==49||i==74||i==99||i==124||i==149||i==174||i==199||i==224||i==249||i==274||i==299||i==324||i==349||i==374){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-26));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+24));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+25));
        }
        
        
        else  if(i==25||i==50||i==75||i==100||i==125||i==150||i==175||i==200||i==225||i==250||i==275||i==300||i==325||i==350){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-24));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+26));
        }
        
        
        else if((i<49&& i>25) || (i<74&&i>50) || (i<99&&i>75) ||(i<124&&i>100) || (i<149 && i>125)|| (i<174 && i>150)|| (i<199 && i>175)|| (i<224 && i>200)|| (i<249 && i>225)|| (i<274 && i>250)|| (i<299 && i>275)|| (i<324 && i>300)|| (i<349 && i>325)|| (i<374 && i>350)){
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-1));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-24));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i-26));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+24));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+25));
            boardObj.tiles.at(i).adjacentTiles.push_back(&boardObj.tiles.at(i+26));
        }
        
        
        
    }
    
    for(int k=0;k<400;k++)
    {
        for(int c=0;c<boardObj.tiles.at(k).adjacentTiles.size();c++)
        {
            
            if(boardObj.tiles.at(k).adjacentTiles.at(c)->bomb==true){
                boardObj.tiles.at(k).n++;
            }
            
        }
    }
}

void loadTestBoard(Board &b, string file){
    ifstream inFile("boards/" + file);


    if(!inFile.is_open()){ 
        cerr<<"Error opening File"<<endl;
        exit(1);
    }
    string line;
    string filenums;
    char myarr[400];
    
   // reset(b);
    for(int i=0;i<400;i++){
        b.tiles.at(i).bomb=false;
        
    }
    while(getline(inFile,line,' ')){
    
		stringstream ss(line);

        for (int i=0;i<400;i++){
			char temp;
			ss >> temp;
            
            if (temp =='1'){
                b.tiles.at(i).bomb=true;
                
                
            }
            if (temp =='0'){
                b.tiles.at(i).bomb=false;
               
              
            }          
        }
    
    } 
   inFile.close(); 
}

int main() {
	Tile test;
	Board boardObj;


	int n1, n2, n3;
    bool de=false;

    int mineCount=0;


    srand((unsigned)time(0));
    
    sf::RenderWindow window(sf::VideoMode(800,600),"Minesweeper");
   
    window.setFramerateLimit(60);
 
    tileTextures["hiddenTile"].loadFromFile("images/tile_hidden.png");
    tileTextures["revealedTile"].loadFromFile("images/tile_revealed.png");
    tileTextures["number1"].loadFromFile("images/number_1.png");
    tileTextures["number2"].loadFromFile("images/number_2.png");
    tileTextures["number3"].loadFromFile("images/number_3.png");
    tileTextures["number4"].loadFromFile("images/number_4.png");
    tileTextures["number5"].loadFromFile("images/number_5.png");
    tileTextures["number6"].loadFromFile("images/number_6.png");
    tileTextures["number7"].loadFromFile("images/number_7.png");
    tileTextures["number8"].loadFromFile("images/number_8.png");
    tileTextures["mine"].loadFromFile("images/mine.png");
    tileTextures["flag"].loadFromFile("images/flag.png");
    tileTextures["debug"].loadFromFile("images/debug.png");
 
    tileTextures["happyface"].loadFromFile("images/face_happy.png");
    tileTextures["winface"].loadFromFile("images/face_win.png");
    tileTextures["loseface"].loadFromFile("images/face_lose.png");
    tileTextures["test1"].loadFromFile("images/test_1.png");
    tileTextures["test2"].loadFromFile("images/test_2.png");
    tileTextures["test3"].loadFromFile("images/Test_3.png");
    
 
    sf::Sprite revealedTileSprite;
    sf::Sprite debugSprite;
    sf::Sprite test1Sprite;
    sf::Sprite test2Sprite;
    sf::Sprite test3Sprite;
    sf::Sprite happySprite;
    sf::Sprite winSprite;
    sf::Sprite loseSprite;
 
    
    sf::Sprite score1;
    sf::Sprite score2;
    sf::Sprite score3;
    

    sf::Texture digarray[11];
  
    digarray[0].loadFromFile("images/digits.png",sf::IntRect(0,0,32,32));
    digarray[1].loadFromFile("images/digits.png",sf::IntRect(18,0,27,32));
    digarray[2].loadFromFile("images/digits.png",sf::IntRect(40,0,27,32));
    digarray[3].loadFromFile("images/digits.png",sf::IntRect(60,0,27,32));
    digarray[4].loadFromFile("images/digits.png",sf::IntRect(80,0,27,32));
    digarray[5].loadFromFile("images/digits.png",sf::IntRect(102,0,27,32));
    digarray[6].loadFromFile("images/digits.png",sf::IntRect(123,0,27,32));
    digarray[7].loadFromFile("images/digits.png",sf::IntRect(145,0,27,32));
    digarray[8].loadFromFile("images/digits.png",sf::IntRect(165,0,27,32));
    digarray[9].loadFromFile("images/digits.png",sf::IntRect(190,0,25,32));
    digarray[10].loadFromFile("images/digits.png",sf::IntRect(210,0,32,32));
   
    
	score1.setPosition(200,512);
	score2.setPosition(250,512);
	score3.setPosition(300,512);
    
   
    test1Sprite.setTexture(tileTextures["test1"]);
    test2Sprite.setTexture(tileTextures["test2"]);
    test3Sprite.setTexture(tileTextures["test3"]);
    happySprite.setTexture(tileTextures["happyface"]);
    winSprite.setTexture(tileTextures["winface"]);
    loseSprite.setTexture(tileTextures["loseface"]);
    test1Sprite.setPosition(560,512);
    test2Sprite.setPosition(624,512);
    test3Sprite.setPosition(688,512);
    happySprite.setPosition(368,512);
    winSprite.setPosition(368,512);
    loseSprite.setPosition(368,512);
    
    revealedTileSprite.setTexture(tileTextures["revealedTile"]);
    debugSprite.setTexture(tileTextures["debug"]);
    debugSprite.setPosition(496,512);
   
    int i=0;

    for(int y=0;y<16;y++)
    {
		for(int x=0;x<25;x++)
		{
            test.foreground.setTexture(tileTextures["hiddenTile"]);
            test.bomb=false;
            test.n=0;
            test.background.setTexture(tileTextures["revealedTile"]);
            test.number.setTexture(tileTextures["revealedTile"]);
            test.mine.setTexture(tileTextures["mine"]);

            test.flag.setTexture(tileTextures["flag"]);
            test.isFlaged = false;
            
            boardObj.tiles.push_back(test);
            boardObj.tiles.at(i).flag.setPosition(x*32,y*32);
            boardObj.tiles.at(i).mine.setPosition(x*32, y*32);
            boardObj.tiles.at(i).number.setPosition(x*32,y*32);
            boardObj.tiles.at(i).foreground.setPosition(x*32,y*32);
            boardObj.tiles.at(i).background.setPosition(x*32,y*32);
        
            i++;
        }
    }
    
	while(mineCount<50){
        int x=rand()%400;
		if(boardObj.tiles.at(x).bomb==false){
         boardObj.tiles.at(x).bomb=true;
         mineCount++;
     
		}
     
	}
    
  
    int flagbomb=50;
    
    adjacentMines(boardObj);
    num2put(boardObj);
    

    

    while(window.isOpen() )
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                    
                case sf::Event::MouseButtonPressed:
                    
                    if(event.mouseButton.button == sf::Mouse::Right){
                        
                        if((boardObj.win==true && boardObj.lose==false ) || (boardObj.win==false && boardObj.lose==true)){}
                        
                        else{
                        
                        int i=0;
                        for(int x=0;x<25;x++)
                        {
                            for(int y=0;y<16;y++)
                            {
                                
                                if(boardObj.tiles.at(i).foreground.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                    
                                    
                                    
                                    
                                    if(boardObj.tiles.at(i).isFlaged == true){
                                        
                                        boardObj.tiles.at(i).isFlaged=false;
                                        flagbomb++;
                                        
                                    }
                                    
                                    else{
                                        boardObj.tiles.at(i).isFlaged=true;
                                        flagbomb--;
 
                                    }
                                    if(boardObj.tiles.at(i).isRevealed==true){
                                        boardObj.tiles.at(i).isFlaged=false;
                                    }
                                
                               
                            }
                                 i++;
                            }
                        }
                    }
                    }
                    if(event.mouseButton.button == sf::Mouse::Left){
                        
                        
                        if((boardObj.win==true && boardObj.lose==false ) || (boardObj.win==false && boardObj.lose==true)){
                            if(loseSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                reset(boardObj);
                                adjacentMines(boardObj);
                                num2put(boardObj);
                                flagbomb=50;
                        }
                        }
                        else{
                            
                            if(happySprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                
                              reset(boardObj);
                              adjacentMines(boardObj);
                              num2put(boardObj);
                                flagbomb=50;
                            }
                            
                            
                            if(test1Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                reset(boardObj);
                                loadTestBoard(boardObj, "testboard1.brd");
                                adjacentMines(boardObj);
                                num2put(boardObj);
                            }
                            if(test2Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                reset(boardObj);
                                loadTestBoard(boardObj, "testboard2.brd");
                                adjacentMines(boardObj);
                                num2put(boardObj);
                            }
                            if(test3Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                reset(boardObj);
                                loadTestBoard(boardObj, "testboard3.brd");
                                adjacentMines(boardObj);
                                num2put(boardObj);
                            }
                            
                            
                        if(debugSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                           
                            if((boardObj.win==true && boardObj.lose==false ) || (boardObj.win==false && boardObj.lose==true)){}
                            else{
                            if(de==false){
                            de=true;
                           
                            }
                            else if(de==true){
                                de=false;
                             
                            }
                            }
                        }
                        
                        int i=0;
                       
                        for(int x=0;x<25;x++)
                        {
                            for(int y=0;y<16;y++)
                            {
                                if(boardObj.tiles.at(i).foreground.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                                    
                                   
                                    
                                    if(boardObj.tiles.at(i).isRevealed==false && boardObj.tiles.at(i).isFlaged==true){
                                    
                                        boardObj.tiles.at(i).isRevealed=false;
                                    }
                                    
                                   
                                    
                                    if(boardObj.tiles.at(i).isRevealed==false&& boardObj.tiles.at(i).isFlaged==false && boardObj.tiles.at(i).bomb==false){
                                        
                                        if(boardObj.tiles.at(i).num==false){
                                            boardObj.tilesRevealed++;
                                                    boardObj.RevealRecursion(boardObj.tiles.at(i));
                                            
                                        
                                        }
                                        
                                        else{
                                        boardObj.tiles.at(i).isRevealed=true;
                                        boardObj.tilesRevealed++;
                                        boardObj.tiles.at(i).isFlaged=false;
                                        }
                                      
                                       
                                    }
                                    
                                    if(boardObj.tilesRevealed==350&&boardObj.lose==false){
                                        boardObj.win=true;
                                       
                                    }
                                    else{
                                        boardObj.win=false;
                                        
                                    }
                                    
                                    
                                    if(boardObj.tiles.at(i).bomb==true && boardObj.tiles.at(i).isRevealed==false&&boardObj.tiles.at(i).isFlaged==false){
                                      
                                        for(int j=0;j<400;j++){
                                            if(de==true&&boardObj.tiles.at(i).isFlaged==true){
                                                
                                            }
                                            else{
                                         
                                            if(boardObj.tiles.at(j).bomb==true){
                                                  boardObj.lose=true;
                                         
                                                 boardObj.tiles.at(j).isRevealed=true;
                                            }
                                           
                                           
                                            }
                                        }
                                    }
                                 
                                }
                                i++;
                            }
                        }
                    
                    }
            
                    
                    break;
                    
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                    
            }
            
            
        }
        
        }
            
        window.clear();

        
        int j=0;
        
        for(int x=0;x<25;x++)
        {
            for(int y=0;y<16;y++)
            {
              
                
            
              window.draw(boardObj.tiles.at(j).background);
               
                if(boardObj.tiles.at(j).isRevealed==false){
                
                window.draw(boardObj.tiles.at(j).foreground);
                }
                
                if(boardObj.tiles.at(j).num==true && boardObj.tiles.at(j).isRevealed==true){
   
                     window.draw(boardObj.tiles.at(j).number);
                }
               
             
                if(boardObj.tiles.at(j).bomb==true && boardObj.tiles.at(j).isRevealed==true){

                
                    window.draw(boardObj.tiles.at(j).mine);
                    
                    
                }
               
                if(de==true){
                    if(boardObj.tiles.at(j).bomb==true)
                       window.draw(boardObj.tiles.at(j).mine);
                }
                
               if(boardObj.tiles.at(j).isRevealed==false&& de==false){
                    window.draw(boardObj.tiles.at(j).foreground);
                }
                
                if(boardObj.tiles.at(j).isFlaged==true)
                    window.draw(boardObj.tiles.at(j).flag);
             
                
                if(boardObj.win ==false && boardObj.lose==true){
                    window.draw(loseSprite);
                }
                if(boardObj.win==true&& boardObj.tilesRevealed==350&&boardObj.lose==false){
                    window.draw(winSprite);
                    if(boardObj.tiles.at(j).bomb==true){
                        window.draw(boardObj.tiles.at(j).flag);
                    }
                }
                if(boardObj.win==false&&boardObj.lose==false){
                    window.draw(happySprite);
                }
                
           
                
                int f=flagbomb;
                if(flagbomb>0){
                 n3 = f%10;
                f = f/10;
                 n2 = f%10;
                f=f/ 10;
                 n1 = f%10;
                }
                else{
                    f=abs(flagbomb);
                    n3 = f%10;
                    f = f/10;
                    n2 = f%10;
                    f=f/ 10;
                    n1 = f%10;
                    
                   
                }
          
                if(flagbomb>=0){
                score1.setTexture(digarray[n1]);
                score2.setTexture(digarray[n2]);
                score3.setTexture(digarray[n3]);
                }
               else{
               
                       
                    score1.setTexture(digarray[10]);
                    score2.setTexture(digarray[n2]);
                    score3.setTexture(digarray[n3]);
                
               
                }
               
                window.draw(debugSprite);
                window.draw(test1Sprite);
                window.draw(test2Sprite);
                window.draw(test3Sprite);
                
                
                window.draw(score1);
                window.draw(score2);
                window.draw(score3);
               
            
                
                j++;
            }
        }
          
    
        
        window.display();
        
    
        
    
    }
    return 0;
}
