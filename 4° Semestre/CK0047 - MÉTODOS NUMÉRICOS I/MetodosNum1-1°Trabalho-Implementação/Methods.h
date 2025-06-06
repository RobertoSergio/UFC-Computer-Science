#pragma once
#include "Format.h"
#include <cmath>
#include <iostream>

double funcao(double d, double a);
double derivada(double d, double a);

std::pair<double, std::map<int, std::vector<double>>>
newton_raphson(double a, double x0, double epsilon1, double epsilon2);

std::pair<double, std::map<int, std::vector<double>>>
newton_modificado(double a, double x0, double epsilon1, double epsilon2);

std::pair<double, std::map<int, std::vector<double>>>
secante(double a, double x0, double x1, double epsilon1, double epsilon2);