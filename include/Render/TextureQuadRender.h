#pragma once

namespace vrv {

  class Geometry;
  class StateSet;
  class Texture2D;

  class TextureQuadRender {
  public:
    TextureQuadRender();

    void drawTexture(Texture2D*);

  protected:
    void initialize();

  protected:
    Geometry* myQuadGeometry;
    StateSet* myStateSet;
  };
}