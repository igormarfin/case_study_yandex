#include "FeatureFixed.h"
#include <iostream>
#include <fstream>
#include <cassert>


using namespace std;

int main(int argc, char* argv[])
{

  vector<double> pts ; 

  ///
  cout<<"Test of Circle\n";
  FeatureFixed feature_circle(FeatureFixed::eCircle);
  if (!feature_circle.isValid()) return 1;

  for (size_t i =1; i<4; i++)   pts.push_back(i);
  if (!feature_circle.setPoints(pts)) return 1;

  cout<<"original ==>    \n";
  cout<<feature_circle;
  cout<<"\n";

   ofstream file_in ("featuresFixed.dat", ios::out | ios::binary);

  feature_circle.serialize(file_in);
  file_in.close();


  FeatureFixed feature_transfered;
  ifstream file_out ("featuresFixed.dat", ios::in | ios::binary);
  feature_transfered.deserialize(file_out);
  file_out.close();


  cout<<"transfered ==>    \n";
  cout<<feature_transfered;
  cout<<"\n";
  assert(feature_circle.getType() == feature_transfered.getType());
  for (size_t i =1; i<4; i++)    assert(feature_circle.getPoint(i) == feature_transfered.getPoint(i));

  cout<<"draw feature (restored)\n";
  feature_transfered.draw();



  ///
  cout<<"Test of Triangle\n";
  FeatureFixed feature_triangle(FeatureFixed::eTriangle);
  if (!feature_triangle.isValid()) return 1;

  for (size_t i =4; i<7; i++)   pts.push_back(i);
  if (!feature_triangle.setPoints(pts)) return 1;

  cout<<"original ==>    \n";
  cout<<feature_triangle;
  cout<<"\n";

  file_in.open("featuresFixed.dat", ios::out | ios::binary);
  feature_triangle.serialize(file_in);
  file_in.close();


  file_out.open ("featuresFixed.dat", ios::in | ios::binary);
  feature_transfered.deserialize(file_out);
  file_out.close();


  cout<<"transfered ==>    \n";
  cout<<feature_transfered;
  cout<<"\n";
  assert(feature_triangle.getType() == feature_transfered.getType());
  for (size_t i =0; i<6; i++)    assert(feature_triangle.getPoint(i) == feature_transfered.getPoint(i));
  cout<<"draw feature (restored)\n";
  feature_transfered.draw();



    return 0;
}

