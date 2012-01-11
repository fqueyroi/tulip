#ifndef TULIPFONTDIALOG_H
#define TULIPFONTDIALOG_H

#include <QtGui/QDialog>
#include <tulip/tulipconf.h>
#include <tulip/TulipFont.h>

namespace Ui {
class TulipFontDialog;
}

namespace tlp {

class TLP_QT_SCOPE TulipFontDialog : public QDialog {
  Q_OBJECT

  Ui::TulipFontDialog* _ui;

public:
  explicit TulipFontDialog(QWidget *parent = 0);
  TulipFont font() const;
  int fontSize() const;

public slots:
  void selectFont(const TulipFont&);

protected slots:
  void fontChanged();
};

}

#endif // TULIPFONTDIALOG_H
