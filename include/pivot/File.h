#ifndef PIVOT_FILE_H
#define PIVOT_FILE_H

namespace Pivot {

class File {
public:
  File();
  virtual ~File();
  File(const String8& filePath);

  bool exists() const;
  bool isDir() const;
  String8 getAbsolutePath() const;

private:
  String8 mFilePath;

};

} // namespace Pivot

#endif // PIVOT_FILE_H
