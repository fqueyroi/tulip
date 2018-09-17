/**
 *
 * This file is part of Tulip (http://tulip.labri.fr)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#ifndef SOMVIEW_H_
#define SOMVIEW_H_

#include <tulip/GlMainView.h>
#include <tulip/MouseInteractors.h>

#include <SOMAlgorithm.h>
#include <InputSample.h>

#include "../../utils/PluginNames.h"

namespace tlp {
class SOMPreviewComposite;
class SOMMap;
class NumericProperty;
class ColorProperty;
class ColorScale;
class BooleanProperty;
class GlGraphComposite;
class LayoutProperty;
class SizeProperty;
class SOMMapElement;
class SOMPropertiesWidget;

/*@{*/
/** \file
 *  \brief  Tulip self organizing map view

 * This view plug-in allows users to generate self organizing map (sometimes called Kohonen map)
 from graph data.
 * The model was first described as an artificial neural network by the Finnish professor Teuvo
 Kohonen.
 * This view is useful to visualize high-dimensional data in a low-dimensional representation.
 *
 * Self organizing maps operate in two modes: training and mapping.
 * Training builds the map using input examples.
 * Mapping automatically classifies data on the map generated by training.
 */
class SOMView : public GlMainView {
  Q_OBJECT

  PLUGININFORMATION(
      ViewName::SOMViewName, "Dubois Jonathan", "02/2009",
      "The Self Organizing Map view allows to generate self organizing map (also called Kohonen "
      "map) from graph data. "
      "The model was first described as an artificial neural network by the Finnish professor "
      "Teuvo Kohonen. "
      "This view is useful to visualize high-dimensional data in a low-dimensional representation."
      "<p>Self organizing maps operate in two modes: training and mapping.<ul><li>Training builds "
      "the map using input examples.</li><li>Mapping automatically classifies data on the map "
      "generated by training.</li></ul></p>",
      "1.1", "View")
public:
  SOMView(PluginContext *);
  ~SOMView() override;
  std::string icon() const override {
    return ":/som_view.png";
  }
  void construct(QWidget *parent);
  void setState(const DataSet &dataSet) override;
  DataSet state() const override;
  void graphChanged(Graph *) override;
  void draw() override;
  void drawMapWidget();
  void drawPreviewWidget();
  void init();
  void refresh() override;
  QList<QWidget *> configurationWidgets() const override;

  void createPicture(const std::string &pictureName, int width, int height);

  bool createPicture(const std::string &pictureName, int width, int height, bool center);

  void update(std::set<tlp::Observable *>::iterator begin,
              std::set<tlp::Observable *>::iterator end);
  void observableDestroyed(tlp::Observable *);

  bool eventFilter(QObject *, QEvent *) override;

  /**
   * Return all the previews.
   * @return a vector with all the previews.
   */
  std::vector<SOMPreviewComposite *> getPreviews();

  /**
   * Return the name of the selected property
   * @return
   */
  std::string getSelectedProperty() {
    return selection;
  }

  /**
   * Get the DoubleProperty pointer on the the current selected property. Return nullptr if no
   * properties are selected.
   * @return
   */
  NumericProperty *getSelectedPropertyValues();

  /**
   * Return the ColorProperty pointer for the selected property. Return nullptr if no properties are
   * selected.
   * @return
   */
  ColorProperty *getSelectedBaseSOMColors();
  /**
   * Returns the current SOMMap.
   **/
  SOMMap *getSOM() {
    return som;
  }

  /**
   * Return the input sample
   **/
  InputSample &getInputSample() {
    return inputSample;
  }

  /**
   * Get the color scale of the main SOM.
   * @return
   */
  ColorScale *getColorScale();

  /**
   * Change the color of the main SOM using those in the given property.
   * @param newColor
   */
  void setColorToMap(tlp::ColorProperty *newColor);

  std::map<tlp::node, std::set<tlp::node>> &getMappingTab() {
    return mappingTab;
  }

  /**
   * Add a mask on the som. All the nodes in the set will be printed with right color others will be
   * printed in gray.
   * @param mask
   */
  void setMask(const std::set<node> &mask);

  /**
   * Get the current mask on the data.
   * @return The pointer on the som mask or nullptr if there is no mask.
   */
  BooleanProperty *getMask() {
    return mask;
  }

  tlp::GlMainWidget *getMapWidget() {
    return mapWidget;
  }

public slots:

  /**
   * Display the detailled mode
   */
  void switchToDetailledMode(SOMPreviewComposite *preview);

  /**
   * Display the preview mode
   */
  void switchToPreviewMode();

  /**
   * Add the property with the given name to the selection.
   * @param propertyName the name of the property.
   */
  void addPropertyToSelection(const std::string &propertyName);
  /**
   * Remove the property with the given name from the selection.
   * @param propertyName the name of the property.
   */
  void removePropertyFromSelection(const std::string &propertyName);
  /**
   * Clear all the preview selection.
   */
  void clearSelection();
  /**
   *
   */
  void updateDefaultColorProperty();

  /**
   * Clear the mask.
   */
  void clearMask();

  /**
   * Copy the current selection to the mask
   */
  void copySelectionToMask();

  /**
   * Select all the inputs nodes contained in the mask.
   */
  void selectAllNodesInMask();
  /**
   * Invert the mask selection. Set all the gray nodes to original colors and original colors to
   * gray.
   */
  void invertMask();

  void applySettings() override;

protected slots:

  void fillContextMenu(QMenu *menu, const QPointF &) override;

private:
  void copyToGlMainWidget(GlMainWidget *widget);

  void addEmptyViewLabel();
  void removeEmptyViewLabel();

  void registerTriggers();

  /**
   * Init the GlMainWidget object. At this time only init the previewWidget as the mapWidget is
   * initialized when a new graph is given in the function changeMapViewGraph.
   */
  void initGlMainViews();
  /**
   * Init the menu.
   */
  void initMenu();

  /**
   * Function called when a new graph is set. Init the SOM view with the new Graph.
   * @param graph The new graph.
   */
  void changeMapViewGraph(tlp::Graph *graph);

  /**
   * Build the SOM with the properties stored in the SOMPropertiesDialog.
   */
  void buildSOMMap();
  /**
   *  Clean the current SOM.
   */
  void cleanSOMMap();

  /**
   * Update the current input sample with the current graph.
   */
  void updateInputSample();

  /**
   * Get the previews composite at the viewport coord.
   * @param x the x value.
   * @param y the y value.
   * @param result The vector with the previews at the current pos.
   */
  void getPreviewsAtViewportCoord(int x, int y, std::vector<SOMPreviewComposite *> &result);

  /**
   * Draw the previews.
   */
  void drawPreviews();

  /**
   * Update the previews colors.
   */
  void refreshPreviews();

  /**
   * Clear the preview screen.
   */
  void clearPreviews();

  /**
   * Draw the SOM with the properties selected.
   */
  void refreshSOMMap();
  /**
   * Clear the SOM screen.
   */
  void clearSOMMapView();

  /**
   * Function used to create and fill a ColorProperty corresponding to a NumericProperty in the SOM.
   * @param propertyName the name of the property to compute.
   * @param minValue the smallest value in the double property.
   * @param maxValue the greatest value in the double property.
   * @return
   */
  ColorProperty *computePropertyColor(const std::string &propertyName, double &minValue,
                                      double &maxValue);

  /**
   * Compute a ColorProperty object from a DoubleProperty in the SOM. Get the min and the max value
   * of the SOM double property.
   * @param SOM the map.
   * @param property the property name.
   * @param colorScale the ColorScale used to compute the color.
   * @param result the color property containing the final color.
   */
  void computeColor(SOMMap *som, tlp::NumericProperty *property, tlp::ColorScale &colorScale,
                    tlp::ColorProperty *result);

  void internalSwitchToDetailledMode(SOMPreviewComposite *preview, bool animation);

  void internalSwitchToPreviewMode(bool animation);

  void interactorsInstalled(const QList<Interactor *> &interactors) override;

  bool checkGridValidity() const;

  GlGraphComposite *graphComposite;

  // Properties
  tlp::LayoutProperty *graphLayoutProperty;
  tlp::SizeProperty *graphSizeProperty;
  tlp::BooleanProperty *mask;

  tlp::BooleanProperty *somMask;

  SOMAlgorithm algorithm;

  SOMMapElement *mapCompositeElements;

  SOMMap *som;
  InputSample inputSample;

  std::map<tlp::node, std::set<tlp::node>> mappingTab;

  std::string selection;

  std::map<std::string, ColorProperty *> propertyToColorProperty;
  std::map<std::string, SOMPreviewComposite *> propertyToPreviews;

  GlMainWidget *previewWidget;
  GlMainWidget *mapWidget;

  bool isDetailledMode;

  bool mappingIsVisible;

  MousePanNZoomNavigator navigator;
  MouseNKeysNavigator knav;

  // QAction
  QAction *hideMappingAction;
  QAction *showMappingAction;
  QAction *computeMappingAction;
  QAction *updateNodesColorAction;
  QAction *addSelectionToMaskAction;
  QAction *clearMaskAction;
  QAction *invertMaskAction;
  QAction *selectNodesInMaskAction;

  SOMPropertiesWidget *properties;

  bool destruct;
  bool somMapIsBuild;
  bool isConstruct;

private slots:

  /**
   * Map the nodes of the input sample on the SOM.
   */
  void computeMapping();

  /**
   * Train the current SOM.
   * Ask user for properties to use and for iteration number and call the training SOM process :
   * initialization, training.
   */
  void computeSOMMap();

  /**
   * Hide the input samples nodes on the SOM view.
   */
  void showMapping();
  /**
   * Show the input samples nodes on the SOM view.
   */
  void hideMapping();

  /**
   * Set it's SOM bmu node color for each node of the input sample.
   */
  void updateNodeColorMapping(tlp::ColorProperty *cp = nullptr);

  /**
   * Slot called when the grid structure properties are updated.
   */
  void gridStructurePropertiesUpdated();
  /**
   * Called when the learning algorithm properties are updated
   */
  void learningAlgorithmPropertiesUpdated();
  /**
   * Called when the Graph representation properties are updated
   */
  void graphRepresentationPropertiesUpdated();

  /**
   * Called when the number of dimension is updated.
   */
  void dimensionUpdated();

  void toggleInteractors(const bool activate);
};
} // namespace tlp
#endif /* SOMVIEW_H_ */
