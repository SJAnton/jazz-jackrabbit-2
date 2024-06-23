#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>
#include "leveleditor.h"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWindow(QWidget *parent = nullptr);
    ~SetupWindow();

private slots:
    void on_startLevelEditorButton_clicked();

private:
    Ui::SetupWindow *ui;
    LevelEditor *levelEditor;
};

#endif // SETUPWINDOW_H

