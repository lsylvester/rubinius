#ifndef RBX_SCOPE_VARIABLES_HPP
#define RBX_SCOPE_VARIABLES_HPP

#include "builtin/object.hpp"

namespace rubinius {
  class VariableScope;

  class StackVariables {
    VariableScope* on_heap_;
    VariableScope* parent_;
    Object* self_;
    Object* block_;
    Module* module_;
    Object* locals_[];

  public:
    void initialize(Object* self, Object* block, Module* module, int locals) {
      on_heap_ = 0;
      parent_ = 0;
      self_ = self;
      block_ = block;
      module_ = module;

      for(int i = 0; i < locals; i++) {
        locals_[i] = Qnil;
      }
    }

    VariableScope* on_heap() {
      return on_heap_;
    }

    VariableScope* parent() {
      return parent_;
    }

    void set_parent(VariableScope* scope) {
      parent_ = scope;
    }

    Object* self() {
      return self_;
    }

    Object* block() {
      return block_;
    }

    Module* module() {
      return module_;
    }

    bool made_alias_p() {
      return on_heap_ != 0;
    }

    Object* get_local(int which) {
      return locals_[which];
    }

    void set_local(int which, Object* val) {
      locals_[which] = val;
    }

    VariableScope* create_heap_alias(STATE, CallFrame* call_frame);
    void flush_to_heap(STATE);

    friend class GarbageCollector;
  };
}

#endif
