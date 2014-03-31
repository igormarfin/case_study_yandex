#ifndef FEATURE_H
#define FEATURE_H

#include <iostream>
#include <stdio.h>
#include <new>


 
class Feature
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
 
    Feature() : type(eUnknown), points(0) { }

///Problem2
    Feature( FeatureType ft ) : type(ft), points(0) { }
 
    ~Feature()
    {

///Problem3
        if (points)
            delete points;
    }

    bool isValid() 
    {
		std::cout<<"Type is "<<type<<std::endl;
        return type != eUnknown;
    }
 
    bool read(FILE* file)
    {        

///Problem6 
        //read first prt for points
        fread(&points, sizeof(double *), 1, file);

///Problem4 and Problem5 and Problem6
//        if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
        if (fread(&type, sizeof(FeatureType), 1, file) != 1)
            return false;
        short n = 0;
        switch (type) 
        {
        case eCircle: n = 3; break;
        case eTriangle: n = 6; break;
        case eSquare: n = 8; break;
        default: type = eUnknown; return false;
        }

///Problem3 
//       points = new double[n];
	  try {
       points = new double[n];
		}  catch (std::bad_alloc& ba)
  	{
   	 std::cerr << "bad_alloc caught: " << ba.what() << '\n';
  	}

	std::cout<<"num points is "<<n<<std::endl;
        if (!points)
            return false;

///Problem 6 and Problem7 
        return fread(&points, sizeof(double), n, file) == n*sizeof(double);
    }

///Problem8
    void draw()
    {
        switch (type)
        {
///Problem 9
       case eCircle: drawCircle(points[0], points[1], points[2]); break;
        case eTriangle: drawPolygon(points, 6); break;
        case eSquare: drawPolygon(points, 8); break;
        }

    }


/// to print out the Feature
///friend std::ostream & operator <<(std::ostream & out, const Feature & right){ /* NOTHING-TO-DO */	}

//protected:

/// Problem8
//   void drawCircle(double centerX, double centerY, double radius);
//   void drawPolygon(double* points, int size);

    void drawCircle(double centerX, double centerY, double radius) {/* NOTHING-TO-DO */ } 

///Problem10 double* points -->  const double*
//    void drawPolygon(double* points, int size) {/* NOTHING-TO-DO */}
    void drawPolygon(const double* points, int size) {/* NOTHING-TO-DO */}


///Problem 1 
    double* points;
    FeatureType type;        
};


#endif




