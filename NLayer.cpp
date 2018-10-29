#include <iostream>
#include <ctime>
#include <cmath>
#include "NLayer.h"
using namespace std;

void NLayer::SigmLayer()
{
	for (int i = 0; i < numNeur; ++i) {
		layer[i] = 1. / (1 + exp(-2 * layer[i]));
	}
}

NLayer::NLayer(int numPrevNeur, int numNeur, double lRate)
{
	this->numPrevNeur = numPrevNeur;
	this->numNeur = numNeur;
	this->lRate = lRate;

	layer = new double[numNeur];
	error = new double[numNeur];
	delta = new double[numNeur];
	rateNeur = new double*[numNeur];
	for (int i = 0; i < numNeur; ++i) {
		rateNeur[i] = new double[numPrevNeur];
	}

	srand(time(nullptr));
	for (int i = 0; i < numNeur; ++i) {
		for (int j = 0; j < numPrevNeur; ++j) {
			rateNeur[i][j] = (rand() % 201 - 100) / 100.;
		}
	}
}

NLayer::NLayer()
{
	numPrevNeur = 0;
	numNeur = 0;
	lRate = 0;

	layer = new double[numNeur];
	error = new double[numNeur];
	delta = new double[numNeur];
	rateNeur = new double*[numNeur];
	for (int i = 0; i < numNeur; ++i) {
		rateNeur[i] = new double[numPrevNeur];
	}

	srand(time(nullptr));
	for (int i = 0; i < numNeur; ++i) {
		for (int j = 0; j < numPrevNeur; ++j) {
			rateNeur[i][j] = (rand() % 201 - 100) / 100.;
		}
	}
}

NLayer::~NLayer()
{
	delete[] layer;
	delete[] error;
	delete[] delta;
	for (int i = 0; i < numNeur; ++i) {
		delete[] rateNeur[i];
	}
	delete[] rateNeur;
}

void NLayer::set_layer(int numPrevNeur, int numNeur, double lRate)
{
	delete[] layer;
	delete[] error;
	delete[] delta;
	for (int i = 0; i < this->numNeur; ++i) {
		delete[] rateNeur[i];
	}
	delete[] rateNeur;

	this->numPrevNeur = numPrevNeur;
	this->numNeur = numNeur;
	this->lRate = lRate;

	layer = new double[numNeur];
	error = new double[numNeur];
	delta = new double[numNeur];
	rateNeur = new double*[numNeur];
	for (int i = 0; i < numNeur; ++i) {
		rateNeur[i] = new double[numPrevNeur];
	}

	srand(time(nullptr));
	for (int i = 0; i < numNeur; ++i) {
		for (int j = 0; j < numPrevNeur; ++j) {
			rateNeur[i][j] = (rand() % 201 - 100) / 100.;
		}
	}
}


void NLayer::step(NLayer &prevLayer)
{
	for (int i = 0; i < numNeur; ++i) {
		layer[i] = 0;
		for (int j = 0; j < numPrevNeur; ++j) {
			layer[i] += prevLayer.layer[j] * rateNeur[i][j];
		}
	}
	SigmLayer();
}

void NLayer::set_layer(double *layer)
{
	for (int i = 0; i < numNeur; ++i) {
		this->layer[i] = layer[i];
	}
}

double* NLayer::get_layer()
{
	return layer;
}

int NLayer::get_num()
{
	return numNeur;
}

int NLayer::get_numPrev()
{
	return numPrevNeur;
}

void NLayer::set_rateNeur(double **rateNeur)
{
	for (int i = 0; i < numNeur; ++i) {
		for (int j = 0; j < numPrevNeur; ++j) {
			this->rateNeur[i][j] = rateNeur[i][j];
		}
	}
}


double **NLayer::get_rateNeur()
{
	return rateNeur;
}

void NLayer::learning(NLayer &nextLayer)
{
	for (int i = 0; i < nextLayer.numNeur; ++i) {
		for (int j = 0; j < numNeur; ++j) {
			nextLayer.rateNeur[i][j] -= layer[j] * nextLayer.delta[i] * lRate;
		}
	}

	for (int i = 0; i < numNeur; ++i) {
		error[i] = 0;
		for (int j = 0; j < nextLayer.numNeur; ++j) {
			error[i] += nextLayer.rateNeur[j][i] * nextLayer.delta[j];
		}
		delta[i] = error[i] * layer[i] * (1 - layer[i]);
	}

}

void NLayer::first_learning(double *result)
{
	for (int i = 0; i < numNeur; ++i) {
		error[i] = layer[i] - result[i];
		delta[i] = error[i] * layer[i] * (1 - layer[i]);
	}
}
