#include "../GeoSet.h"

void loadCube( GeoSet& gset )
{
        cout<<"Creating *cube* GeoSet\n"<<flush;

    float coords[] =
    {
      -5.0f, -5.0f,  5.0f,
       5.0f, -5.0f,  5.0f,
       5.0f,  5.0f,  5.0f,
      -5.0f,  5.0f,  5.0f,
      -5.0f, -5.0f, -5.0f,
       5.0f, -5.0f, -5.0f,
       5.0f,  5.0f, -5.0f,
      -5.0f,  5.0f, -5.0f
    };

    float colors[] = { 1.0f, 0.0f, 0.0f, 1.0f,
                       0.0f, 0.0f, 1.0f, 1.0f,
                       0.0f, 1.0f, 1.0f, 1.0f,
                       0.3f, 0.3f, 0.3f, 1.0f,

                       1.0f, 1.0f, 1.0f, 1.0f,
                       0.0f, 0.5f, 1.5f, 1.0f,
                       0.5f, 0.5f, 0.0f, 1.0f,
                       0.5f, 0.0f, 0.5f, 1.0f };




    unsigned int cindex[] =
    {
      0, 1, 2, 3,           // front
      0, 3, 7, 4,           // left
      4, 7, 6, 5,           // back
      1, 5, 6, 2,           // right
      3, 2, 6, 7,           // top
      0, 4, 5, 1            // bottom
    };

    float norms[] =
    {
       0.0,  0.0,  1.0,
       0.0,  0.0, -1.0,
       0.0,  1.0,  0.0,
       0.0, -1.0,  0.0,
       1.0,  0.0,  0.0,
      -1.0,  0.0,  0.0
    };

    unsigned int nindex[] =
    {
      0,
      5,
      1,
      4,
      2,
      3
    };

    gset.setPrimType( GeoSet::QUADS );
    gset.setNumPrims( 6 );
    gset.allocate();
    gset.setAttr( GeoSet::COORD3, GeoSet::PER_VERTEX, coords, cindex );
    gset.setAttr( GeoSet::COLOR4, GeoSet::PER_VERTEX, colors, cindex );
    gset.setAttr( GeoSet::NORMAL3, GeoSet::PER_PRIM, norms, nindex );
}

void main()
{
  GeoSet gset;
  loadCube( gset );
}
