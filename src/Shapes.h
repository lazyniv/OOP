#ifndef SHAPES_H
#define SHAPES_H

#include <cmath>
#include "Base.h"
#include "Container.h"

class Shape : public virtual Printable {
    public:
        static int getCount() {
            return sm_count;
        }

        friend std::ostream & operator<<(std::ostream & out, Shape * shape) {
            return out << shape->getInfo();
        }

        Shape() {
            ++sm_count;
        }

        virtual ~Shape() {
            --sm_count;
        }

    private:
        static int sm_count;
};

int Shape::sm_count = 0; 


class Point : public Shape, public virtual Named {
    public:
        Point(double x, double y):
            Named("Point"),
            m_x(x),
            m_y(y) {}

        Point(Point const & other):
            Named("Point"),
            m_x(other.m_x),
            m_y(other.m_y) {}

        double getX() const {
            return m_x;
        }

        double getY() const {
            return m_y;
        }
        
        std::string getInfo() const {
            return Named::getInfo() + "{" + std::to_string(m_x) + ", " + std::to_string(m_y) + "}\n";
        }
    private:
        double m_x;
        double m_y;
};

class Circle : public Shape, public Named {
    public:
        Circle(Point & center, double const radius): 
            Named("Circle"),
            m_center(center),
            m_radius(radius) {}

        double getArea() const {
            return M_PI * m_radius * m_radius;
        }

        double getLength() const {
            return 2 * M_PI * m_radius;
        }
        
        std::string getInfo() const {
            return Named::getInfo() + " {\n" 
            + "\tCenter: " + m_center.getInfo() + 
            + "\tRadius: " + std::to_string(m_radius) + "\n"
            + "\tArea: " + std::to_string(getArea()) + "\n"
            + "\tPerimeter: " + std::to_string(getLength()) + "\n}\n"; 
        }
        
    private:
        Point m_center;
        double m_radius;
};

class Rect : public virtual Shape, public virtual Named {
    public:
        Rect(Point const & firstPoint, Point const & secondPoint): 
            Named("Rectangle"),
            m_firstPoint(firstPoint),
            m_secondPoint(secondPoint) {}

        Rect(double const firstPoint_x, double const firstPoint_y, double const secondPoint_x, double const secondPoint_y):
            Rect(Point(firstPoint_x, firstPoint_y), Point(secondPoint_x, secondPoint_y)) {}
        
        Rect(Point const & lowerLeft, double const width, double const height):
            Rect(lowerLeft, Point(lowerLeft.getX() + width, lowerLeft.getY() + height)) {}

        std::string getInfo() const {
            return Named::getInfo() + " {\n" 
            + "\tLower left point: " + m_firstPoint.getInfo() + 
            + "\tUpper right point: " + m_secondPoint.getInfo() + 
            + "\tArea: " + std::to_string(getArea()) + "\n"
            + "\tPerimeter: " + std::to_string(getPerimeter()) + "\n}\n"; 
        }

        double getArea() const {
            return abs(m_firstPoint.getX() - m_secondPoint.getX()) * abs(m_firstPoint.getY() - m_secondPoint.getY());
        }

        double getPerimeter() const {
            return 2 * abs(m_firstPoint.getX() - m_secondPoint.getX()) + 2 * abs(m_firstPoint.getY() - m_secondPoint.getY());
        }
    
    protected:
        Point m_firstPoint;
        Point m_secondPoint;
};


class Square : public Shape, public Named {
    public:
        Square(Point const & lowerLeft, double const width): 
            Named("Square"),
            m_lowerLeft(lowerLeft),
            m_width(width) {}
        
        std::string getInfo() const {
             return Named::getInfo() + " {\n" 
            + "\tLower left point: " + m_lowerLeft.getInfo() + 
            + "\tWidth: " + std::to_string(m_width) + 
            + "\tArea: " + std::to_string(getArea()) + "\n"
            + "\tPerimeter: " + std::to_string(getPerimeter()) + "\n}\n"; 
        }

        double getArea() const {
            return m_width * m_width;
        }

        double getPerimeter() const {
            return 4 * m_width;
        }
    private:
        Point m_lowerLeft;
        double m_width;
};

class Polyline : public Shape, public Named {
    public:
        Polyline(Container<Point> & points, std::string const & name = "Polyline"): 
            Named(name),
            m_points(points) {}

        Polyline(Polyline const & other, std::string const & name = "Polyline"):
            Named(name),
            m_points(other.m_points) {}

        Polyline(std::string const & name = "Polyline"):
            Named(name) {}

        virtual ~Polyline() {}

        void addPoint(Point const & point) {
            m_points.pushBack(point);
        }

        double getLength() const {
            double result = 0;
            for(int i = 0; i < m_points.getSize() - 1; i++) {
                result += lineLength(m_points.getByIndex(i), m_points.getByIndex(i+1));
            }
            return result;
        }

        std::string getInfo() const {
            return Named::getInfo() + " {\n" 
            + "\tPoints: {\n" + getPointsAsString() + "\t}\n"
            + "\tLength: " + std::to_string(getLength()) + "\n}\n";
        }

        double lineLength(Point const & p1, Point const & p2) const {
            return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
        }

        std::string getPointsAsString() const {
            std::string result;
            for(int i = 0; i < m_points.getSize(); i++) {
                result += "\t\t" + m_points.getByIndex(i).getInfo() + "\n";
            }

            return result;
        }
    
    protected:
        Container<Point> m_points;
};

class Polygon : public Polyline {
    public:
        Polygon(Container<Point> & points):
            Polyline(points, "Polygon") {}

        Polygon():
            Polyline("Polygon") {}

        Polygon(Polyline const & polyline):
            Polyline(polyline, "Polygon") {}

        double getLength() const {
            return Polyline::getLength() + lineLength(m_points.getByIndex(0), m_points.getByIndex(m_points.getSize() - 1));
        }

        std::string getInfo() const {
            return Polyline::getInfo();
        }
};

#endif

