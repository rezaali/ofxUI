/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_SCROLLABLE_CANVAS
#define OFXUI_SCROLLABLE_CANVAS

#include "ofxUICanvas.h"

class ofxUIScrollableCanvas : public ofxUICanvas
{    
public:    
    ~ofxUIScrollableCanvas()
    {
        delete sRect;
    }
    
    ofxUIScrollableCanvas(float x, float y, float w, float h) : ofxUICanvas(x,y,w,h)
    {
        initScrollable();
    }
    
    ofxUIScrollableCanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources) : ofxUICanvas(x,y,w,h,sharedResources)
    {
        initScrollable();        
    }
    
    ofxUIScrollableCanvas() : ofxUICanvas()
    {
        initScrollable();
    }
    
    ofxUIScrollableCanvas(ofxUICanvas *sharedResources) : ofxUICanvas(sharedResources)
    {
        initScrollable();
    }

    void initScrollable()
    {
        kind = OFX_UI_WIDGET_SCROLLABLECANVAS;
        sRect = new ofxUIRectangle(rect->x, rect->y, rect->getWidth(), rect->getHeight());
        paddedRect->setParent(sRect);
        isScrolling = false;
        vel.set(0);
        pos.set(0); 
        ppos.set(0); 
        acc.set(0);
        damping = .75;
        scrollX = false; 
        scrollY = true; 
        
        nearTop = false; 
        nearBot = false;        
        nearRight = false; 
        nearLeft = false;
        
        hitWidget = false; 
        stickyDistance = 32;
        hit = false; 
        snapping = true; 
#ifdef TARGET_OPENGLES
        touchId = -1; 
#endif
    }

    void setDamping(float _damping)
    {
        damping = _damping; 
    }
    
    void setSnapping(bool _snapping)
    {
        snapping = _snapping; 
    }
    
    void setScrollArea(float x, float y, float w, float h)
    {
        sRect->x = x; 
        sRect->y = y; 
        sRect->setWidth(w);
        sRect->setHeight(h);
        paddedRect->setWidth(w+padding*2);
        paddedRect->setHeight(h+padding*2);
    }
    
    void setScrollAreaToScreen()
    {
        sRect->x = 0; 
        sRect->y = 0; 
        sRect->setWidth(ofGetWidth());
        sRect->setHeight(ofGetHeight());
    }
    
    void setScrollAreaToScreenWidth()
    {
        sRect->x = 0; 
        sRect->setWidth(ofGetWidth());
    }

    void setScrollAreaToScreenHeight()
    {
        sRect->y = 0;
        sRect->setHeight(ofGetHeight());
    }
    
    void setScrollAreaHeight(float _height)
    {
        sRect->setHeight(_height);
        paddedRect->setHeight(_height+padding*2);
    }

    void setScrollAreaWidth(float _width)
    {
        sRect->setWidth(_width);
        paddedRect->setWidth(_width+padding*2);
    }
    
    void setScrollableDirections(bool _scrollX, bool _scrollY)
    {
        scrollX = _scrollX;
        scrollY = _scrollY;
    }
    
    void setStickDistance(float _stickyDistance)
    {
        stickyDistance = _stickyDistance; 
    }
    
    void dampenX()
    {
        if(nearRight || nearLeft)
        {
            acc.x -=vel.x*(.5);
        }
        else
        {
            acc.x -=vel.x*(1.0-damping);
        }        
    }
    
    void dampenY()
    {
        if(nearTop || nearBot)
        {
            acc.y -=vel.y*(.5);
        }
        else
        {
            acc.y -=vel.y*(1.0-damping);
        }
    }
    
    void update()
    {
        if(!isScrolling)
        {
            if(scrollX && snapping)
            {
                float dxLeft = rect->x - sRect->x; 
                float dxRight = (sRect->x+sRect->getWidth()) - (rect->x+rect->getWidth()); 
                
                if(fabs(dxLeft) < stickyDistance)
                {
                    nearLeft = true;                     
                }            
                else if(fabs(dxRight) < stickyDistance)
                {
                    nearRight = true; 
                }
                else
                {
                    nearLeft = false; 
                    nearRight = false;                     
                }
                
                if(dxLeft > 0)
                {
                    acc.x += (-dxLeft)/10.0;
                    dampenX();
                }
                else if(nearLeft)
                {
                    acc.x += (-dxLeft)/10.0;
                    dampenX();
                }                
                else if(dxRight > 0)
                {
                    acc.x += (dxRight)/10.0;
                    dampenX();
                }
                else if(nearRight)
                {
                    acc.x += (dxRight)/10.0;
                    dampenX(); 
                }                
            }
            
            if(scrollY && snapping)
            {
                float dyTop = rect->y - sRect->y; 
                float dyBot = (sRect->y+sRect->getHeight()) - (rect->y+rect->getHeight()); 
                if(fabs(dyBot) < stickyDistance)
                {
                    nearTop = false;
                    nearBot = true;
                }
                if(fabs(dyTop) < stickyDistance)
                {
                    nearTop = true;
                    nearBot = false;
                }
                   
                if(dyTop > 0)
                {
                    acc.y += (-dyTop)/10.0;
                    dampenY();
                }
                else if(nearTop)
                {
                    acc.y += (-dyTop)/10.0;
                    dampenY();
                }
                
                if(dyBot > 0)
                {
                    acc.y += (dyBot)/10.0;
                    dampenY();
                }
                else if(nearBot)
                {
                    acc.y += (dyBot)/10.0;
                    dampenY(); 
                }
                
                nearTop = false;
                nearBot = false;
            }
            
            acc.limit(50);
            vel +=acc;
            vel.limit(100);
            if(scrollX && fabs(vel.x) > 1.0) rect->x += floor(vel.x);
            if(scrollY && fabs(vel.y) > 1.0) rect->y += floor(vel.y);
            
            vel *=damping;    
            acc.set(0);
        }
        
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->update();
		}		
    }
    
    virtual void drawBack()
    {
        if(draw_back)
        {
            ofFill();
            ofSetColor(color_back);
            sRect->draw();            
        }
    }
    
    virtual void drawOutline()
    {
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline);
            sRect->draw();
        }
    }
    
    virtual void drawOutlineHighlight()
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight);
            sRect->draw();
        }
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
            ofFill();
            ofSetColor(color_fill);
            sRect->draw();
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill();
            ofSetColor(color_fill_highlight);
            sRect->draw();
        }
    }
    
    virtual void drawPadded()
    {
		if(draw_padded_rect && !embedded)
		{
            ofFill();
            ofSetColor(color_padded_rect);
			paddedRect->draw();
		}
    }
    
    virtual void drawPaddedOutline()
    {
        if(draw_padded_rect_outline && !embedded)
		{
            ofNoFill();
            ofSetColor(color_padded_rect_outline);
			paddedRect->draw();
		}
    }
    
    virtual void draw()
    {
        ofPushStyle();
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetLineWidth(1.0);
        
        drawPadded();
        
        drawPaddedOutline();
        
        drawBack();
        
        drawFill();
        
        drawFillHighlight();
        
        drawOutline();
        
        drawOutlineHighlight();
        
        for(vector<ofxUIWidget *>::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
        {
            if((*it)->isVisible() && (*it)->getRect()->rInside(*sRect))
            {
                (*it)->draw();
            }
		}
        
        ofPopStyle();
    }
    
    virtual void setPosition(int x, int y)
    {
        rect->x = x;
        rect->y = y;
        sRect->x = x;
        sRect->y = y; 
    }

    virtual void setDimensions(float _width, float _height)
    {
        sRect->setWidth(MIN(_width, ofGetWidth() - sRect->getX()));
        sRect->setHeight(MIN(_height, ofGetHeight() - sRect->getY()));
        rect->setWidth(_width);
        rect->setHeight(_height);
        paddedRect->width = rect->width+padding*2;
        paddedRect->height = rect->height+padding*2;
    }

    
    void drawScrollableRect()
    {
        sRect->draw();
    }
    	
#ifdef TARGET_OPENGLES
    void touchDown(ofTouchEventArgs& touch)
    {        
        if(sRect->inside(touch.x, touch.y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
                if((*it)->isHit(touch.x, touch.y))
                {            
                    if((*it)->isDraggable())
                    {
                        hitWidget = true;                                                                        
                    }
                    (*it)->touchDown(touch); 
                }
			}
		}        
        
        if(sRect->inside(touch.x, touch.y) && touch.id == 0)
        {
            hit = true; 
            isScrolling = false; 
            vel.set(0);             
        }
    }
    
    void touchMoved(ofTouchEventArgs& touch) 
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchMoved(touch);
        }
        
        if(hit && touch.id == 0)
        {
            if(!hitWidget)
            {
                if(isScrolling != true)
                {
                    isScrolling = true; 
                    ppos = ofPoint(touch.x,touch.y);
                    vel.set(0); 
                }
                else
                {
                    pos = ofPoint(touch.x, touch.y);             
                    vel = pos-ppos; 
                    if(scrollX) rect->x +=vel.x; 
                    if(scrollY) rect->y +=vel.y;             
                    ppos = pos; 
                }
            }
        }        
    }
    
    void touchUp(ofTouchEventArgs& touch) 
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchUp(touch); 
        }
        
        hit = false; 
        hitWidget = false; 
        if(isScrolling)
        {
            isScrolling = false; 
            pos = ofPoint(touch.x,touch.y);
        }        
    }
    
    void touchCancelled(ofTouchEventArgs& touch) 
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchUp(touch); 
        }
        
        hit = false; 
        hitWidget = false; 
        if(isScrolling)
        {
            isScrolling = false; 
            pos = ofPoint(touch.x,touch.y);
        }        
    } 
    
#endif

    void mouseDragged(int x, int y, int button) 
    {	
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->mouseDragged(x, y, button); 
        }
        
        if(hit)
        {
            if(!hitWidget)
            {
                if(isScrolling != true)
                {
                    isScrolling = true; 
                    ppos = ofPoint(x,y);
                    vel.set(0,0);
                }
                else
                {
                    pos = ofPoint(x, y);             
                    vel = pos-ppos; 
                    if(scrollX) rect->x +=vel.x; 
                    if(scrollY) rect->y +=vel.y;             
                    ppos = pos; 
                }
            }
        }
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(sRect->inside(x, y))
        {
            hit = true; 
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                if((*it)->isVisible())
                {
                    if((*it)->isHit(x, y))
                    {            
                        if((*it)->isDraggable())
                        {
                            hitWidget = true;                                                                        
                        }
                        (*it)->mousePressed(x, y, button); 
                    }
                }
            }       
        }		
        
        isScrolling = false; 
        vel.set(0,0);
    }
    
    void mouseReleased(int x, int y, int button) 
    {	
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible()) (*it)->mouseReleased(x, y, button); 
        }            
        
        hit = false; 
        hitWidget = false; 
        if(isScrolling)
        {
            isScrolling = false; 
            pos = ofPoint(x,y);
        }
    }	

    ofxUIRectangle *getSRect()
    {
        return sRect; 
    }

    
    virtual bool isHit(int x, int y)
    {
        if(isEnabled() && sRect->inside(x, y))
        {
            return true;
        }
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible() && (*it).second->isHit(x, y))
                {
                    return true;
                }
            }
        }
        return false;
    }

protected:
    ofxUIRectangle *sRect;
    bool isScrolling;
    bool snapping; 
    bool scrollX, scrollY; 
    bool nearTop, nearBot, nearRight, nearLeft;
    bool hitWidget; 
    ofPoint pos; 
    ofPoint ppos; 
    ofPoint vel; 
    ofPoint acc; 
    float damping;
    float stickyDistance;     
};
    
    
    
#endif
