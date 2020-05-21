#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <cstdlib>
#include <cmath>
#include "Shapes.h"

const double ABS_COORDINATE_BOUND = 1000.0;
const int MAX_VERTICES = 15;
const int SHAPES_COUNT = 6;

enum ShapeType {
    POINT,
    CIRCLE,
    RECTANGLE,
    SQUARE,
    POLYLINE,
    POLYGON
};

class ShapeFactory
{
public:

    static void initRand() {
        std::srand((unsigned int)time(NULL));
    }
    
    static Shape * createShape(ShapeType const type) {
        switch (type) {
            case POINT:
                return createPoint();
            case CIRCLE:
                return createCircle();
            case RECTANGLE:
                return createRectangle();
            case SQUARE:
                return createSquare();
            case POLYLINE:
                return createPolyline();
            case POLYGON:
                return createPolygon();
            default:
		        throw std::runtime_error("ShapeFactory::createShape(ShapeType const type): invalid type.");
		    break; 
        };
    }

    static Shape * createRandomShape() {
        return createShape(static_cast<ShapeType>(rand() % SHAPES_COUNT));
    }

private:
    static Point * createPoint() {
        double x = getRandomDouble(-ABS_COORDINATE_BOUND, ABS_COORDINATE_BOUND);
        double y = getRandomDouble(-ABS_COORDINATE_BOUND, ABS_COORDINATE_BOUND);
        return new Point(x,y);
    }

    static Circle * createCircle() {
        double radius = abs(getRandomDouble(-ABS_COORDINATE_BOUND, ABS_COORDINATE_BOUND));
        Point * center = createPoint();
        Circle * circle = new Circle(*center, radius);  
        delete center; 
        return circle;
    }

    static Rect * createRectangle() {
        Point * firstPoint = createPoint();
        Point * secondPoint = createPoint();
        Rect * rectangle = new Rect(*firstPoint, *secondPoint);
        delete firstPoint;
        delete secondPoint;
        return rectangle;
    }

    static Square * createSquare() {
        Point * lowerLeft = createPoint();
        double width = abs(getRandomDouble(-ABS_COORDINATE_BOUND, ABS_COORDINATE_BOUND));
        Square * square = new Square(*lowerLeft, width);
        delete lowerLeft; 
        return square;
    }

    static Polyline * createPolyline() {
        int numVerticies = getRandomInt(MAX_VERTICES);
        Container<Point> points; 
        Point * p;
        for(int i = 0; i < numVerticies; i++) {
            p = createPoint();
            points.pushBack(*p);
            delete p;
        }
        return new Polyline(points);
    }

    static Polygon * createPolygon() {
        int numVerticies = getRandomInt(MAX_VERTICES);
        Container<Point> points; 
        Point * p;
        for(int i = 0; i < numVerticies; i++) {
            p = createPoint();
            points.pushBack(*p);
            delete p;
        }
        return new Polygon(points);
    }

    static double getRandomDouble(double lowerBound, double upperBound) {
        double randDouble = (double) rand() / RAND_MAX;
        return lowerBound + randDouble * (upperBound - lowerBound);
    }

    static int getRandomInt(int upperBound) {
        return rand() % MAX_VERTICES  + 1;
    }
};

#endif