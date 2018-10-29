class NLayer {
private:
	double lRate;
	int numNeur;
	int numPrevNeur;
	double *layer;
	double **rateNeur;
	double *error;
	double *delta;
	void SigmLayer();
public:
	NLayer(int numPrevNeur, int numNeur, double lRate);
	NLayer();
	~NLayer();
	void set_layer(int numPrevNeur, int numNeur, double lRate);
	void step(NLayer &prevLayer);
	void set_layer(double *layer);
	double *get_layer();
	int get_num();
	int get_numPrev();
	void set_rateNeur(double **rateNeur);
	double **get_rateNeur();

	void learning(NLayer &nextLayer);
	void first_learning(double *result);

};