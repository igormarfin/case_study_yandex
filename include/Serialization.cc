#include "FeatureFixed.h"


#include <iostream>
#include <fstream>






void FeatureFixed::serialize (std::ofstream& stream){

        std::size_t size;
        if (type == FeatureFixed::eUnknown )  return;
        if (type == FeatureFixed::eCircle) size=3 ;
        else if  (type == FeatureFixed::eTriangle) size=6;
        else size=8;

        std::size_t type_size=sizeof(type);
        stream.write( reinterpret_cast<const char *>(&type), sizeof(FeatureFixed::FeatureType) );
        for (size_t i=0;i<size;i++) stream.write( reinterpret_cast<const char *>(&points[i]), sizeof(double));

}



void FeatureFixed::deserialize (std::ifstream& stream){

    std::size_t size;
    std::vector<char> buffer_type(sizeof(FeatureFixed::FeatureType));
    std::vector<char> buffer_point(sizeof(double));
    stream.read(&buffer_type[0], sizeof(FeatureFixed::FeatureType) );
    type = *reinterpret_cast<FeatureType *>(&buffer_type[0]);


        if (points) delete [] points;

        if (type == FeatureFixed::eUnknown ) { points=0; return; }
        else if  (type == FeatureFixed::eCircle )  size=3;
        else if  (type == FeatureFixed::eTriangle) size=6;
        else if  (type == FeatureFixed::eSquare)  size=8;
        else { type=FeatureFixed::eUnknown; points=0; return; }



        try { points = new double[size]; }  catch (std::bad_alloc& ba)
  	{
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            type=FeatureFixed::eUnknown; points=0; return;
        }


        for (size_t i=0;i<size;i++) {
            stream.read(&buffer_point[0], sizeof(double) );
            points[i] = *reinterpret_cast<double *>(&buffer_point[0]);

        }

        return;

}


/// to print out the FeatureFixed
std::ostream & operator <<(std::ostream & out, const FeatureFixed & right)
{

    std::string type_str;
    FeatureFixed::FeatureType type = right.getType();

    if (type == FeatureFixed::eCircle) type_str = " :Circle: ";
    else if (type == FeatureFixed::eTriangle) type_str = " :Triangle: ";
    else if (type == FeatureFixed::eSquare) type_str = " :Square: ";
    else type_str = " :Unknown: ";

    std::size_t size;
    if (type == FeatureFixed::eUnknown )  size=0;
    if (type == FeatureFixed::eCircle) size=3 ;
    else if  (type == FeatureFixed::eTriangle) size=6;
    else size=8;


    if (!right.isValid())
        out<<"Feature is not valid \n";

    else {
        std::vector<double> points = right.getPoints();
        out<<  "Feature {"<< type_str;
        for (size_t i=0;i<size;i++)  out<<", "<<points[i];
        out<<" }\n";
        }

   
}





