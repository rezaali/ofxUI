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

#ifndef OFXUI_IMAGE_SLIDER
#define OFXUI_IMAGE_SLIDER

#include "ofxUISlider.h"
#include "ofxUIRectangle.h"

class ofxUIImageSlider : public ofxUISlider         ///** I need to simplify this widget to only use one image as the handle of the slider
{
public:    
    ofxUIImageSlider(float x, float y, float w, float h, float _min, float _max, float _value, string _pathURL, string _name) : ofxUISlider()
    {
        useReference = false;
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _min, _max, &_value, _pathURL, _name);
    }
    
    ofxUIImageSlider(float w, float h, float _min, float _max, float _value, string _pathURL, string _name) : ofxUISlider()
    {
        useReference = false;
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _min, _max, &_value, _pathURL, _name);
    }    
    
    
    ofxUIImageSlider(float x, float y, float w, float h, float _min, float _max, float *_value, string _pathURL, string _name) : ofxUISlider()
    {
        useReference = true;
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _min, _max, _value, _pathURL, _name);
    }
    
    ofxUIImageSlider(float w, float h, float _min, float _max, float *_value, string _pathURL, string _name) : ofxUISlider()
    {
        useReference = true;
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _min, _max, _value, _pathURL, _name);
    }
    
    virtual void init(float w, float h, float _min, float _max, float *_value, string _pathURL, string _name) 
    {
        name = string(_name);  				
		if(w > h)
		{
			kind = OFX_UI_WIDGET_IMAGESLIDER_H;  			
		}
		else 
		{
			kind = OFX_UI_WIDGET_IMAGESLIDER_V;  			
		}
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        
        value = *_value;                                               //the widget's value
        if(useReference)
        {
            valueRef = _value;
        }
        else
        {
            valueRef = new float();
            *valueRef = value;
        }

		max = _max; 
		min = _min;
        labelPrecision = 2;
        
		if(value > max)
		{
			value = max; 
		}
		if(value < min)
		{
			value = min; 
		}
		
		value = ofMap(value, min, max, 0.0, 1.0, true); 
        
		if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(max,labelPrecision)), OFX_UI_FONT_SMALL); 
		}
		else 
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), name, OFX_UI_FONT_SMALL); 	
		}
        
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        increment = fabs(max - min) / 10.0;
        
        string coreURL = _pathURL;
        string extension = "";
        string period (".");
        size_t found;        
        
        found=_pathURL.find(period);
        if (found!=string::npos)        
        {
            coreURL = _pathURL.substr(0,found);
            extension = _pathURL.substr(found);
        }
        
        track = new ofImage();         //back
        track->loadImage(coreURL+"track"+extension);            
        
        trackleft = new ofImage();         //back
        trackleft->loadImage(coreURL+"trackleft"+extension);
        tlaspect = (float)trackleft->getWidth()/(float)trackleft->getHeight();
        
        trackright = new ofImage();         //back
        trackright->loadImage(coreURL+"trackright"+extension);
        traspect = (float)trackright->getWidth()/(float)trackright->getHeight();
        
        progress = new ofImage();      //fill
        progress->loadImage(coreURL+"progress"+extension);        

        progressright = new ofImage();      //fill
        progressright->loadImage(coreURL+"progressright"+extension);

        progressleft = new ofImage();      //fill
        progressleft->loadImage(coreURL+"progressleft"+extension);
        
        handle = new ofImage();        //handle
        handle->loadImage(coreURL+"handle"+extension);
                
        handleDown = new ofImage();    //handleOver State                        
        handleDown->loadImage(coreURL+"handledown"+extension);        
        
        handleHalfWidth = handle->getWidth()*.5;
        handleHalfHeight = handle->getHeight()*.5;
        
        if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
        {
            ratio = rect->getHeight() / (float) track->getHeight();
            imageRect = new ofxUIRectangle(handleHalfWidth*ratio,0,rect->getWidth()-handle->getWidth()*ratio, rect->getHeight());

        }
        else
        {
            ratio = rect->getWidth() /  (float) track->getWidth();
            imageRect = new ofxUIRectangle(0,handleHalfHeight*ratio,rect->getWidth(), rect->getHeight()-handle->getHeight()*ratio);
        }
        imageRect->setParent(rect);     
    }
    
    ~ofxUIImageSlider()
    {
        delete track;
        delete trackleft;
        delete trackright;
        delete progress;
        delete progressright;
        delete progressleft;
        delete handle; 
        delete handleDown;
        delete imageRect; 
    }
    
    
    virtual void drawBack() 
    {
        if(draw_back)
        {
            if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
            {
                ofSetColor(255);
                
                trackleft->draw(rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());                
                trackright->draw(rect->getX()+rect->getWidth()-traspect*rect->getHeight(), rect->getY(), traspect*rect->getHeight(), rect->getHeight());
                track->draw(rect->getX()+rect->getHeight()*tlaspect-1, rect->getY(), rect->getWidth()-rect->getHeight()*tlaspect - rect->getHeight()*traspect + 1, rect->getHeight());
            }
        }
    }
    
    virtual void drawOutline() 
    {
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            rect->draw(); 
        }
    }
    
    virtual void drawOutlineHighlight() 
    {
        
    }    
    
    virtual void drawFill() 
    {
        if(draw_fill)
        {			 
            ofSetColor(255); 
			if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
			{
                if(value > 0.00)
                    progressleft->draw(rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());

                progress->draw(rect->getX()+rect->getHeight()*tlaspect - 1,rect->getY(),(rect->getWidth() - 2.0*rect->getHeight()*tlaspect)*value + 1, rect->getHeight());

                if(value > .99)
                    progressright->draw(rect->getX()+rect->getWidth() - tlaspect*rect->getHeight(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());

                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(255); 
                handle->draw(imageRect->getX()+value*imageRect->getWidth(), rect->getY()+rect->getHalfHeight(), ratio*handle->getWidth(), ratio*handle->getHeight());
                ofSetRectMode(OF_RECTMODE_CORNER);
			}
        }
    }
    
    virtual void drawFillHighlight() 
    {
        if(draw_fill_highlight)
        {
            ofSetColor(255); 
			if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
			{
                if(value > 0.00)
                progressleft->draw(rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
                
                progress->draw(rect->getX()+rect->getHeight()*tlaspect-1,rect->getY(),(rect->getWidth() - 2.0*rect->getHeight()*tlaspect)*value + 1, rect->getHeight());
                
                if(value > .99)
                    progressright->draw(rect->getX()+rect->getWidth() - tlaspect*rect->getHeight(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
                
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(255);
                handleDown->draw(imageRect->getX()+value*imageRect->getWidth(), rect->getY()+rect->getHalfHeight(), ratio*handle->getWidth(), ratio*handle->getHeight());
                ofSetRectMode(OF_RECTMODE_CORNER);
			}
			else 
			{
             
			
            }
			if(kind == OFX_UI_WIDGET_IMAGESLIDER_V)
			{
				label->drawString(imageRect->getX()+imageRect->getWidth()+padding, label->getRect()->getHeight()/2.0+imageRect->getY()+imageRect->getHeight()-imageRect->getHeight()*value, ofToString(getScaledValue(),labelPrecision)); 
			}
        }        
    }
    
    virtual void stateChange()
    {                
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_back = true; 
                draw_fill = true; 
                draw_fill_highlight = false;             
                draw_outline_highlight = false;             
				label->unfocus(); 				
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_back = true;       
                draw_fill = true;                
                draw_fill_highlight = false;            
                draw_outline_highlight = false;    
				label->unfocus(); 
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_back = true;   
                draw_fill = false;                
                draw_fill_highlight = true;            
                draw_outline_highlight = false;             
				label->focus(); 				
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;
				label->unfocus(); 				
            }
                break;            
                
            default:
                break;
        }        
    }

    virtual void input(float x, float y)
	{
		if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
		{
			value = imageRect->percentInside(x, y).x;             
		}
		else 
		{
			value = 1.0-imageRect->percentInside(x, y).y; 
		}	
        
        if(value > 1.0)
        {
            value = 1.0;
        }
        else if(value < 0.0)
        {
            value = 0.0;
        }                      
		updateLabel(); 
	}
    
	virtual void updateLabel()
	{
		if(kind == OFX_UI_WIDGET_IMAGESLIDER_H)
		{
			label->setLabel(name + ": " + ofToString(getScaledValue(),labelPrecision)); 		
		}		
	}
    
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *track;         //back
    
    ofImage *trackleft;         //back
    float tlaspect;
    ofImage *trackright;         //back
    float traspect;
    
    float ratio; 
    
    ofImage *progress;      //fill
    ofImage *progressright;      //fill
    ofImage *progressleft;      //fill
    ofImage *handle;        //handle
    ofImage *handleDown;    //handleOver State    
    int handleHalfWidth; 
    int handleHalfHeight; 
    ofxUIRectangle *imageRect;
    
    
}; 

#endif
