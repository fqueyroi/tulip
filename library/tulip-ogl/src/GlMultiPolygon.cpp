#include "tulip/GlMultiPolygon.h"

using namespace std;

namespace tlp {

  static const Color oColor(255,255,255,255);
  static const Color fColor(0,0,0,0);

  GlMultiPolygon::GlMultiPolygon(bool filled, bool outlined,const Color &fillColor, const Color &outlineColor):
    filled(filled),outlined(outlined),fillColor(fillColor),outlineColor(outlineColor) {
  }

  void GlMultiPolygon::addPolygon(const vector<Coord> &poly) {
    polygons.push_back(GlPolygon(filled,outlined));
    GlPolygon *newPolygon=&(*(--polygons.end()));
    for(vector<Coord>::const_iterator it=poly.begin();it!=poly.end();++it) {
      newPolygon->addPoint((*it),fillColor,outlineColor);
    }

    BoundingBox bb(newPolygon->getBoundingBox());
    boundingBox.expand(bb[0]);
    boundingBox.expand(bb[1]);
  }

  void GlMultiPolygon::draw(float lod,Camera *camera) {
    for(vector<GlPolygon>::iterator it=polygons.begin();it!=polygons.end();++it) {
      (*it).draw(lod,camera);
    }
  }
  //=====================================================
  void GlMultiPolygon::translate(const Coord& vec) {
    boundingBox.translate(vec);
    
    for(vector<GlPolygon>::iterator it=polygons.begin();it!=polygons.end();++it) {
      (*it).translate(vec);
    }
  }
  //=====================================================
  void GlMultiPolygon::getXML(xmlNodePtr rootNode) {
  }
  //============================================================
  void GlMultiPolygon::setWithXML(xmlNodePtr rootNode) {
  }

}
