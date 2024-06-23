#include "leveleditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LevelEditor editor;
    editor.show();
    return app.exec();
}
