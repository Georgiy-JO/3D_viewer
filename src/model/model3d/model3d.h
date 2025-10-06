
#ifndef SRC_MODEL_MODEL3D_MODEL3D_H
#define SRC_MODEL_MODEL3D_MODEL3D_H

#include <string>

#include "elements/axisbounds.h"
#include "elements/mesh.h"

namespace inbound_model {

class Model3D {
 public:
  void AddVert(double x_, double y_, double z_);
  void RemoveVert(uint32_t number);

  void AddEdge(size_t beg_, size_t end_);
  void RemoveEdge(size_t number);

  uint32_t GetVerticesAmount() const;
  size_t GetEdgesAmount() const;

  double GetScaleFactor() const;
  const Vec3& GetCenteringVector() const;

  void Clear();

  void CenterScale();
  void UnscaleUncenter();

  /**
   * @note If you are using Scale() and Center() separately
   * plese note the order of call and when/if you use
   * Uncenter() and Unscale() later call those in opposite
   * order (Scale()->Center() ==> Uncenter()->Unscale()).
   * @note If you are going to use both, consider using
   * CenterScale() (and UnscaleUncenter()).
   * @note It is recomended to call Center() before Scale().
   */
  double Scale();
  /**
   * @note If you are using Scale() and Center() separately
   * plese note the order of call and when/if you use
   * Uncenter() and Unscale() later call those in opposite
   * order (Scale()->Center() ==> Uncenter()->Unscale()).
   * @note If you are going to use both, consider using
   * CenterScale().
   */
  Vec3 Center();
  /**
   * Return true - if the model is scaled,
   * false - if is not scaled or scaling not needed.
   **/
  bool IsScaled() const;
  /**
   * Return true - if the model is centered,
   * false - if is not centered or centering not needed.
   **/
  bool IsCentered() const;
  void Unscale();   // Checks if model is scaled before unscaling.
  void Uncenter();  // Checks if model is centered before uncentering.

  void SortEdges();
  void NormalizeEdges();  // sorting and removing duplicates
  /**
   * Creates edges from isolated vertices (has no edge mentioned
   * in the edges list) and add those to the edges list.
   **/
  void AddSingleVertEdges();
  // Removes Isolated vertices edges from the edges list.
  void RemoveSingleVertEdges();
  // The method removes edges that mention not existent Vertices.
  void RemoveGhostEdges();
  /**
   * Include following functions' actions:
   *    SortEdges();
   *    NormalizeEdges() - remove duplicates;
   *    RemoveGhostEdges().
   * Is a little bit more efficient if all of those are required.
   */
  void ManageEdges();

  void SetName(const std::string& new_name);
  const std::string& GetName();

  // Returns vector of the folowing index.
  const Vec3& operator[](uint32_t number) const;
  // Returns edge of the folowing index.
  const Edge& operator()(size_t number) const;

 private:
  static constexpr double kDefaultScaleFactor = 1.0;
  const Vec3& DefaultCenteringVector() const;
  void Scale(double factor);
  void Center(const Vec3& vec);
  void SetScaleFactor();      // Called inside Scale()
  void SetCenteringVector();  // Called inside Center()

  void ScaleBounds(double factor);
  void CenterBounds(const Vec3& vec);
  bool IsBound(const Vec3& vec) const;  // Check if vec is one of bounds.
  void RecalculateBounds();  // Inside check if bounds should be recalculated
  void UpdateBounds();       // Update bounds after adding new vertex.
  // Set bounds to the first vertex values (does not care what bounds were).
  void SetBoundsFirst();
  // Compare vect values to bounds and set new bounds if needed.
  void SetBoundsVect(const Vec3& vect);

  std::string m_model_name;
  Vertices m_vertices;
  Edges m_edges;
  AxisBounds3D m_bounds;

  double m_scale_factor = kDefaultScaleFactor;
  Vec3 m_centering_vector{0, 0, 0};
};  // class Model3D

}  // namespace inbound_model

#endif  // SRC_MODEL_MODEL3D_MODEL3D_H
