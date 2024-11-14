#include "Dessinable.h"
#include <iostream>
#include <functional> 
#include <random>
using namespace std;

int Dessinable::tirage(int a, int b) const {
	int min(a); int max(b);
	uniform_int_distribution<int> distribution(min, max);
	random_device rd; 
	unsigned int graine(rd());
	default_random_engine generateur(graine);
	auto tir(bind(distribution, generateur));
	return tir();
	/*return (a+b)/2.*/;
}
	
Dessinable::~Dessinable()
{}
