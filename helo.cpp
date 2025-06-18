//// helo.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//#include "enemy.h"
//#include <iostream>
//#include<sstream>
//#include<SFML/Graphics.hpp>
//#include<SFML/Window.hpp>
//#include<SFML/system.hpp>
//#include<time.h>
//using namespace sf;
//using namespace std;
//int main()
//{
//     srand(time_t(NULL));
//     sf::RenderWindow window(sf::VideoMode(600,480), "GOTTA RUN!",Style::Close);
//     window.setFramerateLimit(60);
//
//     Texture b;
//     b.loadFromFile("F:/SFML-2.5.1/back.jpg");
//     sf::Sprite back(b);
//     back.setScale(.40,0.40);
//
//     sf::CircleShape circle(10.0f);
//     int dir = 0;
//     circle.setFillColor(sf::Color::Green);
//
//     Texture cr;
//     cr.loadFromFile("F:/SFML-2.5.1/cr.png");
//     Sprite carracing(cr);
//     carracing.setScale(0.10, 0.10);
//     carracing.setPosition(200.0, 300.0);
//
//     Texture er;
//     er.loadFromFile("F:/SFML-2.5.1/enemy.png");
//     Enemy enemy1[10];
//     float  y = 0;
//     float x[] = { 0 ,0 };
//     int enemySpawnTimer = 0;
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//                 window.close();
//         }
//
//
//
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && carracing.getPosition().x > 0)
//         {
//             // left key is pressed: move our character
//
//             carracing.move(-5.5f, 0.0f);
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && carracing.getPosition().x < window.getSize().x - 50)
//         {
//             // left key is pressed: move our character
//             /*x=x+0.1;
//             carracing.move(x, 0.0f);*/
//             carracing.move(5.5f, 0.0f);
//
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && carracing.getPosition().y > 150)
//         {
//             // left key is pressed: move our character
//
//             carracing.move(0.0f, -5.5f);
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && carracing.getPosition().y < window.getSize().y - 50)
//         {
//             // left key is pressed: move our character
//             /*x=x+0.1;
//             carracing.move(x, 0.0f);*/
//             carracing.move(0.0f, 5.5f);
//         }
//
//
//         if (y == -15)
//         {
//            
//             if (enemySpawnTimer < 10)
//             {
//                 enemySpawnTimer+=5;
//                
//                     x[0] = rand() % (window.getSize().x);
//                 if (enemySpawnTimer >= 10)
//                 {
//
//                    
//                     x[1] = rand() % (window.getSize().x);
//
//                     enemySpawnTimer = 0;
//                 }
//
//             }
//        }
//             if (enemy1[1].car(er, x[0], y).getPosition().y <= -15)
//                 dir = 1;
//             else if (enemy1[1].car(er, x[0], y).getPosition().y >= window.getSize().y)
//                 dir = 0;
//             if (dir == 0)
//             {
//
//                 y = -15;
//             }
//             if (dir == 1)
//             {
//
//                 y = y + 5.0;
//             }
//             
//             window.clear();
//             window.draw(back);
//
//
//             window.draw(enemy1[1].car(er, x[0],y));
//             window.draw(enemy1[2].car(er, x[1], y - 200));
//             // window.draw(enemy1[2].car(er,x,y));
//             window.draw(carracing);
//             /*for (size_t i = rand()%10; i < 480.0; i++)
//             {*/
//             /*circle.setPosition(i,0);*/
//
//         //}
//
//
//             window.display();
//     }
//
//
//         return 0;
//}
//
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
