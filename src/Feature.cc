#include "Feature.h"
#include <iostream>


using namespace std;

int main(int argc, char* argv[])
{

/// Problem1

//    Feature feature;
    Feature feature(Feature::eCircle);

  FILE * pFile;
  pFile = fopen ("features.dat", "w");
  fwrite (&feature , sizeof(Feature), 1, pFile);
  fclose (pFile);

/// to test Problem1
  feature.isValid();
   
    pFile = fopen("features.dat", "r");
    bool status=feature.read(pFile);
    fclose (pFile);

///Problem7
	if (!status) cout<<"something wrong with reading"<<endl;


    if (!feature.isValid()) {
	 cout<<"feature:: invalid"<<endl;
        return 1; } else  	 cout<<"feature:: valid"<<endl;

///Problem8 
	feature.draw();
    return 0;
}

