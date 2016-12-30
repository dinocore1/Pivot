
namespace pivot {

  extern void initialize_string8();
  extern void terminate_string8();

  class LibPivotStatics {
  public:
    LibPivotStatics() {
      initialize_string8();
    }

    ~LibPivotStatics() {
      terminate_string8();
    }
  };

  static LibPivotStatics gTheStaticObj;

} // namespace pivot
