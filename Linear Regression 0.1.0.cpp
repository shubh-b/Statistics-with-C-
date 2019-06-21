# include <iostream>
# include <vector>
# include <numeric>
# include <cmath>

using namespace std;

double getSlope(vector<double> &x, vector<double> &y)

{
double sx = accumulate(x.begin(), x.end(), 0);
double sy = accumulate(y.begin(), y.end(), 0);
double sxx = inner_product(x.begin(), x.end(), x.begin(), 0);
double sxy = inner_product(x.begin(), x.end(), y.begin(), 0);
int n = (x.size());

double nr = n*sxy - sx*sy;
double denr = n*sxx - sx*sx;

if(denr!=0)
{
return nr/denr;
}
}

double getIntercept(vector<double> &x, vector<double> &y, double slope)

{
double sx = accumulate(x.begin(), x.end(), 0);
double sy = accumulate(y.begin(), y.end(), 0);
int n = (x.size());
return (sy - slope*sx)/n;
}

// slope: a
// intercept: b
// derivative of slope: da
// derivative of intercept: db

double getCost(vector<double> &x, vector<double> &y, double a, double b, double &da, double &db)
{
int n = (x.size());
double sx = accumulate(x.begin(), x.end(), 0);
double sy = accumulate(y.begin(), y.end(), 0);
double sxx = inner_product(x.begin(), x.end(), x.begin(), 0);
double sxy = inner_product(x.begin(), x.end(), y.begin(), 0);
double syy = inner_product(y.begin(), y.end(), y.begin(), 0);
double cost = syy - 2*a*sxy - 2*b*sy + a*a*sxx + 2*a*b*sx + n*b*b;

cost /= n;
da = 2*(- sxy + a*sxx + b*sx)/n;
db = 2*(- sy + a*sx + n*b)/n;

return cost;
}

void linearRegression(vector<double> &x, vector<double> &y, double slope = 1, double intercept = 0)
{
double lrate = 0.0002;
double threshold = 0.0001;
int iter = 0;
while(true)
{
double da = 0;
double db = 0;
double cost = getCost(x, y, slope, intercept, da, db);
if(iter%1000 == 0)

{
//cout<<"Iter: " << iter << " cost = " << cost << " da = " << da << " db = " << db << endl;
}
iter++;

if(abs(da) < threshold && abs(db) < threshold)
{
cout << "y = " << slope << " * x + " << "(" << intercept << ")" << endl;
break;
}
slope -= lrate* da;
intercept -= lrate * db;
}
}

int main() {
vector <double> x = {38, 40, 31, 32, 28, 37, 32, 39, 30, 34, 31};
vector <double> y = {124, 147, 118, 132, 123, 144, 109, 174, 96, 132, 105};

// initialize with random two points

cout<< "Initialization with random pair of points from the data" << endl;
vector <double> xSub = {31, 32};
vector <double> ySub = {118, 132};
double slopeSub = getSlope(xSub,ySub);
double interceptSub = getIntercept(xSub, ySub, slopeSub);

cout << "y = " << slopeSub << " * x + " << "(" << interceptSub << ")" << endl;
linearRegression(x, y, slopeSub, interceptSub);

cout << "Compare with ground truth" << endl;

double slope = getSlope(x,y);
double intercept = getIntercept(x, y, slope);

cout << "y = " << slope << " * x + " << "(" << intercept << ")" <<endl;

double x_value;
cout << "\nEnter a value for x: ";
cin >> x_value;

cout << "The value for y is " << x_value*slope + intercept << endl;

return 0;

}
