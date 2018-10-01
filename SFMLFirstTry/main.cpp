#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

class Vector
{
    private:
        double* buffer;
        int nElements;




    public:
        Vector (int capacity)
        {
            assert (capacity > 0);
            nElements = capacity;
            buffer = (double*) calloc (capacity, sizeof(double));
        }

        double& operator[] (int i);
        double  operator[] (double i);
};

double& Vector::operator[] (int i)
{
    assert (i >= 0);
    assert (i <  nElements);
    return buffer [i];
}

double Vector::operator[] (double i)
{
    assert (i >= 0);
    assert (i <  nElements);


    int wholePart = (int) (i + 0.05);
    double t = i - (double)wholePart;

    return (-t*(1-t)*(1-t)*buffer[wholePart - 1] + (2 - 5*t*t + 3*t*t*t)*buffer[wholePart] + t*(1 + 4*t - 3*t*t)*buffer[wholePart + 1] + t*t*(1 - t)*buffer[wholePart + 2])/2;

    //printf ("wp = %d, leftInt = %lg, rightInt = %lg  ", wholePart, buffer[wholePart], buffer[wholePart + 1]);


    //return (buffer[wholePart] * (1 - (i - (double)wholePart)) + buffer[wholePart + 1] * (i - (double)wholePart));

}



int massiveInitialization (Vector& v1);
int printGraphic (Vector& v1);
int drawDot (sf::RenderWindow* window, double x, double y);




int main()
{
    Vector v1 (10);

    massiveInitialization (v1);

     printGraphic (v1);




    return 0;
}


int massiveInitialization (Vector& v1)
{
	   /*
    for (double i = 0; i < 10; i = i + 0.1)
    {
        //a = floor (i) + 0.5;
        printf ("i = %lf, wp = %d\n", i, (int) (i + 0.05));
    }

    printf ("\n\n\n\n");
    */
    for (int counter = 0; counter < 10; counter++)
    {
        v1 [counter] = counter * counter;
        printf ("i = %d, x = %.3f\n", counter, v1 [counter]);
    }

    printf ("\n\n\n\n");

    for (double counter = 1; counter <= 9; counter = counter + 0.1)
    {
        printf ("i = %lg, x = %.3f\n", counter, v1 [counter]);
    }
    return 0;
}


int printGraphic (Vector& v1)
{
    //sf::RenderWindow* window = nullptr;
    sf::RenderWindow window(sf::VideoMode(1100, 500), "CutmulRomGraphic");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent (event))
            if (event.type == sf::Event::Closed)
                window.close();

        for (double i = 1; i <= 9; i += 0.1)
        {
            // drawDot (&window, i, v1[i]);
        }



    }

    return 0;
}
/*
int drawDot (sf::RenderWindow* window, double x, double y)
{
    sf::CircleShape circle;

    circle.setRadius (3);
    circle.setFillColor (sf::Color::Red);

    circle.setOrigin (3, 3);
    circle.setPosition (x, y);

    window->draw (circle);
    return 0;
}


*/






/*
{

}
*/
