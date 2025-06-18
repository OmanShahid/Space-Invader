
#include<iostream>
#include<sstream>    //string data store kai lia
#include<SFML\Graphics.hpp> // SFML Graphics
#include<time.h>  //random file time kai lia
#include<vector> //vectors use for multiple enemies and firing
#include "Menu.h"
#include<fstream>
#include<SFML/Audio.hpp>
int gamestart();              // function prototype            // vectors mai size nahi dena padta wo automatically increse hota rehta hai jab
bool gameEnd(int& score,int &hscore);                          // koi value us mai add kari jai ," push back " vector mai value add kar nai kai lia aur
using namespace sf;                                            // "pop back " element remove karwanai kai lia
using namespace std;
int main()
{
	srand(time_t(10));   // generate enemies time 
	fstream save,High;    // file handling
	
	
	int hscore = 0;
	int score = 0;
	a:RenderWindow window(VideoMode(640, 480), "GOTTA RUN");    // set window and title
	window.setFramerateLimit(60);    // computer speed frame rate FPS
	
	
	int k=gamestart();     
	if (k == 1)          // menu sai play button press ho 
		score = 0;
		
    else if (k == 2|| k == 1)   // menu sai play and load  button press ho 
	{
		save.open("text.txt", ios::in);            // open file in read mode
		High.open("HighestScore.txt", ios::in);
		if (!save)
		{
			cout << " Error Or No Save Data Found";
			goto a;   // load kar na hai tu shoro sai start kar nai kai lia goto use howa hai
		}
		else
		{
			save >> score;
			High >> hscore;
			
			save.close();
		}
		
	}
	else
		window.close();              // exits button press ho menu sai
	Texture b;                        // pics (background)
	   b.loadFromFile("back.jpg");   //load
	   Sprite back(b);     // object jo screen pai show ho means aeroplane
	   back.setScale(.40,0.40);   //  set scale 

	//BALLS (firing)    bullets in form of circle
	CircleShape bullet;             // Graphic SFML function ya keyword in SFML
	bullet.setFillColor(Color::Yellow);
	bullet.setRadius(3.5f);

	//enemies pics
	Texture eny;
	eny.loadFromFile("enemy.png");
	Sprite enemy(eny);      // object create jis par pic lagani hai
	enemy.setScale(.15,0.15);   // enemy pics size ka size set

	// player (aeroplane)
	Texture pl;
	pl.loadFromFile("cr.png");
	Sprite player(pl);   // object pics
	player.setScale(0.10f,0.10f);  // plane size
	player.setPosition(window.getSize().x / 2 - player.getScale().x, window.getSize().y - player.getScale().y * 2 - 50.f); // position of our aeroplane
	Vector2f playerCenter;    // storing x-axis and y-axis position
	int shootTimer = 0;         

	vector<CircleShape> bullets;             //produce bullets in circle shape
	bullets.push_back(CircleShape(bullet));   //insert bullets like insert elemnet in an array = push_back work
	
	vector<Sprite> enemies;              //  create multiple enemies (makes array storing enemy/)
	enemies.push_back(Sprite(enemy));         //  insert enemies like insert elemnet in an array
	int enemySpawnTimer = 0;            // number of enemy 
	
	SoundBuffer fir,cla;                     // audio (sounds)
	cla.loadFromFile("fire.wav");            // firing sound and blast sound
	fir.loadFromFile("gun.wav");             
	Sound fire(fir);
	Sound clash(cla);
	
	bool p = true;
	while (window.isOpen())
	{
		
		Event event;    // like texture Event is used (keyword)
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)   // when cross button pressed
				window.close();
			
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)  // close when escape key is pressed
				window.close();
		}

		//UPDATE
		//PLAYER
		playerCenter = Vector2f(player.getPosition().x + player.getScale().x + 22, player.getPosition().y + player.getScale().y);  // position of plane

		if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x > 0) // set game window ( screen sai bahir na jai)
		{
			// left key is pressed: move our character

			player.move(-6.5f, 0.0f);  // move along -ve x-axis
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x < window.getSize().x - 50)  // plane ki position ko game screen ki postio sai check kia
		{
			// left key is pressed: move our character

			player.move(6.5f, 0.0f);   // move along  +ve x-axis

		}
		if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y > 150)
		{
			// left key is pressed: move our character

			player.move(0.0f, -5.5f);   // move along y-axis
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y < window.getSize().y - 50)
		{
			// left key is pressed: move our character

			player.move(0.0f, 5.5f); // move along y-axis
		}
		save.open("text.txt", ios::out);
		High.open("HighestScore.txt", ios::out);
		save << score;
		High << hscore;
		save.close();
		High.close();

		//Score
		Font arial;
		arial.loadFromFile("arial.ttf");

		ostringstream sscore,end;       // like ofstream it creates string and save data
		sscore << "Score =  " << score; // string  mai store kar raha hai
		  

		Text lscore;   // game window per text print karwanai kai lia varaible
		lscore.setCharacterSize(30);  // size set kia characters ka
		lscore.setPosition(10,10);   // set position

		lscore.setFont(arial);           // font of score
		lscore.setString(sscore.str());  // string 

		
		//bulletS
		if (shootTimer < 5)
			shootTimer++;   // shoot timer enemy while generating 

		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >=5) //Shoot   (press " space "to fire)
		{
			bullet.setPosition(playerCenter);           // position of aeroplane = position of bullet (centre sai niklai gi plane kai)
			bullets.push_back(CircleShape(bullet));     // push back = insert bullets like insert elemnet in an array

			shootTimer = 0; 
		}

		for (int i = 0; i < bullets.size(); i++)  // yai loop bullets generate kar raha hai
		{
			bullets[i].move(0.f, -10.f);          // move = moves bullet upward 

			if (bullets[i].getPosition().y <= 0)
				bullets.erase(bullets.begin() + i);
		}

		//ENEMIES
		if (enemySpawnTimer < 17) {   // if mai score kai hisaab sai enemy number incresae ho rahai hai
			if (score < 60) {

				enemySpawnTimer++;  // icrease by one
			}
			else if (score < 120)
			{
				enemySpawnTimer += 2; // increment of 2
			}
			else
				enemySpawnTimer += 4; // increment of 4
		}

		if (enemySpawnTimer >= 17)    // time generating enemy
		{
			
			enemy.setPosition((rand() % int(window.getSize().x -50)), 0.f);   // " get size " is use to get the size of vector
			enemies.push_back(Sprite(enemy));  // push back means add enemy in array

			enemySpawnTimer = 0;
		}

		for (int i = 0; i < enemies.size(); i++)  // loop increse speed of enemies
		{
			if(score <50)
			enemies[i].move(0.f, 4.f);
			else if (score < 100)
				enemies[i].move(0.f, 6.f);
			else if (score < 150)
				enemies[i].move(0.f, 8.f);
			else if (score < 200)
				enemies[i].move(0.f, 10.f);
			else
				enemies[i].move(0.f, 12.f);

			if (enemies[i].getPosition().y > window.getSize().y)
				enemies.erase(enemies.begin() + i);  // erase khatam kar raha hai jab collision ho 
		}

		//Collision
		
			if (!enemies.empty() && !bullets.empty())
			{
				for (int i = 0; i < bullets.size(); i++)  // number of bullets
				{
					for (int k = 0; k < enemies.size(); k++) // number of enemies
					{
						if (bullets[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))  // intersect funtion use
						{
							bullets.erase(bullets.begin() + i);   // bullets and enemies are removed jo intersect kar jai
							enemies.erase(enemies.begin() + k);
							score++;  // score increse ho ta jai ga
							
							fire.play();      // sound 
							
							break;
						}

					}
				}
			}
		
			// plane aur enemy ki intersection 
		for (int k = 0; k < enemies.size(); k++) {
			if (player.getGlobalBounds().intersects(enemies[k].getGlobalBounds())) // get global position laita hai
			{
				clash.play();       // sound play
				if (score > hscore) // max and sec max kia hai
					hscore = score;
				bool b;
				b=gameEnd(score,hscore);
				p = false;
				if (p == b)       // yai exit button per b ko false return kar raha hai agar hum "space" preess karai tu true return karai ga
					window.close();
				else
				goto a; // true anai per dobara game play karai ga
			}
		}

		//DRAW
		
			window.clear();     // clear window
			window.draw(back);  // background draw ho raha hai
			window.draw(player); // player draw plane

			for (int i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i]);    // " draw " = enemies ko draw kar rahai hai window per 
			}

			for (int i = 0; i < bullets.size(); i++)  // bullet size vector ka size lai rha hai
			{
				window.draw(bullets[i]);  // draw bullets
			}
			window.draw(lscore);
			window.display();
		
	}


	return 0;
}

// end game
bool gameEnd(int &score,int &hscore)
{
	RenderWindow window(VideoMode(640, 480), "GOTTA RUN");   // set window (and title
	window.setFramerateLimit(60);  // computer speed FPS

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				return true;
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				return false;
				window.close();
			}
		}


		// end screen 

		Texture b;                        // pics (background)
		b.loadFromFile("endBack.jpg");   //load
		Sprite back(b);     // object jo screen pai show ho means aeroplane
		back.setScale(1.2, 1.6);   //  set scale 


		Font arial;
		arial.loadFromFile("arial.ttf");

		// highest score  at end screen
		std::ostringstream sscore, end;   // ostring measns storing data in string 
		sscore << "Score =  " << score << endl << "Highest Score = " << hscore;
		end << "(Space) to Continue\n(Escape) To Exit";
		Text lscore;
		lscore.setCharacterSize(20);
		lscore.setFillColor(Color::Red);
		lscore.setPosition(100, 400);
		lscore.setFont(arial);
		lscore.setString(sscore.str());

		Text over;
		over.setFillColor(Color::Cyan); // Game over color 
		over.setCharacterSize(20);         // Game Over  Font size 
		over.setPosition(350, 400);         // Game over Position
		over.setFont(arial);               // Font Style
		over.setString(end.str());

		window.draw(back);
		window.draw(over);
		window.draw(lscore);

	
		window.display();

	}
	
}

// menu create kia hai

int gamestart()
{
	RenderWindow window(VideoMode(640, 480), "Menu", Style::Default);   // third window create
	window.setFramerateLimit(60);

	Texture b;                        // pics (background)
	b.loadFromFile("front.jpg");   //load
	Sprite back(b);     // object jo screen pai show ho means aeroplane
	back.setScale(.17, .2);   //  set scale 


	Menu menu(window.getSize().x, window.getSize().y);   // class banai hai

	while (window.isOpen())       
	{
		Event event;
		while (window.pollEvent(event))  // pollevent sfml ka function hai jo
		{
			switch (event.type)
			{
			case Event::KeyReleased:

				switch (event.key.code)
				{
				case Keyboard::W:  // W is use to move up
					menu.MoveUp();
					break;

				case Keyboard::S:   // s use to move down
					menu.MoveDown();
					break;



				case Keyboard::Return:   // menu.h file sai input a rahi hai

					switch (menu.GetPressedItem())
					{
					case 0:
						cout << "Play button has been pressed " << endl;
						return 1;
						window.close();
						break;

					case 1:
						cout << "Load button has been pressed " << endl;
						return 2;
						window.close();
						break;

					case 2:
						cout << "exit button has been pressed " << endl;
						return 3;
						window.close();
						break;

					}


				}
				break;


			case Event::Closed:   // close window 
				window.close();

				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
					window.close();

			}



			window.clear();
			window.draw(back);
			menu.draw(window);
			
			window.display();
		}
	}

	return 0;
}