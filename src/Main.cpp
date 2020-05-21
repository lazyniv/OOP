#include <iostream>
#include "Container.h"
#include "Base.h"
#include "ShapeFactory.h"
#include "Shapes.h"

int main() {
    Container<Shape*> shapes(20);

    ShapeFactory::initRand();

    for(int i = 0; i < 20; i++) {
        try {
            shapes.pushBack(ShapeFactory::createRandomShape());
        } catch(std::exception & e) {
            std::cout << e.what();
        }
    }


    std::cout << "Number of shapes: " << Shape::getCount() << std::endl;

    std::cout << "Info about shapes:\n" << std::endl;

    for(int i = 0; i < shapes.getSize(); i++) {
        std::cout << shapes.getByIndex(i) << std::endl;
    }

    for(int i = 0; i < shapes.getSize(); i++) {
        delete shapes.getByIndex(i);
    }

    std::cout << "After delete of all shapes Shape::getCount() returns " << Shape::getCount() << std::endl;

}