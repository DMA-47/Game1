#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;
const int N = 20;
char board[N][N];

HANDLE hStdOut;
#include "NLayer.h"
#include "Func.h"

char way[30] = "c:\\save2\\weight.txt";

int main()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Game");
	double lRate = 0.1;
	int numLayer = 1;
	const int constNumLayer = 1;
	int inputNum = 9;
	int outputNum = 4;
	int numHidden[constNumLayer] = { 9 };
	int ind = 0;

	NLayer inputLayer;
	NLayer *hiddenLayer;
	NLayer outputLayer;

	cout << "Load weights?" << endl;
	cin >> ind;
	if (ind) {
		//load
		ifstream fin(way);
		fin >> lRate;
		fin >> numLayer;
		fin >> inputNum;
		fin >> outputNum;
		for (int i = 0; i < numLayer; ++i) {
			fin >> numHidden[i];
		}

		//create layers
		inputLayer.set_layer(0, inputNum, lRate);
		hiddenLayer = new NLayer[numLayer];
		hiddenLayer[0].set_layer(inputNum, numHidden[0], lRate);
		for (int i = 1; i < numLayer; ++i) {
			hiddenLayer[i].set_layer(numHidden[i - 1], numHidden[i], lRate);
		}
		outputLayer.set_layer(numHidden[numLayer - 1], outputNum, lRate);



		for (int h = 0; h < numLayer; ++h) {
			double **weight = new double*[hiddenLayer[h].get_num()];
			for (int i = 0; i < hiddenLayer[h].get_num(); ++i) {
				weight[i] = new double[hiddenLayer[h].get_numPrev()];
				for (int j = 0; j < hiddenLayer[h].get_numPrev(); ++j) {
					fin >> weight[i][j];
				}
			}
			hiddenLayer[h].set_rateNeur(weight);
			for (int i = 0; i < hiddenLayer[h].get_num(); ++i) {
				delete[] weight[i];
			}
			delete[]weight;
		}

		double **weight = new double*[outputLayer.get_num()];
		for (int i = 0; i < outputLayer.get_num(); ++i) {
			weight[i] = new double[outputLayer.get_numPrev()];
			for (int j = 0; j < outputLayer.get_numPrev(); ++j) {
				fin >> weight[i][j];
			}
		}
		outputLayer.set_rateNeur(weight);
		for (int i = 0; i < outputLayer.get_num(); ++i) {
			delete[] weight[i];
		}
		delete[]weight;
		fin.close();
	}
	else {
		//create layers
		inputLayer.set_layer(0, inputNum, lRate);
		hiddenLayer = new NLayer[numLayer];
		hiddenLayer[0].set_layer(inputNum, numHidden[0], lRate);
		for (int i = 1; i < numLayer; ++i) {
			hiddenLayer[i].set_layer(numHidden[i - 1], numHidden[i], lRate);
		}
		outputLayer.set_layer(numHidden[numLayer - 1], outputNum, lRate);
	}

	int x = 10;
	int y = 10;
	int x0 = 5;
	int y0 = 5;
	ClearAll(board);
	for (int i = 0; i < N; ++i) {
		board[0][i] = '*';
		board[N - 1][i] = '*';
		board[i][0] = '*';
		board[i][N - 1] = '*';
	}
	//menu
	int key = 1;
	do {
		system("cls");
		gotoxy(0, 0);
		cout << "1 - Play" << endl;
		cout << "2 - Learning" << endl;
		cout << "3 - Print rate" << endl;
		cout << "4 - Save" << endl;
		cout << "0 - Exit" << endl;

		cin >> key;
		switch (key) {
		case 1: { // play
			PrintBoard(board);
			gotoxy(x, y);
			Active(x, y);
			ActiveMy(x0, y0);
			bool exit = false;
			int key2, key3;
			while (exit == false) {
				Sleep(50);
				key3 = 0;
				if (_kbhit()) {
					key3 = _getch();
				}
				switch (key3) {
				case 77: {//right
					if (x0 < N - 2) {
						inActiveMy( x0, y0);
						board[y0][x0] = ' ';
						x0++;
						ActiveMy(x0, y0);
						board[y0][x0] = '*';
					}
					break;
				}
				case 75: {//left
					if (x0 > 1) {
						inActiveMy(x0, y0);
						board[y0][x0] = ' ';
						x0--;
						ActiveMy(x0, y0);
						board[y0][x0] = '*';
					}
					break;
				}
				case 80: {//down
					if (y0 < N - 2) {
						inActiveMy(x0, y0);
						board[y0][x0] = ' ';
						y0++;
						ActiveMy(x0, y0);
						board[y0][x0] = '*';
					}
					break;
				}
				case 72: {//up
					if (y0 > 1) {
						inActiveMy(x0, y0);
						board[y0][x0] = ' ';
						y0--;
						ActiveMy(x0, y0);
						board[y0][x0] = '*';
					}
					break;
				}
				case 27: {
					exit = true;
					break;
				}
				}
				key2 = Pos(board, x, y, inputLayer, hiddenLayer, numLayer, outputLayer);
				switch (key2) {
				case 0: {//right
					if (x < N - 1) {
						inActive(x, y);
						x++;
						Active(x, y);
					}
					break;
				}
				case 1: {//left
					if (x > 0) {
						inActive(x, y);
						x--;
						Active(x, y);
					}
					break;
				}
				case 2: {//down
					if (y < N - 1) {
						inActive(x, y);
						y++;
						Active(x, y);
					}
					break;
				}
				case 3: {//up
					if (y > 0) {
						inActive(x, y);
						y--;
						Active(x, y);
					}
					break;
				}
				}
				if (board[y][x] != ' ') {
					PrintBoard(board);
					x = 10;
					y = 10;
					Active(x, y);
					ActiveMy(x0, y0);
				}
			}
			break;
		}
		case 2: { // learning

			break;
		}
		case 3: {
			cout << "input" << endl;
			for (int i = 0; i < inputLayer.get_num(); ++i) {
				for (int j = 0; j < inputLayer.get_numPrev(); ++j) {
					cout << inputLayer.get_rateNeur()[i][j] << " ";
				}
				cout << endl;
			}
			cout << "hidden" << endl;
			for (int h = 0; h < numLayer; ++h) {
				cout << h + 1 << endl;
				for (int i = 0; i < hiddenLayer[h].get_num(); ++i) {
					for (int j = 0; j < hiddenLayer[h].get_numPrev(); ++j) {
						cout << hiddenLayer[h].get_rateNeur()[i][j] << " ";
					}
					cout << endl;
				}
			}
			cout << "output" << endl;
			for (int i = 0; i < outputLayer.get_num(); ++i) {
				for (int j = 0; j < outputLayer.get_numPrev(); ++j) {
					cout << outputLayer.get_rateNeur()[i][j] << " ";
				}
				cout << endl;
			}

			break;
		}
		case 4: {//save
			ofstream fout(way);
			fout << lRate << endl;
			fout << numLayer << endl;
			fout << inputNum << endl;
			fout << outputNum << endl;
			for (int i = 0; i < numLayer; ++i) {
				fout << numHidden[i] << " ";
			}

			fout << endl;
			for (int h = 0; h < numLayer; ++h) {
				fout << endl;
				for (int i = 0; i < hiddenLayer[h].get_num(); ++i) {
					for (int j = 0; j < hiddenLayer[h].get_numPrev(); ++j) {
						fout << hiddenLayer[h].get_rateNeur()[i][j] << " ";
					}
					fout << endl;
				}
			}
			fout << endl;
			for (int i = 0; i < outputLayer.get_num(); ++i) {
				for (int j = 0; j < outputLayer.get_numPrev(); ++j) {
					fout << outputLayer.get_rateNeur()[i][j] << " ";
				}
				fout << endl;
			}
			fout.close();
			break;
		}
		}//switch

	} while (key != 0);

}
