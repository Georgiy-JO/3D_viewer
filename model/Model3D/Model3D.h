
#pragma once
#include <vector>
#include <string>

#include "Vertices/Vertices.h"
#include "Edges/Edges.h"

namespace s21 {

  class Model3D {
      Vertices vertices;
      Edges edges;

      double scale_factor=0;
      Vec3 centering_vector{0,0,0};
      std::string model_name;

    public:
      void addVert(double x_, double y_, double z_);
      void removeVert(size_t number);

      void addEdge(size_t beg_, size_t end_);
      void removeEdge(size_t number);

      size_t getVerticesAmount() const;
      size_t getEdgesAmount() const;

      void setScaleFactor();
      void setCenteringVector();

      double getScaleFactor() const;
      Vec3 getCenteringVector() const;

      void clearModel();
      double scaleModel(double factor);   //in cpp file set default to scale_factor
      Vec3 centerModel(Vec3 center_vec);  //in cpp file set default to centering_vector

      Vec3 operator[](size_t number) const; //returns vector of the folowing index
      Edge operator()(size_t number) const; //returns edge of the folowing index 
  };  //class Model
}  // namespace s21
