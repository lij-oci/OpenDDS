/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include "dds_generator.h"
#include <utl_scoped_name.h>
#include <ast.h>

#include <string>

struct FieldInfo {
  struct EleLen {
    AST_Type* ele_;
    std::size_t len_;
    explicit EleLen(FieldInfo& af);
    bool operator<(const EleLen& o) const;
  };
  typedef std::set<EleLen> EleLenSet;

  static const std::string scope_op;
  static bool cxx11();
  static std::string at_pfx();
  static std::string get_type_name(AST_Type& field);
  static std::string underscored_type_name(UTL_ScopedName* sn, AST_Type& field);
  static std::string underscore(const std::string& scoped_type);
  static std::string ref(const std::string& scoped_t, const std::string& underscored_t, const std::string& const_s = "const ");

  AST_Type* type_;
  std::string name_;
  std::string underscored_;
  AST_Type* act_;
  AstTypeClassification::Classification cls_;
  AST_Array* arr_;
  AST_Sequence* seq_;
  AST_Type* as_base_;
  AST_Type* as_act_;
  AstTypeClassification::Classification as_cls_;
  std::string scoped_elem_;
  std::string underscored_elem_;
  std::string elem_ref_;
  std::string elem_const_ref_;

  std::string scoped_type_;
  std::string struct_name_;
  std::string type_name_;

  std::size_t n_elems_;
  std::string length_;

  std::string unwrap_;
  std::string const_unwrap_;
  std::string arg_;
  std::string ref_;
  std::string const_ref_;
  std::string ptr_;

  explicit FieldInfo(AST_Field& field); //for anonymous types
  FieldInfo(UTL_ScopedName* sn, AST_Type* base);
  void init();
  bool is_new(EleLenSet& el_set);
  bool anonymous_array() const;
  bool anonymous_sequence() const;
  bool anonymous() const;
};

#endif