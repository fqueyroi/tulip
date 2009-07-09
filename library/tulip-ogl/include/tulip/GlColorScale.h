/*
	  GlColorScale.h

   Created on: 18 févr. 2009
       Author: Antoine Lambert
       E-mail: antoine.lambert@labri.fr

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

 */

#ifndef GLCOLORSCALE_H_
#define GLCOLORSCALE_H_

#include <tulip/Observable.h>
#include <tulip/GlPolyQuad.h>
#include <tulip/ColorScale.h>

namespace tlp {

class TLP_GL_SCOPE GlColorScale : public GlSimpleEntity, public Observer {

public:

  enum Orientation {
    Horizontal, Vertical
  };

  GlColorScale(ColorScale *colorScale, const Coord &baseCoord, const float length,
			   const float thickness, Orientation orientation);

  ~GlColorScale();

  Color getColorAtPos(Coord pos);

  void draw(float lod, Camera* camera);

  void translate(const Coord &move);

  void getXML(xmlNodePtr rootNode) {}

  void setWithXML(xmlNodePtr rootNode) {}

  Coord getBaseCoord() const {return baseCoord;}

  float getThickness() const {return thickness;}

  float getLength() const {return length;}

  GlPolyQuad *getColorScalePolyQuad() const {return colorScalePolyQuad;}

  void setColorScale(ColorScale * scale);

  ColorScale *getColorScale() {return colorScale;}

  void update(std::set<Observable *>::iterator begin ,std::set<Observable *>::iterator end);

  void observableDestroyed(Observable *) {}

private:

  void updateDrawing();

  ColorScale *colorScale;
  Coord baseCoord;
  float length, thickness;
  GlPolyQuad *colorScalePolyQuad;
  Orientation orientation;
};

}

#endif /* GLCOLORSCALE_H_ */
