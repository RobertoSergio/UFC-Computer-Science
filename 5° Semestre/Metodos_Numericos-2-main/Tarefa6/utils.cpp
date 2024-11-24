#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Função para calcular os polinômios de Hermite de grau 1
double pol_hermite_1(double x) {
    return 2*x;
}

// Função para calcular os polinômios de Hermite de grau 2
double pol_hermite_2(double x) {
    return 4 * pow(x, 2) - 2;
}

// Função para calcular os polinômios de Hermite de grau 3
double pol_hermite_3(double x) {
    cout << 8 * pow(x, 3) - 12;
    return 8 * pow(x, 3) - 12;
}

// Função para calcular as raízes de Hermite para n = 2
vector<double> raiz_hermite_2() {
    return { -1.0 / sqrt(2.0), 1.0 / sqrt(2.0) };
}

// Função para calcular as raízes de Hermite para n = 3
vector<double> raiz_hermite_3() {
    return { -sqrt(3.0 / 2.0), 0.0, sqrt(3.0 / 2.0) };
}

// Função para calcular as raízes de Hermite para n = 4
vector<double> raiz_hermite_4() {
    return { -sqrt((3.0 + sqrt(6.0)) / 2.0), 
             -sqrt((3.0 - sqrt(6.0)) / 2.0), 
              sqrt((3.0 - sqrt(6.0)) / 2.0), 
              sqrt((3.0 + sqrt(6.0)) / 2.0) };
}

// Função para calcular os pesos de Hermite para n = 2
vector<double> w_de_hermite_2(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 2; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = (pow(2, 2 - 1) * fatorial * sqrt(pi)) / (pow(2, 2) * pow(pol_hermite_1(raiz), 2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Hermite para n = 3
vector<double> w_de_hermite_3(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 3; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = (pow(2, 3 - 1) * fatorial * sqrt(pi)) / (pow(3, 2) * pow(pol_hermite_2(raiz), 2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Hermite para n = 4
vector<double> w_de_hermite_4(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 4; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = (pow(2, 3) * fatorial * sqrt(pi)) / (pow(4, 2) * pow(pol_hermite_3(raiz), 2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// Função para calcular os polinômios de Laguerre de grau 1
double pol_Laguerre_1(double x) {
    return -x+1;
}

// Função para calcular os polinômios de Laguerre de grau 2
double pol_Laguerre_2(double x) {
    return (pow(x,2)-4*x+2)/2;
}

// Função para calcular os polinômios de Laguerre de grau 3
double pol_Laguerre_3(double x) {
    return (-pow(x,3)+9*pow(x,2)-18*x+6)/2;
}

// Função para calcular as raízes de Laguerre para n = 2
vector<double> raiz_Laguerre_2() {
    return { 2 - sqrt(2.0), 2 + sqrt(2.0) };
}

// Função para calcular as raízes de Laguerre para n = 3
vector<double> raiz_Laguerre_3() {
    return { 0.4157745568, 2.2942803603, 6.2899450829 };
}

// Função para calcular as raízes de Laguerre para n = 4
vector<double> raiz_Laguerre_4() {
    return { 0.1293, 0.7010, 1.7587, 3.6311};
}

// Função para calcular os pesos de Laguerre para n = 2
vector<double> w_de_Laguerre_2(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 2; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = raiz/(pow(2+1,2)*pow(pol_Laguerre_1(raiz),2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Laguerre para n = 3
vector<double> w_de_Laguerre_3(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 3; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = raiz/(pow(3+1,2)*pow(pol_Laguerre_2(raiz),2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Laguerre para n = 4
vector<double> w_de_Laguerre_4(const vector<double>& raizes) {
    int fatorial = 1;
    double pi = 3.141592653589793;

    for (int i = 4; i >= 1; i--) {
        fatorial *= i;
    }

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = raiz/(pow(4+1,2)*pow(pol_Laguerre_3(raiz),2));
        pesos.push_back(resultado);
    }

    return pesos;
}

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// -----------------------------------------------------------------

// Função para calcular as raízes de Chebyshev para n = 2
vector<double> raiz_Chebyshev_2() {
    return { -1.0 / sqrt(2.0), 1.0 / sqrt(2.0) };
}

// Função para calcular as raízes de Chebyshev para n = 3
vector<double> raiz_Chebyshev_3() {
    return { -sqrt(3.0 / 2.0), 0.0, sqrt(3.0 / 2.0) };
}

// Função para calcular as raízes de Chebyshev para n = 4
vector<double> raiz_Chebyshev_4() {
    return { -1.0, -0.5 , 0.5 ,  1.0 };
}

// Função para calcular os pesos de Chebyshev para n = 2
vector<double> w_de_Chebyshev_2(const vector<double>& raizes) {
    double pi = 3.141592653589793;

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = pi/2;
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Chebyshev para n = 3
vector<double> w_de_Chebyshev_3(const vector<double>& raizes) {
    double pi = 3.141592653589793;

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = pi/3;
        pesos.push_back(resultado);
    }

    return pesos;
}

// Função para calcular os pesos de Chebyshev para n = 4
vector<double> w_de_Chebyshev_4(const vector<double>& raizes) {
    double pi = 3.141592653589793;

    vector<double> pesos;
    for (double raiz : raizes) {
        double resultado = pi/4;
        pesos.push_back(resultado);
    }

    return pesos;
}