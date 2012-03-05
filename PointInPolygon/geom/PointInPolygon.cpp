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

bool BinarySearch(vector <point_type> vertices, point_type pt) {
    int n = vertices.size();
	int minInd = 0;
	for (int i = 1; i < n; i++) {
		if(vertices[i].x < vertices[minInd].x || vertices[i].x == vertices[minInd].x && vertices[i].y < vertices[minInd].y){
			minInd = i;
		}
	}
	rotate(vertices.begin(), vertices.begin() + minInd, vertices.end());

	vector <double> angles(n);

	for (int i = 1; i < n; i++) {
		angles[i] = atan2((vertices[i].y - vertices[0].y)*1.0, vertices[i].x - vertices[0].x);
	}

	if (pt.x <  vertices[0].x) {
		return false;
	}
	else {
		double ptAngle = atan2((pt.y - vertices[0].y)*1.0, pt.x - vertices[0].x);
		if(ptAngle < angles[1] || ptAngle > angles[n-1]){
			return false;
		}
		else {
			int first = 1;
			int last = n-1;
			int middle;

			while (first < last - 1) {
				middle = (first + last) / 2;
				if (ptAngle < angles[middle])
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
		if(vertices[i].x == pt.x && vertices[i].y == pt.y) 
			return true;

		int j = (i + 1) % n;
		if( (vertices[i].y > pt.y) != (vertices[j].y > pt.y)){
			if((pt.x - vertices[i].x) * (vertices[j].y - vertices[i].y) == (pt.y - vertices[i].y) * (vertices[j].x - vertices[i].x)) 
				return true;
			
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
