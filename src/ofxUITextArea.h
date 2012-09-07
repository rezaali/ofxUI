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
    ofxUITextArea(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        init(_name, _textstring, w, h, x, y, _size);
    }
    
    void init(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        rect = new ofxUIRectangle(x,y,w,h);
		name = _name;
		kind = OFX_UI_WIDGET_TEXTAREA;
		textstring = _textstring;
        
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
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect;
        label->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline;
        label->setDrawPaddingOutline(false);
	}
    
    virtual void drawBack()
    {
        if(draw_back)
        {
            ofFill();
            ofSetColor(color_back);
            rect->draw();

            ofSetColor(color_fill);
            for(int i = 0; i < textLines.size(); i++)
            {
                label->drawString(rect->getX()+padding*2, rect->getY()+label->getStringHeight("|")*(i+1)+padding, textLines[i]);
            }

        }
    }
    
		
    void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(visible);
    }
    
    string getTextString()
	{
		return textstring;
	}
	
	
	void setTextString(string s)
	{
        textstring = s;
        formatTextString();
	}
    
    void formatTextString()
    {
        float rectWidthLimit = rect->getWidth()-padding*6;
        float rectHeightLimit = rect->getHeight()-label->getLineHeight()-padding;

        if(label->getStringWidth(textstring) <= rectWidthLimit)
        {
            return;
        }
        
        float tempWidth;
        float tempHeight;
        textLines.clear();
        string line = "";
        size_t i=0;
        
        bool overheight = false;
        
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
                        tempHeight = (textLines.size()+1)*label->getStringHeight("|");
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
        
        if(autoSize)
        {
            rect->setHeight(label->getStringHeight("|")*textLines.size()+padding*3);
        }
        
        if(overheight)
        {
            rect->setHeight(MAX(rect->getHeight(),label->getStringHeight("|")*textLines.size()+padding*3));
        }
    }

	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        formatTextString();
        label->setLabel(textstring);
        label->setVisible(false);
		paddedRect->height = rect->height+padding*2.0;				        
	}
	
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
	string textstring;
    vector<string> textLines;
    bool autoSize; 
};

#endif
