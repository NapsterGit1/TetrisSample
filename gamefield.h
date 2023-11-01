#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>

class GameField : public QWidget {
  Q_OBJECT

  // Выжно! название свойства и его тип (uint rowsNumber / columnsNumber)
  // Должны совпадать с названием и типом, который вы указываете в
  // динамических свойства в Дизайнере
  Q_PROPERTY(uint rowsNumber READ GetRowsNumber WRITE SetRowsNumber NOTIFY
                 RowsNumberChanged FINAL)

  Q_PROPERTY(uint columnsNumber READ GetColumnsNumber WRITE SetColumnsNumber
                 NOTIFY ColumnsNumberChanged FINAL)
  // где:
  // uint columnsNumber - название и тип свойства
  // READ GetColumnsNumber - указание метода, ответственного за получение
  // значания WRITE SetRowsNumber - указание метода, ответственного за установку
  // значания NOTIFY RowsNumberChanged - указание сигнала, вызываемого, при
  // изменении значения

 public:
  explicit GameField(QWidget *parent = nullptr);

 signals:
  void RowsNumberChanged();
  void ColumnsNumberChanged();
  void InitialisationStarted();

 public slots:
  void StartNewGame();

 private slots:
  void SetCells();

 public:
  uint GetColumnsNumber() const;
  void SetColumnsNumber(uint columnsCount);
  uint GetRowsNumber() const;
  void SetRowsNumber(uint rowsCount);

 protected:
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);

 private:
  void DrawCells(QPainter *painter);
  QSize GetSize() const;
  void ResetCellsColor();

 private:
  const uint kCellSize = 20;
  const QColor kCellDefaultColor = QColor(150, 150, 150);

  QVector<QVector<QColor>> cellsColors_;

  uint rowsCount_ = 0;
  uint columnsCount_ = 0;
  bool isPlaying_;
};

#endif  // GAMEFIELD_H
