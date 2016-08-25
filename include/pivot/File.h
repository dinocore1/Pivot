#ifndef PIVOT_FILE_H
#define PIVOT_FILE_H

namespace Pivot {

class File {
public:
  File();
  virtual ~File();
  File(const String& filePath);

  bool exists() const;
  bool isDir() const;

private:
  String mFilePath;

};

} // namespace Pivot

#endif // PIVOT_FILE_H
