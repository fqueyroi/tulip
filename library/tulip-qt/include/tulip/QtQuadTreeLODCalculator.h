//-*-c++-*-
/**
 Author: Morgan Mathiaut
 Email : mathiaut@labri.fr
 Last modification : 29/05/2009
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
*/
#ifndef Tulip_QTQUADTREELODCALCULATOR_H
#define Tulip_QTQUADTREELODCALCULATOR_H

#include <map>
#include <vector>

#include <tulip/BoundingBox.h>
#include <tulip/GlGraphInputData.h>
#include <tulip/Matrix.h>
#include <tulip/Vector.h>
#include <tulip/GlSceneObserver.h>

#include "tulip/QtCPULODCalculator.h"

namespace tlp {

  class Camera;
  class QuadTreeNode;
  class GlScene;

  /**
   * Class use to compute bounding boxs of a vector of GlEntity
   */
  class TLP_QT_SCOPE QtQuadTreeLODCalculator : public QtCPULODCalculator, public GraphObserver, public Observer, public GlSceneObserver {

  public:

    QtQuadTreeLODCalculator();
    ~QtQuadTreeLODCalculator();

    void setScene(GlScene *scene);

    bool needEntities();
    void setNeedEntities(bool);

    void addSimpleEntityBoundingBox(unsigned long entity,const BoundingBox& bb);
    void addNodeBoundingBox(unsigned int id,const BoundingBox& bb);
    void addEdgeBoundingBox(unsigned int id,const BoundingBox& bb);

    void compute(const Vector<int,4>& globalViewport,const Vector<int,4>& currentViewport,RenderingEntitiesFlag type);

    void computeFor3DCamera(SimpleBoundingBoxVector *inputSimple,ComplexBoundingBoxVector *inputNodes,ComplexBoundingBoxVector *inputEdges,
        SimpleLODResultVector *outputSimple, ComplexLODResultVector *outputNodes, ComplexLODResultVector *outputEdges,
        const Coord &eye,
        const Matrix<float, 4> transformMatrix,
        const Vector<int,4>& globalViewport,
        const Vector<int,4>& currentViewport);

    void clear();

    void removeObservers();
    void addObservers();

    void setInputData(GlGraphInputData *newInputData);

    void update(std::set<Observable *>::iterator begin ,std::set<Observable *>::iterator end);
    void observableDestroyed(Observable *) {}
    void addNode(Graph *,const node ){haveToCompute=true;removeObservers();}
    void addEdge(Graph *,const edge ){haveToCompute=true;removeObservers();}
    void delNode(Graph *,const node ){haveToCompute=true;removeObservers();}
    void delEdge(Graph *,const edge ){haveToCompute=true;removeObservers();}
    void addLocalProperty(Graph*, const std::string &name);
    void delLocalProperty(Graph*, const std::string &name);

    void addLayer(GlScene*, const std::string&, GlLayer*){haveToCompute=true;removeObservers();}
    void delLayer(GlScene*, const std::string&, GlLayer*){haveToCompute=true;removeObservers();}
    void modifyLayer(GlScene*, const std::string&, GlLayer*){haveToCompute=true;removeObservers();}
    void modifyEntity(GlScene *,GlSimpleEntity *){haveToCompute=true;removeObservers();}

    virtual GlLODCalculator *clone() {
      QtQuadTreeLODCalculator *newCalculator=new QtQuadTreeLODCalculator();
      newCalculator->setScene(scene);
      newCalculator->setInputData(inputData);
      return newCalculator;
    }

  protected :

    GlScene *scene;
    Graph *rootGraph;

    QuadTreeNode *nodesQuadTree;
    QuadTreeNode *edgesQuadTree;
    QuadTreeNode *nodesSelectedQuadTree;
    QuadTreeNode *edgesSelectedQuadTree;
    QuadTreeNode *entitiesQuadTree;
    VectorOfSimpleBoundingBoxVector simpleEntities;

    bool haveToCompute;

    GlGraphInputData *inputData;

    BoundingBox nodesGlobalBoundingBox;
    BoundingBox edgesGlobalBoundingBox;
    BoundingBox entitiesGlobalBoundingBox;

    std::vector<std::pair<Camera*,Camera> > cameras;
    Camera *currentCamera;
    Graph *currentGraph;
    PropertyInterface *layoutProperty;
    PropertyInterface *sizeProperty;
    PropertyInterface *selectionProperty;

    //int size;
  };

}

#endif // Tulip_GLQUADTREELODCALCULATOR_H
