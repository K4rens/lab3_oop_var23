#include "figures.hpp"
#include "array.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <sstream>

TEST(PointTest, DefaultValues) {
    Point p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, Initialization) {
    Point p{1.5, 2.5};
    EXPECT_DOUBLE_EQ(p.x, 1.5);
    EXPECT_DOUBLE_EQ(p.y, 2.5);
}

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {
  
        triangle_points = {{0, 0}, {1, 0}, {0.5, 0.866}};
        
  
        hexagon_points = {{1, 0}, {0.5, 0.866}, {-0.5, 0.866}, 
                         {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}};
     
        octagon_points = {{1, 0}, {0.707, 0.707}, {0, 1}, {-0.707, 0.707},
                         {-1, 0}, {-0.707, -0.707}, {0, -1}, {0.707, -0.707}};
    }

    std::vector<Point> triangle_points;
    std::vector<Point> hexagon_points;
    std::vector<Point> octagon_points;
};


TEST_F(FigureTest, TriangleConstructor) {
    EXPECT_NO_THROW(Triangle triangle);
    EXPECT_NO_THROW(Triangle triangle(triangle_points));
    
    std::vector<Point> wrong_points = {{0, 0}, {1, 0}}; 
    EXPECT_THROW(Triangle triangle(wrong_points), Figure::IncorrectPointsCountException);
}

TEST_F(FigureTest, HexagonConstructor) {
    EXPECT_NO_THROW(Hexagon hexagon);
    EXPECT_NO_THROW(Hexagon hexagon(hexagon_points));
    
    std::vector<Point> wrong_points = {{0, 0}, {1, 0}}; 
    EXPECT_THROW(Hexagon hexagon(wrong_points), Figure::IncorrectPointsCountException);
}

TEST_F(FigureTest, OctagonConstructor) {
    EXPECT_NO_THROW(Octagon octagon);
    EXPECT_NO_THROW(Octagon octagon(octagon_points));
    
    std::vector<Point> wrong_points = {{0, 0}, {1, 0}}; 
    EXPECT_THROW(Octagon octagon(wrong_points), Figure::IncorrectPointsCountException);
}


TEST_F(FigureTest, TriangleSquare) {
    Triangle triangle(triangle_points);
    double area = triangle.square();
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, 0.433, 0.01);
}

TEST_F(FigureTest, HexagonSquare) {
    Hexagon hexagon(hexagon_points);
    double area = hexagon.square();
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, 2.598, 0.01);
}

TEST_F(FigureTest, OctagonSquare) {
    Octagon octagon(octagon_points);
    double area = octagon.square();
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, 2.828, 0.01);
}

TEST_F(FigureTest, TriangleCenter) {
    Triangle triangle(triangle_points);
    Point center = triangle.center();
    EXPECT_NEAR(center.x, 0.5, 0.1);
    EXPECT_NEAR(center.y, 0.289, 0.1);
}

TEST_F(FigureTest, HexagonCenter) {
    Hexagon hexagon(hexagon_points);
    Point center = hexagon.center();
    EXPECT_NEAR(center.x, 0.0, 1e-6);
    EXPECT_NEAR(center.y, 0.0, 1e-6);
}

TEST_F(FigureTest, OctagonCenter) {
    Octagon octagon(octagon_points);
    Point center = octagon.center();
    EXPECT_NEAR(center.x, 0.0, 1e-6);
    EXPECT_NEAR(center.y, 0.0, 1e-6);
}

TEST_F(FigureTest, EmptyFigureExceptions) {
    Triangle triangle;
    EXPECT_THROW(triangle.square(), Figure::EmptyFigureException);
    EXPECT_THROW(triangle.center(), Figure::EmptyFigureException);
    
    std::stringstream ss;
    EXPECT_THROW(ss >> triangle, Figure::EmptyFigureException);
}

TEST_F(FigureTest, AssignmentOperator) {
    Triangle triangle1(triangle_points);
    Triangle triangle2;
    
    triangle2 = triangle1;
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST_F(FigureTest, EqualityOperator) {
    Triangle triangle1(triangle_points);
    Triangle triangle2(triangle_points);
    
    EXPECT_TRUE(triangle1 == triangle2);
    
    std::vector<Point> different_points = {{0, 0}, {2, 0}, {1, 1}};
    Triangle triangle3(different_points);
    EXPECT_FALSE(triangle1 == triangle3);
}

class FiguresArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        triangle = new Triangle({{0, 0}, {1, 0}, {0.5, 0.866}});
        hexagon = new Hexagon({{1, 0}, {0.5, 0.866}, {-0.5, 0.866}, 
                              {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}});
        octagon = new Octagon({{1, 0}, {0.707, 0.707}, {0, 1}, {-0.707, 0.707},
                              {-1, 0}, {-0.707, -0.707}, {0, -1}, {0.707, -0.707}});
    }

    void TearDown() override {
        delete triangle;
        delete hexagon;
        delete octagon;
    }

    Figure* triangle;
    Figure* hexagon;
    Figure* octagon;
};

TEST_F(FiguresArrayTest, DefaultConstructor) {
    FiguresArray array;
    EXPECT_EQ(array.getSize(), 0);
}

TEST_F(FiguresArrayTest, InitializerListConstructor) {
    FiguresArray array = {triangle, hexagon, octagon};
    EXPECT_EQ(array.getSize(), 3);
}

TEST_F(FiguresArrayTest, VectorConstructor) {
    std::vector<const Figure*> figures = {triangle, hexagon};
    FiguresArray array(figures);
    EXPECT_EQ(array.getSize(), 2);
}

TEST_F(FiguresArrayTest, SizeConstructor) {
    FiguresArray array(3, triangle);
    EXPECT_EQ(array.getSize(), 3);
}

TEST_F(FiguresArrayTest, PushBack) {
    FiguresArray array;
    array.pushBack(triangle);
    array.pushBack(hexagon);
    EXPECT_EQ(array.getSize(), 2);
}

TEST_F(FiguresArrayTest, Remove) {
    FiguresArray array = {triangle, hexagon, octagon};
    array.remove(1);
    EXPECT_EQ(array.getSize(), 2);
}

TEST_F(FiguresArrayTest, RemoveInvalidIndex) {
    FiguresArray array = {triangle};
    EXPECT_THROW(array.remove(5), FiguresArray::InvalidIndexException);
}

TEST_F(FiguresArrayTest, SumOfSquares) {
    FiguresArray array = {triangle, hexagon, octagon};
    double sum = array.sumOfSquares();
    EXPECT_GT(sum, 0.0);
    
    double expected_sum = triangle->square() + hexagon->square() + octagon->square();
    EXPECT_NEAR(sum, expected_sum, 1e-6);
}

TEST_F(FiguresArrayTest, CopyConstructor) {
    FiguresArray original = {triangle, hexagon};
    FiguresArray copy(original);
    EXPECT_EQ(copy.getSize(), original.getSize());
}

TEST_F(FiguresArrayTest, MoveConstructor) {
    FiguresArray original = {triangle, hexagon};
    FiguresArray moved(std::move(original));
    EXPECT_EQ(moved.getSize(), 2);
    EXPECT_EQ(original.getSize(), 0);
}

TEST_F(FiguresArrayTest, PrintMethods) {
    FiguresArray array = {triangle, hexagon};

    EXPECT_NO_THROW(array.printCenters());
    EXPECT_NO_THROW(array.printSquares());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
