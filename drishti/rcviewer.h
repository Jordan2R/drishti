#ifndef RCVIEWER_H
#define RCVIEWER_H


#include <QGLViewer/qglviewer.h>
#include <QGLViewer/vec.h>
using namespace qglviewer;

#include <QGLFramebufferObject>

#include "mybitarray.h"
#include "volumefilemanager.h"
#include "boundingbox.h"

class RcViewer : public QObject
{
  Q_OBJECT

 public :
  RcViewer();
  ~RcViewer();

  void setViewer(QGLViewer *v) { m_viewer = v; }

  void init();

  void draw();
  void fastDraw();

  void setGridSize(int, int, int);
  void setVolDataPtr(VolumeFileManager*);
  void updateSubvolume(Vec, Vec);

  void resizeGL(int, int);

  void setLut(uchar*);

  void activateBounds(bool);

  void setXformMatrix(double*);

 
  bool exactCoord() { return m_exactCoord; }
  int skipLayers() { return m_skipLayers; }
  int spec() { return m_spec; }
  int edge() { return m_edge; }
  int shadow() { return m_shadow; }
  Vec shadowColor() { return m_shadowColor; }
  Vec edgeColor() { return m_edgeColor; }
  float stillStep() { return m_stillStep; }
  float dragStep() { return m_dragStep; }

  public slots :
    void updateVoxelsForRaycast();
    void setRaycastStyle(int);
    void setSkipLayers(int l) { m_skipLayers = l; m_viewer->update(); }
    void setShadowColor();
    void setEdgeColor();
    void setSpec(int a) { m_spec = (float)a/10.0f; m_viewer->update(); }
    void setEdge(int e) { m_edge = e; m_viewer->update(); }
    void setShadow(int e) { m_shadow = e; m_viewer->update(); }
    void setShadowOffsetX(int x) { m_shdX = x; m_viewer->update(); }
    void setShadowOffsetY(int y) { m_shdY = y; m_viewer->update(); }
    void setExactCoord(bool);
    void setStillAndDragStep(float, float);

 private :

  QGLViewer *m_viewer;

  VolumeFileManager *m_vfm;
  uchar *m_volPtr;
  uchar *m_lut;
  
  double m_b0xform[16];
  double m_b0xformInv[16];

  qint64 m_depth, m_width, m_height;
  int m_minDSlice, m_maxDSlice;
  int m_minWSlice, m_maxWSlice;
  int m_minHSlice, m_maxHSlice;
  Vec m_dataMin, m_dataMax;

  int m_dbox, m_wbox, m_hbox, m_boxSize;
  QList<int> m_boxMinMax;
  MyBitArray m_filledBoxes;

  float m_amb, m_diff, m_spec;
  int m_shadow;
  float m_edge;
  Vec m_shadowColor, m_edgeColor;
  int m_shdX, m_shdY;

  int m_max3DTexSize;
  int m_skipLayers;
  float m_stillStep, m_dragStep;

  GLuint m_slcBuffer;
  GLuint m_rboId;
  GLuint m_slcTex[2];

  GLuint m_eBuffer;
  GLuint m_ebId;
  GLuint m_ebTex[3];

  GLuint m_dataTex;
  GLuint m_lutTex;
  int m_sslevel;
  Vec m_corner, m_vsize;

  GLhandleARB m_blurShader;
  GLint m_blurParm[20];

  GLhandleARB m_rcShader;
  GLint m_rcParm[20];

  GLhandleARB m_eeShader;
  GLint m_eeParm[20];

  bool m_exactCoord;
  bool m_fullRender;
  bool m_dragMode;
  int m_renderMode;
  
  float m_stillstep;

  BoundingBox m_boundingBox;
  
  void generateBoxMinMax();
  void updateFilledBoxes();

  void createRaycastShader();
  void createShaders();
  void createFBO();

  void raycasting();
  void volumeRaycast(float, float, bool);

  void drawBox(GLenum);
  void drawFace(int, Vec*, Vec*);
  void drawClipFaces(Vec*, Vec*);

  void drawInfo();
};




#endif