#include <iostream>
#include <cstring> // added cstring

struct Point {
    int x, y;

    Point () : x(), y() {}
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
    public:
        int vertices;
        Point** points;

        Shape (int _vertices) {
            vertices = _vertices;
            points = new Point*[vertices+1];
        }

        ~Shape () { // need to delete all points in points array first, then delete the points array
            for(int i = 0; i < vertices; i++) {
                delete points[i];
            }
            delete[] points;
        }

        void addPoints (Point* pts) { // /* formal parameter for unsized array called pts */) {
           // for (int i = 0; i <= vertices; i++) {
           //     memcpy(points[i], &pts[i%vertices], sizeof(Point));
           // }
	    for (int i = 0; i < vertices; i++) { // memcpy method proved unsuccessful; switched to manual version to initialize the new points
		points[i] = new Point(pts[i]);
	    }
        }

        double area () { // removed the double* return type, as there was no need to have the return type be a pointer
            int temp = 0;
            for (int i = 0; i < vertices; i++) { // for loop going out of bounds, so removed the =
                // FIXME: there are two methods to access members of pointers
                //        use one to fix lhs and the other to fix rhs
                int lhs = points[i]->x * points[(i+1) % vertices]->y;
                int rhs = (*points[(i+1) % vertices]).x * (*points[i]).y;
                temp += (lhs - rhs);
            }
            double area = abs(temp)/2.0;
            return area; // removed the & (see above comment)
        }
};

int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
    //          tri1 = (0, 0)
    //          tri2 = (1, 2)
    //          tri3 = (2, 0)
    struct Point tri1;
    tri1.x = 0;
    tri1.y = 0;

    struct Point tri2 = {1, 2};

    struct Point tri3 = Point(2, 0);
    // adding points to tri
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)

    struct Point quad1 = {0, 0};
    struct Point quad2 = {0, 2};
    struct Point quad3 = {2, 2};
    struct Point quad4 = {2, 0};

    // adding points to quad
    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    std::cout << tri->area() << std::endl;
    std::cout << quad->area() << std::endl;
    delete tri;
    delete quad;
}
