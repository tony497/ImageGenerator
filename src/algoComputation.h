#pragma once

#include <vector>

#include "ofMain.h"
#include "ofImage.h"
#include "ofLog.h"

struct Cluster
{
	double m_numberOfElement;
	double m_sumOfElement;
	int m_centerOfMass;
};

class algoComputation  {

		//working with color images
		const int nbChannels = 3;
	
		//Different colors in the final image
		int nbrCluster = 5;

		ofPixels imageTabOriginal;
		ofPixels imageTabResult;
		int nbPixelsColumns, nbPixelsLines;

	public:
	
		algoComputation(ofPixels &tab, int columns, int lines );
		inline ofPixels getImageTabResult() {return imageTabResult;}
		void InitClassTab(int nbrCluster, std::vector<Cluster> &classTab);
		void compute();
		int isClassificationDone(int nbrCluster, std::vector<Cluster> &classTab);
		void updateCenterOfMassValue(int nbrCluster, std::vector<Cluster> &classTab);
		void printAllClass(int &nbrCluster, std::vector<Cluster> &classTab, double totalNbrOfPixels);
		int distance(int a, int b);
		double distanceTab(std::vector<unsigned char> &tab, int taille, int center);
};
