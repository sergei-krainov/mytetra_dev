#ifndef __RECORD_H__
#define __RECORD_H__

#include <QString>
#include <QMap>
#include <QByteArray>


// Класс одной записи в таблице записей

// В полях записей с crypt=0 хранятся незашифрованные данные
// В полях записей с crypt=1 хранятся зашифрованные данные
// Это необходимо, чтобы дерево знаний генерировалось в/из XML быстро и без шифрации

class Record
{
public:
  Record();
  virtual ~Record();

  QString getText() const;
  QString getTextDirect() const;
  void setText(QString iText);

  QString getField(QString name) const;
  void setField(QString name, QString value);

  QMap<QString, QString> getFieldList() const;

  QMap<QString, QString> getAttachList() const;
  void setAttachList(QMap<QString, QString> list);
  void insertToAttachList(QString fileId, QString fileName);

  QMap<QString, QByteArray> getPictureFiles() const;
  void setPictureFiles(QMap<QString, QByteArray> iPictureFiles);

  QMap<QString, QByteArray> getAttachFiles() const;
  void setAttachFiles(QMap<QString, QByteArray> iAttachFiles);

  bool isNull() const;
  bool isLite() const;
  void switchToLite();
  void switchToFat();

  // Шифрация
  void switchToEncryptAndSaveLite(void);
  void switchToEncryptAndSaveFat(void);

  // Расшифровка
  void switchToDecryptAndSaveLite(void);

  void pushFatAttributes();

protected:

  bool liteFlag;

  // Установка содержимого свойств происходит в вышестоящем коде

  // Легкие свойства
  QMap<QString, QString> fieldList; // Перечень свойств записи (атрибутов)
  QMap<QString, QString> attachList; // Перечень прикрепляемых файлов

  // Полновесные свойства
  QString text; // Содержимое файла с текстом записи
  QMap<QString, QByteArray> pictureFiles; // Содержимое картинок, используемых в тексте записи (используется при переносе через буфер обмена, при DragAndDrop)
  QMap<QString, QByteArray> attachFiles; // Содержимое прикрепляемых файлов (используется при переносе через буфер обмена, при DragAndDrop)

  void saveTextDirect(QString iText);

  QString getIdAndNameAsString() const; // Внутренний метод для облегчения печати отладочной информации

  QString getFullDirName() const;
  QString getFullTextFileName() const;
  QString getFullFileName(QString fileName) const;

  void switchToEncryptFields(void);

  void checkAndFillFileDir(QString &nameDirFull, QString &nameFileFull);
  void checkAndCreateTextFile() const;

};

#endif // __RECORD_H__