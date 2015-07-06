#ifndef GL_IGLDRAWWORK_H
#define GL_IGLDRAWWORK_H
#include "head.h"
#include "GLvboBuffer.h"
#include "GLTexture.h"
class IGLDrawWork:public RefCount
{
public:
    IGLDrawWork() = default;
    virtual ~IGLDrawWork() = default;
    /*Main interface*/
    virtual void onDraw(GLTexture* src, GLvboBuffer* vs, GLvboBuffer* ts) = 0;
    
    /*All parameters is in [0,1), set self parameters by these, if parameters is NULL, don't do anything just return the number of parameters needed*/
    virtual int vMap(double* parameters, int n) = 0;
private:
    IGLDrawWork(const IGLDrawWork&) = default;
    IGLDrawWork& operator=(const IGLDrawWork&) = default;
};
#endif