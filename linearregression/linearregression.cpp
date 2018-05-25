#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

class polynomial {
    vector<double> factors;

public:
    polynomial(vector<double>& factors) {
        this->factors = factors;
    }

    void consolelog() {
        for (int i = 0; i < factors.size() - 2; ++i) {
            cout << factors[i] << "x^" << factors.size()-(i+1) << " + ";
        }
        if (factors.size() > 1) {
            cout << factors[factors.size()-2] << "x + ";
        }
        if (factors.size() > 0) {
            cout << factors[factors.size()-1] << endl;
        }
    }

    string toString() {
        string newstr = "";
        for (int i = 0; i < factors.size() - 2; ++i) {
            newstr += to_string(factors[i]) + "x^" + to_string(factors.size()-(i+1)) + " + ";
        }
        if (factors.size() > 1) {
            newstr += to_string(factors[factors.size()-2]) + "x + ";
        }
        if (factors.size() > 0) {
            newstr += to_string(factors[factors.size()-1]);
        }
        return newstr;
    }

    polynomial derivative() {
        vector<double> poly;
        for (int i = 0; i < factors.size() - 2; ++i) {
            poly.push_back(factors[i] * (factors.size()-(i+1)));
        }
        if (factors.size() > 1) {
            poly.push_back(factors[factors.size()-2]);
        }
        return polynomial(poly);
    }
};


class lequation {
    double m;
    double b;

public:
    lequation(double m, double b) {
        this->m = m;
        this->b = b;
    }

    double operator()(double x) {
        return (m * x) + b;
    }

    double xintercept() {
        return (-b) / m;
    }

    double yintercept() {
        return b;
    }

    double areaunder() {
        return (xintercept() * yintercept()) / 2;
    }

    void consolelog() {
        cout << "y = " << m << "x + " << b << endl;
    }

    string toString() {
        string le("y = " + to_string(m) + "x + " + to_string(b));
        return le;
    }
};

class Statistics {
public:
    Statistics() {}

    template<typename T>
    static double getMean(T& datapoints) {
        double sum = 0;
        for (int i = 0; i < datapoints.size(); ++i) {
            sum += datapoints[i];
        }
        return sum / datapoints.size();
    }

    template<typename T>
    static double standardDeviation(T& datapoints, double mean) {
        double sum = 0;
        for (int i = 0; i < datapoints.size(); ++i) {
            double tmp = datapoints[i] - mean;
            sum += tmp * tmp;
        }
        double totalvariation = sum / (datapoints.size() - 1);
        return sqrt(totalvariation);    
    }

    template<typename T>
    static double zscore(T xsubi, double mean, double sd) {
        return (xsubi - mean) / sd;
    }

    template<typename T>
    static double correlationCoefficient(T& xdata, T& ydata, double xmean,
                                    double ymean, double xsd, double ysd) {
        double sum = 0;
        for (int i = 0; i < xdata.size(); ++i) {
            sum += zscore(xdata[i], xmean, xsd) * zscore(ydata[i], ymean, ysd);
        }
        return sum / (xdata.size() - 1);
    }

    static double slope(double sdx, double sdy, double cc) {
        return (sdy / sdx) * cc;
    }

    static double getB(double xmean, double ymean, double slope) {
        return ymean - (xmean*slope);
    }

    template<typename T>
    static lequation linearRegression(T& datax, T& datay) {
        double meanx = getMean(datax);
        double meany = getMean(datay);
        double sdx = standardDeviation(datax, meanx);
        double sdy = standardDeviation(datay, meany);
        double cc = correlationCoefficient(datax, datay, meanx, meany, sdx, sdy);
        double m = slope(sdx, sdy, cc);
        return move(lequation(m, getB(meanx, meany, m)));
    }
};

int main() {
    vector<double> datax1 = {1, 2, 3, 4, 5};
    vector<double> datay1 = {2, 4, 6, 8, 10};

    vector<double> datax2 = {1, 2, 3, 4, 5};
    vector<double> datay2 = {4, 8, 12, 16, 20};

    vector<double> datax3 = {0, 4, 2, 1, 5};
    vector<double> datay3 = {2, 4, 6, 8, 10};

    lequation le1 = Statistics::linearRegression(datax1, datay1);
    lequation le2 = Statistics::linearRegression(datax2, datay2);
    lequation le3 = Statistics::linearRegression(datax3, datay3);

    le1.consolelog();
    le2.consolelog();
    le3.consolelog();

    cout << "x1 intercept: " << le1.xintercept() << endl;
    cout << "y1 intercept: " << le1.yintercept() << endl;
    cout << "x2 intercept: " << le2.xintercept() << endl;
    cout << "y2 intercept: " << le2.yintercept() << endl;
    cout << "x3 intercept: " << le3.xintercept() << endl;
    cout << "y3 intercept: " << le3.yintercept() << endl;

    cout << "area under 1: " << le1.areaunder() << endl;
    cout << "area under 2: " << le2.areaunder() << endl;
    cout << "area under 3: " << le3.areaunder() << endl;

    cout << le1.toString() << endl;
    cout << le2.toString() << endl;
    cout << le3.toString() << endl;

    cout << le1(5) << endl;
    cout << le2(5) << endl;
    cout << le3(5) << endl;

    vector<double> poly1 = {2, 1, 5, 4, 5};
    polynomial poly(poly1);
    poly.consolelog();
    cout << poly.toString() << endl;
    poly.derivative().consolelog();

    return 0;
}