#pragma once

#include "bytecode.h"

#include <vbcc.h>

namespace vbcc
{
  using namespace trieste;

  const auto Binop =
    T(Add,
      Sub,
      Mul,
      Div,
      Mod,
      Pow,
      And,
      Or,
      Xor,
      Shl,
      Shr,
      Eq,
      Ne,
      Lt,
      Le,
      Gt,
      Ge,
      Min,
      Max,
      LogBase,
      Atan2);

  const auto Unop =
    T(Neg,
      Not,
      Abs,
      Ceil,
      Floor,
      Exp,
      Log,
      Sqrt,
      Cbrt,
      IsInf,
      IsNaN,
      Sin,
      Cos,
      Tan,
      Asin,
      Acos,
      Atan,
      Sinh,
      Cosh,
      Tanh,
      Asinh,
      Acosh,
      Atanh,
      Len,
      MakePtr,
      Read);

  const auto Constant = T(Const_E, Const_Pi, Const_Inf, Const_NaN);

  const auto Def = Unop / Binop / Constant /
    T(Global,
      Const,
      ConstStr,
      Convert,
      Stack,
      Heap,
      Region,
      StackArray,
      StackArrayConst,
      HeapArray,
      HeapArrayConst,
      RegionArray,
      RegionArrayConst,
      Copy,
      Move,
      FieldRef,
      ArrayRef,
      ArrayRefConst,
      Load,
      Store,
      Lookup,
      FnPointer,
      Call,
      CallDyn,
      Subcall,
      SubcallDyn,
      Try,
      TryDyn,
      FFI,
      When,
      Typetest);

  Parse parser();
  PassDef statements();
  PassDef labels();
  PassDef assignids(std::shared_ptr<State> state);
  PassDef validids(std::shared_ptr<State> state);
  PassDef liveness(std::shared_ptr<State> state);

  struct Options : public trieste::Options
  {
    std::filesystem::path compilation_path;
    std::filesystem::path bytecode_file;
    bool strip = false;

    void configure(CLI::App& cli) override;
    std::filesystem::path relative(const std::filesystem::path& path);
  };

  Node err(Node node, const std::string& msg);
  ValueType val(Node ptype);
  Options& options();

  std::string unescape(const std::string_view& in);
}
