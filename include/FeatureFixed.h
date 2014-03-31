#ifndef FEATUREFIXED_H
#define FEATUREFIXED_H

#include <iostream>
#include <Serialization.h>
#include <new>
#include <algorithm>
#include <vector>


 
class FeatureFixed: public Serializable
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};


    FeatureFixed() : type(eUnknown), points(0) { }

    FeatureFixed( FeatureType ft ) : type(ft) {



        size_t n;
        switch (ft)
        {
        case eCircle: n = 3; break;
        case eTriangle: n = 6; break;
        case eSquare: n = 8; break;
        default: type = eUnknown; points=0; return;
        }

	  try { points = new double[n]; }  catch (std::bad_alloc& ba)
  	{
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            type=eUnknown; points=0;
  	}



    }


    ~FeatureFixed()
    {

///Problem3
        if (points)
            delete [] points;
    }

    bool  isValid() const
    {
        return type != eUnknown;
    }

    bool setPoints(std::vector<double> & pts)
    {
        if ( (type == eUnknown) ||
             (type == eCircle && pts.size()!=3) ||
             (type == eTriangle && pts.size()!=6) ||
             (type == eSquare && pts.size()!=8)
           ) return false;

        std::size_t size = pts.size();
        std::copy(pts.begin(),pts.end(),points);

        return true;
    }




    FeatureType getType() const { return type; }

    std::vector<double> getPoints() const {
        if (type == eUnknown )  return std::vector<double>();

        std::size_t size;
        if (type == eCircle) size=3 ;
        else if  (type == eTriangle) size=6;
        else size=8;

        std::vector<double> pts(size);
        std::copy(points,points+size,pts.begin());

        return pts;


    }

    double getPoint(size_t i) const {
        if (type == eUnknown ) return 0;

        std::size_t size;
        if (type == eCircle) size=3 ;
        else if  (type == eTriangle) size=6;
        else size=8;

        if (i<size) return getPoints()[i];
        return 0;

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


/// to print out the FeatureFixed
    friend std::ostream & operator <<(std::ostream & out, const FeatureFixed & right);

    virtual void serialize (std::ofstream& stream);
    virtual void deserialize(std::ifstream& stream);

protected:

/// Problem8
//   void drawCircle(double centerX, double centerY, double radius);
//   void drawPolygon(double* points, int size);

    void drawCircle(double centerX, double centerY, double radius) {
        std::cout<<"Drawing Circle: \n";
        std::cout<<"CenterX = "<<centerX<<"\n";
        std::cout<<"CenterY = "<<centerY<<"\n";
        std::cout<<"radius = "<<radius<<"\n";
    }

///Problem10 double* points -->  const double*
//    void drawPolygon(double* points, int size) {/* NOTHING-TO-DO */}
    void drawPolygon(const double* points, int size) {
        std::cout<<"Drawing Polygon: \n";
        for (size_t i=0; i<size; i++)         std::cout<<"point["<<i<<"] = "<<points[i]<<"\n";

    }



///Problem 1 
    double* points;
    FeatureType type;        
};


#endif




