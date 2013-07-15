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

#ifndef OFXUI_TEXT_AREA
#define OFXUI_TEXT_AREA

#include "ofxUIWidgetWithLabel.h"

class ofxUITextArea : public ofxUIWidgetWithLabel
{
public:
    ofxUITextArea(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM) : ofxUIWidgetWithLabel()
    {
        init(_name, _textstring, w, h, x, y, _size);
    }
    
    void init(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        rect = new ofxUIRectangle(x,y,w,h);
		name = string(_name); 
		kind = OFX_UI_WIDGET_TEXTAREA;
		textstring = _textstring;        
        setDrawFill(true);
        setDrawBack(false);
        drawShadow = false; 
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, padding*2.0);
		paddedRect->setParent(rect);
        		
		label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), _size);
		label->setParent(label);
		label->setRectParent(rect);
        label->setEmbedded(true);
        
        if(h == 0)
        {
            autoSize = true;
        }
        else
        {
            autoSize = false;
        }
    }
    
    virtual void drawBack()
    {
        if(draw_back)
        {
            ofFill();
            ofSetColor(color_back);
            rect->draw();
        }
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
            if(drawShadow)
            {
                ofSetColor(color_back);
                for(unsigned int i = 0; i < textLines.size(); i++)
                {
                    label->drawStringShadow(rect->getX(), rect->getY()+(lineHeight+lineSpaceSize)*(i+1)-lineSpaceSize, textLines[i]);
                }
            }
            
            ofSetColor(color_fill);
            for(unsigned int i = 0; i < textLines.size(); i++)
            {
                label->drawString(rect->getX(), rect->getY()+(lineHeight+lineSpaceSize)*(i+1)-lineSpaceSize, textLines[i]);
            }
        }
    }
		
    void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(false);
    }
    
    string getTextString()
	{
		return textstring;
	}
	
	
	void setTextString(string s)
	{
        textLines.clear();        
        textstring = s;
        formatTextString();
	}
    
    void formatTextString()
    {
        float rectWidthLimit = rect->getWidth()-padding*6;
        float rectHeightLimit = rect->getHeight()-label->getLineHeight()-padding;
        bool overheight = false;
        
        lineHeight = label->getStringHeight("1");
        lineSpaceSize = padding*2;
        
        offsetY = floor(padding*.125);
        
        if(label->getStringWidth(textstring) <= rectWidthLimit)
        {
            if(textstring.size() > 0)
            {
                textLines.push_back(textstring);
            }
        }
        else
        {        
            float tempWidth;
            float tempHeight;
            textLines.clear();
            string line = "";
            size_t i=0;                    
            
            while (i < textstring.size() && !overheight) //if not at the end of the string && not over the rect's height
            {
                tempWidth = label->getStringWidth(line);
                if(tempWidth < rectWidthLimit)
                {
                    line+=textstring.at(i);
                    i++;
                    if(i == textstring.size())
                    {
                        textLines.push_back(line);
                    }
                }
                else
                {
                    bool notFound = true;
                    
                    while (notFound && !overheight)
                    {
                        if(strncmp(&textstring.at(i), " ",1) == 0)
                        {
                            tempHeight = (textLines.size()+1)*(lineHeight+lineSpaceSize);
    //                        cout << tempHeight << endl;
    //                        cout << rectHeightLimit << endl;
                            if(!autoSize && tempHeight >= rectHeightLimit)
                            {
                                textLines.push_back(line);
                                textLines[textLines.size()-1]+="...";
                                overheight = true;
                            }
                            notFound = false; 
                            if(!overheight)
                            {
                                textLines.push_back(line);
                                line.clear();
                                i++; 
                            }
                        }
                        else 
                        {
                            i--; 											
                            line.erase(line.end()-1); 
                        }					
                    }
                }		
            }
        }
        
        if(autoSize)
        {
            rect->setHeight((lineHeight+lineSpaceSize)*textLines.size()-lineSpaceSize);
        }
        
        if(overheight)
        {
            rect->setHeight(MAX(rect->getHeight(),(lineHeight+lineSpaceSize)*textLines.size()-lineSpaceSize));
        }
    }

	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        formatTextString();
        label->setVisible(false);
		paddedRect->height = rect->height+padding*2.0;
	}
    
    void setDrawShadow(bool _drawShadow)
    {
        drawShadow = _drawShadow;
    }
	
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
	string textstring;
    vector<string> textLines;
    bool autoSize;
    bool drawShadow; 
    int lineSpaceSize;
    int lineHeight; 
    int offsetY; 
};

#endif
