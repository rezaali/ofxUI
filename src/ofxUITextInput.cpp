
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

#include "ofxUITextInput.h"
#include "ofxUI.h"

ofxUITextInput::ofxUITextInput(string _name, string _textstring, float w, float h, float x, float y, int _size) : ofxUIWidgetWithLabel()
{
    init(_name, _textstring, w, h, x, y, _size);
}

void ofxUITextInput::init(string _name, string _textstring, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_TEXTINPUT;
    textstring = string(_textstring);
    defaultstring = string(_textstring);
    displaystring = string(_textstring);
    
    clicked = false;                                            //the widget's value
    autoclear = true;
    triggerOnClick = true;
    label = new ofxUILabel((name+" LABEL"), _size);
    addEmbeddedWidget(label);
    
    inputTriggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
    cursorWidth = 0; spaceOffset = 0;
    theta = 0;
    autoUnfocus = true;
    cursorPosition = 0;
    firstVisibleCharacterIndex = 0;
}

void ofxUITextInput::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUITextInput::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUITextInput::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        rect->draw();
    }
    if(clicked)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
        
        float h = label->getRect()->getHeight();
        
        float ph = rect->getHeight();
        label->getRect()->setY(ph/2.0 - h/2.0);
        
        ofxUIFill();
        ofxUISetColor(label->getColorFillHighlight(), 255.0*fabs(cos(theta)));
        theta +=0.05;
        
        int displayCursorPosition = cursorPosition - firstVisibleCharacterIndex;
        string displayStringBeforeCursor = displaystring.substr(0, displayCursorPosition);
        spaceOffset = label->getStringWidth(displayStringBeforeCursor);
        
        float x = label->getRect()->getX()+spaceOffset;
        float y = label->getRect()->getY()-padding;
        float t = label->getRect()->getHeight()+padding*2.0;
        ofxUIDrawRect(x, y, cursorWidth, t);
    }
    
    if(textstring.size() == 0 && !clicked)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        label->drawString(rect->getX()+defaultX, rect->getY()+defaultY, defaultstring);
    }
}

void ofxUITextInput::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUITextInput::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUITextInput::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        if(state == OFX_UI_STATE_OVER)
        {
            clicked = true;
            theta = 0;
            hit = true;
        }
#ifdef OFX_UI_TARGET_TOUCH
        clicked = true;
        theta = 0;
        hit = true;
#endif
        cursorPosition = label->getLabel().length();
        
        state = OFX_UI_STATE_DOWN;
        inputTriggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
        
        if(triggerOnClick)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
        if(clicked)
        {
            unClick();
        }
    }
    stateChange();
}

void ofxUITextInput::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        //			inputTriggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS;
        //			triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    hit = false;
    stateChange();
}

void ofxUITextInput::keyPressed(int key)
{
    if(clicked)
    {
        switch (key)
        {
            case OF_KEY_BACKSPACE:
                if (textstring.size() > 0 && cursorPosition > 0)
                {
                    cursorPosition--;
                    textstring.erase(cursorPosition, 1);
                    
                    // when we're deleting the first visible character, shift the string to the right
                    if(firstVisibleCharacterIndex == cursorPosition)
                        firstVisibleCharacterIndex = 0;
                    recalculateDisplayString();
                }
                break;
                
            case OF_KEY_DEL:
                if (textstring.size() > 0 && cursorPosition < textstring.length())
                {
                    textstring.erase(cursorPosition, 1);
                    recalculateDisplayString();
                }
                break;
                
            case OF_KEY_RETURN:
                
                inputTriggerType = OFX_UI_TEXTINPUT_ON_ENTER;
                if(autoUnfocus)
                {
                    clicked = false;
                }

                triggerEvent(this);
                if(autoclear)
                {
                    cursorPosition = 0;
                    textstring.clear();
                    recalculateDisplayString();
                }
                break;
                
            case OF_KEY_RIGHT:
            case OF_KEY_DOWN:
                if(cursorPosition < textstring.length())
                {
                    cursorPosition++;
                    recalculateDisplayString();
                }
                break;
                
            case OF_KEY_LEFT:
            case OF_KEY_UP:
                if(cursorPosition > 0)
                {
                    cursorPosition--;
                    recalculateDisplayString();
                }
                break;
                
#if (OF_VERSION_MINOR > 7)
            case OF_KEY_TAB:
            case OF_KEY_COMMAND:
            case OF_KEY_CONTROL:
            case OF_KEY_LEFT_SHIFT:
            case OF_KEY_RIGHT_SHIFT:
            case OF_KEY_LEFT_CONTROL:
            case OF_KEY_RIGHT_CONTROL:
            case OF_KEY_LEFT_ALT:
            case OF_KEY_RIGHT_ALT:
            case OF_KEY_LEFT_SUPER:
            case OF_KEY_RIGHT_SUPER:
#endif
            case OF_KEY_F1:
            case OF_KEY_F2:
            case OF_KEY_F3:
            case OF_KEY_F4:
            case OF_KEY_F5:
            case OF_KEY_F6:
            case OF_KEY_F7:
            case OF_KEY_F8:
            case OF_KEY_F9:
            case OF_KEY_F10:
            case OF_KEY_F11:
            case OF_KEY_F12:
            case OF_KEY_PAGE_UP:
            case OF_KEY_PAGE_DOWN:
            case OF_KEY_HOME:
            case OF_KEY_END:
            case OF_KEY_INSERT:
            case OF_KEY_ALT:
            case OF_KEY_SHIFT:
                break;
                
            default:
            {
                textstring.insert(cursorPosition, 1, key);
                cursorPosition++;
                recalculateDisplayString();
            }
                break;
        }
    }
}

void ofxUITextInput::unClick()
{
    if(clicked)
    {
        clicked = false;
        inputTriggerType = OFX_UI_TEXTINPUT_ON_UNFOCUS;
        triggerEvent(this);
    }
}
void ofxUITextInput::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
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

bool ofxUITextInput::isClicked()
{
    return clicked;
}

string ofxUITextInput::getTextString()
{
    return textstring;
}

void ofxUITextInput::setInputTriggerType(int _triggerType)
{
    inputTriggerType = _triggerType;
}

int ofxUITextInput::getInputTriggerType()
{
    return inputTriggerType;
}

void ofxUITextInput::setTextString(string s)
{
    textstring = "";
    string temp = "";
    
    int length = s.length();
    
    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
            temp+=s.at(i);
            float newWidth = label->getStringWidth(temp);
            
            if(newWidth < rect->getWidth()-padding*2.0)
            {
                textstring+=s.at(i);
                label->setLabel(textstring);
            }
        }
    }
    else
    {
        textstring = s;
        label->setLabel(textstring);
    }
    displaystring = textstring;
}

void ofxUITextInput::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    if(rect->getHeight() == 0 || rect->getHeight() < label->getPaddingRect()->getHeight()+padding*2.0)
    {
        rect->setHeight(label->getPaddingRect()->getHeight()+padding*2.0);
    }
    label->setLabel(textstring);
    ofxUIRectangle *labelrect = label->getRect();
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    
    labelrect->setY(ph/2.0 - h/2.0);
    labelrect->setX(padding*2.0);
    defaultY = labelrect->getY(false)+labelrect->getHeight();
    defaultX = labelrect->getX(false);
    
    cursorWidth = label->getStringWidth(".");
    while(label->getStringWidth(textstring) > rect->getWidth()-padding*2.0)
    {
        string::iterator it;
        it=textstring.begin();
        textstring.erase (it);
    }
    
    defaultstring = textstring;
    displaystring = textstring;
    setTextString(textstring);
    calculatePaddingRect();
}

void ofxUITextInput::setAutoClear(bool _autoclear)
{
    autoclear = _autoclear;
}

void ofxUITextInput::setFocus(bool _focus)
{
    if(_focus)
    {
        cursorPosition = 0;
        state = OFX_UI_STATE_DOWN;
        inputTriggerType = OFX_UI_TEXTINPUT_ON_FOCUS;
        clicked = true;
        stateChange();
        triggerEvent(this);
    }
    else
    {
        cursorPosition = textstring.length();
        stateChange();
        unClick();
    }
}

bool ofxUITextInput::isFocused()
{
    return isClicked();
}

void ofxUITextInput::setAutoUnfocus(bool _autoUnfocus)
{
    autoUnfocus = _autoUnfocus;
}

void ofxUITextInput::setTriggerOnClick(bool _triggerOnClick)
{
    triggerOnClick = _triggerOnClick;
}

void ofxUITextInput::recalculateDisplayString()
{
    // the maximum width of the displaystring
    float maxWidth = rect->getWidth()-padding*2.0;
    
    displaystring = textstring;
    string stringBeforeCursor = displaystring.substr(0, cursorPosition);
    string stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    
    // if the cursoroffset - length of the (invisible) string before the label < 0, we have to shift our string to the left to get our cursor in the label
    while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) < 0){
        firstVisibleCharacterIndex --;
        stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    }
    
    // if the cursoroffset - length of the (invisible) string before the label is > maximum width, we have to shift to the right
    while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) > maxWidth){
        firstVisibleCharacterIndex ++;
        stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    }
    
    // we now know how long the string before the label should be, so trim it off
    displaystring = displaystring.substr(MIN(firstVisibleCharacterIndex, displaystring.length()));
    
    // trim off the end of the string until it fits
    while(label->getStringWidth(displaystring) > maxWidth && displaystring.length() > 0)
    {
        displaystring = displaystring.substr(0, displaystring.size()-1);
    }
    
    label->setLabel(displaystring);
}

#ifndef OFX_UI_NO_XML

void ofxUITextInput::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getTextString(), 0);    
}

void ofxUITextInput::loadState(ofxXmlSettings *XML)
{
    setTextString(XML->getValue("Value", getTextString(), 0));
    setInputTriggerType(OFX_UI_TEXTINPUT_ON_LOAD);
}

#endif