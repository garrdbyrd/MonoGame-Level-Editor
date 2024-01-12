#ifndef SELECTABLELABEL_H
#define SELECTABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class SelectableLabel : public QLabel {
  Q_OBJECT

public:
  explicit SelectableLabel(QWidget *parent = nullptr);

  void setSelected(bool selected);
  bool isSelected() const;
  void setTextureFilePath(const QString &filePath) {
    textureFilePath = filePath;
  }
  QString getTextureFilePath() const { return textureFilePath; }

signals:
  void clicked(SelectableLabel *label);

protected:
  void mousePressEvent(QMouseEvent *event) override;

private:
  bool selected;
  QString textureFilePath;
};

#endif // SELECTABLELABEL_H
