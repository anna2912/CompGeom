#include "PointInPolygon.h"

using namespace std;

namespace geom {
namespace algorithms {
namespace point_in_poly {


bool leftOrientation (int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) >= 0;
}

bool leftOrientationStrict (int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0;
}

/*struct point {
	int x;
	int y;
};*/

bool noSelfCrossings(vector <point_type> vertices) {
    int n = vertices.size();
    if (n < 4)
        return true;

    for(int i = 0; i <= n - 1; i++) {
        for(int j = (i + 2) % n; j <= (n+ i - 2) % n; j++) {
            if(leftOrientationStrict(vertices[i].x,vertices[i].y,vertices[(i+1)%n].x,vertices[(i+1)%n].y,vertices[j].x,vertices[j].y) !=
                    leftOrientationStrict(vertices[i].x,vertices[i].y,vertices[(i+1)%n].x,vertices[(i+1)%n].y,vertices[(j+1)%n].x,vertices[(j+1)%n].y) &&
                    leftOrientationStrict(vertices[j].x,vertices[j].y,vertices[(j+1)%n].x,vertices[(j+1)%n].y,vertices[i].x,vertices[i].y) !=
                    leftOrientationStrict(vertices[j].x,vertices[j].y,vertices[(j+1)%n].x,vertices[(j+1)%n].y,vertices[(i+1)%n].x,vertices[(i+1)%n].y)) {
                return false;
            }
        }
    }
    return true;
}

bool isConvex(vector <point_type> vertices) {
    int n = vertices.size();
    for(int i = 0; i <= n - 1; i++) {
        int j = (i+1)%n;
        int k = (i+2)%n;
        if (!leftOrientationStrict(vertices[i].x,vertices[i].y,vertices[j].x,vertices[j].y,vertices[k].x,vertices[k].y))
            return false;
    }
    return true;
}

bool BinarySearch(vector <point_type> vertices, point_type pt, bool newPts) {
    int n = vertices.size();

    if(newPts) {
        int minInd = 0;
        for (int i = 1; i < n; i++) {
            if(vertices[i].x < vertices[minInd].x || vertices[i].x == vertices[minInd].x && vertices[i].y < vertices[minInd].y){
                minInd = i;
            }
        }
        rotate(vertices.begin(), vertices.begin() + minInd, vertices.end());
    }

	if (pt.x <  vertices[0].x) {
		return false;
	}
	else {
        if(!leftOrientation(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y, pt.x, pt.y) ||
                leftOrientationStrict(vertices[0].x, vertices[0].y, vertices[n-1].x, vertices[n-1].y, pt.x, pt.y)) {
            return false;
        }
        else {
			int first = 1;
			int last = n-1;
			int middle;

			while (first < last - 1) {
				middle = (first + last) / 2;
                if(!leftOrientation(vertices[0].x, vertices[0].y, vertices[middle].x, vertices[middle].y, pt.x, pt.y))
				{
					last = middle;
				}
				else
				{
					first = middle;
				}
			}

			if (leftOrientation(vertices[last-1].x, vertices[last-1].y, vertices[last].x, vertices[last].y, pt.x, pt.y)) {
				return true;
			}
			else {
				return false;
			}
        }
	}
}

bool CrossingNumber(vector <point_type> vertices, point_type pt) {
    int n = vertices.size();
	bool ans = false;

	for (int i = 0; i < n; i++) {

        int j = (i + 1) % n;

        if(vertices[i].x == vertices[j].x && vertices[i].x == pt.x){
            if((vertices[i].y >= pt.y) != (vertices[j].y >= pt.y))
                return true;
            else
                return false;
        }

        if(vertices[i].y == vertices[j].y && vertices[i].y == pt.y){
            if((vertices[i].x >= pt.x) != (vertices[j].x >= pt.x))
                return true;
            else
                return false;
        }

        if((pt.x - vertices[i].x) * (vertices[j].y - vertices[i].y) == (pt.y - vertices[i].y) * (vertices[j].x - vertices[i].x)){
            if((pt.x == vertices[i].x) || ((pt.x - vertices[i].x) > 0 ) == ((vertices[j].x - vertices[i].x) > 0 ) &&
                    (abs((pt.x - vertices[i].x)) <= abs((vertices[j].x - vertices[i].x))) )
                return true;
        }

        if( (vertices[i].y > pt.y) != (vertices[j].y > pt.y)){

			int ind1, ind2;
			if(vertices[i].y < vertices[j].y) {
				ind1 = i;
				ind2 = j;
			}
			else {
				ind1 = j;
				ind2 = i;
			}
			if (leftOrientationStrict(vertices[ind1].x, vertices[ind1].y, vertices[ind2].x, vertices[ind2].y, pt.x, pt.y)) {
				ans = !ans;
			}
		}
	}
	return ans;
}

}}}

/*int main(){
	
	ifstream input("pointinpolygon.in");
	ofstream output("pointinpolygon.out");

	int n;
	input >> n;
	vector <point> vertices(n);
	
	for (int i = 0; i < n; i++) {
		input >> vertices[i].x;
		input >> vertices[i].y;
	}
	
	point pt;
	input >> pt.x;
	input >> pt.y;

	if (BinarySearch(n, vertices, pt))
		output << "Yes\n";
	else
		output << "No\n";

	if (CrossingNumber(n, vertices, pt))
		output << "Yes\n";
	else
		output << "No\n";
	
	input.close();
	output.close();

	return 0;
}*/
