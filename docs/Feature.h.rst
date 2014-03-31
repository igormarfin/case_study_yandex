 #ifndef FEATURE_H
 #define FEATURE_H
 
 #include <iostream>
 #include <sstream>  
 #include <stdio.h>
 
 
 
  
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
 	    fread(&type, sizeof(FeatureType), 1, file);
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
        points = new double[n];
 
 	std::cout<<"num points is "<<n<<std::endl;
         if (!points)
             return false;
 ///Problem 6 and Problem7 
         return fread(&points, sizeof(double), n, file) == n*sizeof(double);
     }
     void draw()
     {
         switch (type)
         {
         case eCircle: drawCircle(points[0], points[1], points[2]); break;
         case eTriangle: drawPolygon(points, 6); break;
         case eSquare: drawPolygon(points, 8); break;
         }
     }
 
 
 /// to print out the Feature
 friend std::ostream & operator <<(std::ostream & out, const Feature & right){ /* NOTHING-TO-DO */	}
 
 
 protected:
     void drawCircle(double centerX, double centerY, double radius);
     void drawPolygon(double* points, int size);
 
 
 ///Problem 1 
     double* points;
     FeatureType type;        
 };
 
 
 #endif
 
 
 
 
