#ifndef INTERACTORTOOLBARITEM_H
#define INTERACTORTOOLBARITEM_H

#include <QtGui/QGraphicsItemGroup>

namespace tlp {
class ToolbarItem;
class Interactor;

class InteractorToolbarItem: public QObject, public QGraphicsItemGroup {
  Q_OBJECT
public:
  InteractorToolbarItem(std::list<Interactor *> interactors, QGraphicsItem *parent=0, QGraphicsScene *scene=0);
  virtual ~InteractorToolbarItem();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0);
  virtual QRectF boundingRect() const;

public slots:
  void displayConfigurationWidget(bool);

protected slots:
  void sceneResized();

protected:
  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
  std::list<Interactor *> _interactors;
  ToolbarItem *_toolbar;

  Qt::ToolBarArea _snapArea;
  int _round;
  int _margin;
  QRectF _configureRect;

  QRectF toolbarBoundingRect() const;
};
}

#endif // INTERACTORTOOLBARITEM_H
