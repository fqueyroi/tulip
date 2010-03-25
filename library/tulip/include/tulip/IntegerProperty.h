//-*-c++-*-
#ifndef TULIP_INT_H
#define TULIP_INT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "tulip/AbstractProperty.h"
#include "tulip/TemplateFactory.h"
#include "tulip/IntegerAlgorithm.h"

namespace tlp {

class Graph;
class PropertyContext;

typedef AbstractProperty<IntegerType,IntegerType, IntegerAlgorithm> AbstractIntegerProperty;
/** \addtogroup properties */ 
/*@{*/
class TLP_SCOPE IntegerProperty:public AbstractIntegerProperty, public PropertyObserver{ 

  friend class IntegerAlgorithm;

public :
  IntegerProperty(Graph *, std::string n = "");
  IntegerType::RealType  getNodeMin(Graph *sg=0);
  IntegerType::RealType  getNodeMax(Graph *sg=0);
  IntegerType::RealType  getEdgeMin(Graph *sg=0);
  IntegerType::RealType  getEdgeMax(Graph *sg=0);
  PropertyInterface* clonePrototype(Graph *, const std::string&);
  void copy( const node, const node, PropertyInterface * );
  void copy( const edge, const edge, PropertyInterface * );

  // redefinition of some PropertyObserver methods 
  virtual void beforeSetNodeValue(PropertyInterface* prop, const node n);
  virtual void beforeSetEdgeValue(PropertyInterface* prop, const edge e);
  virtual void beforeSetAllNodeValue(PropertyInterface* prop);
  virtual void beforeSetAllEdgeValue(PropertyInterface* prop);

protected:
  void clone_handler(AbstractProperty<IntegerType,IntegerType> &);

private:
  TLP_HASH_MAP<unsigned int, int> maxN,minN,maxE,minE;
  TLP_HASH_MAP<unsigned int, bool> minMaxOkNode;
  TLP_HASH_MAP<unsigned long, bool> minMaxOkEdge;
  void computeMinMaxNode(Graph *sg=0);
  void computeMinMaxEdge(Graph *sg=0);
};

class TLP_SCOPE IntegerVectorProperty:public AbstractProperty<IntegerVectorType,IntegerVectorType> { 
public :
  IntegerVectorProperty(Graph *g, std::string n =""):AbstractProperty<IntegerVectorType, IntegerVectorType>(g, n) {}
  PropertyInterface* clonePrototype(Graph *, const std::string&);
  void copy( const node, const node, PropertyInterface * );
  void copy( const edge, const edge, PropertyInterface * );
};
/*@}*/

}
#endif
