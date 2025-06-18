#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/system.hpp>
using namespace sf;

class Enemy
{
public:
   
   Sprite car(const Texture & er , float &x,float y=0)
   {
        
        Sprite car(er);
        car.setTexture(er);
        car.setScale(0.15, 0.15);
        car.setPosition(x, y);
       
        return car;
    }
};
