#pragma once

#include <Core/Matrix4f.h>

namespace vrv {

  class RenderState;
  class Program;

  class StateSet {
  public:
    StateSet();
    StateSet(Program* shader);
    StateSet(RenderState* state, Program* shader);

    void setRenderState(RenderState*);
    RenderState* renderState();
    RenderState* renderState() const;

    void setProgram(Program*);
    Program* program();
    Program* program() const;

    bool operator < (StateSet& state) const;

    void bind();
    void unbind();

  protected:
    RenderState* myRenderState;
    Program* myProgram;
    Matrix4f myProjectionMatrix;
  };

}