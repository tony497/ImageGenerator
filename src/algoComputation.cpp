#include "algoComputation.h"

algoComputation::algoComputation(ofPixels &tab, int columns, int lines)
{
	nbPixelsColumns = columns;
	nbPixelsLines = lines;
	imageTabOriginal = tab;

	ofLogVerbose() << "nbPixelsColumns = " << nbPixelsColumns;
	ofLogVerbose() << "nbPixelsLines = " << nbPixelsLines;
	int iNbPixelTotal = nbPixelsLines * nbChannels * nbPixelsColumns;
	ofLogVerbose() << "nbPixelsTotals = " << iNbPixelTotal;
	ofLogVerbose() << "verif nbPixelsTotal : imageTab size = " << imageTabOriginal.size();

	compute();

	return;
}

void algoComputation::printAllClass(int &nbrCluster, std::vector<Cluster> &clusterTab, double totalNbrOfPixels)
{
	int i;
	double percent;
	for (i = 0; i < nbrCluster; ++i)
	{
		percent = (clusterTab[i].m_numberOfElement * 100) / totalNbrOfPixels;
		ofLogNotice() << " Cluster number: " << i ;
		ofLogNotice() << " Pourcentage of presence = " << percent << " percent";
		ofLogNotice() << " Sum of the elements of the cluster = " << clusterTab[i].m_sumOfElement;
		ofLogNotice() << " Number of elements in the cluster = " << clusterTab[i].m_numberOfElement;
		ofLogNotice() << " Center of mass of the cluster = " << clusterTab[i].m_centerOfMass;

	}
}

//_____________________________________________________________
void algoComputation::updateCenterOfMassValue(int nbrCluster, std::vector<Cluster> &clusterTab)
{
	for (int i = 0; i < nbrCluster; ++i)
	{
		clusterTab[i].m_centerOfMass = clusterTab[i].m_sumOfElement / clusterTab[i].m_numberOfElement;
		clusterTab[i].m_sumOfElement = 0;
		clusterTab[i].m_numberOfElement = 0;
		ofLogNotice() << "cluster : "<< i;
	}
	ofLogNotice() << "All cluster have been updated";
}

//_____________________________________________________________
int algoComputation::distance(int a, int b)
{
	return abs(b - a);
}

//_____________________________________________________________
double algoComputation::distanceTab(std::vector<unsigned char> &tab, int taille, int center)
{
	double distanceFinal = 0;
	for (int i = 0; i < taille; ++i)
	{
		distanceFinal = distanceFinal + distance(tab[i], center);
	}
	return distanceFinal;
}

//_____________________________________________________________
int algoComputation::isClassificationDone(int nbrCluster, std::vector<Cluster> &clusterTab)
{
	for (int i = 0; i < nbrCluster; i++)
	{
		if (distance(clusterTab[i].m_centerOfMass, clusterTab[i].m_sumOfElement / clusterTab[i].m_numberOfElement) > 2)
		{
			updateCenterOfMassValue(nbrCluster, clusterTab);
			return 0;
		}
	}
	ofLogError()<<"Number of cluster equal 0";
	return 1;
}


//_____________________________________________________________
void algoComputation::InitClassTab(int nbrCluster, std::vector<Cluster> &classTab)
{
	int pas = 255 / nbrCluster;
	int i;

	ofLogNotice() << "pas = " << pas;

	for (i = 0; i < nbrCluster; ++i)
	{
		classTab[i].m_centerOfMass = ((i * pas) + ((i + 1) * pas)) / 2;
		classTab[i].m_sumOfElement = 0;
		classTab[i].m_numberOfElement = 0;
	}
}

void algoComputation::compute()
{

	int iNumPix;
	int iNumChannel; 
	int iNbPixelTotal = nbPixelsLines * nbChannels * nbPixelsColumns;
	std::vector<int> tabPixel;
	tabPixel.resize(iNbPixelTotal);
	int ucMeanPix;
	std::vector<Cluster> clusterTab;
	clusterTab.resize(nbrCluster);

	ofLogNotice() << "Segmentation de l'image.... A vous!";
	ofLogNotice() << "Nombre de classes = " << nbrCluster;

	InitClassTab(nbrCluster, clusterTab);
	imageTabResult.allocate(imageTabOriginal.getWidth(),imageTabOriginal.getHeight(),imageTabOriginal.getImageType());

	int iNbPixelWidth;
	int iNbPixelHeight;

	int countTest = 0;

	for (iNbPixelWidth = 0; iNbPixelWidth < nbPixelsColumns * nbChannels; iNbPixelWidth = iNbPixelWidth + nbChannels)
	{
		for (iNbPixelHeight = 0; iNbPixelHeight < nbPixelsLines; iNbPixelHeight++)
		{
	
			iNumPix = ((iNbPixelHeight *  nbPixelsColumns * nbChannels) + iNbPixelWidth);
	
			//moyenne sur les composantes RVB 
			ucMeanPix = static_cast<unsigned char>((	imageTabOriginal[iNumPix] 
										+	imageTabOriginal[iNumPix + 1]
										+	imageTabOriginal[iNumPix + 2]
										) / 3);
	
			// sauvegarde du resultat 
			for (iNumChannel = 0; iNumChannel < nbChannels; iNumChannel++)
			{
				imageTabResult[iNumPix + iNumChannel] = ucMeanPix;
				countTest++;
			}
		}
	}

	ofLogVerbose() << "Total pixel count = " << countTest;
	
	//Debut Algo
	ofLogNotice() << "Debut algorithme:" ;
	int nbClass, i, a, j, nombreDePasse = 0;
	std::vector<unsigned char> tab;
	const int sizeTab = 5;
	tab.resize(sizeTab);
	double minTab;
	

	do {
		ofLogNotice() << "Passe numero : " << nombreDePasse << "____________________________________________________";
	
		for (iNbPixelWidth = 1; iNbPixelWidth < (nbPixelsColumns - 1) * nbChannels; iNbPixelWidth = iNbPixelWidth + nbChannels)
		{
			for (iNbPixelHeight = 1; iNbPixelHeight < (nbPixelsLines - 1); iNbPixelHeight++)
			{
				iNumPix = ((iNbPixelHeight *  nbPixelsColumns * nbChannels) + iNbPixelWidth);

				//on remplie le tableau
				tab[0] = imageTabResult[iNumPix];
				tab[1] = imageTabResult[iNumPix + nbChannels];
				tab[2] = imageTabResult[iNumPix - nbChannels];
				tab[3] = imageTabResult[nbPixelsColumns * nbChannels + iNumPix + nbChannels];
				tab[4] = imageTabResult[- nbPixelsColumns * nbChannels + iNumPix - nbChannels];

				//On trie le tableau  
				std::sort(tab.begin(), tab.end());
	
				ucMeanPix = imageTabResult[iNumPix];

				//Looking for the miunimum distance		
				nbClass = INT_MAX;
				minTab = DBL_MAX;
	
				for (i = 0; i < nbrCluster; ++i)
				{
					if (distanceTab(tab, 5, clusterTab[i].m_centerOfMass) <= minTab)
					{
						minTab = distanceTab(tab, 5, clusterTab[i].m_centerOfMass);
						nbClass = i;
					}
				}
	
				clusterTab[nbClass].m_sumOfElement = clusterTab[nbClass].m_sumOfElement + ucMeanPix;
				clusterTab[nbClass].m_numberOfElement = clusterTab[nbClass].m_numberOfElement + 1;
				tabPixel[iNumPix] = nbClass;
				tabPixel[iNumPix + 1] = nbClass;
				tabPixel[iNumPix + 2] = nbClass;
	
			}
		}
		printAllClass(nbrCluster, clusterTab, static_cast<double>((nbPixelsLines - 2)*(nbPixelsColumns - 2)));
	
		nombreDePasse++;
	
	} while (isClassificationDone(nbrCluster, clusterTab) == 0);
	
	ofLogNotice() << "Sauvegarde des couleurs..";
	//On change les couleurs dépendament d ela classe 
	

	for (iNbPixelWidth = 1; iNbPixelWidth < (nbPixelsColumns - 1) * nbChannels; iNbPixelWidth = iNbPixelWidth + nbChannels)
	{
		for (iNbPixelHeight = 1; iNbPixelHeight < (nbPixelsLines - 1); iNbPixelHeight++)
		{
			iNumPix = ((iNbPixelHeight *  nbPixelsColumns * nbChannels) + iNbPixelWidth);
	
			for (iNumChannel = 0; iNumChannel < nbChannels; iNumChannel++)
			{
				imageTabResult[iNumPix + iNumChannel] = clusterTab[tabPixel[iNumPix]].m_centerOfMass;
			}
		}
	}
	
	ofLogNotice() << "The Computation is finished";

}
