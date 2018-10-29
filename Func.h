#pragma once
void gotoxy(int x, int y);
void Active(int x, int y);
void inActive(int x, int y);
void ClearAll(char board[N][N]);
void PrintBoard(char board[N][N]);
char CheckWin(char board[N][N]);
int PosRandom(char board[N][N]);
int CheckEasy(char board[N][N]);
int Pos(char board[N][N], int x, int y, NLayer &inputLayer, NLayer *hiddenLayer, int numLayer, NLayer &outputLayer);
void AddBoard(char board[N][N], double **boardB, int &numB, int pos);
void Learning(double **boardB, int numB, NLayer &inputLayer, NLayer *hiddenLayer, int numLayer, NLayer &outputLayer, double rate);


void gotoxy(int x, int y)
{
	COORD cursorPos = { x, y };
	SetConsoleCursorPosition(hStdOut, cursorPos);
}

void Active(int x, int y)
{
	gotoxy(x * 2, y);
	cout << " o";
}

void inActive(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
}

void ActiveMy(int x, int y)
{
	gotoxy(x * 2, y);
	cout << " *";
}

void inActiveMy(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
}


void PrintBoard(char board[N][N])
{
	system("cls");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << " " << board[i][j];
		}
		cout << endl;
	}
}

void ClearAll(char board[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = ' ';
		}
	}
}

char CheckWin(char board[N][N])
{
	for (int i = 0; i < N; i++) {
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
			return 'X';
		}
		if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
			return 'O';
		}
	}

	for (int j = 0; j < N; j++) {
		if (board[0][j] == 'X' && board[1][j] == 'X' && board[2][j] == 'X') {
			return 'X';
		}
		if (board[0][j] == 'O' && board[1][j] == 'O' && board[2][j] == 'O') {
			return 'O';
		}
	}

	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
		return 'X';
	}
	if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
		return 'O';
	}

	if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
		return 'X';
	}
	if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
		return 'O';
	}
	return NULL;
}

int PosRandom(char board[N][N])
{
	int p = CheckEasy(board);
	if (p != -1) {
		return p;
	}

	int numNull = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == ' ') {
				numNull++;
			}
		}
	}

	int randPos = rand() % numNull;
	int pos = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == ' ') {
				if (randPos == 0) {
					pos = (i * N) + j;
					i = N;
					j = N;
					//break
				}
				else {
					randPos--;
				}
			}
		}
	}

	return pos;
}

int CheckEasy(char board[N][N])
{
	int step = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != ' ') {
				step++;
			}
		}
	}

	if (step == 8) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == ' ') {
					return (i * N) + j;
				}
			}
		}
	}


	char xo;
	if (step % 2 == 0) {
		xo = 'X';
	}
	else {
		xo = 'O';
	}
	for (int q = 0; q < 2; q++) {
		for (int i = 0; i < N; i++) {
			if (board[i][0] != ' ' && board[i][0] == xo && board[i][1] == xo && board[i][2] == ' ') {
				return (i * N) + 2;
			}
			if (board[i][1] != ' ' && board[i][1] == xo && board[i][2] == xo && board[i][0] == ' ') {
				return (i * N);
			}
			if (board[i][2] != ' ' && board[i][2] == xo && board[i][0] == xo && board[i][1] == ' ') {
				return (i * N) + 1;
			}
			//i = j
			if (board[0][i] != ' ' && board[0][i] == xo && board[1][i] == xo && board[2][i] == ' ') {
				return (2 * N) + i;
			}
			if (board[1][i] != ' ' && board[1][i] == xo && board[2][i] == xo && board[0][i] == ' ') {
				return i;
			}
			if (board[2][i] != ' ' && board[2][i] == xo && board[0][i] == xo && board[1][i] == ' ') {
				return (1 * N) + i;
			}
		}

		if (board[1][1] != ' ') {
			if (board[1][1] == xo && board[0][0] == xo && board[2][2] == ' ') {
				return 8;
			}
			if (board[1][1] == xo && board[0][2] == xo && board[2][0] == ' ') {
				return 6;
			}
			if (board[1][1] == xo && board[2][2] == xo && board[0][0] == ' ') {
				return 0;
			}
			if (board[1][1] == xo && board[2][0] == xo && board[0][2] == ' ') {
				return 2;
			}
		}
		else {
			if ((board[0][0] == xo && board[2][2] == xo) || (board[0][2] == xo && board[2][0] == xo)) {
				return 4;
			}
		}

		if (xo == 'O') {
			xo = 'X';
		}
		else {
			xo = 'O';
		}
	}

	return -1;
}

int Pos(char board[N][N], int x, int y, NLayer &inputLayer, NLayer *hiddenLayer,int numLayer, NLayer &outputLayer)
{
	double input[9];
	int p = 0;
	for (int i = y - 1; i <= y + 1; ++i) {
		for (int j = x - 1; j <= x + 1; ++j) {
			if (x < 0 || y < 0 || x >= N || y >= N) {
				input[p] = 0;
			}
			else {
				if (board[i][j] == ' ') {
					input[p] = 0;
				}
				else {
					input[p] = 1;
				}
			}
			++p;
		}
	}

	inputLayer.set_layer(input);
	hiddenLayer[0].step(inputLayer);
	for (int i = 1; i < numLayer; ++i) {
		hiddenLayer[i].step(hiddenLayer[i - 1]);
	}
	outputLayer.step(hiddenLayer[numLayer - 1]);

	double max = outputLayer.get_layer()[0];
	int posMax = 0;
	for (int i = 1; i < outputLayer.get_num(); ++i) {
		if (outputLayer.get_layer()[i] > max) {
			max = outputLayer.get_layer()[i];
			posMax = i;
		}
	}

	switch (posMax) {
	case 0: {//right
		if (x < N - 1) {
			x++;
		}
		break;
	}
	case 1: {//left
		if (x > 0) {
			x--;
		}
		break;
	}
	case 2: {//down
		if (y < N - 1) {
			y++;
		}
		break;
	}
	case 3: {//up
		if (y > 0) {
			y--;
		}
		break;
	}
	}
	if (board[y][x] != ' ') {
		double *output = new double[4];
		for (int i = 0; i < 4; ++i) {
			output[i] = outputLayer.get_layer()[i];
		}
		output[posMax] = 0;
		//learn
		outputLayer.first_learning(output);
		hiddenLayer[numLayer - 1].learning(outputLayer);
		for (int i = numLayer - 2; i >= 0; --i) {
			hiddenLayer[i].learning(hiddenLayer[i + 1]);
		}
		inputLayer.learning(hiddenLayer[0]);
	}
	return posMax;
}

void AddBoard(char board[N][N], double **boardB, int &numB, int pos)
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (board[i][j] == ' ') {
				boardB[numB][i * 3 + j] = 0;
			}
			else {
				if (board[i][j] == 'X') {
					boardB[numB][i * 3 + j] = 4;
				}
				else {
					boardB[numB][i * 3 + j] = 2;
				}
			}
		}
	}
	boardB[numB][9] = pos;
	numB++;
}

void Learning(double **boardB, int numB, NLayer &inputLayer, NLayer *hiddenLayer, int numLayer, NLayer &outputLayer, double rate)
{
	//double rate = 100;
	for (int b = numB - 1; b >= 0; --b) {
		inputLayer.set_layer(boardB[b]);
		hiddenLayer[0].step(inputLayer);
		for (int i = 1; i < numLayer; ++i) {
			hiddenLayer[i].step(hiddenLayer[i - 1]);
		}
		outputLayer.step(hiddenLayer[numLayer - 1]);
		//output
		double *output = new double[9];
		double min, max;
		min = max = outputLayer.get_layer()[0];
		for (int i = 0; i < 9; ++i) {
			output[i] = outputLayer.get_layer()[i];
			if (output[i] < min) {
				min = output[i];
			}
			if (output[i] > max) {
				max = output[i];
			}

		}
		/*for (int i = 0; i < 9; ++i) {
			output[i] = max + rate;
		}*/
		output[(int)boardB[b][9]] = min - rate;

		//learn
		outputLayer.first_learning(output);
		hiddenLayer[numLayer - 1].learning(outputLayer);
		for (int i = numLayer - 2; i >= 0; --i) {
			hiddenLayer[i].learning(hiddenLayer[i + 1]);
		}
		inputLayer.learning(hiddenLayer[0]);
		/*for (int i = 0; i < 9; ++i) {
			cout << output[i] << endl;
		}
		cout << endl;*/
		rate /= 1.5;
	}
}