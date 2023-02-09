#include "ui/MainWindow.h"

#include "core/DatabaseAccess.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <concepts>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "WIMFS_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  MainWindow w;
  w.show();

  return a.exec();
}
