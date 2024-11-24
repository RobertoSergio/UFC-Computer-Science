
double problema1_exponecial_dupla(double x);

double problema1_exponecial_simples(double s);

double problema2_exponecial_dupla(double x);

double problema2_exponecial_simples(double s);

void integracao(double a, double b, double epsilon, int problema, int forma, int metodo);

double abordagem_fechada_grau3(double xi, double xf, double (*func)(double));

double abordagem_aberta_grau3(double xi, double xf, double (*func)(double));

double gauss_legendre_4pontos(double xi, double xf, double (*func)(double));

double gauss_legendre_3pontos(double xi, double xf, double (*func)(double));

double gauss_legendre_2pontos(double xi, double xf, double (*func)(double));