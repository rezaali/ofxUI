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
        isScrolling = false; 
        vel.set(0); 
        pos.set(0); 
        ppos.set(0); 
        acc.set(0); 
        damping = .90; 
        scrollX = false; 
        scrollY = true; 
        
        nearTop = false; 
        nearBot = false;        
        nearRight = false; 
        nearLeft = false;
        
        hitWidget = false; 
        stickyDistance = 100;  
        hit = false; 
        snapping = true; 
#ifdef TARGET_OPENGLES
        touchId = -1; 
#endif
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
    
    void setScrollableDirections(bool _scrollX, bool _scrollY)
    {
        scrollX = _scrollX;
        scrollY = _scrollY;
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
                    acc.x -=vel.x*(1.0-damping); 
                }
                else if(nearLeft)
                {
                    acc.x += (-dxLeft)/10.0;
                    acc.x -=vel.x*(1.0-damping); 
                }                
                else if(dxRight > 0)
                {
                    acc.x += (dxRight)/10.0;
                    acc.x -=vel.x*(1.0-damping); 	
                }
                else if(nearRight)
                {
                    acc.x += (dxRight)/10.0;
                    acc.x -=vel.x*(1.0-damping); 	
                }                
            }
            
            if(scrollY && snapping)
            {
                float dyTop = rect->y - sRect->y; 
                float dyBot = (sRect->y+sRect->getHeight()) - (rect->y+rect->getHeight()); 
                if(fabs(dyTop) < stickyDistance)
                {
                    nearTop = true;                     
                }            
                else if(fabs(dyBot) < stickyDistance)
                {
                    nearBot = true; 
                }
                else
                {
                    nearTop = false; 
                    nearBot = false;                     
                }
                   
                if(dyTop > 0)
                {
                    acc.y += (-dyTop)/10.0;
                    acc.y -=vel.y*(1.0-damping); 
                }
                else if(nearTop)
                {
                    acc.y += (-dyTop)/10.0;
                    acc.y -=vel.y*(1.0-damping);                     
                }
                else if(dyBot > 0)
                {
                    acc.y += (dyBot)/10.0;
                    acc.y -=vel.y*(1.0-damping); 	
                }                                     
                else if(nearBot)
                {
                    acc.y += (dyBot)/10.0;
                    acc.y -=vel.y*(1.0-damping); 	
                }
            }
            
            acc.limit(10);
            vel +=acc; 
            vel.limit(50);
            if(scrollX) rect->x +=vel.x; 
            if(scrollY) rect->y +=vel.y;             
            
            vel *=damping;    
            acc.set(0); 
        }
        
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->update();
		}		
    }
    
    void drawScrollableRect()
    {
        sRect->draw(); 
    }
    	
#ifdef TARGET_OPENGLES
    void touchDown(ofTouchEventArgs& touch)
    {        
        if(rect->inside(touch.x, touch.y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
                if(widgets[i]->isHit(touch.x, touch.y))
                {            
                    if(widgets[i]->isDraggable())
                    {
                        hitWidget = true;                                                                        
                    }
                    widgets[i]->touchDown(touch); 
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
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchMoved(touch);
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
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchUp(touch); 
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
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchUp(touch); 
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
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->mouseDragged(x, y, button); 
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
        if(rect->inside(x, y))
        {
            hit = true; 
            for(int i = 0; i < widgets.size(); i++)
            {
                if(widgets[i]->isVisible())
                {
                    if(widgets[i]->isHit(x, y))
                    {            
                        if(widgets[i]->isDraggable())
                        {
                            hitWidget = true;                                                                        
                        }
                        widgets[i]->mousePressed(x, y, button); 
                    }
                }
            }       
        }		
        
        isScrolling = false; 
        vel.set(0,0);
    }
    
    void mouseReleased(int x, int y, int button) 
    {	
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible()) widgets[i]->mouseReleased(x, y, button); 
        }            
        
        hit = false; 
        hitWidget = false; 
        if(isScrolling)
        {
            isScrolling = false; 
            pos = ofPoint(x,y);
        }
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
