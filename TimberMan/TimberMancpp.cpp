
#include<SFML/Graphics.hpp> //header file used to handle rendering
#include<sstream>          //sstream is used for string manipulation (converting numbers to text)
#include<iostream>      //iostream is used for standard input and output
#include<SFML/Audio.hpp>  // header file use to handle audio

using namespace std;
using namespace sf;

//Function Declaration
void updateBranches(int speed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the branch? LEFT OR RIGHT
enum class side{LEFT,RIGHT,NONE}; 
side branchPositions[NUM_BRANCHES];

int main() {
	VideoMode vm(1920, 1080); //create a window videomode object
	RenderWindow window(vm, "TIMBERMAN"); // create and open window for the Game
	/*
	VideoMode vm(960, 540);
	RenderWindow window(vm, "Timber");
	View view(FloatRect(0, 0, 1920, 1080));
	window.setView(view);*/

	/*-------------BACKGROUND---------------------*/
	Texture textureBackground; //create a texture to hold graphic on the GPU
	textureBackground.loadFromFile("graphics/background.png"); //Load graphics to the texture
	Sprite spriteBackground; 
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	/*--------------------TREE--------------------*/
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(830,0);   // set the position
	spriteTree.setScale(0.8f, 0.99f); // resize the image

;
	Sprite spriteTree1,spriteTree2;
	spriteTree1.setTexture(textureTree);
	spriteTree1.setPosition(130, 0);
	spriteTree1.setScale(0.7f, 0.875f);
	spriteTree2.setTexture(textureTree);
	spriteTree2.setPosition(1600, 0);
	spriteTree2.setScale(0.7f, 0.97f);



	/*-------------------CLOUD--------------------*/
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Texture textureCloudr;
	textureCloudr.loadFromFile("graphics/rcloud.png");

	Sprite spriteCloud1, spriteCloud2, spriteCloud3, spriteCloud4; //Multiple Clouds
	spriteCloud1.setTexture(textureCloudr); 
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloudr);
	spriteCloud4.setTexture(textureCloud);
	//Position of the Cloud
	spriteCloud1.setPosition(0, 10);
	spriteCloud2.setPosition(500, 100);
	spriteCloud3.setPosition(1100, 10);
	spriteCloud4.setPosition(1600, 100);
	//resize the cloud
	spriteCloud1.setScale(1.5f, 0.9f);
	spriteCloud2.setScale(1.5f, 0.9f);
	spriteCloud3.setScale(1.5f, 0.9f);
	spriteCloud4.setScale(1.5f, 0.9f);

	float cloud1Active = false;
	float cloud2Active = false;
	float cloud3Active = false;
	float cloud4Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	float cloud4Speed = 0.0f;



	/*------------------BEE--------------------------*/
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0,400);

	float beeSpeed = 0.0f; // Is the Bee active
	float beeActive = false; // How fast the Bee is Moving

	/*------------------TEXT------------------------*/
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	Text messageText;
	messageText.setString("Press Enter To Start The Game! "); //Text to display
	messageText.setFont(font);
	messageText.setFillColor(Color::White); //set the text colour
	messageText.setCharacterSize(50); //text size
	messageText.setPosition(500, 500); //text position

	/*------------------SCORE-----------------------*/
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("SCORE=0");
	scoreText.setFillColor(Color::White);
	scoreText.setCharacterSize(30);
	scoreText.setPosition(840,100);

	/*-----------------TIME BAR----------------------*/
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 50;
	timeBar.setFillColor(Color::Red);
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setPosition(750, 900);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


	//---------------PREPARING BRANCHES---------------------------------
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	//set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES;i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);

	}

	/*updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);*/

	//---------------PLAYER---------------------------------------------
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	side PlayerSide = side::LEFT;



	//--------------GRAVESTONE------------------------------------------
	Texture textureGrave;
	textureGrave.loadFromFile("graphics/rip.png");
	Sprite spriteGrave;
	spriteGrave.setTexture(textureGrave);
	spriteGrave.setPosition(600, 860);
	spriteGrave.setScale(0.8f, 0.8f);

	//---------------AXE-------------------------------------------------
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	const float AXE_Position_LEFT = 700;
	const float AXE_Position_RIGHT = 1075;

	//--------------------LOG--------------------------------------------
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(830, 720);
	spriteLog.setScale(0.8f, 0.99f);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	//--------------PREPARE THE SOUND-------------------------------------

	//Chopping Sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	//Death sound
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	//Out of Time
	SoundBuffer outoftimeBuffer;
	outoftimeBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outoftime;
	outoftime.setBuffer(outoftimeBuffer);



	Clock clock;
	bool paused = true;
	int score=0;
	bool acceptInput = false; // control the player input



	//----------GAME LOOP----------------- 
	while(window.isOpen()) {
		Time dt = clock.restart(); // restart the clock every frame
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { //This will keep the window open until the escape key is pressed
			window.close(); // close the window when escape key is pressed
		}
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {

				//Listen for key presses again
				acceptInput = true;
				//hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;

			//Reset the time and Score 
			score = 0;
			timeRemaining = 6;

			for (int i = 0;i < NUM_BRANCHES;i++) {
				branchPositions[i] = side::NONE;
			}
			spriteGrave.setPosition(675, 2000); //Moves the grave sprite off-screen (probably resetting after a player death).
			spritePlayer.setPosition(580, 720);  //Resets the player's position to (580, 720), likely the starting point.
		}

		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				PlayerSide = side::RIGHT;
				score++;
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_Position_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);
				updateBranches(score);
				spriteLog.setPosition(830, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				PlayerSide = side::LEFT;
				score++;
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_Position_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);
				updateBranches(score);
				spriteLog.setPosition(830, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}
		}




		if (!paused) {
			/*-------------------SCORE-------------------------------------*/
			stringstream ss; //Creates a stringstream object (ss) to store and manipulate text data.
			ss << "Score=" << score;
			scoreText.setString(ss.str());

			timeRemaining -= dt.asSeconds(); //Updating the Time Remaining
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight)); // Updating the Time Bar Size

			if (timeRemaining < 0.0f) { //Checking If Time is Up
				paused = true;
				messageText.setString("Out of Time!");
				messageText.setFillColor(Color::Black);
				messageText.setPosition(800, 400);
				outoftime.play();

			}
			/*---------------------MAKING THE BEE FLY-------------------------------*/
			if (!beeActive) {
				//for speed
				srand((int)time(0));
				beeSpeed = (rand() % 200)+50;  //Generate random numbers between 50 and 250
				//for height
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500; //Generate random numbers between 500 and 1000
				spriteBee.setPosition(1900, height);
				beeActive = true;
			}
			else {
				spriteBee.setPosition(spriteBee.getPosition().x - beeSpeed * dt.asSeconds(),
					spriteBee.getPosition().y);
				if (spriteBee.getPosition().x < -50) {
					beeActive = false;
				}
			}

			/*---------------------MAKING CLOUD MOVE----------------------------------*/
			//CLOUD 1
			if (!cloud1Active) {
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 50) + 50;
				srand((int)time(0) * 10);
				float CloudHeight = (rand() % 100);
				spriteCloud1.setPosition(-200, CloudHeight);
				cloud1Active = true;
			}
			else {
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed * dt.asSeconds(),
					spriteCloud1.getPosition().y);
				if (spriteCloud1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}
			//CLOUD 2
			if (!cloud2Active) {
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 100) + 100;
				srand((int)time(0) * 10);
				float cloud2Height = (rand() % 50);
				spriteCloud2.setPosition(1700, cloud2Height);
				cloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(spriteCloud2.getPosition().x - cloud2Speed * dt.asSeconds(),
					spriteCloud2.getPosition().y);
				if (spriteCloud2.getPosition().x < -400) {
					cloud2Active = false;
				}
			}
			//CLOUD 3
			if (!cloud3Active) {
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 100) + 100;
				srand((int)time(0) * 30);
				float cloud3Height = (rand() % 100);
				spriteCloud3.setPosition(-500, cloud3Height);
				cloud3Active = true;
			}
			else {
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed * dt.asSeconds(),
					spriteCloud3.getPosition().y);
				if (spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}
			//CLOUD 4
			if (!cloud4Active) {
				srand((int)time(0) * 40);
				cloud4Speed = (rand() % 100) + 50;
				srand((int)time(0) * 10);
				float cloud4Height = (rand() % 50);
				spriteCloud4.setPosition(2000, cloud4Height);
				cloud4Active = true;
			}
			else {
				spriteCloud4.setPosition(spriteCloud4.getPosition().x - cloud4Speed * dt.asSeconds(),
					spriteCloud4.getPosition().y);
				if (spriteCloud4.getPosition().x < -400) {
					cloud4Active = false;
				}
			}
			/*------------UPDATE THE BRANCH SPRITE----------------*/
			for (int i = 0;i < NUM_BRANCHES;i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT){ // move the sprite to the left side
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {  // move the sprite to the Right side
					branches[i].setPosition(1280, height);
					branches[i].setRotation(0); //set the sprite rotation to normal
				}
				else {
					//Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			//Handle a flying log
			if (logActive) {
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x>2000) {
					logActive = false;
					spriteLog.setPosition(830, 720);
				}
			}

			if (branchPositions[5] == PlayerSide) {
				//death
				paused = true;
				acceptInput = false;
				//Draw the gravestone
				spriteGrave.setPosition(525, 760);
				//hide the player
				spritePlayer.setPosition(2000, 660);
				//change the text of the message
				messageText.setString("SQISHED");
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				death.play();
			}
		} // end if paused







		//Clear everything from the last frame
		window.clear();
		//Draw game scene 
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteCloud4);
		window.draw(spriteBee);
		window.draw(spriteTree);
		window.draw(spriteTree1);
		window.draw(spriteTree2);
		for (int i = 0; i < NUM_BRANCHES;i++) {
			window.draw(branches[i]);
		}
		if (paused) {
			window.draw(messageText);
		}
		window.draw(scoreText);
		window.draw(timeBar);
		window.draw(spriteLog);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteGrave);
		//Show everything we just draw
		window.display();
	}
	return 0;
}

void updateBranches(int seed) {
	for (int j = NUM_BRANCHES - 1;j > 0;j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}


/*g++ Timberman.cpp -o timber -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
./timber*/
